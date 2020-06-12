/*
 * event_set.h
 *
 * Created on: 2011-5-26
 * Author: freezezdj
 */

#ifndef NET_EVENT_SET_H_
#define NET_EVENT_SET_H_

#include "net/net_types.h"

namespace Water {

class EventSet {
 public:
	EventSet();
	EventSet(u_int32 event_set);
	EventSet(const EventSet& other);
	virtual ~EventSet();

 public:
	inline EventSet& operator=(const EventSet& other);

 public:
	inline u_int32 GetEventSet() const;
	inline void SetEventSet(u_int32 event_set);
	inline void AddEvent(ReactorEvent event);
	inline bool InEventSet(ReactorEvent event) const;
	inline void ClearEvent(ReactorEvent event);
	inline void ClearAllEvent();

 private:
	u_int32 event_set_;
};

} // namespace Water

#include "event_set-inl.h"

#endif // NET_EVENT_SET_H_
