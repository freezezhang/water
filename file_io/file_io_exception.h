/*
 * file_io_exception.h
 *
 * Created on: 2011-3-4
 * Author: freezezdj
 */

#ifndef FILE_IO_FILE_IO_EXCEPTION_H_
#define FILE_IO_FILE_IO_EXCEPTION_H_

#include <cerrno>
#include <cstring>

#include "water_exception.h"

namespace Water {

class BadOpenFile : public WaterException {
public:
  explicit BadOpenFile(int errer_no) {
    ErrnoToInfo(errer_no);
  }

  explicit BadOpenFile(const string& exception_info)
      : exception_info_(exception_info) {
  }

  virtual ~BadOpenFile() throw () {

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

} // namespace Water

#endif // FILE_IO_FILE_IO_EXCEPTION_H_
