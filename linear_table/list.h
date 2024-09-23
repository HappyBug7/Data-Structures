#include<iostream>
#include"singly_linked_list.h"
#include"doubly_linked_list.h"
#include"array.h"

template<template<typename> class StorageStructure, typename T>
class LinearList {
private:
  StorageStructure<T>* linear_list;
  
  /**
   * @brief bubble sort
   */
  void bubble_sort() {
    linear_list -> bubble_sort();
  }

  void quick_sort() {
    linear_list -> quick_sort(0, linear_list -> get_size()-1);
  }

public:
  /**
   * @brief generate a linear list with certain capasity
   * @param capasity 
   */
  LinearList(int capasity) {
    linear_list = new StorageStructure<T>(capasity);
  }

  /**
   * @brief generate a linear list with a storage structure instance
   * @param linear_list_new 
   */
  LinearList(StorageStructure<T>* linear_list_new) {
    linear_list = linear_list_new;
  }

  /**
   * @brief insert an element with certain value at a certain index
   * @param idx the index where the element is inserted
   * @param val the value
   */
  void insert(int idx, T val) {
    linear_list -> insert(idx, val);
  }

  /**
   * @brief push an element at the end of the linear list
   * @param val the value of the element
   */
  void push_back(T val) {
    linear_list -> push_back(val);
  }
  friend LinearList<StorageStructure, T> operator>>(const T& val, LinearList<StorageStructure, T> list) {
    list.linear_list -> push_back(val);
    return list;
  }

  /**
   * @brief push an element at the start of the linear list
   * @param val the value of the element
   */
  void push_front(T val) {
    linear_list -> push_front(val);
  }

  /**
   * @brief remove the element at the certain index
   * @param idx the index of the element
   */
  void remove(int idx) {
    linear_list -> delete_at_idx(idx);
  }

  /**
   * @brief update the value of the element at certain index
   * @param idx the index of the element
   * @param val the new value of the element
   */
  void update(int idx, T val) {
    linear_list -> update(idx, val);
  }

  /**
   * @brief return the index of the first elemet with same value, return -1 when there is no such element
   * @param val the object value 
   */
  int search(T val) {
    return linear_list -> search(val);
  }

  /**
   * @brief return whether the linear list is full or not
   */
  bool is_full() {
    return linear_list -> is_full();
  }

  /**
   * @brief return whether the linear list is empty or not
   */
  bool is_empty() {
    return linear_list -> is_empty();
  }

  int get_size() {
    return linear_list -> get_size();
  }

  /**
   * @brief return the previous element's value of the element at the certain index
   * @param idx the index
   */
  T prev(int idx) {
    return linear_list -> prev();
  }

  /**
   * @brief return the next element's value of the element at the certain index
   * @param idx the index
   */
  T next(int idx) {
    return linear_list -> next();
  }

  /**
   * @brief get the value of the element at idx
   * @param idx the index
   */
  T index(int idx) {
    return linear_list -> index(idx);
  }
  T operator[](int idx) {
    return index(idx);
  }


  /**
   * @brief print the whole list, and the form will differ between different storage structure
   */
  void print_list() {
    linear_list -> print_list();
  }
  friend std::ostream& operator<<(std::ostream& os, const LinearList<StorageStructure, T>& list) {
    list.linear_list -> print_list(os);
    return os;
  }

  /**
   * @brief copy the whole list to another list
   * @param L the receiver list
   */
  void duplicate(const LinearList& L) {
    linear_list -> duplicate(L.linear_list);
  }
  static void duplicate(const LinearList& from, LinearList& to) {
    StorageStructure<T>::duplicate(from.linear_list, to.linear_list);
  }

  LinearList& operator=(const LinearList& L) {
    if (this != &L) {
      LinearList<StorageStructure, T>::duplicate(L, *this);
    }
    return *this;
  }

  /**
   * @brief merge two list into one, and return
   * @param L1 the first list
   * @param L2 the second list 
   */
  static LinearList<StorageStructure, T>* merge(LinearList<StorageStructure, T> L1, LinearList<StorageStructure, T> L2) {
    StorageStructure<T>* linear_list_new = StorageStructure<T>::merge(L1.linear_list, L2.linear_list);
    return new LinearList(linear_list_new);
  }
  LinearList operator+(LinearList& other) {
    return *merge(*this, other);
  }

  /**
   * @brief dispose the list into two lists, the first list end at index-1, the second begin at index
   * @param L1 the first list receiver
   * @param L2 the second list receiver
   * @param idx the break index
   */
  void dispose(LinearList<StorageStructure, T>& L1, LinearList<StorageStructure, T>& L2, int idx) {
    linear_list -> dispose(L1.linear_list, L2.linear_list, idx);
  }

  /**
   * @brief sort the list where the list starts with the smallist element, end with the biggest element
   * @param sort_function an string indecating which sort function to use
   */
  void sort(std::string sort_function) {
    if (sort_function == "bubble") {
      bubble_sort();
      return;
    }
    if (sort_function == "quick") {
      quick_sort();
      return;
    }
  }


};
