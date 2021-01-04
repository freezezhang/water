/*
 * event_set.h
 *
 * Created on: 2011-5-26
 * Author: freezezhang
 */

#ifndef NET_EVENT_SET_H_
#define NET_EVENT_SET_H_

#include "net/net_types.h"

namespace Water {

class EventSet {
 public:
  EventSet();
  EventSet(Uint32 event_set);
  EventSet(const EventSet& other);
  virtual ~EventSet();

 public:
  inline EventSet& operator=(const EventSet& other);

 public:
  inline Uint32 GetEventSet() const;
  inline void SetEventSet(Uint32 event_set);
  inline void AddEvent(ReactorEvent event);
  inline bool InEventSet(ReactorEvent event) const;
  inline void ClearEvent(ReactorEvent event);
  inline void ClearAllEvent();

 private:
  Uint32 event_set_;
};

inline EventSet::EventSet()
    : event_set_(0) {
}

inline EventSet::EventSet(Uint32 event_set)
    : event_set_(event_set) {
}

inline EventSet::EventSet(const EventSet& other)
    : event_set_(other.GetEventSet()) {
}

inline EventSet::~EventSet() {
}

inline EventSet& EventSet::operator =(const EventSet& other) {
  event_set_ = other.GetEventSet();
  return *this;
}

inline Uint32 EventSet::GetEventSet() const {
  return event_set_;
}

inline void EventSet::SetEventSet(Uint32 event_set) {
  event_set_ = event_set;
}

inline void EventSet::AddEvent(ReactorEvent event) {
  event_set_ |= event;
}

inline bool EventSet::InEventSet(ReactorEvent event) const {
  return event_set_ & event;
}

inline void EventSet::ClearEvent(ReactorEvent event) {
  event_set_ &= (~event);
}

inline void EventSet::ClearAllEvent() {
  event_set_ = 0;
}

} // namespace Water

#endif // NET_EVENT_SET_H_
