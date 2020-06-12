#ifndef NET_EVENT_SET_INL_H_
#define NET_EVENT_SET_INL_H_

namespace Water {

inline EventSet::EventSet()
    : event_set_(0) {
}

inline EventSet::EventSet(u_int32 event_set)
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

inline u_int32 EventSet::GetEventSet() const {
  return event_set_;
}

inline void EventSet::SetEventSet(u_int32 event_set) {
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

#endif // NET_EVENT_SET_INL_H_
