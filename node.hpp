#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

template<class T>
class Node {
  private:
    T data;
    Node<T>* next;
    Node<T>* prev;

  public:
    Node();
    Node(const T&);

    void setData(const T&);
    void setNext(Node<T>*);
    void setPrev(Node<T>*);

    T& getData();
    Node<T>* getNext();
    Node<T>* getPrev();
};


/// -------------NODE IMPLEMENTATION---------------

template<class T>
Node<T>::Node() : next(nullptr), prev(nullptr) {}

template<class T>
Node<T>::Node(const T& e) : data(e), next(nullptr), prev(nullptr) {}

template<class T>
void Node<T>::setData(const T& e) {
    data = e;
}

template<class T>
void Node<T>::setNext(Node<T>* p) {
    next = p;
}

template<class T>
void Node<T>::setPrev(Node<T>* p) {
    prev = p;
}

template<class T>
T& Node<T>::getData() {
    return data;
}

template<class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template<class T>
Node<T>* Node<T>::getPrev() {
    return prev;
}


#endif // NODE_HPP_INCLUDED
