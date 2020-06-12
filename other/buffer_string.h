/*
 * buffer_string.h
 *
 *  Created on: 2013-5-20
 *      Author: zdj
 */

#ifndef BUFFER_STRING_H_
#define BUFFER_STRING_H_

#include <vector>

class BufferString {
public:
  const char* String() const {return string_.data();}
  size_t Size() const {return string_.size();}
  size_t Length() const {return length_;}
  void SetLength(size_t length) {
    length_ = length;
    string_.data()[length_] = '\0';
  }
  char* Buffer() {return string_.data();}
  void Reserve(size_t size) {string_.reserve(size);}
  void Clean() {string_.clear(); length_ = 0; }

private:
  std::vector<char> string_;
  size_t length_;
};

#endif // BUFFER_STRING_H_