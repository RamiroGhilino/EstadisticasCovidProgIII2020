#ifndef U06_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U06_ARBOL_ARBOL_ARBOLBINARIO_H_

#include "NodoArbol.h"
#include <iostream>
using namespace std;

template <class T> class ArbolBinario {
private:
  NodoArbol<T> *root;

public:
  ArbolBinario();

  void put(T data);

  T search(T data);

  void remove(T data);

  void preorder();

  void inorder();

  void postorder();

  ~ArbolBinario();

  bool esVacio();

  void print();

  int ContarPorNivel();



private:
  T search(T data, NodoArbol<T> *r);

  NodoArbol<T> *put(T data, NodoArbol<T> *r);

  NodoArbol<T> *remove(T data, NodoArbol<T> *r);

  NodoArbol<T> *findMax(NodoArbol<T> *r, bool *found);

  void preorder(NodoArbol<T> *r);

  void inorder(NodoArbol<T> *r);

  void postorder(NodoArbol<T> *r);

  int ContarPorNivel(NodoArbol<T> *r);

};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T> ArbolBinario<T>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T> ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T> T ArbolBinario<T>::search(T data) {
  return search(data, root);
}
template <class T> T ArbolBinario<T>::search(T data, NodoArbol<T> *r) {
  if (r == nullptr) {
    throw 404;
  }
  if (r->getData() == data) {
    return r->getData();
  }
  if (r->getData() > data) {
    return search(data, r->getLeft());
  } else {
    return search(data, r->getRight());
  }
}
/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T> void ArbolBinario<T>::put(T data) { root = put(data, root); }

template <class T> NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r) {
  if (r == nullptr) {
    return new NodoArbol<T>(data);
  }
  if (r->getData() == data) {
    throw 200;
  }
  if (r->getData() > data) {
    r->setLeft(put(data, r->getLeft()));
  } else {
    r->setRight(put(data, r->getRight()));
  }

  return r;
}
/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T> void ArbolBinario<T>::remove(T data) {
  root = remover(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r) {
  NodoArbol<T> *aux;

  if (r == nullptr) {
    throw 404;
  }
  if (r->getData() == data) {
    if (r->getLeft() == nullptr && r->getRight() == nullptr) {
      delete r;
      return nullptr;
    } else if (r->getLeft() != nullptr && r->getRight() == nullptr) {
      aux = r->getLeft();
      delete r;
      return aux;

    } else if (r->getLeft() == nullptr && r->getRight() != nullptr) {
      aux = r->getRight();
      delete r;
      return aux;

    } else if (r->getLeft() != nullptr && r->getRight() != nullptr) {
      if (r->getLeft()->getRight() != nullptr) {
        bool found;
        aux = findMax(r->getLeft(), &found);
        aux->setRight(r->getRight());
        aux->setLeft(r->getLeft());
      } else {
        aux = r->getLeft();
        r->getLeft()->setRight(r->getRight());
      }
      delete r;
      return aux;
    }
  } else if (r->getData() > data) {
    r->setLeft(remove(data, r->getLeft()));
  } else {
    r->setRight(remove(data, r->getRight()));
  }

  return r;
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::findMax(NodoArbol<T> *r, bool *found) {
  NodoArbol<T> ret;
  *found = false;

  if (r->getRight() == nullptr) {
    *found = true;
    return r;
  }
  ret = findMax(r->getRight(), found);
  if (*found) {
    r->setRight(nullptr);
    *found = false;
  }

  return ret;
}
/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T> bool ArbolBinario<T>::esVacio() {
  return root== nullptr;
}

/**
 * Recorre un árbol en preorden
 */
template <class T> void ArbolBinario<T>::preorder() {
  preorder(root);
}

template <class T> void ArbolBinario<T>::preorder(NodoArbol<T> *r) {
  if(r == nullptr){
    return;
  }

  cout<<r->getData()<<" ";
  preorder(r->getLeft());
  preorder(r->getRight());

}

/**
 * Recorre un árbol en orden
 */
template <class T> void ArbolBinario<T>::inorder() {
inorder(root);
}

template <class T> void ArbolBinario<T>::inorder(NodoArbol<T> *r){
  if(r == nullptr){
    return;
  }
  inorder(r->getLeft());
  cout<<r->getData()<<" ";
  inorder(r->getRight());
}
/**
 * Recorre un árbol en postorden
 */
template <class T> void ArbolBinario<T>::postorder() {
postorder(root);
}

template <class T> void ArbolBinario<T>::postorder(NodoArbol<T> *r){
  if(r == nullptr){
    return;
  }
  postorder(r->getLeft());
  postorder(r->getRight());
  cout<<r->getData()<<" ";
}

/**
 * Muestra un árbol por consola
 */
template <class T> void ArbolBinario<T>::print() {}

template <class T> int ArbolBinario<T>::ContarPorNivel() {
  return ContarPorNivel(root);
}

template <class T> int ArbolBinario<T>::ContarPorNivel(NodoArbol<T> *r){
int a,b;
if(r== nullptr){
  return 0;
}
if(r->getLeft()== nullptr && r->getRight()== nullptr){
  return 1;
}else{
  a=ContarPorNivel(r->getLeft());
  b=ContarPorNivel(r->getRight());
  if(a<b){
    return b+1;
  }else{
    return a+1;
  }
}

}

#endif // U06_ARBOL_ARBOL_ARBOLBINARIO_H_
