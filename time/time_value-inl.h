#ifndef TIME_TIME_VALUE_INL_H_
#define TIME_TIME_VALUE_INL_H_

namespace Water {

inline TimeValue::operator timeval() {
	return time_value_;
}

inline TimeValue::operator timespec() {
	timespec time_spec;
	time_spec.tv_sec = time_value_.tv_sec;
	time_spec.tv_nsec = time_value_.tv_usec * 1000;
	return time_spec;
}

inline TimeValue::operator time_t() {
	return GetSecond();
}

inline TimeValue TimeValue::operator+(const TimeValue& other) const {
	TimeValue time_value(*this);
	time_value += other;
	return time_value;
}

inline TimeValue TimeValue::operator-(const TimeValue& other) const {
	TimeValue time_value(*this);
	time_value -= other;
	return time_value;
}

inline TimeValue& TimeValue::operator+=(const TimeValue& other) {
	time_t this_second = time_value_.tv_sec;
	suseconds_t this_microsecond = time_value_.tv_usec;
	time_t other_second = other.GetSecond();
	suseconds_t other_microsecond = other.GetMicrosecond();

	time_value_.tv_sec = this_second + other_second +
			(this_microsecond + other_microsecond) / 1000000;
	time_value_.tv_usec =
			(this_microsecond + other_microsecond) % 1000000;
	return *this;
}

inline TimeValue& TimeValue::operator-=(const TimeValue& other) {
	time_t this_second = time_value_.tv_sec;
	suseconds_t this_microsecond = time_value_.tv_usec;
	time_t other_second = other.GetSecond();
	suseconds_t other_microsecond = other.GetMicrosecond();

	time_t second = this_second - other_second;
	suseconds_t microsecond = this_microsecond - other_microsecond;
	if (microsecond < 0 ) {
		second -= 1;
		microsecond += 1000000;
	}
	time_value_.tv_sec = second;
	time_value_.tv_usec = microsecond;
	return *this;
}

inline TimeValue& TimeValue::operator=(const TimeValue& other) {
	if (this != &other) {
		time_value_.tv_sec = other.GetSecond();
		time_value_.tv_usec = other.GetMicrosecond();
	}
	return *this;
}

inline TimeValue& TimeValue::operator=(const timeval& time_val) {
	time_value_.tv_sec = time_val.tv_sec;
	time_value_.tv_usec = time_val.tv_usec;
	return *this;
}

inline TimeValue& TimeValue::operator=(const timespec& time_spce) {
	time_value_.tv_sec = time_spce.tv_sec;
	time_value_.tv_usec = time_spce.tv_nsec / 1000;
	return *this;
}

inline TimeValue& TimeValue::operator=(long millisecond) {
	time_value_.tv_sec = millisecond / 1000;
	time_value_.tv_usec = millisecond % 1000 * 1000;
	return *this;
}

inline bool TimeValue::operator<(const TimeValue& other) const {
	return other > *this;
}

inline bool TimeValue::operator>(const TimeValue& other) const {
	if (time_value_.tv_sec > other.GetSecond()
			|| (time_value_.tv_sec == other.GetSecond()
					&& time_value_.tv_usec > other.GetMicrosecond())) {
		return true;
	} else {
		return false;
	}
}

inline bool TimeValue::operator<=(const TimeValue& other) const {
	return other >= *this;
}

inline bool TimeValue::operator>=(const TimeValue& other) const {
	if (time_value_.tv_sec > other.GetSecond()
			|| (time_value_.tv_sec == other.GetSecond()
					&& time_value_.tv_usec >= other.GetMicrosecond())) {
		return true;
	} else {
		return false;
	}
}

inline bool TimeValue::operator==(const TimeValue& other) const {
	return (time_value_.tv_sec == other.GetSecond())
			&& (time_value_.tv_usec == other.GetMicrosecond());
}

inline bool TimeValue::operator!=(const TimeValue& other) const {
	return !(*this == other);
}

inline void TimeValue::SetSecond(time_t second) {
	time_value_.tv_sec = second;
}

inline time_t TimeValue::GetSecond() const {
	return time_value_.tv_sec;
}

inline void TimeValue::SetMicrosecond(suseconds_t microsecond) {
	time_value_.tv_usec = microsecond;
}

inline suseconds_t TimeValue::GetMicrosecond() const {
	return time_value_.tv_usec;
}

inline time_t TimeValue::Millisecond() const {
	// 有数值溢出可能
	return time_value_.tv_sec * 1000 + 	time_value_.tv_usec / 1000;
}

inline TimeValue TimeValue::Now() {
	timeval time_val;
	gettimeofday(&time_val, NULL);
	return TimeValue(time_val);
}

} // namespace Water

#endif // TIME_TIME_VALUE_INL_H_
