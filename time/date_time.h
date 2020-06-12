/*
 * date_time.h
 *
 * Created on: 2011-3-8
 * Author: freezezdj
 */

#ifndef TIME_DATE_TIME_H_
#define TIME_DATE_TIME_H_

#include <sys/time.h>
#include <ctime>

#include "water_types.h"
#include "time/time_exception.h"

#define __need_timeval

namespace Water {

class TimeValue;
// TODO DateTime 未测试

class DateTime {
public:
	DateTime() throw (BadDateTime);
	explicit DateTime(const TimeValue& time_value) throw (BadDateTime);
	explicit DateTime(time_t time) throw (BadDateTime);
	explicit DateTime(tm& time) throw (BadDateTime);
	virtual ~DateTime();

public:
	inline operator time_t();
	inline operator tm();
	inline operator TimeValue();

public:
	inline tm GMTime() const;

	inline tm LocalTime() const;

	inline time_t Time() const ;

	inline string TimeString() const;

	string TimeFormatString(const string& format,
	                        bool is_local = true) const;

public:
	static void HighResolutionTime(time_t& second, long& microsecond);

	inline static string TimeString(time_t time);

	inline static string TimeString(const tm& time);

	static string TimeFormatString(const string& format,
	                               time_t time,
	                               bool is_local = true);

	static string TimeFormatString(const string& format,const tm& time);

private:
	time_t time_;
};

} // namespace Water

#include "date_time-inl.h"

#endif // TIME_DATE_TIME_H_
