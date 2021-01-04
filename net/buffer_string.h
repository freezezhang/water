/*
 * buffer_string.h
 *
 * Created on: 2013-5-20
 * Author: freezezhang
 */

#ifndef BUFFER_STRING_H_
#define BUFFER_STRING_H_

#include <vector>

#include "water_types.h"

namespace Water {

class BufferString {
public:
  const char* String() const {return string_.data();}
  SizeType Size() const {return string_.size();}
  SizeType Length() const {return length_;}
  void SetLength(SizeType length) {
    length_ = length;
    string_.data()[length_] = '\0';
  }
  char* Buffer() {return string_.data();}
  void Reserve(SizeType size) {string_.reserve(size);}
  void Clean() {string_.clear(); length_ = 0; }

private:
  std::vector<char> string_;
  SizeType length_;
};

} // namespace Water

#endif // BUFFER_STRING_H_