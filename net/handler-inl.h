/*
 * handler-inl.h
 *
 * Created on: 2011-5-29
 * Author: freezezdj
 */

#ifndef NET_HANDLER_INL_H_
#define NET_HANDLER_INL_H_

namespace Water {

inline void Handler::set_fd(int fd) {
	fd_ = fd;
}

inline int Handler::fd() const {
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

inline void Handler::SetPriority(int priority) {
	priority_ = priority;
}

inline int Handler::GetPriority() const {
	return priority_;
}

inline int Handler::SetNoBlock() const {
	int flags = fcntl(fd_, F_GETFL);
	if (flags < 0) return -1;
	if (fcntl(fd_, F_SETFL, flags | O_NONBLOCK) < 0)
		return -1;
	return 0;
}

inline int Handler::UnSetNoBlock() const {
	int flags = fcntl(fd_, F_GETFL);
	if (flags < 0) return -1;
	if (fcntl(fd_, F_SETFL, flags & (~O_NONBLOCK)) < 0)
		return -1;
	return 0;
}

} // namespace Water

#endif // NET_HANDLER_INL_H_
