/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class DLinkedList : public IList<T>{
    public:
        class Node;
        class Iterator;
        class BWDIterator;
    protected:
        Node *head;
        Node *tail;
        int count;
        bool (*itemEqual)(T &lhs, T &rhs);
        void (*deleteUserData)(DLinkedList<T> *);
    public:
        DLinkedList(void (*deleteUserData)(DLinkedList<T> *)=0, bool (*itemEqual)(T &, T &)=0);
        DLinkedList(const DLinkedList<T> &list);
        DLinkedList<T> &operator=(const DLinkedList<T> &list);
        ~DLinkedList();
        void add(T e);
        void add(int index, T e);
        void deleteAllNode(Node* &head){
            while (this->head!=NULL){
                Node* tmp=this->head;
                head=head->next;
                delete tmp;
            }
        }
        T removeAt(int index);
        bool removeItem(T item, void (*removeItemData)(T)=0);
        bool empty();
        int size();
        void clear();
        T &get(int index);
        int indexOf(T item);
        bool contains(T item);
        string convert(T item){
            stringstream ss;
            ss << item;
            return ss.str();
        }
        string toString(string (*item2str)(T &)=0);
        void println(string (*item2str)(T &)=0){cout << toString(item2str) << endl;}
        void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0){this->deleteUserData = deleteUserData;}
        bool contains(T array[], int size){
            int idx = 0;
            for (DLinkedList<T>::Iterator it=begin(); it!=end(); it++) {
                if (!equals(*it, array[idx++], this->itemEqual)) return false;
            }
            return true;
        }
        Iterator begin() {return Iterator(this, true);}
        Iterator end() {return Iterator(this, false);}
        BWDIterator bbegin() {return BWDIterator(this, true);}
        BWDIterator bend() {return BWDIterator(this, false);}
    protected:
        void copyFrom(const DLinkedList<T> &list);
        void removeInternalData();
        Node *getPreviousNodeOf(int index);
    public:
        static void free(DLinkedList<T> *list){
            typename DLinkedList<T>::Iterator it = list->begin();
            while (it != list->end()){
                delete *it;
                it++;
            }
        }
    protected:
        static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &)){
            if (itemEqual == 0) return lhs == rhs;
            else return itemEqual(lhs, rhs);
        }
    public:
        class Node{
            public:
                T data;
                Node *next;
                Node *prev;
                friend class DLinkedList<T>;
            public:
                Node(Node *next = 0, Node *prev = 0){
                    this->next=next;
                    this->prev=prev;
                }
                Node(T data, Node *next = 0, Node *prev = 0){
                    this->data=data;
                    this->next=next;
                    this->prev=prev;
                }
        };
    public:
        class Iterator{
            private:
                DLinkedList<T> *pList;
                Node *pNode;
            public:
                friend class DLinkedList<T>;
                Iterator(DLinkedList<T> *pList=0, bool begin=true){
                    if (begin){
                        if (pList!=0) this->pNode = pList->head->next;
                        else pNode = 0;
                    } 
                    else{
                        if (pList != 0) this->pNode = pList->tail;
                        else pNode = 0;
                    }
                    this->pList = pList;
                }
                Iterator &operator=(const Iterator &iterator){
                    this->pNode = iterator.pNode;
                    this->pList = iterator.pList;
                    return *this;
                }
                void remove(void (*removeItemData)(T) = 0){
                    if (pNode==pList->head){
                        Node *pNext = pNode;
                        pNode=pNode->next;
                        pList->head=pNode;
                        if (removeItemData != 0) removeItemData(pNext->data);
                        delete pNext;
                    }
                    else if (pNode->next==pList->tail->next){
                        Node *pNext = pNode;
                        pNode=pNode->prev;
                        pList->tail=pNode;
                        if (removeItemData != 0) removeItemData(pNext->data);
                        delete pNext;
                    }
                    else{
                        pNode->prev->next = pNode->next;
                        pNode->next->prev = pNode->prev;
                        Node *pNext = pNode->prev;
                        if (removeItemData != 0) removeItemData(pNode->data);
                        delete pNode;
                        pNode = pNext;
                    }
                    pList->count -= 1;
                }
                T &operator*() {return pNode->data;}
                bool operator!=(const Iterator &iterator){return pNode != iterator.pNode;}
                Iterator &operator++(){
                    pNode = pNode->next;
                    return *this;
                }
                Iterator operator++(int){
                    Iterator iterator = *this;
                    ++*this;
                    return iterator;
                }
        };
        class BWDIterator{
            private:
                Node* currentNode;
                DLinkedList<T> *pList;
            public:
                friend class DLinkedList<T>;
                BWDIterator(DLinkedList<T> *pList, bool begin){
                    if (begin){
                        if (pList!=0) this->currentNode = pList->tail->prev;
                        else currentNode=0;
                    } 
                    else{
                        if (pList != 0) this->currentNode = pList->head;
                        else currentNode = 0;
                    }
                    this->pList = pList;
                }
                BWDIterator &operator=(const BWDIterator &iterator){
                    this->currentNode = iterator.currentNode;
                    this->pList = iterator.pList;
                    return *this;
                }
                T &operator*() {return currentNode->data;}
                bool operator!=(const BWDIterator &iterator){return currentNode != iterator.currentNode;}
                BWDIterator &operator++(){
                    currentNode = currentNode->prev;
                    return *this;
                }
                BWDIterator operator++(int){
                    BWDIterator iterator = *this;
                    ++*this;
                    return iterator;
                }
                void remove(void (*removeItemData)(T) = 0){
                    currentNode->prev->next = currentNode->next;
                    currentNode->next->prev = currentNode->prev;
                    Node *pNext = currentNode->next;
                    if (removeItemData != 0) removeItemData(currentNode->data);
                    delete currentNode;
                    currentNode = pNext;
                    pList->count -= 1;
                }
        };
};

template <class T>
using List = DLinkedList<T>;

template <class T>
DLinkedList<T>::DLinkedList(void (*deleteUserData)(DLinkedList<T> *), bool (*itemEqual)(T &, T &)) {
    this->head=new Node(), this->tail=new Node();
    head->next=tail;
    tail->prev=head;
    this->count=0;
    this->itemEqual=itemEqual;
    this->deleteUserData=deleteUserData;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list) : itemEqual(list.itemEqual), deleteUserData(list.deleteUserData), count(0){
    this->head=new Node(), this->tail=new Node();
    head->next=tail;
    tail->prev=head;
    Node* tmp=list.head->next;
    while (tmp!=list.tail){
        this->add(tmp->data);
        tmp=tmp->next;
    }
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list) {
    if (this!=&list){
        if (this->deleteUserData!=NULL) this->deleteUserData(this);
        this->deleteAllNode(this->head);
        this->count=list.count;
        this->itemEqual=list.itemEqual;
        this->deleteUserData=list.deleteUserData;
        this->head=new Node(), this->tail=new Node();
        head->next=tail;
        tail->prev=head;
        Node* tmp=list.head->next;
        while (tmp->next!=NULL){
            this->add(tmp->data);
            tmp=tmp->next;
        }
    }
    return *this;
}

template <class T>
DLinkedList<T>::~DLinkedList(){
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    this->deleteAllNode(this->head);
}

template <class T>
void DLinkedList<T>::add(T e) {
    Node* newNode=new Node(e);
    this->tail->prev->next=newNode;
    newNode->next=this->tail;
    newNode->prev=this->tail->prev;
    this->tail->prev=newNode;
    ++count;
}

template <class T>
void DLinkedList<T>::add(int index, T e) {
    if (index<0||index>count) throw out_of_range("Index is out of range!");
    Node* newNode=new Node(e);
    Node* tmp=this->head->next;
    if (index==0){      
        newNode->next=head->next;
        head->next=newNode;
        newNode->prev=head;
        newNode->next->prev=newNode;
    }
    else if (index==count){
        newNode->next=tail;
        tail->prev->next=newNode;
        newNode->prev=tail->prev;
        newNode->next->prev=newNode;
    }
    else{
        for (int i=0 ; i<index ; i++) tmp=tmp->next;
        newNode->next=tmp;
        tmp->prev->next=newNode;
        newNode->prev=tmp->prev;
        tmp->prev=newNode;
    }
    ++count;
}

template <class T>
T DLinkedList<T>::removeAt(int index) {
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
    Node* tmp=head->next;
    for (int i=0 ; i<index ; i++) tmp=tmp->next;
    tmp->prev->next=tmp->next;
    tmp->next->prev=tmp->prev;
    T res=tmp->data;
    delete tmp;
    --count;
    return res;
}

template <class T>
bool DLinkedList<T>::empty() { return this->count==0; }

template <class T>
int DLinkedList<T>::size() { return this->count; }

template <class T>
void DLinkedList<T>::clear() {
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    Node* tmp=head->next;
    while (tmp!=tail){
        Node* res=tmp;
        tmp=tmp->next;
        delete res;
    }
    head->next=tail;
    tail->prev=head;
    this->count=0;
}

template <class T>
T &DLinkedList<T>::get(int index) {
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
    Node* tmp=head->next;
    for (int i=0 ; i<index ; i++) tmp=tmp->next;
    return tmp->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item) {
    Node* tmp=head->next;
    for (int i=0 ; i<count ; i++){
        if (this->equals(item,tmp->data,itemEqual)) return i;
        tmp=tmp->next;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T)) {
    Node* tmp=head->next;
    for (int i=0 ; i<count ; i++){
        if (this->equals(item,tmp->data,itemEqual)){
            if (removeItemData!=NULL) removeItemData(tmp->data);
            this->removeAt(i);
            return true;                
        }
        tmp=tmp->next;
    }
    return false;
}

template <class T>
bool DLinkedList<T>::contains(T item) {
    return this->indexOf(item)!=-1;
}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &)){
    Node* tmp=head->next;
    string result="[";
    for (int i=0; i<count; i++){
        if (item2str==NULL) result+=convert(tmp->data);
        else result+=item2str(tmp->data);
        if (i!=count-1) result+=", ";
        tmp=tmp->next;
    }
    result+="]";
    return result;
}

template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list) {
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    this->deleteAllNode(this->head);
    this->capacity=list.capacity;
    this->count=list.count;
    this->itemEqual=list.itemEqual;
    this->deleteUserData=list.deleteUserData;
    this->head=new Node(), this->tail=new Node();
    head->next=tail;
    tail->prev=head;
    Node* tmp=list.head->next;
    while (tmp->next!=NULL){
        this->add(tmp->data);
        tmp=tmp->next;
    }
}

template <class T>
void DLinkedList<T>::removeInternalData() {
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    this->deleteAllNode(this->head);
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index) {
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
    if (index==0) return NULL;  
    if (index<=count/2){
        Node* tmp=head->next->next;
        for (int i=1 ; i<index ; i++) tmp=tmp->next;
        return tmp->prev;
    }
    else{
        Node* tmp=tail->prev;
        for (int i=count-1 ; i>=index ; i--) tmp=tmp->prev;
        return tmp;
    }
}

#endif /* DLINKEDLIST_H */