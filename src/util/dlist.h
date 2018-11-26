/****************************************************************************
  FileName     [ dlist.h ]
  PackageName  [ util ]
  Synopsis     [ Define doubly linked list package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include <cassert>

template <class T> class DList;

// DListNode is supposed to be a private class. User don't need to see it.
// Only DList and DList::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class DListNode
{
   friend class DList<T>;
   friend class DList<T>::iterator;

   DListNode(const T& d, DListNode<T>* p = 0, DListNode<T>* n = 0):
      _data(d), _prev(p), _next(n) {}

   // [NOTE] DO NOT ADD or REMOVE any data member
   T              _data;
   DListNode<T>*  _prev;
   DListNode<T>*  _next;
};


template <class T>
class DList
{
public:
   // TODO: decide the initial value for _isSorted
   DList() {
      _head = new DListNode<T>(T());
      _head->_prev = _head->_next = _head; // _head is a dummy node
      _isSorted = true;
   }
   ~DList() { clear(); delete _head; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class DList;

   public:
      iterator(DListNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return _node->_data; }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () { 
         this -> _node = this -> _node -> _next;
         return *(this); 
      }
      iterator operator ++ (int) {
         iterator newit = *this;
         this -> _node = this -> _node -> _next;
         return newit; 
      }
      iterator& operator -- () { 
         this -> _node = this -> _node -> _prev;
         return *(this); 
      }
      iterator operator -- (int) { 
         iterator newit = *this;
         this -> _node = this -> _node -> _prev;
         return newit; 
      }

      iterator& operator = (const iterator& i) { 
         this -> _node = i._node;
         return *(this); 
      }

      bool operator != (const iterator& i) const { 
         return this -> _node != i._node; 
      }
      bool operator == (const iterator& i) const { 
         return this -> _node == i._node; 
      }

   private:
      DListNode<T>* _node;
   };

   // TODO: implement these functions
   iterator begin() const { return iterator(_head); }
   iterator end() const { return iterator(_head -> _prev); }
   bool empty() const { return _head == _head -> _prev;}
   size_t size() const {
      DListNode<T>* _temp=_head;
      size_t n = 0;
      while (_temp -> _next!=_head){
         n++;
         _temp = _temp -> _next;
      } 
      return n; 
   }

   void push_back(const T& x) {
      
      if (empty()){
         _isSorted = true;
         DListNode<T>* t = new DListNode<T>(x,_head,_head);
         _head->_prev = t;
         _head->_next = t;
         _head = t;
      }
      else {
         _isSorted = (_isSorted && x>=_head->_prev->_prev->_data)?true:false;
         DListNode<T>* t = new DListNode<T>(x,_head->_prev->_prev,_head->_prev);
         _head -> _prev -> _prev -> _next = t;
         _head -> _prev -> _prev = t;
      }
      return;
   }
   void pop_front() { 
      if (!empty()){
         DListNode<T>* t = _head;
         _head = _head -> _next;
         _head -> _prev = t -> _prev;
         _head -> _prev -> _next = _head;
         delete t;
      }
      return;
   }
   void pop_back() {
      if (!empty()){
         DListNode<T>* end = _head -> _prev -> _prev;
         if (_head == end){
            clear();
            return;
         }
         else{
            end -> _prev -> _next = _head -> _prev;
            _head -> _prev -> _prev = end -> _prev;
            delete end;
         }
      }
      return;
   }

   // return false if nothing to erase
   bool erase(iterator pos) { 
      if (empty()) return false;
      else{
         if (pos._node == _head){
            _head = pos._node -> _next;
         }
         pos._node -> _prev -> _next = pos._node -> _next;
         pos._node -> _next -> _prev = pos._node -> _prev;
         delete pos._node;
      }
      return true; 
   }
   bool erase(const T& x) { 
      for (iterator it=begin();it!=end();it++){
         if (it._node->_data == x){
            if (it._node == _head)
               _head = _head -> _next;
            it._node -> _prev -> _next = it._node -> _next;
            it._node -> _next -> _prev = it._node -> _prev;
            delete it._node;
            return true;
         }
      }
      return false; 
   }

   iterator find(const T& x) { 
      for (iterator it = begin(); it != end(); it++){
         if (it._node -> _data == x)
            return it;
      }
      return end(); 
   }

   void clear() {
      DListNode<T>* dummy = _head -> _prev;
      if (!empty()){
         for (iterator it = begin();it!=end();it++){
            delete it._node;
         }
         _head = dummy;
         _head -> _prev = _head;
         _head -> _next = _head;
      }
   }  // delete all nodes except for the dummy node

   void sort() { 
      // return if is sorted or link list only contains 1 element
      if (_isSorted || size()<=1) return;
      else{
         DListNode<T> *temp = _head->_next, *temp_forward = temp;
         while(temp -> _next != _head){
            temp_forward = temp;
            temp = temp -> _next;
            // cout << "temp: " << temp -> _data << endl;
            // cout << "tf: " << temp_forward -> _data << endl;
            // cout << "head: " << _head -> _data << endl;
            while (temp_forward -> _data < temp_forward -> _prev -> _data && temp_forward != _head){
               swap_forth(temp_forward);
            }
         }
      }
      _isSorted = true;
      return;
   }

private:
   // [NOTE] DO NOT ADD or REMOVE any data member
   DListNode<T>*  _head;     // = dummy node if list is empty
   mutable bool   _isSorted; // (optionally) to indicate the array is sorted

   // [OPTIONAL TODO] helper functions; called by public member functions
   void swap_forth(DListNode<T>* tf) {
      DListNode<T> *former = tf -> _prev, *tempnext = tf -> _next, *ff = former -> _prev;
      if(tf == _head)
         return;
      else{
         if (former == _head) _head = tf;
         tf -> _prev = former -> _prev;
         tf -> _next = former;
         former -> _prev = tf;
         former -> _next = tempnext;
         tempnext -> _prev = former;
         ff -> _next = tf;
         // cout << "inner head: " << _head -> _data << ' ' << _head -> _next -> _data << ' ' << _head -> _next -> _next -> _data << endl;
      }
      return;
   }
};

#endif // DLIST_H
