#include "timer_queue.h"

#include <assert.h>

namespace Water {

TimerType TimerQueue::allot_timer_id_ = 0;

TimerQueue::TimerQueue() {
  timer_queue_.reserve(16); 
}

TimerQueue::~TimerQueue() {
  for (TimerVector::iterator delete_iter = timer_queue_.begin();
       delete_iter != timer_queue_.end(); ++delete_iter) {
    delete *delete_iter;
    *delete_iter = NULL;
  }
}

size_t TimerQueue::Size() const { 
  return timer_queue_.size(); 
}

bool TimerQueue::Empty() const {
  return timer_queue_.empty(); 
}

TimerType TimerQueue::Push(TimerEvent *timer_event) {
  assert(timer_event);
  timer_event->SetTimerId(++allot_timer_id_);
  timer_queue_.push_back(timer_event);
  push_heap(timer_queue_.begin(), timer_queue_.end(), TimerEventCompare());
  return allot_timer_id_;
}

void TimerQueue::Pop() {
  pop_heap(timer_queue_.begin(), timer_queue_.end(), TimerEventCompare());
  delete timer_queue_.back();
  timer_queue_.back() = NULL;
  timer_queue_.pop_back();
}

TimerEvent *TimerQueue::Top() const { 
  return timer_queue_.front(); 
}

Int32 TimerQueue::Remove(Handler *handler) {
  assert(handler);
  TimerVector::iterator iter =
      remove_if(timer_queue_.begin(), timer_queue_.end(),
                TimerEventHandlerEqual(handler));
  if (iter != timer_queue_.end()) {
    Int32 remove_number = 0;
    for (TimerVector::iterator delete_iter = iter;
         delete_iter != timer_queue_.end(); ++delete_iter) {
      delete *delete_iter;
      *delete_iter = NULL;
    }
    remove_number = timer_queue_.end() - iter;
    timer_queue_.erase(iter, timer_queue_.end());
    make_heap(timer_queue_.begin(), timer_queue_.end(), TimerEventCompare());
    return remove_number;
  } 
  return 0;
}

Int32 TimerQueue::Remove(TimerType timer_id) {
  // TODO: 可性能优化，自己实现删除一个元素后堆的调整
  TimerVector::iterator iter =
      remove_if(timer_queue_.begin(), timer_queue_.end(),
                TimerEventTimerTypeEqual(timer_id));
  if (iter != timer_queue_.end()) {
    Int32 remove_number = 0;
    for (TimerVector::iterator delete_iter = iter;
         delete_iter != timer_queue_.end(); ++delete_iter) {
      delete *delete_iter;
      *delete_iter = NULL;
    }
    remove_number = timer_queue_.end() - iter;
    timer_queue_.erase(iter, timer_queue_.end());
    make_heap(timer_queue_.begin(), timer_queue_.end(), TimerEventCompare());
    return remove_number;
  } else {
    return 0;
  }
}
} // namespace Water
