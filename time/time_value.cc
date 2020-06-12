#include "time_value.h"
#include "time/date_time.h"

namespace Water {

TimeValue TimeValue::zero(0, 0);
TimeValue TimeValue::null(-1, -1);

TimeValue::TimeValue() {
	time_value_.tv_sec = 0;
	time_value_.tv_usec = 0;
}

TimeValue::TimeValue(time_t second, suseconds_t microsecond) {
	time_value_.tv_sec = second;
	time_value_.tv_usec = microsecond;
}

TimeValue::TimeValue(const TimeValue& other) {
	time_value_.tv_sec = other.GetSecond();
	time_value_.tv_usec = other.GetMicrosecond();
}

TimeValue::TimeValue(const DateTime& date_time) {
	time_value_.tv_sec = date_time.Time();
	time_value_.tv_usec = 0;
}

TimeValue::TimeValue(const timeval& time_val) {
	time_value_.tv_sec = time_val.tv_sec;
	time_value_.tv_usec = time_val.tv_usec;
}

TimeValue::TimeValue(const timespec& time_spce) {
	time_value_.tv_sec = time_spce.tv_sec;
	time_value_.tv_usec = time_spce.tv_nsec / 1000;
}

TimeValue::TimeValue(long millisecond) {
	time_value_.tv_sec = millisecond / 1000;
	time_value_.tv_usec = millisecond % 1000 * 1000;
}

TimeValue::~TimeValue() {

}

TimeValue::operator DateTime() {
	return DateTime(time_value_.tv_sec);
}

TimeValue& TimeValue::operator=(const DateTime& date_time) {
	time_value_.tv_sec = date_time.Time();
	time_value_.tv_usec = 0;
	return *this;
}

} // namespace Water
