//
// Created by ser on 4/22/24.
//

#ifndef UNTITLED__PRINTER_H_
#define UNTITLED__PRINTER_H_
#include <iostream>
#include <vector>
#include <map>

template<typename T>
void printImpl(const T &o) {
  std::cout << o << ' ';
}

template<typename T>
void printImpl(const std::vector<T> &vec) {
  char sep = '{';
  cout << sep;
  for (const auto &innerVector : vec) {
    printImpl(innerVector);
    sep = ',';
  }
  std::cout << "}";
}

template<typename K, typename V>
void printImpl(const std::map<K, V> &cont) {
  char sep = '{';
  std::cout << sep;
  for (auto &&[k, v] : cont) {
    printImpl(k);
    std::cout << ":";
    printImpl(v);
    sep = ',';
  }
  std::cout << "}";
}

template<typename K, typename V>
void printImpl(const std::unordered_map<K, V> &cont) {
  char sep = '{';
  std::cout << sep;
  for (auto &&[k, v] : cont) {
    printImpl(k);
    std::cout << ":";
    printImpl(v);
    sep = ',';
  }
  std::cout << "}";
}
template<typename V>
void printImpl(const std::set<V> &cont) {
  char sep = '{';
  std::cout << sep;
  for (auto &v : cont) {
    printImpl(v);
    sep = ',';
  }
  std::cout << "}";
}
template<typename V>
void printImpl(const std::unordered_set<V> &cont) {
  char sep = '{';
  std::cout << sep;
  for (auto &v : cont) {
    printImpl(v);
    sep = ',';
  }
  std::cout << "}";
}

template<typename V>
void printImpl(const std::unordered_multiset<V> &cont) {
  char sep = '{';
  std::cout << sep;
  for (auto &v : cont) {
    printImpl(v);
    sep = ',';
  }
  std::cout << "}";
}

template<typename... Args>
void print(Args &&... args) {
  (printImpl(std::forward<Args>(args)), ...);
}

#endif //UNTITLED__PRINTER_H_
