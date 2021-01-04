/*
 * handler.h
 *
 * Created on: 2011-5-23
 * Author: freezezhang
 */

#ifndef NET_HANDLER_H_
#define NET_HANDLER_H_

#include <assert.h>
#include <fcntl.h>

#include "net/event_set.h"
#include "net/reactor.h"
#include "time/time_value.h"

namespace Water {

class Handler {
 public:
  Handler();
  virtual ~Handler();

 public:
  inline Int32 Init(Int32 fd, Reactor* reactor);

  inline void set_fd(Int32 fd);
  inline Int32 fd() const;

  inline void set_reactor(Reactor* reactor);
  inline Reactor* reactor() const;

  inline void set_concern_event_set(const EventSet& event_set);
  inline const EventSet& concern_event_set() const;
  inline void ClearAllConcernEventSet();

  inline void AddConcernEvent(ReactorEvent event);
  inline void ClearConcernEvent(ReactorEvent event);

  inline void ConcernInput();
  inline void ConcernOutput();
  inline void ConcernException();

  inline void set_actived_event_set(EventSet event_set);
  inline const EventSet& actived_event_set() const;
  inline void ClearAllActivedEventSet();

  inline void AddActivedEvent(ReactorEvent event);
  inline void ClearActivedEvent(ReactorEvent event);

  inline void SetPauseState(bool is_pause);
  inline bool GetPauseState() const;

  inline void Suspend();
  inline void Resume();

  inline void SetPriority(Int32 priority);
  inline Int32 GetPriority() const;

  inline Int32 SetNoBlock() const;
  inline Int32 UnSetNoBlock() const;

 public:

  virtual Int32 HandleOpen();

  virtual Int32 HandleInput(Int32 fd = -1);
  virtual Int32 HandleOutput(Int32 fd = -1);
  virtual Int32 HandleTimeout();
  virtual Int32 HandleException();

  //TODO：暂未实现Signal事件分派 virtual Int32 HandleSignal();

  virtual Int32 HandleClose();

 private:
  Int32 fd_;  // 文件描述符

  Reactor* reactor_;  // 反应器

  EventSet concern_event_set_;  // 关注事件集
  EventSet actived_event_set_;  // 已激活事件集

  bool is_pause_;  // 是否暂停分派事件给事件处理器

  Int32 priority_;  // 事件优先级,需Reactor实现支持
};

inline Int32 Handler::Init(Int32 fd, Reactor* reactor) {
  assert(reactor);
  fd_ = fd;
  reactor_ = reactor;
  return 0;
}

inline void Handler::set_fd(Int32 fd) {
  fd_ = fd;
}

inline Int32 Handler::fd() const {
  return fd_;
}

inline void Handler::set_reactor(Reactor* reactor) {
  assert(reactor);
  reactor_ = reactor;
}

inline Reactor* Handler::reactor() const {
  return reactor_;
}

inline void Handler::set_concern_event_set(const EventSet& event_set) {
  concern_event_set_ = event_set;
}

inline const EventSet& Handler::concern_event_set() const {
  return concern_event_set_;
}

inline void Handler::ClearAllConcernEventSet() {
  concern_event_set_.ClearAllEvent();
}

inline void Handler::AddConcernEvent(ReactorEvent event) {
  concern_event_set_.AddEvent(event);
}

inline void Handler::ClearConcernEvent(ReactorEvent event) {
  concern_event_set_.ClearEvent(event);
}

inline void Handler::ConcernInput() {
  concern_event_set_.AddEvent(kEventInput);
}

inline void Handler::ConcernOutput() {
  concern_event_set_.AddEvent(kEventOutput);
}

inline void Handler::ConcernException() {
  concern_event_set_.AddEvent(kEventException);
}

inline void Handler::set_actived_event_set(EventSet event_set) {
  actived_event_set_ = event_set;
}

inline const EventSet& Handler::actived_event_set() const {
  return actived_event_set_;
}

inline void Handler::ClearAllActivedEventSet() {
  actived_event_set_.ClearAllEvent();
}

inline void Handler::AddActivedEvent(ReactorEvent event) {
  actived_event_set_.AddEvent(event);
}

inline void Handler::ClearActivedEvent(ReactorEvent event) {
  actived_event_set_.ClearEvent(event);
}

inline void Handler::Suspend() {
  is_pause_ = true;
}

inline void Handler::Resume() {
  is_pause_ = false; 
}

inline void Handler::SetPauseState(bool is_pause) {
  is_pause_ = is_pause;
}

inline bool Handler::GetPauseState() const {
  return is_pause_;
}

inline void Handler::SetPriority(Int32 priority) {
  priority_ = priority;
}

inline Int32 Handler::GetPriority() const {
  return priority_;
}

inline Int32 Handler::SetNoBlock() const {
  Int32 flags = fcntl(fd_, F_GETFL);
  if (flags < 0) return -1;
  if (fcntl(fd_, F_SETFL, flags | O_NONBLOCK) < 0)
    return -1; //TODO: freeze
  return 0;
}

inline Int32 Handler::UnSetNoBlock() const {
  Int32 flags = fcntl(fd_, F_GETFL);
  if (flags < 0) return -1;
  if (fcntl(fd_, F_SETFL, flags & (~O_NONBLOCK)) < 0)
    return -1; //TODO: freeze
  return 0;
}

} // namespace Water

#endif // NET_HANDLER_H_
