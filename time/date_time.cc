#include "date_time.h"

#include <assert.h>

#include "time/time_value.h"

namespace Water {

DateTime::DateTime() throw (BadDateTime) {
	time_ = time(NULL);
	if (time_ < 0) {
		throw BadDateTime("DateTime structure failure");
	}
}

DateTime::DateTime(time_t time) throw (BadDateTime) {
	time_ = time;
	if (time_ < 0) {
		throw BadDateTime("DateTime structure failure");
	}
}

DateTime::DateTime(const TimeValue& time_value) throw (BadDateTime) {
	time_ = time_value.GetSecond();
	if (time_ < 0) {
		throw BadDateTime("DateTime structure failure");
	}
}

DateTime::DateTime(tm& time) throw (BadDateTime) {
	time_ = mktime(&time);
	if (time_ < 0) {
		throw BadDateTime("DateTime structure failure");
	}
}

DateTime::~DateTime() {

}

DateTime::operator TimeValue() {
	return TimeValue(time_, 0);
}


string DateTime::TimeFormatString(const string& format,
                                  bool is_local) const {
	char buf[256];
	tm* p_time = is_local ? localtime(&time_) : gmtime(&time_);
	size_t string_size = strftime(buf, 256, format.c_str(), p_time);
	if (string_size > 0)
		return buf;
	else
		return "";
}

void DateTime::HighResolutionTime(time_t& second,
                                  long& microsecond) {
	timeval time;
	gettimeofday(&time, NULL);
	second = time.tv_sec;
	microsecond = time.tv_usec;
}

string DateTime::TimeFormatString(const string& format,
                                  time_t time,
                                  bool is_local) {
	char buf[256];
	tm* p_time = is_local ? gmtime(&time) : localtime(&time);
	size_t string_size = strftime(buf, 256, format.c_str(), p_time);
	if (string_size > 0)
		return buf;
	else
		return "";
}

string DateTime::TimeFormatString(const string& format,
                                  const tm& time) {
	char buf[256];
	size_t string_size = strftime(buf, 256, format.c_str(), &time);
	if (string_size > 0)
		return buf;
	else
		return "";
}

} // namespace Water
