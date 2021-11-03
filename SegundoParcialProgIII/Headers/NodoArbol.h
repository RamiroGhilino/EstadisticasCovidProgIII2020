#ifndef U06_ARBOL_ARBOL_NODOARBOL_H_
#define U06_ARBOL_ARBOL_NODOARBOL_H_

template <class T> class NodoArbol {
private:
  T data;
  NodoArbol *left, *right;

public:
  NodoArbol(){
    left= nullptr;
    right= nullptr;
  }

  NodoArbol(T d){
    data=d;
    left= nullptr;
    right= nullptr;
  }

  T getData() const{
    return data;
  }

  void setData(T d){
    this->data=d;
  }

  NodoArbol *getRight() const{
    return right;
  }

  void setRight(NodoArbol *r){
    this->right= r;
  }

  NodoArbol *getLeft() const{
    return left;
  }

  void setLeft(NodoArbol *l){
    this->left= l;
  }

};

#endif // U06_ARBOL_ARBOL_NODOARBOL_H_
