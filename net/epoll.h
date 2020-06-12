/*
 * epoll.h
 *
 * Created on: 2011-5-25
 * Author: freezezdj
 */

#ifndef NET_EPOLL_H_
#define NET_EPOLL_H_

#include <sys/epoll.h>

#include <vector>
using std::vector;

#include <tr1/unordered_map>
using std::tr1::unordered_map;

#include "net/net_types.h"
#include "net/net_exception.h"
#include "net/reactor_implement.h"
#include "time/time_value.h"
#include "net/timer_queue.h"

namespace Water {

class EventSet;
class Handler;
class TimeValue;

class EPoll : public ReactorImplement {
 public:
	EPoll() throw(BadEPoll);
	virtual ~EPoll();

 public:
	virtual int RegisterHandler(Handler* handler,
	                            const EventSet& event_set,
	                            int priority = kNormalPriority);

	virtual int RemoveHandler(Handler* handler);

	virtual TimerID ScheduleTimer(Handler* handler,
	                         const TimeValue& delay,
	                         const TimeValue& repeat = TimeValue::zero);

	virtual int CancelTimer(Handler* handler);
	virtual int CancelTimer(TimerID timer_id);

	virtual void SuspendHandler(Handler* handler);
	virtual void ResumeHandler(Handler* handler);

	virtual int StartEventLoop();
	virtual int EndEventLoop();

 private:
	int HandleEvents(const TimeValue& timeout, TimeValue& expiration);
	int EventLoop();

	u_int32 EventSetToEPollEvents(const EventSet& event_set) const;
	EventSet EPollEventsToEventSet(u_int32 epoll_events) const;

	int EPollControl(int operation, Handler* handler) const;

	int CleanPastTimeoutEvents(const TimeValue& expiration);

	int IssueEventHandle();

 private:
	typedef unordered_map<int, Handler*> HandlerMap;
	typedef vector<Handler*> HandlerList;
	typedef vector<epoll_event> EventList;

 private:
	int epoll_fd_;

	HandlerMap register_map_;
	HandlerList activated_list_;
	EventList return_event_list_;

	TimerQueue timer_queue_;

	bool is_run_;
};

} // namespace Water

#endif // NET_EPOLL_H_
