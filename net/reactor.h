/*
 * reactor.h
 *
 * Created on: 2011-5-23
 * Author: freezezdj
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
  Reactor(ReactorImplement* implement);
  virtual ~Reactor();

public:
  inline int RegisterHandler(Handler* handler,
                             const EventSet& event_set,
                             int priority = kNormalPriority);

  inline int RemoveHandler(Handler* handler);

  inline TimerID ScheduleTimer(Handler* handler,
                               const TimeValue& delay,
                               const TimeValue& repeat = TimeValue::zero);

  inline int CancelTimer(Handler* handler);

  inline void SuspendHandler(Handler* handler);
  inline void ResumeHandler(Handler* handler);

  inline int StartEventLoop();
  inline int EndEventLoop();

private:
  ReactorImplement* implement_;

};

} // namespace Water

#include "reactor-inl.h"

#endif // NET_REACTOR_H_
