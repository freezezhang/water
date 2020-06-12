/*
 * handler.h
 *
 * Created on: 2011-5-23
 * Author: freezezdj
 */

#ifndef NET_HANDLER_H_
#define NET_HANDLER_H_

#include <assert.h>
#include <fcntl.h>

#include "net/event_set.h"
#include "net/reactor.h"
#include "time/time_value.h"

namespace Water {

class TimeValue;

class Handler {
 public:
	Handler(int file_descriptor, Reactor* reactor);
	virtual ~Handler();

 public:
	inline void set_fd(int file_descriptor);
	inline int fd() const;

	inline void set_reactor(Reactor* reactor);
	inline Reactor* reactor() const;

	inline void set_concern_event_set(const EventSet& event_set);
	inline const EventSet& concern_event_set() const;
	inline void ClearAllConcernEventSet();

	inline void AddConcernEvent(ReactorEvent event);
	inline void ClearConcernEvent(ReactorEvent event);

	inline void ConcernInput();
	inline void ConcernOutput();
	inline void ConcernException();

	inline void set_actived_event_set(EventSet event_set);
	inline const EventSet& actived_event_set() const;
	inline void ClearAllActivedEventSet();

	inline void AddActivedEvent(ReactorEvent event);
	inline void ClearActivedEvent(ReactorEvent event);

	inline void SetPauseState(bool is_pause);
	inline bool GetPauseState() const;

	inline void Suspend();
	inline void Resume();

	inline void SetPriority(int priority);
	inline int GetPriority() const;

	inline int SetNoBlock() const;
	inline int UnSetNoBlock() const;

 public:
	virtual int HandleOpen();

	virtual int HandleInput(int fd = -1);
	virtual int HandleOutput(int fd = -1);
	virtual int HandleTimeout();
	virtual int HandleException();

	//TODO：暂未实现Signal事件分派 virtual int HandleSignal();

	virtual int HandleClose();

 private:
	int fd_;	// 文件描述符

	Reactor* reactor_;	// 反应器

	EventSet concern_event_set_;	// 关注事件集
	EventSet actived_event_set_;	// 已激活事件集

	bool is_pause_;	// 是否暂停分派事件给事件处理器

	int priority_;	// 事件优先级,需Reactor实现支持
};

} // namespace Water

#include "handler-inl.h"

#endif // NET_HANDLER_H_
