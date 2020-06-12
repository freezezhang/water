#include "reactor.h"

namespace Water {

inline Reactor::Reactor(ReactorImplement* implement)
    : implement_(implement) {
  assert(implement);
}

inline Reactor::~Reactor() {
}

inline int Reactor::RegisterHandler(Handler* handler,
                                    const EventSet& event_set,
                                    int priority) {
  assert(handler);
  return implement_->RegisterHandler(handler, event_set, priority);
}

inline int Reactor::RemoveHandler(Handler* handler) {
  assert(handler);
  return implement_->RemoveHandler(handler);
}

inline TimerID Reactor::ScheduleTimer(Handler* handler,
                                      const TimeValue& delay,
                                      const TimeValue& repeat) {
  assert(handler);
  return implement_->ScheduleTimer(handler, delay, repeat);
}

inline int Reactor::CancelTimer(Handler* handler) {
  assert(handler);
  return implement_->CancelTimer(handler);
}

inline void Reactor::SuspendHandler(Handler* handler) {
  assert(handler);
  implement_->SuspendHandler(handler);
}

inline void Reactor::ResumeHandler(Handler* handler) {
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
