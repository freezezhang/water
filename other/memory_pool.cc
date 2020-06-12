/*
 * memory_pool.cc
 *
 *  Created on: 2012-11-2
 *      Author: zdj
 */
#include "memory_pool.h"

#include <cassert>

MemoryPool::MemoryPool() 
  : initialized_(false)
  , memory_manage_array_(nullptr) {
}

MemoryPool::~MemoryPool() {
}

int MemoryPool::Init() {
  allocate_size_ = 0;
  memory_manage_array_ = static_cast<Block**>(malloc(sizeof(Byte*) * kBlockManageArraySize));
  if (memory_manage_array_ == nullptr) return -1;
  size_t init_memory_size = 0;
  for (size_t i = kMinBlockSize; i <= kMaxBlockSize; i += kMinBlockSize) {
    init_memory_size += i * kAllocateBlockCount;
  }
  Byte* init_memory = static_cast<Byte*>(malloc(init_memory_size));
  if (memory_manage_array_ == nullptr) {
    free(memory_manage_array_);
    return -1;
  }
  allocate_size_ += init_memory_size; 
  for (size_t i = 0, offset = 0; i < kMaxBlockSize / kMinBlockSize; ++i) {
    offset += i * kMinBlockSize * kAllocateBlockCount;
    Byte* blocks = init_memory + offset; 
    LinkBlock(blocks, (i + 1) * kMinBlockSize * kAllocateBlockCount, (i + 1) * kMinBlockSize);
    memory_manage_array_[i] = reinterpret_cast<Block*>(blocks);
  }
  initialized_ = true;

  return 0;
}

void* MemoryPool::Allocate(size_t size) {
  assert(size > 0 && initialized_);
  if (size > kMaxBlockSize) {
    allocate_size_ += size; 
    return malloc(size);
  }
  size_t manage_index = size / kMinBlockSize + (size % kMinBlockSize == 0 ? 0 : 1) - 1; 
  Block* block = memory_manage_array_[manage_index];
  if (block == nullptr) {
    size_t new_memory_size = ((manage_index + 1) * kMinBlockSize) * kAllocateBlockCount;
    Byte* new_memory = static_cast<Byte*>(malloc(new_memory_size));
    if (new_memory == nullptr) return nullptr;
      allocate_size_ += new_memory_size; 
      LinkBlock(new_memory, new_memory_size, (manage_index + 1) * kMinBlockSize); 		
      block = reinterpret_cast<Block*>(new_memory);
  }
  if (block != nullptr) {
    void* result = reinterpret_cast<void*>(block);
    block = block->next;
    memory_manage_array_[manage_index] = block; 
    return result; 
  }
  return nullptr;
}

void MemoryPool::Deallocate(void* ptr, size_t size) {
  assert(ptr && size > 0 && initialized_);
  if (size > kMaxBlockSize) free(ptr); 
  size_t manage_index = size / kMinBlockSize + (size % kMinBlockSize == 0 ? 0 : 1) - 1; 
  Block* block = memory_manage_array_[manage_index];
  Block* return_block = reinterpret_cast<Block*>(ptr);
  memory_manage_array_[manage_index] = return_block;
  return_block->next = block;
}

void MemoryPool::LinkBlock(Byte* memory, size_t memory_size, size_t block_size) {
  size_t block_count = memory_size / block_size;
  Block* block = reinterpret_cast<Block*>(memory);
  for (size_t i = 1; i <= block_count; ++i) {
    if (i != block_count) {
      block->next = reinterpret_cast<Block*>(memory + i * block_size);
      block = block->next;
    } else {
      block->next = nullptr;
    }
  }
}
