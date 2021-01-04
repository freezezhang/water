/*
 * buffer.h
 *
 * Created on: 2012-11-8
 * Author: freezezhang
 */

#ifndef NET_BUFFER_H_
#define NET_BUFFER_H_

#include <utility>
#include <vector>

#include "water_types.h"

#include "buffer_string.h"

namespace Water {

class Buffer {
 public:
  typedef std::vector<iovec> IOVecs; 
  typedef std::pair<iovec*, Int32> IOVecsSizePair;

 public:
  Buffer();
  ~Buffer();

 public:
  SizeType Read(void* buffer, size_t count);
  SizeType Write(const void* data, size_t count);

  SizeType ReadMove(size_t count);
  SizeType WriteMove(size_t count);

  Int32 Expand(SizeType size);

  SizeType DataCount() const;
  SizeType SpaceCount() const;

  void ContinuousData(void** ptr, SizeType* size) const;
  void ContinuousSpace(void** ptr, SizeType* size) const;

  IOVecsSizePair DataIOvecs(IOVecs* iovecs);
  IOVecsSizePair SpaceIOvecs(IOVecs* iovecs);

  void Splice(Buffer& other);
  SizeType Append(const Buffer& other);

  void WriteLine(char* string);
  void ReadLine(BufferString* value);

 private:
  static const SizeType kBlockDefaultSize = 512;

  struct Block {
    Block* next;
    char* buffer;
    SizeType capacity;
    SizeType start;
    SizeType end;
  };

 private:
  Buffer(const Buffer&);
  Buffer& operator=(const Buffer&);

  Block* CreateBlock(SizeType size);
  inline bool Empty() const;

 private:
  Block* read_;
  Block* write_;
  Block* head_;
  Block* tail_;
  SizeType block_count_;
};

inline bool Buffer::Empty() const {
  return block_count_ == 0;
}

} // namespace Water

#endif // NET_BUFFER_H_
