/*
 * memory_pool.h
 *
 *  Created on: 2012-11-2
 *      Author: zdj
 */

#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_

#include <stdlib.h>
#include "define.h"

class MemoryPool {
 public:
	 MemoryPool();
	 ~MemoryPool();
	 
 public:
  int Init();

  void* Allocate(size_t size);
  void Deallocate(void* ptr, size_t size);

  size_t allocate_size_;

 private:
  struct Block {
    Block* next;
  };

  static const size_t kMinBlockSize = 8;
  static const size_t kMaxBlockSize = 256;
  static const size_t kBlockManageArraySize = kMaxBlockSize / kMinBlockSize ;
  static const size_t kAllocateBlockCount = 32;

 private:
  MemoryPool(const MemoryPool&other);
  MemoryPool& operator =(const MemoryPool&);

 private:
  void LinkBlock(Byte* memory, size_t memory_size, size_t block_size);

 private:
  bool initialized_;
  Block** memory_manage_array_;

};


#endif // MEMORY_POOL_H_
