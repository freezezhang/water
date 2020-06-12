/*
 * system_info_exception.h
 *
 * Created on: 2011-3-15
 * Author: freezezdj
 */

#ifndef SYSTEM_INFO_SYSTEM_INFO_EXCEPTION_H_
#define SYSTEM_INFO_SYSTEM_INFO_EXCEPTION_H_

#include <cerrno>
#include <cstring>

#include "water_exception.h"

namespace Water {

class BadUser : public WaterException {
 public:
	explicit BadUser(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadUser(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadUser() throw() {

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

class BadGroup : public WaterException {
 public:
	explicit BadGroup(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadGroup(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadGroup() throw() {

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

#endif // SYSTEM_INFO_SYSTEM_INFO_EXCEPTION_H_
