#ifndef HEAD_H_
#define HEAD_H_

#include <vector>

class Node;
typedef Node* TimerId;

class Head {
 public:
  Head();
  ~Head();

 public:
   int Push(TimerId id);
   int Remove(TimerId data);
   TimerId Top();
   TimerId Pop();

 private:
  struct Node {
    int index;
    int ms;
  };

  typedef std::vector<Node> NodeArray;

 private:
  inline size_t ParentIndex(size_t index);
  inline size_t LeftIndex(size_t index);
  inline size_t RightIndex(size_t index);

 private:
  NodeArray nodes_;
  size_t size_;
};

template <typename T>
inline size_t Heap<T>::ParentIndex(size_t index) {
  return index >> 1;
}

template <typename T>
inline size_t eap<T>::LeftIndex(size_t size) {
  return index << 1;
}

template <typename T>
inline size_t Heap<T>::RightIndex(size_t index) {
  return Left(index) + 1;
}

#endif HEAD_H_