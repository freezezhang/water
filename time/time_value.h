/*
 * time_value.h
 *
 * Created on: 2011-5-23
 * Author: freezezdj
 */

#ifndef TIME_TIME_VALUE_H_
#define TIME_TIME_VALUE_H_

#include <sys/time.h>
#include <time.h>
#include "date_time.h"

namespace Water {

class TimeValue {
 public:
	TimeValue();
	TimeValue(time_t seconds, suseconds_t microseconds);
	TimeValue(const TimeValue& other);
	explicit TimeValue(const DateTime& date_time);
	explicit TimeValue(const timeval& time_val);
	explicit TimeValue(const timespec& time_spce);
	explicit TimeValue(long millisecond);
	virtual ~TimeValue();

 public:
	inline operator timeval();
	inline operator timespec();
	inline operator time_t();
	operator DateTime();

	inline TimeValue operator+(const TimeValue& other) const;
	inline TimeValue operator-(const TimeValue& other) const;
	inline TimeValue& operator+=(const TimeValue& other);
	inline TimeValue& operator-=(const TimeValue& other);
	inline TimeValue& operator=(const TimeValue& other);
	inline TimeValue& operator=(const timeval& time_val);
	inline TimeValue& operator=(const timespec& time_spce);
	inline TimeValue& operator=(long millisecond);
	TimeValue& operator=(const DateTime& date_time);
	inline bool operator<(const TimeValue& other) const;
	inline bool operator>(const TimeValue& other) const;
	inline bool operator<=(const TimeValue& other) const;
	inline bool operator>=(const TimeValue& other) const;
	inline bool operator==(const TimeValue& other) const;
	inline bool operator!=(const TimeValue& other) const;

 public:
	inline void SetSecond(time_t second);
	inline time_t GetSecond() const;

	inline void SetMicrosecond(suseconds_t microsecond);
	inline suseconds_t GetMicrosecond() const;

	inline time_t Millisecond() const;

	inline static TimeValue Now();

 public:
	static TimeValue zero;
	static TimeValue null;

 private:
	timeval time_value_;

};

} // namespace Water

#include "time_value-inl.h"

#endif // TIME_TIME_VALUE_H_

/*
1秒=1000毫秒(ms)
1毫秒=1／1,000秒(s)
1秒=1,000,000 微秒(μs)
1微秒=1／1,000,000秒(s)
1秒=1,000,000,000 纳秒(ns)
1纳秒=1／1,000,000,000秒(s)
1秒=1,000,000,000,000 皮秒(ps)
1皮秒=1／1,000,000,000,000秒(s)
*/
