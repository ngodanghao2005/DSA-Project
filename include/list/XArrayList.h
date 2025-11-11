/*
 * File:   XArrayList.h
 */

#ifndef XARRAYLIST_H
#define XARRAYLIST_H
#include "list/IList.h"
#include <memory.h>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class XArrayList : public IList<T>{
    public:
        class Iterator;
    protected:
        T *data;
        int capacity;
        int count;
        bool (*itemEqual)(T &lhs, T &rhs);
        void (*deleteUserData)(XArrayList<T> *);
    public:
        XArrayList(void (*deleteUserData)(XArrayList<T> *)=0, bool (*itemEqual)(T &, T &)=0, int capacity=10);
        XArrayList(const XArrayList<T> &list);
        XArrayList<T> &operator=(const XArrayList<T> &list);
        ~XArrayList();
        void resize(int newcapacity){
            T* tmp=new T[newcapacity];
            for (int i=0 ; i<count ; i++) tmp[i]=this->data[i];
            delete[] this->data;
            this->data=tmp;
            this->capacity=newcapacity;
        }
        void add(T e);
        void add(int index, T e);
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
        void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T> *)=0){this->deleteUserData=deleteUserData;}
        Iterator begin(){return Iterator(this, 0);}
        Iterator end(){return Iterator(this, count);}
    protected:
        void checkIndex(int index);
        void ensureCapacity(int index);
        void copyFrom(const XArrayList<T> &list);
        void removeInternalData();
    protected:
        static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &)){
            if (itemEqual==0) return lhs==rhs;
            else return itemEqual(lhs, rhs);
        }
    public:
        static void free(XArrayList<T> *list){
            typename XArrayList<T>::Iterator it=list->begin();
            while (it!=list->end()){
                delete *it;
                it++;
            }
        }
    public:
        class Iterator{
            private:
                int cursor;
                XArrayList<T> *pList;
            public:
                Iterator(XArrayList<T> *pList = 0, int index = 0) {this->pList = pList, this->cursor = index;}
                Iterator &operator=(const Iterator &iterator){
                    cursor = iterator.cursor;
                    pList = iterator.pList;
                    return *this;
                }
                void remove(void (*removeItemData)(T) = 0){
                    T item = pList->removeAt(cursor);
                    if (removeItemData != 0) removeItemData(item);
                    cursor -= 1;
                }
                T &operator*(){return pList->data[cursor];}
                bool operator!=(const Iterator &iterator){return cursor != iterator.cursor;}
                Iterator &operator++(){
                    this->cursor++;
                    return *this;
                }
                Iterator operator++(int){
                    Iterator iterator = *this;
                    ++*this;
                    return iterator;
                }
        };
};

template <class T>
XArrayList<T>::XArrayList(void (*deleteUserData)(XArrayList<T> *), bool (*itemEqual)(T &, T &), int capacity){
    this->capacity=capacity;
    this->itemEqual=itemEqual;
    this->deleteUserData=deleteUserData;
    this->count=0;
    this->data=new T[capacity];
}

template <class T>
XArrayList<T>::XArrayList(const XArrayList<T> &list): capacity(list.capacity), count(list.count){
    this->data=new T[capacity];
    for (int i=0 ; i<count ; i++) this->data[i]=list.data[i];
    this->itemEqual=list.itemEqual;
    this->deleteUserData=list.deleteUserData;
}

template <class T>
XArrayList<T> &XArrayList<T>::operator=(const XArrayList<T> &list){
    if (this!=&list){
        if (this->deleteUserData!=NULL) this->deleteUserData(this);
        delete[] this->data;
        this->capacity=list.capacity;
        this->count=list.count;
        this->itemEqual=list.itemEqual;
        this->deleteUserData=list.deleteUserData;
        this->data=new T[capacity];
        for (int i=0 ; i<count ; i++) this->data[i]=list.data[i];
    }
    return *this;
}

template <class T>
XArrayList<T>::~XArrayList(){
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    delete[] this->data;
}

template <class T>
void XArrayList<T>::add(T e){
    if (count<capacity) this->data[count++]=e;
    else{
        this->ensureCapacity(count);
        this->data[count++]=e;
    }
}

template <class T>
void XArrayList<T>::add(int index, T e){
    if (index<0||index>count) throw out_of_range("Index is out of range!");
    this->ensureCapacity(index);
    if (count==capacity){
        capacity=capacity*2+1;
        resize(capacity);
    }
    for (int i=count ; i>index ; i--) this->data[i]=this->data[i-1];
    this->data[index]=e;
    ++count;
}

template <class T>
T XArrayList<T>::removeAt(int index){
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
    T res=this->data[index];
    for (int i=index ; i<count-1 ; i++) this->data[i]=this->data[i+1];
    --count;
    return res;
}

template <class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T)){
    if (count==0) return false;
    for (int i=0 ; i<count ; i++){
        if (this->equals(item,this->data[i],itemEqual)){
            if (removeItemData!=NULL) removeItemData(this->data[i]);
            this->removeAt(i);
            return true;
        }
    }
    return false;
}

template <class T>
bool XArrayList<T>::empty(){return this->count==0;}

template <class T>
int XArrayList<T>::size(){return this->count;}

template <class T>
void XArrayList<T>::clear(){
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    delete[] this->data;
    this->data=new T[capacity];
    this->count=0;
}

template <class T>
T &XArrayList<T>::get(int index){
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
    return this->data[index];
}

template <class T>
int XArrayList<T>::indexOf(T item){
    for (int i=0 ; i<count ; i++){
        if (this->equals(item,this->data[i],itemEqual)) return i;
    }
    return -1;
}

template <class T>
bool XArrayList<T>::contains(T item){
    return this->indexOf(item)!=-1;
}

template <class T>
string XArrayList<T>::toString(string (*item2str)(T &)) {
    string tmp="[";
    for (int i=0; i<count; i++){
        if (item2str==NULL) tmp+=convert(data[i]);
        else tmp+=item2str(data[i]);
        if (i!=count-1) tmp+=", ";
    }
    tmp+="]";
    return tmp;
}

template <class T>
void XArrayList<T>::checkIndex(int index){
    if (index<0||index>=count) throw out_of_range("Index is out of range!");
}

template <class T>
void XArrayList<T>::ensureCapacity(int index){
    if (index<0) throw out_of_range("Index is out of range!");
    else if (index>=capacity) this->resize(2*index+1);
}

template <class T>
void XArrayList<T>::copyFrom(const XArrayList<T> &list){
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    delete[] this->data;
    this->capacity=list.capacity;
    this->count=list.count;
    this->itemEqual=list.itemEqual;
    this->deleteUserData=list.deleteUserData;
    this->data=new T[capacity];
    for (int i=0 ; i<count ; i++) this->data[i]=list.data[i];
}

template <class T>
void XArrayList<T>::removeInternalData(){
    if (this->deleteUserData!=NULL) this->deleteUserData(this);
    delete[] this->data;
}
#endif /* XARRAYLIST_H */