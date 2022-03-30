#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include "node.hpp"
#include<cassert>
#include<iostream>

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList(){
    head_ = nullptr;
    tail_ = nullptr;
    node_order_ = Order::kASC;
  }
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void KASC(const T& data);
  void KDESC(const T& data);
  void Reverse();
  void ChangeOrder() {
    if(node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
  }

  void PushBack(const T& data);
  Node<T>* GetHead(){return head_;}
  Node<T>* GetTail(){return tail_;}
  int GetSize();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << "adress: " <<  iter << " data: "<< iter->data  << " next adress: " << iter->next << " next data: " << iter->next->data << '\n';
    //os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}


template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source){
  if(source.head_ == nullptr) {
    return;
  }
  if(source.head_ == source.tail_) {
    head_ = new Node<T> (source.head_->data);
    tail_ = head_;
    tail_->next = head_;
    return;
  }
  Node<T>* temp = source.head_;
  while(temp->next != source.head_) {
    PushBack(temp->data);
    temp=temp->next;
  }
  PushBack(temp->data);
  tail_->next = head_;
  node_order_ = source.node_order_;
}

template <typename T>
void CircularLinkedList<T>::PushBack(const T& data){
   if (head_ == nullptr) {
    head_ = tail_ = new Node<T>(data);
   } else {
      Node<T>* tmp = new Node<T>(data);
      tail_->next = tmp;
      tail_ = tmp;
   }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source){
  if(source.head_ == nullptr || this == &source) {
    return *this;
  }
  if(source.head_ == source.tail_) {
    delete head_;
    head_ = new Node<T>(source.head_->data);
    tail_ = head_;
    tail_->next = head_;
    return *this;
  }

  if(head_!=nullptr) {
    tail_->next = nullptr;
    Node<T>* to_delete = head_;
    while (head_ != nullptr){
      to_delete = head_;
      head_ = head_->next;
      delete[] to_delete;
    }
    head_ = nullptr;
    node_order_ = Order::kASC;
  }
  

  if(source.head_ == source.tail_) {
    head_ = new Node<T> (source.head_->data);
    tail_ = head_;
    tail_->next = head_;
    return *this;
  }
  Node<T>* temp = source.head_;
  while(temp->next != source.head_) {
    PushBack(temp->data);
    temp=temp->next;
  }
  PushBack(temp->data);
  tail_->next = head_;
  node_order_ = source.node_order_;
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList(){
  if(head_ == nullptr){
    return;
  }
  tail_->next = nullptr;
  Node<T>* to_delete = head_;
  while (head_ != nullptr){
    to_delete = head_;
    head_ = head_->next;
    delete[] to_delete;
  }
  head_ = nullptr;
  node_order_ = Order::kASC;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data){
  if(node_order_ == Order::kASC){
    KASC(data);
  } else {
    KDESC(data);
  }
}

template <typename T>
void CircularLinkedList<T>::KASC(const T& data){
  Node<T>* temp = new Node<T>(data);
  if(head_ == nullptr) {
    head_ = tail_ = temp;
    tail_->next = head_;
    return;
  } else if(head_->data >= data) {
    temp->next = head_;
    head_ = temp;
    tail_->next = head_;
    return;
  } else if(tail_->data <= data) {
    tail_->next = temp;
    tail_ = temp;
    tail_->next = head_;
    return;
  } else {
    Node<T>* current = head_;
    while (current->next != head_ && current->next->data <= data){
      current = current->next;
    }
    temp -> next = current -> next;
    current -> next = temp;
  }
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::KDESC(const T& data){
  Node<T>* temp = new Node<T>(data);
  if(head_ == nullptr) {
    head_ = tail_ = temp;
    tail_->next = head_;
    return;
  } else if(head_->data <= data) {
    temp->next = head_;
    head_ = temp;
    tail_->next = head_;
    return;
  } else if(tail_->data >= data) {
    tail_->next = temp;
    tail_ = temp;
    tail_->next = head_;
    return;
  } else {
    Node<T>* current = head_;
    while (current->next != head_ && current->next->data >= data){
      current = current->next;
    }
    temp -> next = current -> next;
    current -> next = temp;
  }
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::Reverse(){
  if(head_== nullptr || tail_ == head_) {
    if(node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
    return;
  }
  int size = GetSize();
  Node<T>* pre = head_;
  Node<T>* current = head_->next;
  Node<T>* tmp_pre = nullptr;
  Node<T>* tmp = nullptr;
  for(int i = 0; i<size; i++) {
    tmp_pre=current;
    tmp=current->next;
    current->next = pre;
    pre = tmp_pre;
    current = tmp;
  }
  head_->next = tail_;
  if(node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  Node<T>* new_head = tail_;
  tail_= head_;
  head_ = new_head;
}

template <typename T>
int CircularLinkedList<T>::GetSize() {
  if(head_ == nullptr) {
    return 0;
  } else if(head_ == tail_) {
    return 1;
  }
  int size = 1;
  Node<T>* current = head_;
  while(current->next != head_){
    size++;
    current = current->next;
  }
  return size;
}

#endif
