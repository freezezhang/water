/*
 * reactor_implement.h
 *
 * Created on: 2011-5-26
 * Author: freezezdj
 */

#ifndef NET_REACTOR_IMPLEMENT_H_
#define NET_REACTOR_IMPLEMENT_H_

#include "net/event_set.h"

namespace Water {

class Handler;
class EventSet;
class TimeValue;

class ReactorImplement {
 public:
	ReactorImplement() {};
	virtual ~ReactorImplement() {};

 public:
	virtual int RegisterHandler(Handler* handler,
	                            const EventSet& event_set,
	                            int priority) = 0;

	virtual int RemoveHandler(Handler* handler) = 0;

	virtual TimerID ScheduleTimer(Handler* handler,
	                              const TimeValue& delay,
	                              const TimeValue& repeat) = 0;

	virtual int CancelTimer(Handler* handler) = 0;

	virtual void SuspendHandler(Handler* handler) = 0;
	virtual void ResumeHandler(Handler* handler) = 0;

	virtual int StartEventLoop() = 0;
	virtual int EndEventLoop() = 0;

};

} // namespace Water

#endif // NET_REACTOR_IMPLEMENT_H_
