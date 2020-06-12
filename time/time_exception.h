/*
 * time_exception.h
 *
 * Created on: 2011-3-8
 * Author: freezezdj
 */

#ifndef TIME_TIME_EXCEPTION_H_
#define TIME_TIME_EXCEPTION_H_

#include <cerrno>
#include <cstring>

#include "water_exception.h"

namespace Water {

class BadDateTime : public WaterException {
 public:
	explicit BadDateTime(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadDateTime(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadDateTime() throw() {

	}

 public:
	virtual const char* what() const throw() {
		return exception_info_.c_str();
	}

 private:
	void ErrnoToInfo(int errer_no) {
		exception_info_ = strerror(errer_no);
	}

 private:
	string exception_info_;
};

} // namespace Water

#endif // TIME_TIME_EXCEPTION_H_
