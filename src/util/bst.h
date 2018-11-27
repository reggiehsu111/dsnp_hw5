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

	BSTreeNode(const T& d, BSTreeNode<T>* p = NULL, BSTreeNode<T>* l = NULL, BSTreeNode<T>* r = NULL):
	_data(d), _parent(p), _left(l), _right(r) {_height = 1;}
	~BSTreeNode(){}

   T               _data;
   BSTreeNode<T>*  _parent;
   BSTreeNode<T>*  _left;
   BSTreeNode<T>*  _right;
   size_t          _height;
};


template <class T>
class BSTree
{
   // TODO: design your own class!!
public:
	BSTree():_root(NULL), _min(NULL), _max(NULL),_size(0){}
	~BSTree(){clear();delete _root;}
	// implementation of iterator
   class iterator { 
   		friend class BSTree<T>;
   public:
   		iterator(BSTreeNode<T>* n):_node(n){}
   		iterator(const iterator& i) : _node(i._node) {}
   		~iterator() {}
   		const T& operator * () const { return _node->_data; }
   		T& operator * () { return _node->_data; }

   		iterator& operator ++ () { 
	        this -> _node = BSTree<T>::successor(this -> _node);
	        return *this; 
      	}
      	iterator operator++(int) {
	        iterator temp = *this;
	        this -> _node = BSTree<T>::successor(this -> _node);
	        return temp;
	    }
	    iterator& operator -- () { 
	        this -> _node = BSTree<T>::predecessor(this -> _node);
	        return *this; 
      	}
      	iterator operator--(int) {
	        iterator temp = *this;
	        this -> _node = BSTree<T>::predecessor(this -> _node);
	        return temp;
	    }
	    iterator& operator=(const iterator& i) {
	        _node = i._node;
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
    iterator end() const { return iterator(NULL); }
    void sort(){return;}
    bool empty() const { return !_root;}
    size_t size() const { return _size;}
    iterator find(const T& x) { 
    	BSTreeNode<T>* cur = _root;
    	while(true){
    		if (!cur) break;
    		if (cur -> _data == x)
    			return iterator(cur);
    		else if (cur -> _data > x)
    			cur = cur -> _left;
    		else if (cur -> _data < x)
    			cur = cur -> _right;
    	}
    	return end(); 
   }
    void insert(const T& x){
    	// create root node if empty
    	// BSTreeNode<T>* node;
    	if (empty()){
    		_root =  new BSTreeNode<T>(x);
    		_min = _max = _root;
    	}
    	else{
    		insertNode(_root,x);
	   	}
	   	_size++;
	   	return;
    }
    void clear(){
    	if (_root) {
    		delete_sub(_root);
    		_size = 0;
    	}
    }
    void pop_front() {
		if(_root) {
			erase(iterator(_min));
		}
    }
   void pop_back()
   {
      if(_root)
      {
         erase(iterator(_max));
      }
   }

    bool erase(iterator pos){
    	if (_root){
    		T x = pos._node -> _data;
    		return erase(x);
    	}
    	return false;
    }
    bool erase(const T& x) { 
    	if (_root){
    		if (deleteNode(_root,x)){
    			_size --;
    			return true;
    		}
    		else{
	    		return false;
    		}
    	}
    	return false;
    }
    void print() const {
      if(_root)
         print_under(_root,0);
   }


private:
	BSTreeNode<T>*  _root;
  BSTreeNode<T>*  _min;
  BSTreeNode<T>*  _max;
  size_t _size;

  	//helper functions:
  	static BSTreeNode<T>* successor(BSTreeNode<T>* node) {
  		// node is root
  		if (!node -> _parent){
  			// cout << "node is root" << endl;
  			return (node -> _right) ? minV(node -> _right):NULL;
  		}
  		//node is a left child
  		if (node -> _parent -> _left == node){
  			// cout << "node is left child" << endl;
  			if (node -> _right){
  				BSTreeNode<T>* temp = minV(node -> _right);
  				return (node -> _parent -> _data < temp -> _data) ? node -> _parent:temp;
  			}
  			else return node -> _parent;
  		}
  		else{
  			// cout << "node is right child" << endl;
  			if (node -> _right){
  				return minV(node -> _right);
  			}
  			else{
  				BSTreeNode<T>* temp = node;
  				while(true){
  					if (!temp -> _parent)
  						return NULL;
  					else if (temp -> _parent -> _left == temp){
  						return temp -> _parent;
  					}
  					temp = temp -> _parent;
  				}
  			}
  		}
  	}
  	static BSTreeNode<T>* predecessor(BSTreeNode<T>* node) {
      cout << "here" << endl;
      // node is root
  		if (!node -> _parent){
        cout << "node is root" << endl;
  			return node -> _left ? maxV(node -> _left):NULL;
  		}
      // node it right child
  		if (node -> _parent -> _right == node){
        cout << "right" << endl;
  			if (node -> _left){
  				BSTreeNode<T>* temp = maxV(node -> _left);
  				return (node -> _parent -> _data > temp -> _data) ? node -> _parent:temp;
  			}
  			else return node -> _parent;
  		}
  		else {
        cout << "left" << endl;
  			if (node -> _left){
  				return (maxV(node -> _left));
  			}
  			else{
  				BSTreeNode<T>* temp = node;
  				while(true){
  					if (!temp -> _parent)
  						return NULL;
  					else if (temp -> _parent -> _right== temp){
  						return temp -> _parent;
  					}
  					temp = temp -> _parent;
  				}
  			}
  		}
  	}
  	void delete_sub(BSTreeNode<T>* x){
  		if (x -> _left){
  			delete_sub(x -> _left);
  		}
  		if (x -> _right){
  			delete_sub(x -> _right);
  		}
  		if (!x->_right && !x->_left){ // leaf
  			if (!x->_parent){
  				delete x;
  				_min = _max = _root = NULL;
  				return;
  			}
  			if (x -> _parent -> _left == x){
  				x -> _parent -> _left = NULL;
  				delete x;
  			}
  			if (x -> _parent -> _right == x){
  				x -> _parent -> _right = NULL;
  				delete x;
  			}
  		}
  		return;
  	}
  	BSTreeNode<T>* rightRotate(BSTreeNode<T>* node){
  		// cout << "rR" << endl;
  		BSTreeNode<T> *x = node -> _left, *t2 = x -> _right;
  		x -> _right = node;
  		x -> _parent = node -> _parent;
  		node -> _parent = x;
  		node -> _left = t2;
  		if (t2)
  			t2 -> _parent = node;
  		node -> _height = max(getHeight(node -> _left), getHeight(node -> _right))+1; 
    	x -> _height = max(getHeight(x -> _left), getHeight(x-> _right))+1;
    	if (node == _root) _root = x;
    	return x;
  	}
  	BSTreeNode<T>* leftRotate(BSTreeNode<T>* node){
  		// cout << "lR" << endl;
  		BSTreeNode<T> *x = node -> _right, *t2 = x -> _left;
  		x -> _left = node;
  		x -> _parent = node -> _parent;
  		node -> _parent = x;
  		node -> _right = t2;
  		if (t2)
  			t2 -> _parent = node;
  		node -> _height = max(getHeight(node -> _left), getHeight(node -> _right))+1; 
    	x -> _height = max(getHeight(x -> _left), getHeight(x-> _right))+1; 
    	if (node == _root) _root = x;
    	return x;
  	}
  	int getBalance(BSTreeNode<T>* node){
  		if (node == NULL)
  			return 0;
  		else
  			return getHeight(node -> _left) - getHeight(node -> _right);
  	}

  	size_t max(size_t a, size_t b){
  		return(a>b)?a:b;
  	}
  	void print_under(BSTreeNode<T>* x, size_t indent) const
  	{
      cout << string(indent, ' ');
      if (x) {
         cout << x->_data << "\n";
      }
      else {
         cout << "[0]\n";
         return; // no more elements to print
      }
      print_under(x->_left, indent+2);
      print_under(x->_right, indent+2);
      cout.flush();
   }
    BSTreeNode<T>* insertNode(BSTreeNode<T>* node, const T& x, BSTreeNode<T>* parent=NULL){
    	if (!node){
    		BSTreeNode<T>* temp = new BSTreeNode<T>(x, parent);
    		if (x <= _min -> _data) _min = temp;
    		if (x > _max -> _data) _max = temp;
    		return temp;
    	}
    	if (x <= node -> _data)
    		node -> _left = insertNode(node->_left,x,node);
    	else if (x > node -> _data)
    		node -> _right = insertNode(node->_right,x,node);
    	else return node;
    	BSTreeNode<T>* temp = node;
   		temp -> _height = 1 + max(getHeight(temp -> _left), getHeight(temp -> _right));
   		int balance = getBalance(temp);
   		// left left case
   		if (balance > 1 && x < temp -> _left -> _data){
   			temp = rightRotate(temp);
   			return temp;
   		}
   		// right right case
   		if (balance < -1 && x > temp -> _right -> _data){
   			temp = leftRotate(temp);
   			return temp;
   		}
   		// left right case
   		if (balance > 1 && x > temp -> _left -> _data){
   			temp -> _left = leftRotate(temp -> _left);
   			temp = rightRotate(temp);
   			return temp;
   		}
   		// right left case
   		if (balance < -1 && x < temp -> _right -> _data){
   			temp -> _right = rightRotate(temp -> _right);
   			temp = leftRotate(temp);
   			return temp;
   		}
   		return temp;
    }
    size_t getHeight(BSTreeNode<T>* node){
    	if (!node) return 0;
    	else return node -> _height;
    }
	BSTreeNode<T>* deleteNode(BSTreeNode<T>* node, T key){
		if (!node) // can't find the node
			return node;
		if (key < node -> _data)
			node -> _left = deleteNode(node -> _left, key);
		else if (key > node -> _data)
			node -> _right = deleteNode(node -> _right, key);
		else{ // key == node->_data
			// one or no child
			if (!(node -> _left) || !(node -> _right)){
				BSTreeNode<T>* temp = node -> _left? node -> _left : node -> _right;
				if (!temp){ // no child case
					if (_min -> _data == key) _min = successor(node);
					if (_max -> _data == key) _max = predecessor(node);
					delete node;
 					node = temp;
				}
				else{ // one child case
					if (_min -> _data == key) _min = successor(node);
					if (_max -> _data == key) _max = predecessor(node);
					temp -> _parent = node -> _parent;
					if (node -> _parent -> _left == node)
						node -> _parent -> _left = temp;
					else if (node -> _parent -> _right == node)
						node -> _parent -> _right = temp;
					delete node;
					node = temp;
				}
			}
			else{ // two children case
				BSTreeNode<T>* temp = minV(node -> _right);
				node -> _data = temp -> _data;
				node -> _right = deleteNode(node -> _right, temp -> _data);
			}
		}
		if (!node){
			return node;
		}
		node -> _height = 1 + max(getHeight(node -> _left), getHeight(node -> _right));
		int balance = getBalance(node);
		// left left case
   		if (balance > 1 && getBalance(node -> _left) >= 0){
   			 return rightRotate(node);
   		}
   		// right right case
   		if (balance < -1 && getBalance(node -> _right) <= 0){
   			 return leftRotate(node);
   		}
   		// left right case
   		if (balance > 1 && getBalance(node -> _left) < 0){
   			node -> _left = leftRotate(node -> _left);
   			return rightRotate(node);
   		}
   		// right left case
   		if (balance < -1 && getBalance(node -> _right) > 0){
   			node -> _right = rightRotate(node -> _right);
   			return leftRotate(node);
   		}
   		return node;
    }
    static BSTreeNode<T>* minV(BSTreeNode<T>* node) { 
	    BSTreeNode<T>* cur = node; 
	    // loop down to find the leftmost leaf
	    while (cur->_left != NULL) 
	        cur = cur->_left;
	    return cur;
	} 
	static BSTreeNode<T>* maxV(BSTreeNode<T>* node) { 
	    BSTreeNode<T>* cur = node; 
	    // loop down to find the leftmost leaf
	    while (cur->_right != NULL) 
	        cur = cur->_right;
	    return cur;
	} 
};

#endif // BST_H
