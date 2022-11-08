#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_; 
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
		static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO

    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		int calculateheight(Node<Key, Value> *root) const;
		void noderemover(Node<Key, Value>* current);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
		current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
		current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool 
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	//returns the result of whether or not this->current_ is equal to rhs->current_

	return (this->current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	//returns the negation of the == operator
	return !(this->current_ == rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
		current_ = successor(current_); 
		return *this;
}
/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
		(this->root_) = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
		this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	Key currentkey = keyValuePair.first; //find out how to access value
	Value replace = keyValuePair.second;
	if (!empty()) {
		Node<Key, Value>* bstiter = root_;
		while ( true ) {
			Key checkerkey = bstiter->getKey();
			if ( currentkey == checkerkey ) { //if the key of the keyvaluepair is equal to current key of location, replace the values
				bstiter->setValue(replace);
				break;
			}
			else if ( currentkey < checkerkey ) { //if key of keyvaluepair is less than current key of location, move left
				if ( bstiter->getLeft() == NULL ) { //if the left is NULL, add to the tree
					Node<Key, Value>* addnode  = new Node<Key, Value>(currentkey , replace , bstiter);
					bstiter->setLeft(addnode);
					break;
				}
				bstiter = bstiter->getLeft();
				
			}
			else if ( currentkey > checkerkey) { //if key of keyvaluepair is greater than current key of location, go right
				if ( bstiter->getRight() == NULL ) { //if the right is NULL, add to tree
					Node<Key, Value>* addnode  = new Node<Key, Value>(currentkey , replace , bstiter);
					bstiter->setRight(addnode);
					break;
				}
				bstiter = bstiter->getRight();
			}
		}
	}
	else {
		Node<Key, Value>* newroot = new Node<Key, Value>(currentkey, replace, NULL);
		root_ = newroot;
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
		
		
		if ( root_ != NULL) {
			Node<Key, Value> *remover = root_;
			while ( true ) {
			Key check = remover->getKey();
			if ( check == key ) { //if we found the key
				if ( remover->getLeft() == NULL && remover->getRight() == NULL ) { //if node has no childre
					if ( remover == root_ ) {
						root_ = NULL;
						delete root_;
						break;
					}
					Node<Key, Value> *parent = remover->getParent();
					if ( parent->getRight() == remover ) { //if remover is right child
						parent->setRight(NULL);
					}
					else if ( parent->getLeft() == remover ) { //if remover is left child
						parent->setLeft(NULL);
					}
					remover->setParent(NULL);
					delete remover;
					break;
				}
				else if ( remover->getLeft() == NULL || remover->getRight() == NULL ) { //if node has one child
					if ( remover->getLeft() == NULL ) { //if the left node is NULL, right child exists
						Node<Key, Value> *rightchild = remover->getRight();
						if ( remover->getParent() == NULL ) { //checking if the current node is the root_
							root_ = rightchild;
							rightchild->setParent(NULL);
							remover->setParent(NULL);	//remove locations of remover
							remover->setRight(NULL);
							break;
						}
						Node<Key, Value> *parent = remover->getParent();
						if ( remover == parent->getRight() ) { //if remover is the left child of its parent
							parent->setRight(rightchild);
							rightchild->setParent(parent);
						}	
						else{ //if remover is the right child of its parent
							parent->setLeft(rightchild);
							rightchild->setParent(parent);
							
						}		
						remover->setParent(NULL);	//remove locations of remover
						remover->setRight(NULL);
					}
					else if ( remover->getRight() == NULL ) { //if the right node is NULL, left child exists
						Node<Key, Value> *leftchild = remover->getLeft();
						if ( remover->getParent() == NULL ) { //checking if the current node is the root_
							root_ = leftchild;
							leftchild->setParent(NULL);
							remover->setParent(NULL);	//remove locations of remover
							remover->setLeft(NULL);
							break;
						}
						Node<Key, Value> *parent = remover->getParent();
						if ( remover == parent->getRight() ) { //if remover is the left child of its parent
							parent->setRight(leftchild);
							leftchild->setParent(parent);		
						}	
						else{ //if remover is the right child of its parent
							parent->setLeft(leftchild);
							leftchild->setParent(parent);
						}	
						remover->setParent(NULL); //remove locations of remover
						remover->setLeft(NULL);	
					}
					delete remover;
					break;
				}
				else { //if node has both children
					Node<Key, Value> *pred = predecessor(remover);
					
					nodeSwap(remover, pred); //remover goes to pred, and pred goes to remover node position
					//if you use pred, node you switch with only has left child or no child

					remove(remover->getKey());
				}
			}
			else if ( key < check ) { //if the current key  node is less than remover key
				if ( remover->getLeft() == NULL ) {
					break;
				}
				remover = remover->getLeft();
			}
			else if (key > check){ //if the current key  node is greater than remover key
				if ( remover->getRight() == NULL ) {
					break;
				}
				remover = remover->getRight();
			}
			else { //means no key in tree
				break;
			}
		}	
	}
	
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) 
{
	//finding the very right most node in the left subtree of current node
	//if no child, find the point when you go right, then the parent that is to the left is the predecessor
	if (current->getLeft() == NULL) { //go up since left subtree does not exist
		while ( current ) {
			Node<Key, Value> *temp = current->getParent(); 
			if ( temp == NULL ) { //if temp ends up being root, no predecessor
				return NULL;
			}
			if ( temp->getLeft() == current ) {
				current = temp;
				continue;
			}
			else if ( temp->getRight() == current) {
				current = temp;
				return current;
				break;
			}
		}
	}
	else { //if left subtree exists
		current = current->getLeft();
		while ( current ) {
			if ( current->getRight() == NULL) {
				return current;
				break;
			}
			else {
				current = current->getRight();
			}
		}
	}
	return NULL;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
	//finding the very left most node in the right subtree of current node
	//if no child, find the point when you go left, then the parent that is to the right is the successor
	if (current->getRight() == NULL) { //go up since right subtree does not exist
		while ( current ) {
			Node<Key, Value> *temp = current->getParent(); 
			if ( temp == NULL ) { //if the temp ends up being the parent, there is no successor
				return NULL;
			}
			if ( temp->getRight() == current ) {
				current = temp;
				continue;
			}
			else if ( temp->getLeft() == current){
				current = temp;
				return current;
				break;
			}
		}
	}
	else { //if right subtree exists
		current = current->getRight();
		while ( current ) {
			if ( current->getLeft() == NULL) {
				return current;
				break;
			}
			else {
				current = current->getLeft();
			}
		}
	}
	return NULL;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
		//recursive 
		//need helper function 
		//base case if current is NULL
		//delete the node
		noderemover(root_);
		root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::noderemover(Node<Key, Value>* current)
{
	if ( current == NULL ) { //if the current node is NULL
		return;
	}
	noderemover(current->getRight());
	noderemover(current->getLeft());
	delete current;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
	//the smallest value in a binary search tree will always be the most left node
	Node<Key, Value>* current = root_;
	while ( true) {
		if ( current->getLeft() != NULL) {
			current = current->getLeft();
			continue;
		}
		else {
			break;
		}
	}
	return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
		if (root_ != NULL ) {
			Node <Key, Value>* current = root_;
			while ( true ) {
				Key currentkey = current->getKey();
				if ( key < currentkey ) { //if current key is less than key, move to left
					if ( current->getLeft() == NULL ) {
						break;
					}
					current = current->getLeft();
				}
				else if (key > currentkey ) { //if current key is greater than key, move right
					if (current->getRight() == NULL ) {
						break;
					}
					current = current->getRight();
				}
				else {
					return current;
					break;
				}
			}
		}
		return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	return calculateheight(root_) != -1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateheight(Node<Key, Value> *root) const
{
	int left = 0; 
	int right = 0;
	int greater;
	if (root == nullptr)  {
		return 0;
	}
	left = calculateheight(root->getLeft());
	right = calculateheight(root->getRight());
	
	if ( left == -1 || right ==-1 ) return -1;
	else if ( abs(left - right) > 1 ) return -1;
	else {
		if ( left >= right) {
			greater = left;
		}
		else {
			greater = right;
		}
	}
	++greater;
	return greater;

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
