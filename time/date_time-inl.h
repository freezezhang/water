#ifndef TIME_DATE_TIME_INL_H_
#define TIME_DATE_TIME_INL_H_

namespace Water {

inline DateTime::operator time_t() {
	return time_;
}

inline DateTime::operator tm() {
	return *localtime(&time_);
}

inline tm DateTime::GMTime() const {
	return *gmtime(&time_);
}

inline tm DateTime::LocalTime() const {
	return *localtime(&time_);
}

inline time_t DateTime::Time() const {
	return time_;
}

inline string DateTime::TimeString() const {
	return ctime(&time_);
}

inline string DateTime::TimeString(time_t time) {
	return ctime(&time);
}

inline string DateTime::TimeString(const tm& time) {
	return asctime(&time);
}

} // namespace Water

#endif //TIME_DATE_TIME_INL_H_
