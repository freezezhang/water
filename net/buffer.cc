#include "buffer.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace Water {

enum {
  BadRead,
  BadWrite,
};

Buffer::Buffer()
    : read_(nullptr) 
    , write_(nullptr)
    , head_(nullptr)
    , tail_(nullptr)
    , block_count_(0) {
}

Buffer::~Buffer() {
  while (head_ != tail_) {
    Block* ptr = head_;
    head_ = head_ ->next;
    ::free(ptr);
  }
  if (head_ == tail_) {
    ::free(head_);
  }
}

Int32 Buffer::Expand(SizeType size) {
  SizeType block_size = std::max(size, kBlockDefaultSize);
  if (Empty()) { 
    Block* block  = CreateBlock(block_size);
    head_ = tail_ = read_ = write_ = block;
    return 0;
  }

  if (head_ == read_) {
    Block* block  = CreateBlock(block_size);
    if (block == nullptr) return -1;
    tail_->next = block;
    tail_ = tail_->next;
    return 0;
  }
  
  SizeType capacity = 0;
  for (Block* iter = head_; iter != read_; iter = head_) {
    Block* block = head_;
    head_ = head_->next;
    capacity += block->capacity;
    block->start = block->end = 0;
    block->next = nullptr;
    tail_->next = block;
    tail_ = tail_->next;
  }
  if (capacity < size) {
    capacity = size - capacity;
    SizeType block_size = std::max(capacity, kBlockDefaultSize);
    Block* block  = CreateBlock(block_size);
    if (block == nullptr) return -1;
    tail_->next = block;
    tail_ = tail_->next;
  }
  return 0;
}

SizeType Buffer::Read(void* buffer, size_t count) {
  assert(buffer);
  SizeType no_copy_count = count;
  //if (Empty()) goto leave;
  while (no_copy_count != 0) {
    SizeType data_count = read_->end - read_->start;
    SizeType copy_count = std::min(no_copy_count, data_count);
    ::memcpy(static_cast<char*>(buffer) + count - no_copy_count, read_->buffer + read_->start, copy_count);
    no_copy_count -= copy_count;
    read_->start += copy_count;
    if (read_ == write_) {
      goto leave;
    }
    if (no_copy_count >= 0) {
      read_ = read_->next;
    }
  }
leave:
  SizeType result = count - no_copy_count;
  if (result != count) {
    throw BadRead;
  }
  return count - no_copy_count;
}

SizeType Buffer::Write(const void* data, size_t count) {
  assert(data);
  SizeType no_copy_count = count;
  if (Empty()) {
    if (Expand(kBlockDefaultSize) != 0) { 
      goto leave;
    }
  }
  while (no_copy_count != 0) {
    SizeType space_count = write_->capacity - write_->end;
    SizeType copy_count = std::min(no_copy_count, space_count);
    ::memcpy(write_->buffer + write_->end, static_cast<const char*>(data) + count - no_copy_count, copy_count);
    no_copy_count -= copy_count;
    write_->end += copy_count;
    if (no_copy_count > 0) {
      if (write_ == tail_) {
        if (Expand(kBlockDefaultSize) != 0) {
          goto leave;
        }
      }
      write_ = write_->next;
    }
  }
leave:
  SizeType result = count - no_copy_count;
  if (result != count) {
    throw BadWrite;
  }
  return count - no_copy_count;
}

Buffer::IOVecsSizePair Buffer::DataIOvecs(IOVecs* iovecs) {
  assert(iovecs);
  iovecs->clear();
  for (Block* iter = read_; iter != write_->next; iter = iter->next) { 
    iovec iov;
    iov.iov_base = iter->buffer + iter->start;
    iov.iov_len = iter->end - iter->start;
    iovecs->push_back(iov);
  }
  return std::make_pair(iovecs->data(), static_cast<Int32>(iovecs->size()));
}

Buffer::IOVecsSizePair Buffer::SpaceIOvecs(IOVecs* iovecs) {
  assert(iovecs);
  iovecs->clear();
  for (Block* iter = write_; iter != tail_->next; iter = iter->next) { 
    iovec iov;
    iov.iov_base = iter->buffer + iter->end;
    iov.iov_len = iter->capacity - iter->end;
    iovecs->push_back(iov);
  }
  return std::make_pair(iovecs->data(), static_cast<Int32>(iovecs->size()));
}

SizeType Buffer::DataCount() const {
  SizeType count = 0;
  for (Block* iter = read_; iter != write_->next; iter = iter->next) { 
    count += iter->end - iter->start;
  }
  return count;
}

SizeType Buffer::SpaceCount() const {
  SizeType count = 0;
  for (Block* iter = write_; iter != tail_->next; iter = iter->next) { 
    count += iter->capacity - iter->end;
  }
  return count;
}

void Buffer::ContinuousData(void** ptr, SizeType* size) const {
  *ptr = read_->buffer + read_->start;
  *size = read_->end - read_->start;
}

void Buffer::ContinuousSpace(void** ptr, SizeType* size) const {
  *ptr = write_->buffer + write_->end;
  *size = write_->capacity - write_->end;
}

SizeType Buffer::ReadMove(size_t count) {
  SizeType no_move_count = count;
  while (no_move_count != 0) {
    SizeType data_count = read_->end - read_->start;
    SizeType move_count = std::min(no_move_count, data_count);
    read_->start += move_count;
    no_move_count -= move_count;  
    if (read_ == write_) {
      return count - no_move_count;
    }
    if (no_move_count >= 0) {
      read_ = read_->next;
    }
  }
  return count - no_move_count;
}

SizeType Buffer::WriteMove(size_t count) {
  SizeType no_move_count = count;
  while (no_move_count != 0) {
    SizeType data_count = write_->capacity - write_->end;
    SizeType move_count = std::min(no_move_count, data_count);
    write_->end += move_count;
    no_move_count -= move_count;  
    if (write_ == tail_) {
      return count - no_move_count;
    }
    if (no_move_count > 0) {
      write_ = write_->next;
    }
  }
  return count - no_move_count;
}

SizeType Buffer::Append(const Buffer& other) {
  SizeType append_size = 0;
  for (Block* iter = other.head_; iter != other.tail_->next; iter = iter->next) {
    append_size += Write(iter->buffer + iter->start, iter->end - iter->start);
  }
  return append_size;
}

void Buffer::WriteLine(char* string) {
  assert(string);
  SizeType length = strlen(string);
  Write(static_cast<void*>(string), length);
  Write("\n", 1);
}

void Buffer::ReadLine(BufferString* value) {
  assert(value);
  value->Clean();
  SizeType line_end_index = 0;
  Int32 move_count = 0;
  for (Block* iter = read_; iter != write_->next; iter = iter->next) { 
    for (const char* ch = iter->buffer + iter->start; ch != iter->buffer + iter->end; ++ch) {
      if (*ch == '\0' || *ch == '\n') {
        move_count = 1;
        break;
      } else if (*ch == '\r' && *(ch + 1) == '\n') {
        move_count = 2;
        break;
      } else {
        ++line_end_index ;
      }
    }
    if (move_count != 0) {
      break;
    }
  }
  if (move_count != 0) {
    value->Reserve(line_end_index + 1);
    SizeType read_count = Read(value->Buffer(), line_end_index);
    value->SetLength(read_count);
    ReadMove(move_count);
  } else {
    value->Clean();
  }
}

void Buffer::Splice(Buffer& other) {
  if (Empty()) {
    head_ = other.head_;
    tail_ = other.tail_ ;
    read_ = other.read_;
    write_ = other.write_;
    block_count_ += other.block_count_;
  } else {
    tail_->next = other.head_;
    tail_ = other.tail_;
    write_ = other.write_;
    block_count_ += other.block_count_;
  }
  other.tail_ = other.head_ = other.read_ = other.write_ = nullptr;
  other.block_count_ = 0;
}

Buffer::Block* Buffer::CreateBlock(SizeType size) {
  Block* block  = static_cast<Block*>(::malloc(sizeof(Block) + size));
  if (block != nullptr) {
    block->next = nullptr;
    block->capacity = size;
    block->buffer = reinterpret_cast<char*>(block + 1);
    block->start = block->end = 0;
  }
  ++block_count_;
  return block;
}

} // namespace Water