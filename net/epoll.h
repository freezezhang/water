/*
 * epoll.h
 *
 * Created on: 2011-5-25
 * Author: freezezhang
 */

#ifndef NET_EPOLL_H_
#define NET_EPOLL_H_

#include <sys/epoll.h>

#include <vector>
using std::vector;

#include <tr1/unordered_map>
using std::tr1::unordered_map;

#include "net/net_types.h"
#include "net/reactor_implement.h"
#include "time/time_value.h"
#include "net/timer_queue.h"

namespace Water {

class EventSet;
class Handler;
class TimeValue;

class EPoll : public ReactorImplement {
 public:
  EPoll();
  virtual ~EPoll();

 public:
  virtual Int32 Init();

  virtual Int32 RegisterHandler(Handler *handler, const EventSet &event_set,
                                 Int32 priority = kNormalPriority);

  virtual Int32 RemoveHandler(Handler *handler);

  virtual TimerType ScheduleTimer(Handler *handler, const TimeValue &delay,
                                   const TimeValue &repeat = TimeValue::zero);

  virtual Int32 CancelTimer(Handler *handler);
  virtual Int32 CancelTimer(TimerType timer_id);

  virtual void SuspendHandler(Handler *handler);
  virtual void ResumeHandler(Handler *handler);

  virtual Int32 StartEventLoop();
  virtual Int32 EndEventLoop();

 private:
  Int32 HandleEvents(const TimeValue& timeout, TimeValue& expiration);
  Int32 EventLoop();
  
  Uint32 EventSetToEPollEvents(const EventSet& event_set) const;
  EventSet EPollEventsToEventSet(Uint32 epoll_events) const;
  
  Int32 EPollControl(int operation, Handler* handler) const;
  
  Int32 CleanPastTimeoutEvents(const TimeValue& expiration);
  
  Int32 IssueEventHandle();

 private:
  typedef unordered_map<Int32, Handler *> HandlerMap;
  typedef vector<Handler *> HandlerList;
  typedef vector<epoll_event> EventList;

 private:
  Int32 epoll_fd_;

  HandlerMap register_map_;
  HandlerList activated_list_;
  EventList return_event_list_;

  TimerQueue timer_queue_;

  bool is_run_;
};

} // namespace Water

#endif // NET_EPOLL_H_
