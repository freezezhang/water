#include "epoll.h"

#include <assert.h>
#include <unistd.h>

#include "net/handler.h"

namespace Water {

EPoll::EPoll() throw (BadEPoll)
    : return_event_list_(kDefaultEventListSize),
      is_run_(false) {
  epoll_fd_ = epoll_create1(EPOLL_CLOEXEC);
  if (epoll_fd_ < 0) {
    throw BadEPoll("create_epoll() error!");
  }
}

EPoll::~EPoll() {
  for (HandlerMap::iterator iter = register_map_.begin();
      iter != register_map_.end(); ++iter) {
    delete iter->second;
  }
  close(epoll_fd_);
}

int EPoll::RegisterHandler(Handler* handler,
                           const EventSet& event_set,
                           int priority) {
  assert(handler);
  handler->SetPriority(priority);
  int fd = handler->fd();
  assert(fd >= 0);
  handler->set_concern_event_set(event_set);
  if (register_map_.find(fd) == register_map_.end()) {
    int result = EPollControl(EPOLL_CTL_ADD, handler);
    if (result == 0) register_map_.insert(std::make_pair(fd, handler));
    return result;
  } else {
    return EPollControl(EPOLL_CTL_MOD, handler);
  }
}

int EPoll::RemoveHandler(Handler* handler) {
  assert(handler);
  int fd = handler->fd();
  assert(fd >= 0);
  assert(register_map_.find(fd) != register_map_.end());
  register_map_.erase(fd);
  timer_queue_.Remove(handler);
  return EPollControl(EPOLL_CTL_DEL, handler);
}

TimerID EPoll::ScheduleTimer(Handler* handler,
                             const TimeValue& delay,
                             const TimeValue& repeat) {
  assert(handler);
  assert(delay >= TimeValue::zero);
  assert(repeat >= TimeValue::zero);
  handler->AddConcernEvent(kEventTimeout);
  TimerEvent* timer_event = new (std::nothrow) TimerEvent(handler,
                                                          TimeValue::Now() + delay,
                                                          repeat);
  assert(timer_event);
  return timer_queue_.Push(timer_event);
}

int EPoll::CancelTimer(Handler* handler) {
  assert(handler);
  return timer_queue_.Remove(handler);
}

int EPoll::CancelTimer(TimerID timer_id) {
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

u_int32 EPoll::EventSetToEPollEvents(const EventSet& event_set) const {
  u_int32 events = event_set.GetEventSet();
  u_int32 epoll_events = 0;
  //epoll_events |= EPOLLET;
  if (events & kEventInput) epoll_events |= EPOLLIN;
  if (events & kEventOutput) epoll_events |= EPOLLOUT;
  if (events & kEventException) epoll_events |= EPOLLPRI;
  return epoll_events;
}

EventSet EPoll::EPollEventsToEventSet(u_int32 epoll_events) const {
  EventSet event_set;
  if (epoll_events & EPOLLIN) event_set.AddEvent(kEventInput);
  if (epoll_events & EPOLLOUT) event_set.AddEvent(kEventOutput);
  if (epoll_events & EPOLLPRI) event_set.AddEvent(kEventException);
  return event_set;
}

int EPoll::HandleEvents(const TimeValue& timeout, TimeValue& expiration) {
  int timeout_ms = -1;
  if (timeout != TimeValue::null) {
    timeout_ms = static_cast<int>(timeout.Millisecond());
    if (timeout_ms <= 0) timeout_ms = 0;
    time_t max_timeout = kEventMaxTimeout.Millisecond();
    if (timeout_ms > max_timeout) timeout_ms = max_timeout;
  }

  int actived_number = epoll_wait(epoll_fd_,
                                  &return_event_list_[0],
                                  static_cast<int>(return_event_list_.size()),
                                  timeout_ms);
  expiration = TimeValue::Now();

  for (int i = 0; i < actived_number; ++i) {
    Handler* handler = static_cast<Handler*>(return_event_list_[i].data.ptr);
    assert(handler);
    assert(register_map_.find(handler->fd()) != register_map_.end());
    const EventSet& event_set = EPollEventsToEventSet(return_event_list_[i]
        .events);
    handler->set_actived_event_set(event_set);
    activated_list_.push_back(handler);
  }

  int list_size = return_event_list_.size();
  if (actived_number == list_size) {
    return_event_list_.resize(list_size * 2);
  }

  return actived_number;
}

int EPoll::EventLoop() {
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

int EPoll::StartEventLoop() {
  is_run_ = true;
  return EventLoop();
}

int EPoll::EndEventLoop() {
  is_run_ = false;
  return 0;
}

int EPoll::EPollControl(int operation, Handler* handler) const {
  assert(operation == EPOLL_CTL_ADD || operation == EPOLL_CTL_MOD || operation == EPOLL_CTL_DEL);
  assert(handler);
  struct epoll_event event;
  bzero(&event, sizeof(event));
  event.events = EventSetToEPollEvents(handler->concern_event_set());
  event.data.ptr = handler;
  return epoll_ctl(epoll_fd_, operation, handler->fd(), &event);
}

int EPoll::CleanPastTimeoutEvents(const TimeValue& expiration) {
  int pop_number = 0;
  while (!timer_queue_.Empty()) {
    TimerEvent* top = timer_queue_.Top();
    assert(top);
    Handler* handler = top->GetHandler();
    assert(handler);

    if (top->GetActivedTime() < expiration) {
      if (top->GetRepeat() != TimeValue::zero) {
        TimerEvent* repeat_timer =
            new (std::nothrow) TimerEvent(handler,
                                          expiration + top->GetRepeat(),
                                          top->GetRepeat());
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

int EPoll::IssueEventHandle() {
  for (HandlerList::iterator iter = activated_list_.begin();
      iter != activated_list_.end(); ++iter) {
    Handler* handler = *iter;
    assert(handler);
    int fd = handler->fd();
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
