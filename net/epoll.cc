#include "epoll.h"

#include <assert.h>
#include <unistd.h>

#include "net/handler.h"
#include "net/net_error.h"

namespace Water {

EPoll::EPoll() : return_event_list_(kDefaultEventListSize), is_run_(false) {
}

EPoll::~EPoll() {
  for (HandlerMap::iterator iter = register_map_.begin();
      iter != register_map_.end(); ++iter) {
    delete iter->second;
  }
  close(epoll_fd_);
}

Int32 EPoll::Init() {
  epoll_fd_ = epoll_create1(EPOLL_CLOEXEC);
  if (epoll_fd_ <= 0) {
    return  kNetErrorEpollCreate;
  }
  return 0;
}

Int32 EPoll::RegisterHandler(Handler* handler,
                           const EventSet& event_set,
                           Int32 priority) {
  assert(handler);
  handler->SetPriority(priority);
  Int32 fd = handler->fd();
  assert(fd >= 0);
  handler->set_concern_event_set(event_set);
  if (register_map_.find(fd) == register_map_.end()) {
    Int32 ret = EPollControl(EPOLL_CTL_ADD, handler);
    if (ret == 0) 
      register_map_.insert(std::make_pair(fd, handler));
    return ret;
  } else {
    return EPollControl(EPOLL_CTL_MOD, handler);
  }
}

Int32 EPoll::RemoveHandler(Handler* handler) {
  assert(handler);
  Int32 fd = handler->fd();
  assert(fd >= 0);
  assert(register_map_.find(fd) != register_map_.end());
  register_map_.erase(fd);
  timer_queue_.Remove(handler);
  return EPollControl(EPOLL_CTL_DEL, handler);
}

TimerType EPoll::ScheduleTimer(Handler *handler, const TimeValue &delay,
                               const TimeValue &repeat) {
  assert(handler);
  assert(delay >= TimeValue::zero);
  assert(repeat >= TimeValue::zero);
  handler->AddConcernEvent(kEventTimeout);
  TimerEvent *timer_event =
      new (std::nothrow) TimerEvent(handler, TimeValue::Now() + delay, repeat);
  if (timer_event != nullptr)
    return timer_queue_.Push(timer_event);
  return 0;
}

Int32 EPoll::CancelTimer(Handler* handler) {
  assert(handler);
  return timer_queue_.Remove(handler);
}

Int32 EPoll::CancelTimer(TimerType timer_id) {
  assert(timer_id > 0);
  return timer_queue_.Remove(timer_id);
}

void EPoll::SuspendHandler(Handler* handler) {
  assert(handler);
  assert(register_map_.find(handler->fd()) != register_map_.end());
  handler->Suspend();
}

void EPoll::ResumeHandler(Handler* handler) {
  assert(handler);
  assert(register_map_.find(handler->fd()) != register_map_.end());
  handler->Resume();
}

Uint32 EPoll::EventSetToEPollEvents(const EventSet& event_set) const {
  Uint32 events = event_set.GetEventSet();
  Uint32 epoll_events = 0;
  //epoll_events |= EPOLLET;
  if (events & kEventInput) epoll_events |= EPOLLIN;
  if (events & kEventOutput) epoll_events |= EPOLLOUT;
  if (events & kEventException) epoll_events |= EPOLLPRI;
  return epoll_events;
}

EventSet EPoll::EPollEventsToEventSet(Uint32 epoll_events) const {
  EventSet event_set;
  if (epoll_events & EPOLLIN) event_set.AddEvent(kEventInput);
  if (epoll_events & EPOLLOUT) event_set.AddEvent(kEventOutput);
  if (epoll_events & EPOLLPRI) event_set.AddEvent(kEventException);
  return event_set;
}

Int32 EPoll::HandleEvents(const TimeValue& timeout, TimeValue& expiration) {
  Int32 timeout_ms = -1;
  if (timeout != TimeValue::null) {
    timeout_ms = static_cast<Int32>(timeout.Millisecond());
    if (timeout_ms <= 0) timeout_ms = 0;
    time_t max_timeout = kEventMaxTimeout.Millisecond();
    if (timeout_ms > max_timeout) timeout_ms = max_timeout;
  }

  Int32 actived_number = epoll_wait(epoll_fd_,
                                  &return_event_list_[0],
                                  static_cast<Int32>(return_event_list_.size()),
                                  timeout_ms);
  expiration = TimeValue::Now();

  for (Int32 i = 0; i < actived_number; ++i) {
    Handler* handler = static_cast<Handler*>(return_event_list_[i].data.ptr);
    assert(handler);
    assert(register_map_.find(handler->fd()) != register_map_.end());
    const EventSet& event_set = EPollEventsToEventSet(return_event_list_[i]
        .events);
    handler->set_actived_event_set(event_set);
    activated_list_.push_back(handler);
  }

  Int32 list_size = return_event_list_.size();
  if (actived_number == list_size) {
    return_event_list_.resize(list_size * 2);
  }

  return actived_number;
}

Int32 EPoll::EventLoop() {
  while (is_run_) {
    TimeValue timeout = TimeValue::null;
    if (!timer_queue_.Empty()) {
      TimerEvent* top = timer_queue_.Top();
      assert(top);
      timeout = top->GetActivedTime() - TimeValue::Now();
    }

    TimeValue expiration;
    if (HandleEvents(timeout, expiration) == -1) return -1;

    CleanPastTimeoutEvents(expiration);

    IssueEventHandle();
  }
  return 0;
}

Int32 EPoll::StartEventLoop() {
  is_run_ = true;
  return EventLoop();
}

Int32 EPoll::EndEventLoop() {
  is_run_ = false;
  return 0;
}

Int32 EPoll::EPollControl(int operation, Handler* handler) const {
  assert(operation == EPOLL_CTL_ADD || operation == EPOLL_CTL_MOD || operation == EPOLL_CTL_DEL);
  assert(handler);
  struct epoll_event event;
  bzero(&event, sizeof(event));
  event.events = EventSetToEPollEvents(handler->concern_event_set());
  event.data.ptr = handler;
  return epoll_ctl(epoll_fd_, operation, handler->fd(), &event);
}

Int32 EPoll::CleanPastTimeoutEvents(const TimeValue& expiration) {
  Int32 pop_number = 0;
  while (!timer_queue_.Empty()) {
    TimerEvent* top = timer_queue_.Top();
    assert(top);
    Handler* handler = top->GetHandler();
    assert(handler);

    if (top->GetActivedTime() < expiration) {
      if (top->GetRepeat() != TimeValue::zero) {
        TimerEvent *repeat_timer = new (std::nothrow) TimerEvent(
            handler, expiration + top->GetRepeat(), top->GetRepeat());
        assert(repeat_timer);
        timer_queue_.Push(repeat_timer);
      }

      handler->AddActivedEvent(kEventTimeout);
      activated_list_.push_back(handler);
      timer_queue_.Pop();
      pop_number++;
    } else {
      break;
    }
  }
  return pop_number;
}

Int32 EPoll::IssueEventHandle() {
  for (HandlerList::iterator iter = activated_list_.begin();
      iter != activated_list_.end(); ++iter) {
    Handler* handler = *iter;
    assert(handler);
    Int32 fd = handler->fd();
    assert(fd >= 0);
    if (handler->GetPauseState()) continue;
    const EventSet& event_set = handler->actived_event_set();
    if (event_set.InEventSet(kEventInput)) {
      if (handler->HandleInput(fd) == -1) {
        handler->HandleClose();
      }
    }
    if (event_set.InEventSet(kEventOutput)) {
      if (handler->HandleOutput(fd) == -1) {
        handler->HandleClose();
      }
    }
    if (event_set.InEventSet(kEventTimeout)) {
      if (handler->HandleTimeout() == -1) {
        handler->HandleClose();
      }
    }
    if (event_set.InEventSet(kEventException)) {
      if (handler->HandleException() == -1) {
        handler->HandleClose();
      }
    }
    handler->ClearAllActivedEventSet();
  }
  activated_list_.clear();
  return 0;
}

} // namespace Water
