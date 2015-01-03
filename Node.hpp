#ifndef NODE_HPP
#define NODE_HPP
template<typename T>
struct Node
{
  T info;
  Node<T> *next;
};

#endif // NODE_HPP
