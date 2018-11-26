/****************************************************************************
  FileName     [ bst.h ]
  PackageName  [ util ]
  Synopsis     [ Define binary search tree package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>

using namespace std;

template <class T> class BSTree;

// BSTreeNode is supposed to be a private class. User don't need to see it.
// Only BSTree and BSTree::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class BSTreeNode
{
   // TODO: design your own class!!
	friend class BSTree<T>;
	friend class BSTree<T>::iterator;

	BSTreeNode(const T& d, BSTreeNode<T>* p = 0, BSTreeNode<T>* l = 0, BSTreeNode<T>* r = 0):
	_data(d), _parent(p), _left(l), _right(r) {}
	~BSTreeNode(){}

   // [NOTE] DO NOT ADD or REMOVE any data member
   T              _data;
   BSTreeNode<T>*  _parent;
   BSTreeNode<T>*  _left;
   BSTreeNode<T>*  _right;
};


template <class T>
class BSTree
{
   // TODO: design your own class!!
public:
	BSTree(){
		_root = new BSTreeNode(T(), _root, _root, _root);
		_min = _max = _root;
	}
	~BSTree(){clear();delete _root;}
	// implementation of iterator
   class iterator { 
   		friend class BSTree;
   public:
   		iterator(BSTreeNode<T>* n=0):_node(n){}
   		iterator(const iterator& i) : _node(i._node) {}
   		~iterator() {}
   		const T& operator * () const { return _node->_data; }
   		T& operator * () { return _node->_data; }

   		iterator& operator ++ () { 
	        this->_node = BSTree<T>::successor(this->_node);
	        return *(this); 
      	}
      	iterator operator++(int) {
	        iterator temp = *this;
	        this->_node = BSTree<T>::successor(this->_node);
	        return temp;
	    }
	    iterator& operator -- () { 
	        this->_node = BSTree<T>::predecessor(this->_node);
	        return *(this); 
      	}
      	iterator operator++(int) {
	        iterator temp = *this;
	        this->_node = BSTree<T>::predecessor(this->_node);
	        return temp;
	    }
	    iterator& operator=(const iterator& i) {
	        this->_node = i._node;
	        return *this;
	    }
      	bool operator!=(const iterator& i) const {
        	return (this->_node != i._node);
    	}
      	bool operator==(const iterator& i) const {
        	return (this->_node == i._node);
    	}

   	private:
   		BSTreeNode<T>* _node;
   };
   iterator begin() const { return iterator(_min); }
   iterator end() const { return iterator(_max); }
private:
	BSTreeNode<T>*  _root;
  	BSTreeNode<T>*  _min;
  	BSTreeNode<T>*  _max;
  	size_t _size;

  	//helper functions:
  	BSTreeNode<T>* successor(BSTreeNode<T>* node){
  		return node;
  	}
  	BSTreeNode<T>* predecessor(BSTreeNode<T>* node){
  		return node;
  	}

};

#endif // BST_H
