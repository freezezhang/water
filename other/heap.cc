#include "Heap.h"

template<typename T>
Head<T>::Head() {
  nodes_.reserve(1024);
}

template<typename T>
Head<T>::~Head() {
}

template<typename T>
int Head<T>::Push(T& data) {
  nodes_.resize(size_.size());
  nodes_.rbegin()->data = data;
}

template<typename T>
int Head<T>::Remove(T& data) {
}

template<typename T>
const T& Head<T>::Top() {
}

template<typename T>
T& Head<T>::Top() {
}

template<typename T>
int Head<T>::Pop() {
}