#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_
#include "HashEntry.h"
#include <iostream>
using namespace std;
template <class K, class T> class HashMap {
private:
  HashEntry<K, T> **table;

  unsigned int size;

  static unsigned int hashFunc(K clave);

  unsigned int (*hashFuncP)(K clave);

public:
  explicit HashMap(unsigned int size);

  HashMap(unsigned int size, unsigned int (*hashFuncP)(K clave));

  HashEntry<K,T> *get(K clave);

  void put(K clave, T valor);

  void remove(K clave);

  ~HashMap();

  bool esVacio();

  void print();

    bool operator==(const HashMap &rhs) const;

    bool operator!=(const HashMap &rhs) const;

    bool operator<(const HashMap &rhs) const;

    bool operator>(const HashMap &rhs) const;

    bool operator<=(const HashMap &rhs) const;

    bool operator>=(const HashMap &rhs) const;
};

template <class K, class T> HashMap<K, T>::HashMap(unsigned int size) {
  this->size = size;
  hashFuncP = hashFunc;
  table = new HashEntry<K, T> *[size];
  for (int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
}

template <class K, class T> HashMap<K, T>::~HashMap() {
  for (int i = 0; i < size; i++) {
    if (table[i] != nullptr) {
      delete table[i];
    }
  }
}

template <class K, class T> HashEntry<K,T> *HashMap<K, T>::get(K clave) {
  unsigned int pos = hashFuncP(clave) % size;
  if (table[pos] == nullptr) {
    throw 2;
  }
  return table[pos];
}

template <class K, class T> void HashMap<K, T>::put(K clave, T valor) {
  unsigned int pos = hashFuncP(clave) % size;

  if (table[pos] != nullptr) {
    HashEntry<K,T> *aux= new HashEntry<K, T>(clave, valor);
    aux->setnext(table[pos]);
    table[pos]=aux;
    return;
  }
  table[pos] = new HashEntry<K, T>(clave, valor);
}

template <class K, class T> void HashMap<K, T>::remove(K clave) {}

template <class K, class T> bool HashMap<K, T>::esVacio() {
  for (int i = 0; i < size; i++) {
    if (table[i] != nullptr) {
      return false;
    }
  }
  return true;
}

template <class K, class T> unsigned int HashMap<K, T>::hashFunc(K clave) {
  return (unsigned int)clave;
}

template <class K, class T>
HashMap<K, T>::HashMap(unsigned int size, unsigned int (*fp)(K)) {
  this->size = size;
  hashFuncP = fp;
  table = new HashEntry<K, T> *[size];
  for (int i = 0; i < size; i++) {
    table[i] = nullptr;
  }
}

template <class K, class T> void HashMap<K, T>::print() {
  for (int i = 0; i < size; i++) {
    cout << "Indice"
         << "\t"
         << "Clave"
         << "\t"
         << "Dato" << endl;
    cout << "____________________________________________" << endl;
    cout << i << "\t";
    if (table[i] != nullptr) {
      cout << table[i]->getKey() << "\t";
      cout << table[i]->getData();
    }
    cout << endl;
  }
}
#endif // U05_HASH_HASHMAP_HASHMAP_H_

template<class K, class T>
bool HashMap<K, T>::operator<(const HashMap &rhs) const {
    if (table < rhs.table)
        return true;
    if (rhs.table < table)
        return false;
    if (size < rhs.size)
        return true;
    if (rhs.size < size)
        return false;
    return hashFuncP < rhs.hashFuncP;
}

template<class K, class T>
bool HashMap<K, T>::operator>(const HashMap &rhs) const {
    return rhs < *this;
}

template<class K, class T>
bool HashMap<K, T>::operator<=(const HashMap &rhs) const {
    return !(rhs < *this);
}

template<class K, class T>
bool HashMap<K, T>::operator>=(const HashMap &rhs) const {
    return !(*this < rhs);
}
