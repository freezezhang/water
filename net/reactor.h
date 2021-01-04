/*
 * reactor.h
 *
 * Created on: 2011-5-23
 * Author: freezezhang
 */

#ifndef NET_REACTOR_H_
#define NET_REACTOR_H_

#include <assert.h>

#include "net/reactor_implement.h"
#include "time/time_value.h"

namespace Water {

class ReactorImplement;
class Handler;
class EventSet;

// Bridge 模式实现，可以由 epoll，select，poll，dev/poll 实现 ReactorImplement
class Reactor {
 public:
  Reactor(ReactorImplement *implement);
  virtual ~Reactor();

 public:
  inline int RegisterHandler(Handler *handler, const EventSet &event_set,
                             int priority = kNormalPriority);

  inline int RemoveHandler(Handler *handler);

  inline TimerType ScheduleTimer(Handler *handler, const TimeValue &delay,
                                 const TimeValue &repeat = TimeValue::zero);

  inline int CancelTimer(Handler *handler);

  inline void SuspendHandler(Handler *handler);
  inline void ResumeHandler(Handler *handler);

  inline int StartEventLoop();
  inline int EndEventLoop();

 private:
  ReactorImplement *implement_;
};

inline Reactor::Reactor(ReactorImplement *implement) : implement_(implement) {
  assert(implement);
}

inline Reactor::~Reactor() {
}

inline int Reactor::RegisterHandler(Handler *handler, const EventSet &event_set,
                                    int priority) {
  assert(handler);
  return implement_->RegisterHandler(handler, event_set, priority);
}

inline int Reactor::RemoveHandler(Handler *handler) {
  assert(handler);
  return implement_->RemoveHandler(handler);
}

inline TimerType Reactor::ScheduleTimer(Handler *handler, const TimeValue &delay,
                                        const TimeValue &repeat) {
  assert(handler);
  return implement_->ScheduleTimer(handler, delay, repeat);
}

inline int Reactor::CancelTimer(Handler *handler) {
  assert(handler);
  return implement_->CancelTimer(handler);
}

inline void Reactor::SuspendHandler(Handler *handler) {
  assert(handler);
  implement_->SuspendHandler(handler);
}

inline void Reactor::ResumeHandler(Handler *handler) {
  assert(handler);
  implement_->ResumeHandler(handler);
}

inline int Reactor::StartEventLoop() { 
  return implement_->StartEventLoop(); 
}

inline int Reactor::EndEventLoop() {
  return implement_->EndEventLoop(); 
}

} // namespace Water

#endif // NET_REACTOR_H_
