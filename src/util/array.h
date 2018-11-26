/****************************************************************************
  FileName     [ array.h ]
  PackageName  [ util ]
  Synopsis     [ Define dynamic array package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <algorithm>

using namespace std;

// NO need to implement class ArrayNode
//
template <class T>
class Array
{
public:
   // TODO: decide the initial value for _isSorted
   Array() : _data(0), _size(0), _capacity(0), _isSorted(true) {}
   ~Array() { delete [] _data; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class Array;

   public:
      iterator(T* n= 0): _node(n) {}
      iterator(const iterator& i): _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { 
         return *_node; 
      }
      T& operator * () { return (*_node); }
      iterator& operator ++ () {
         _node++;
         return (*this); 
      }
      iterator operator ++ (int) { 
         iterator temp = *this;
         this -> _node++;
         return (temp); 
      }
      iterator& operator -- () {
         _node--;
         return (*this); 
      }
      iterator operator -- (int) {
         iterator temp = *this;
         this -> _node--;
         return (temp); 
      }

      iterator operator + (int i) const { return iterator(this->_node+i); }
      iterator& operator += (int i) { 
         this -> _node += i;
         return (*this); 
      }

      iterator& operator = (const iterator& i) { 
         this -> _node = i._node;
         return (*this); 
      }

      bool operator != (const iterator& i) const { return this -> _node != i._node; }
      bool operator == (const iterator& i) const { return this -> _node == i._node; }

   private:
      T*    _node;
   };

   // TODO: implement these functions
   iterator begin() const { return iterator(_data); }
   iterator end() const { return iterator(_data + _size); }
   bool empty() const { return !_size; }
   size_t size() const { return _size; }

   T& operator [] (size_t i) { return _data[i]; }
   const T& operator [] (size_t i) const { return _data[i]; }

   void push_back(const T& x) {
      if (_isSorted && !empty()){
         if (x < *(_data+_size-1))
            _isSorted = false;
      }
      if (_size == _capacity)
         expand();
      _data[_size++] = x;
    }
   void pop_front() {
      if (_size){
         for (size_t i=0; i<_size-1; i++){
            _data[i] = _data[i+1];
         }
         _size--;
      }
   }
   void pop_back() {
      if (_size){
         _size --;
      }
   }

   bool erase(iterator pos) {
      if (pos._node){
         *pos._node = _data[_size-1];
         _size--;
         return true;
      }
      else 
         return false; 
   }
   bool erase(const T& x) {
      iterator cur = iterator(_data);
      while (cur != end()){
         if (*cur._node == x){
            return erase(cur);
         }
         cur++;
      }
      return false; 
   }

   iterator find(const T& x) {
      if (!_isSorted){
         iterator cur = iterator(_data);
         while (cur != end()){
            if (*cur._node == x){
               return cur;
            }
            cur++;
         }
         return end(); 
      }
      else {
         return bin_search(x,_data,_data+_size-1);
      }
   }

   void clear() { _size = 0; }

   // [Optional TODO] Feel free to change, but DO NOT change ::sort()
   void sort() const { if (!empty()) ::sort(_data, _data+_size); _isSorted = true;}

   // Nice to have, but not required in this homework...
   // void reserve(size_t n) { ... }
   // void resize(size_t n) { ... }

private:
   // [NOTE] DO NOT ADD or REMOVE any data member
   T*            _data;
   size_t        _size;       // number of valid elements
   size_t        _capacity;   // max number of elements
   mutable bool  _isSorted;   // (optionally) to indicate the array is sorted

   // [OPTIONAL TODO] Helper functions; called by public member functions
   void expand(){
      _capacity = (_capacity<8)?16:2*_capacity;
      T* temp = _data;
      _data = new T[_capacity];
      if (temp){
         for (size_t i=0; i<_size-1; i++){
            _data[i] = temp[i];
         }
         delete [] temp;
      }
   }
   iterator bin_search(const T& x, T* start, T* back) const{
      if(*start == x) return iterator(start);
      else if(*back == x) return iterator(back);
      if (start == back){
         if (*start == x)
            return iterator(start);
         else 
            return end();
      }
      else if (back-start == 1) return end();
      else{
         T* mid = start + size_t((back-start)/2);
         if (*mid > x) return bin_search(x,start,mid);
         else if (*mid == x) return iterator(mid);
         else return bin_search(x,mid,back);
      }
   }
};

#endif // ARRAY_H
