/*
 * net_exception.h
 *
 * Created on: 2011-5-17
 * Author: freezezdj
 */

#ifndef NET_NET_EXCEPTION_H_
#define NET_NET_EXCEPTION_H_

#include <cerrno>
#include <cstring>

#include "water_exception.h"

namespace Water {

class BadAddress : public WaterException {
 public:
	explicit BadAddress(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadAddress(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadAddress() throw() {

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

class BadSocket : public WaterException {
 public:
	explicit BadSocket(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadSocket(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadSocket() throw() {

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

class BadEPoll : public WaterException {
 public:
	explicit BadEPoll(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadEPoll(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadEPoll() throw() {

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

class BadAcceptor : public WaterException {
 public:
	explicit BadAcceptor(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadAcceptor(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadAcceptor() throw() {

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

class BadConnector : public WaterException {
 public:
	explicit BadConnector(int errer_no) {
		ErrnoToInfo(errer_no);
	}

	explicit BadConnector(const string& exception_info)
		: exception_info_(exception_info) {
	}

	virtual ~BadConnector() throw() {

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

}	//namespace Water

#endif // NET_NET_EXCEPTION_H_
