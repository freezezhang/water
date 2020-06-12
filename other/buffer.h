/*
 * buffer.h
 *
 *  Created on: 2012-11-8
 *      Author: zdj
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <utility>
#include <vector>

#include "define.h"
#include "buffer_string.h"

class Buffer {
 public:
  typedef std::vector<iovec> IOVecs; 
  typedef std::pair<iovec*, int> IOVecsSizePair;

 public:
  Buffer();
  ~Buffer();

 public:
  size_t Read(void* buffer, size_t count);
  size_t Write(const void* data, size_t count);

  size_t ReadMove(size_t count);
  size_t WriteMove(size_t count);

  int Expand(size_t size);

  size_t DataCount() const;
  size_t SpaceCount() const;

  void ContinuousData(void** ptr, size_t* size) const;
  void ContinuousSpace(void** ptr, size_t* size) const;

  IOVecsSizePair DataIOvecs(IOVecs* iovecs);
  IOVecsSizePair SpaceIOvecs(IOVecs* iovecs);

  void Splice(Buffer& other);
  size_t Append(const Buffer& other);

  void WriteLine(char* string);
  void ReadLine(BufferString* value);

 private:
  static const size_t kBlockDefaultSize = 512;

  struct Block {
    Block* next;
    char* buffer;
    size_t capacity;
    size_t start;
    size_t end;
  };

 private:
  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

  Block* CreateBlock(size_t size);
  inline bool Empty() const;

 private:
  Block* read_;
  Block* write_;
  Block* head_;
  Block* tail_;
  size_t block_count_;
};

inline bool Buffer::Empty() const {
  return block_count_ == 0;
}

#endif // BUFFER_H_
