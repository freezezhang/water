/*
 * bad_initialize.h
 *
 * Created on: 2011-2-28
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_FILE_SYSTEM_EXCEPTION_H_
#define FILE_SYSTEM_FILE_SYSTEM_EXCEPTION_H_

#include <cerrno>
#include <cstring>

#include "water_exception.h"

namespace Water {

class BadUpdate : public WaterException {
public:
  explicit BadUpdate(int errer_no) {
    ErrnoToInfo(errer_no);
  }

  explicit BadUpdate(const string& exception_info)
      : exception_info_(exception_info) {
  }

  virtual ~BadUpdate() throw () {

  }

public:
  virtual const char* what() const throw () {
    return exception_info_.c_str();
  }

private:
  void ErrnoToInfo(int errer_no) {
    exception_info_ = strerror(errer_no);
  }

private:
  string exception_info_;
};

class BadOpenDirectory : public WaterException {
public:
  explicit BadOpenDirectory(int errer_no) {
    ErrnoToInfo(errer_no);
  }

  explicit BadOpenDirectory(const string& exception_info)
      : exception_info_(exception_info) {
  }

  virtual ~BadOpenDirectory() throw () {

  }

public:
  virtual const char* what() const throw () {
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

#endif // FILE_SYSTEM_FILE_SYSTEM_EXCEPTION_H_
