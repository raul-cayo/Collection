#ifndef COLLECTION_HPP_INCLUDED
#define COLLECTION_HPP_INCLUDED

#include <iostream>
#include <exception>
#include "node.hpp"
using namespace std;

/// -------- EXCEPTIONS --------
class CollectionException : public exception {
  private:
    string msg;

  public:
    explicit CollectionException(const char* message) : msg(message) {}
    explicit CollectionException(const string& message): msg(message) {}
    virtual ~CollectionException() throw() {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

/// -------- COLLECTION PROTOTYPE --------
template<class T>
class Collection {
  private:
    Node<T>* anchor;
    int colLength;

    bool isValidPos(Node<T>*);
    void doExchange(Node<T>*, Node<T>*);
    void copyCollection(const Collection<T>&);

    void quickSort(Node<T>*, Node<T>*);

  public:
    Collection();
    Collection(const Collection<T>&);
    ~Collection();

    bool isEmpty();

    int length();

    void insertData(const T&, Node<T>*);
    void deleteData(Node<T>*);
    T retrieve(Node<T>*);

    T& operator [] (const int&);
    T& operator = (const Collection<T>&);

    Node<T>* getFirstPos();
    Node<T>* getLastPos();
    Node<T>* getNextPos(Node<T>*);
    Node<T>* getPrevPos(Node<T>*);

    //Queue methods
    void enqueue(const T&);
    T dequeue();
    T getFront();

    //Stack methods
    void push(const T&);
    T pop();
    T getTop();

    void insertSort();
    void quickSort();

    Node<T>* findDataLinear(const T&);

    void printCollection(); //For std data types
    string toString(); //For objects with toString() method

    void deleteAll();
};

/// -------- COLLECTION IMPLEMENTATION --------

/// Private Methods
template<class T>
bool Collection<T>::isValidPos(Node<T>* p) {
    Node<T>* aux(anchor);
    while(aux != nullptr) {
        if(aux == p) {
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template<class T>
void Collection<T>::doExchange(Node<T>* a, Node<T>* b) {
    T aux;

    aux = a->getData();
    a->setData(b->getData());
    b->setData(aux);
}

template<class T>
void Collection<T>::copyCollection(const Collection<T>& c) {
    Node<T>* aux(c.anchor);
    while(aux != nullptr) {
        insertData(aux->getData(), getLastPos());
        aux = aux->getNext();
    }
}

template<class T>
void Collection<T>::quickSort(Node<T>* leftEdge, Node<T>* rightEdge) {
    if(leftEdge == rightEdge) {
        return;
    }

    Node<T>* i(leftEdge);
    Node<T>* j(rightEdge);
    while(i != j) {
        while(i != j && i->getData() >= rightEdge->getData()) {
            i = i->getNext();
        }
        while (i != j && j->getData() <= rightEdge->getData()) {
            j = j->getPrev();
        }
        if(i != j) {
            doExchange(i, j);
        }
    }
    if(i != rightEdge) {
        doExchange(i, rightEdge);
    }

    if(i != leftEdge) {
        quickSort(leftEdge, i->getPrev());
    }
    if(i != rightEdge) {
        quickSort(i->getNext(), rightEdge);
    }
}

///Public Methods
template<class T>
Collection<T>::Collection() : anchor(nullptr), colLength(0) {}

template<class T>
Collection<T>::Collection(const Collection<T>& c) : anchor(nullptr), colLength(0) {
    copyCollection(c);
}

template<class T>
Collection<T>::~Collection() {
    deleteAll();
}

template<class T>
bool Collection<T>::isEmpty() {
    return anchor == nullptr;
}

template<class T>
int Collection<T>::length() {
    return colLength;
}

template<class T>
void Collection<T>::insertData(const T& e, Node<T>* p) {
    if(p != nullptr && !isValidPos(p)) {
        throw CollectionException("insertData: invalid position.");
    }

    Node<T>* aux = new Node<T>(e);
    if(aux == nullptr) {
        throw CollectionException("insertData: memory not available.");
    }

    if(p == nullptr) { //insertando al inicio
        //prev se inicializo nulo
        if(anchor != nullptr) {
            aux->setNext(anchor);
            anchor->setPrev(aux);
        }
        anchor = aux;
    } else {
        aux->setNext(p->getNext());
        aux->setPrev(p);
        if(p->getNext() != nullptr) {
            p->getNext()->setPrev(aux);
        }
        p->setNext(aux);
    }
    colLength++;
}

template<class T>
void Collection<T>::deleteData(Node<T>* p) {
    if(!isValidPos(p)) {
        throw CollectionException("deleteData: invalid position.");
    }

    if(p->getPrev() != nullptr) {
        p->getPrev()->setNext(p->getNext());
    } else {
        anchor = p->getNext();
    }

    if(p->getNext() != nullptr) {
        p->getNext()->setPrev(p->getPrev());
    }

    delete p;
    colLength--;
}

template<class T>
T Collection<T>::retrieve(Node<T>* p) {
    if(!isValidPos(p)) {
        throw CollectionException("retrive: invalid position.");
    }

    return p->getData();
}

template<class T>
T& Collection<T>::operator [] (const int& pos) {
    if(pos >= colLength || pos < 0) {
        throw CollectionException("operator []: invalid position");
    }

    Node<T>* aux(anchor);
    int index(0);
    while(index != pos) {
        aux = aux->getNext();
        index++;
    }

    return aux->getData();
}

template<class T>
T& Collection<T>::operator = (const Collection<T>& c) {
    deleteAll();
    copyCollection(c);
}


template<class T>
Node<T>* Collection<T>::getFirstPos() {
    return anchor;
}

template<class T>
Node<T>* Collection<T>::getLastPos() {
    if(isEmpty()) {
        return nullptr;
    }

    Node<T>* aux(anchor);
    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
Node<T>* Collection<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p)) {
        return nullptr;
    }

    return p->getNext();
}

template<class T>
Node<T>* Collection<T>::getPrevPos(Node<T>* p) {
    if(!isValidPos()) {
        return nullptr;
    }

    return p->getPrev();
}

template<class T>
void Collection<T>::enqueue(const T& e) {
    insertData(e, getLastPos());
}

template<class T>
T Collection<T>::dequeue() {
    T aux(retrieve(getFirstPos()));
    deleteData(getFirstPos());
    return aux;
}

template<class T>
T Collection<T>::getFront() {
    return retrieve(getFirstPos());
}

template<class T>
void Collection<T>::push(const T& e) {
    insertData(e, getLastPos());
}

template<class T>
T Collection<T>::pop() {
    T aux(retrieve(getLastPos()));
    deleteData(getLastPos());
    return aux;
}

template<class T>
T Collection<T>::getTop() {
    return retrieve(getLastPos());
}

template<class T>
void Collection<T>::insertSort() {
    Node<T>* i(getNextPos(getFirstPos()));
    Node<T>* j;
    T aux;

    while(i != nullptr) {
        aux = i->getData();
        j = i;

        while(j != getFirstPos() && aux < j->getPrev()->getData()) {
            j->setData(j->getPrev()->getData());
            j = j->getPrev();
        }
        if(i != j) {
            j->setData(aux);
        }
        i = i->getNext();
    }
}

template<class T>
void Collection<T>::quickSort() {
    quickSort(getFirstPos(), getLastPos());
}

template<class T>
Node<T>* Collection<T>::findDataLinear(const T& e) {
    Node<T>* aux(anchor);

    while(aux != nullptr) {
        if(aux->getData() == e) {
            return aux;
        }

        aux = aux->getNext();
    }

    return nullptr;
}

template<class T>
void Collection<T>::printCollection() {
    Node<T>* aux(anchor);

    while(aux != nullptr) {
        cout << aux->getData() << "\t";

        aux = aux->getNext();
    }
}

template<class T>
string Collection<T>::toString() {
    string result;
    Node<T>* aux(anchor);

    while(aux != nullptr) {
        result += aux->getData().toString();
        result += '\n';

        aux = aux->getNext();
    }
    return result;
}

template<class T>
void Collection<T>::deleteAll() {
    Node<T>* aux;

    while(anchor != nullptr) {
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
    colLength = 0;
}

#endif // COLLECTION_HPP_INCLUDED
