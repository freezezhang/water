#ifndef OBJECT_POOL_H_
#define OBJECT_POOL_H_

#include <cstdlib>
#include <cassert>

template<typename T, size_t Count>
class ObjectPool {
 public:
  ObjectPool();
  ~ObjectPool();

 public:
  int Init();

  T* Allocate();
  void Deallocate(T* object);

 private:
  typedef unsigned char Byte;

  struct Block {
    Block* next;
  };

  const size_t kMinObjectSize = sizeof(Block);
  const size_t kAllocateCount = Count;

 private:
  ObjectPool(const ObjectPool&);
  ObjectPool& operator =(const ObjectPool&);

 private:
  void* AllocateLinkBlock(size_t count);

  bool initialized_;
  Block* block_list_head_;
  void* object_array_;
};

template<typename T, size_t Count>
ObjectPool<T, Count>::ObjectPool() 
  : initialized_(false)
  , object_array_(nullptr)
  , block_list_head_(nullptr) {
}

template<typename T, size_t Count>
ObjectPool<T, Count>::~ObjectPool() {
  free(object_array_);
  block_list_head_ = nullptr;
}

template<typename T, size_t Count>
int ObjectPool<T, Count>::Init() {
  object_array_ = AllocateLinkBlock(kAllocateCount);
  if (object_array_ == nullptr) return -1;
  block_list_head_ = static_cast<Block*>(object_array_);
  initialized_ = true;
  return 0;
}

template<typename T, size_t Count>
T* ObjectPool<T, Count>::Allocate() {
  assert(initialized_);
  T* result = nullptr;
  if (block_list_head_ != nullptr) {
    void* object = reinterpret_cast<void*>(block_list_head_);
    block_list_head_ = block_list_head_->next;
    result = new (object) T; 
  }
  return result;
}

template<typename T, size_t Count>
void ObjectPool<T, Count>::Deallocate(T* object) {
  assert(initialized_ && object != nullptr);
  object->~T();
  Block* block = reinterpret_cast<Block*>(object);
  block->next = block_list_head_;
  block_list_head_ = block;
}

template<typename T, size_t Count>
void* ObjectPool<T, Count>::AllocateLinkBlock(size_t count) {
  size_t object_size = sizeof(T);
  size_t block_size = object_size > kMinObjectSize ? object_size : kMinObjectSize;
  Byte* memory = static_cast<Byte*>(malloc(block_size * count));
  if (memory != nullptr) {
    Block* block = reinterpret_cast<Block*>(memory);
    for (size_t i = 1; i <= count; ++i) {
      if (i != count) {
        block->next = reinterpret_cast<Block*>(memory + i * block_size);
        block = block->next;
      } else {
          block->next = nullptr;
      }
	}
  }
  return memory;
}

#endif // OBJECT_POOL_H_ 

