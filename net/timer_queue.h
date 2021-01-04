/*
 * timer_queue.h
 *
 * Created on: 2011-5-27
 * Author: freezezhang
 */

#ifndef NET_TIMER_QUEUE_H_
#define NET_TIMER_QUEUE_H_

#include <assert.h>

#include <vector>
using std::vector;

#include <algorithm>

#include "time/time_value.h"
#include "net/handler.h"

namespace Water {

class Handler;
class TimerEvent;

class TimerQueue {
 public:
  typedef vector<TimerEvent*> TimerVector;

 public:
  TimerQueue();
  virtual ~TimerQueue();

 public:
  size_t Size() const;

  bool Empty() const;

  // 返回 timer_id
  TimerType Push(TimerEvent* timer_event);

  // 为 Pop 的 TimerEvent* 项执行了 delete 操作
  void Pop();

  TimerEvent* Top() const;

  Int32 Remove(TimerType timer_id);

  // 返回值为被移除个数，且将为被移除的 TimerEvent* 项执行了 delete 操作
  Int32 Remove(Handler* handler);

 private:
  static TimerType allot_timer_id_;
  TimerVector timer_queue_;
};

class TimerEvent {
 public:
   TimerEvent(Handler *handler, const TimeValue &activation_time,
              const TimeValue &repeat = TimeValue::zero)
       : timer_id_(0), handler_(handler), activation_time_(activation_time),
         repeat_(repeat) {
     assert(handler);
   }

 public:
  TimerType GetTimerId() const {
    return timer_id_;
  }

  void SetTimerId(TimerType timer_id) {
    timer_id_ = timer_id;
  }

  const TimeValue& GetActivedTime() const {
    return activation_time_;
  }

  const TimeValue& GetRepeat() const {
    return repeat_;
  }

  Handler* GetHandler() const {
    return handler_;
  }

 private:
  TimerType timer_id_;
  Handler* handler_;
  TimeValue activation_time_;  // 激活定时事件的绝对时间
  TimeValue repeat_;          // 重复定时事件间隔

};

class TimerEventCompare {
 public:
  bool operator()(const TimerEvent* event1,
                  const TimerEvent* event2) const {
    assert(event1 && event2);
    return event1->GetActivedTime() > event2->GetActivedTime();
  }
};

class TimerEventHandlerEqual {
 public:
  TimerEventHandlerEqual(Handler* handler) : handler_(handler) {
    assert(handler);
  }

 public:
  bool operator()(const TimerEvent* event) const {
    assert(event);
    return event->GetHandler() == handler_;
  }

 private:
  Handler* handler_;
};

class TimerEventTimerTypeEqual {
 public:
  TimerEventTimerTypeEqual(TimerType timer_id) : timer_id_(timer_id) {
    assert(timer_id > 0);
  }

 public:
  bool operator()(const TimerEvent* event) const {
    assert(event);
    return event->GetTimerId() == timer_id_;
  }

 private:
  TimerType timer_id_;
};

} // namespace Water

#endif // NET_TIMER_QUEUE_H_
