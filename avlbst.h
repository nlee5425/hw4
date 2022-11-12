#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    //rotate left
    //rotate right
protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key& key);  
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
		
    // Add helper functions here
		void rotateright(AVLNode <Key,Value>* n);
		void rotateleft(AVLNode <Key,Value>* n);
		void insertfix( AVLNode <Key,Value>* p , AVLNode <Key,Value>* n );
		void removefix( AVLNode <Key,Value>* p , int8_t difference );

};


template<class Key, class Value>
void AVLTree<Key, Value>::rotateright (AVLNode <Key,Value>* n)
{
	AVLNode<Key, Value>* nleft = n->getLeft();
	AVLNode<Key, Value>* nparent = n->getParent();
	if ( nparent != NULL ) { //need to check if nparent is NULL, which means n is root
		if ( nparent->getRight() == n ) { //if n is right child of nparent
			nparent->setRight(nleft);
		}
		else { //if n is left child of nparent
			nparent->setLeft(nleft);
		}
	}
	else { //set nleft to the new root_
		this->root_ = nleft;
	}
	nleft->setParent(nparent); //setting child of n to nparent
	n->setParent(nleft);
	AVLNode<Key, Value>* nleft_right = nleft->getRight(); 
	if ( nleft_right != NULL ) {//if left child has a right child
		nleft_right->setParent(n);
	}
	n->setLeft(nleft_right);
	nleft->setRight(n);	
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateleft (AVLNode <Key, Value>* n )
{
	AVLNode<Key, Value>* nright = n->getRight();
	AVLNode<Key, Value>* nparent = n->getParent();
	if ( nparent != NULL ) { //need to check if nparent is NULL, meaning n is root
		if ( nparent->getRight() == n ) { //if n is right child of nparent
			nparent->setRight(nright);
		}
		else { //if n is left child of nparent
			nparent->setLeft(nright);
		}
	}
	else { //set nright to the new root_
		this->root_ = nright;
	}
	nright->setParent(nparent); //setting child of n to nparent
	n->setParent(nright);
	AVLNode<Key, Value>* nright_left = nright->getLeft();
	if ( nright_left != NULL ) { //if right child has a left child
		nright_left->setParent(n);
	}
	n->setRight(nright_left);
	nright->setLeft(n);


}



template<class Key, class Value>
void AVLTree<Key, Value>::insertfix( AVLNode <Key,Value>* p , AVLNode <Key,Value>* n ) 
{
	if ( p == NULL  || p->getParent() == NULL ) {
		return;
	}
	AVLNode<Key, Value>* pparent = p->getParent();
	if ( pparent->getRight() == p ) { //if p is right child of pparent
		pparent->updateBalance(1); //setting new balance
		if (pparent->getBalance() == 0 ) { //if pparent balance is 0, the tree is balanced
			return;
		}
		else if ( pparent->getBalance() == 1 ) { //if pparent balance is 1, recurse through to balance tree
			insertfix(pparent, p);
		}
		else { //if pparent balance is 2 , rotate nodes
			if ( p->getRight() == n ) { //then zig-zig, means nodes are in straight direction
				rotateleft(pparent);
				pparent->setBalance(0);
				p->setBalance(0);
				return;
			}
			else { //zig-zag
				rotateright(p);
				rotateleft(pparent);
				int8_t nbalance = n->getBalance();
				//checking child balance to see what the new rotated nodes balances will become
				if ( nbalance == 1 ) { 
						p->setBalance(0);
						pparent->setBalance(-1);
						n->setBalance(0);
				}
				else if ( nbalance == 0 ) {
					p->setBalance(0);
					pparent->setBalance(0);
					n->setBalance(0);
				}
				else if ( nbalance == -1 ) {
					p->setBalance(1);
					pparent->setBalance(0);
					n->setBalance(0);
				}
				return;
			}
		}
	}
	else if ( pparent->getLeft() == p ) { //if p is left child of pparent
		pparent->updateBalance(-1); //setting new balance
		if (pparent->getBalance() == 0 ) {
			return;
		}
		else if ( pparent->getBalance() == -1 ) { //if pparent balance is -1, recurse through to balance tree
			insertfix(pparent, p);
		}
		else { //if pparent balance is -2 , rotate nodes
			if ( p->getLeft() == n ) { //then zig-zig
				rotateright(pparent);
				p->setBalance(0);
				pparent->setBalance(0);
				return;
			}
			else { //then zig-zag
				rotateleft(p);//goes here
				rotateright(pparent);
				int8_t nbalance = n->getBalance();
				//checking child balance to see what the new rotated nodes balances will become
				if ( nbalance == -1 ) {
						p->setBalance(0);
						pparent->setBalance(1);
						n->setBalance(0);
				}
				else if ( nbalance == 0 ) {
					p->setBalance(0);
					pparent->setBalance(0);
					n->setBalance(0);
				}
				else if ( nbalance == 1 ) {
					p->setBalance(-1);
					pparent->setBalance(0);
					n->setBalance(0);
				}
				return;
			}
		}
	}
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
	Key currentkey = new_item.first; //find out how to access value
	Value replace = new_item.second;
	if (this->empty() == false ) {
		AVLNode<Key, Value>* bstiter = (AVLNode<Key,Value>*)this->root_;
		while ( true ) {
			Key checkerkey = bstiter->getKey();
			if ( currentkey == checkerkey ) { //if the key of the keyvaluepair is equal to current key of location, replace the values
				bstiter->setValue(replace);
				break;
			}
			else if ( currentkey < checkerkey ) { //if key of keyvaluepair is less than current key of location, move left
				if ( bstiter->getLeft() == NULL ) { //if the left is NULL, add to the tree
					AVLNode<Key, Value>* addnode  = new AVLNode<Key, Value>(currentkey , replace , bstiter);
					bstiter->setLeft(addnode);
					if ( bstiter->getBalance() == 1 ) { //if balance is 1, adding left node will set it to 0
						bstiter->setBalance(0);
					}
					else if ( bstiter->getBalance() == 0 ) { //if balance is 0, adding left node will set it to -1, then call insert-fix
						bstiter->setBalance(-1);
						insertfix( bstiter , addnode );
					}
					break;
				}
				bstiter = bstiter->getLeft();
			}
			else if ( currentkey > checkerkey) { //if key of keyvaluepair is greater than current key of location, go right
				if ( bstiter->getRight() == NULL ) { //if the right is NULL, add to tree
					AVLNode<Key, Value>* addnode  = new AVLNode<Key, Value>(currentkey , replace , bstiter);
					bstiter->setRight(addnode);	
					if ( bstiter->getBalance() == -1 ) { //if the balance is -1, adding right node will set it to 0
						bstiter->setBalance(0);
					}
					else if ( bstiter->getBalance() == 0 ) { //if balance is 0, adding right node will set it to 1, then call insert-fix
						bstiter->setBalance(1);
						
						insertfix( bstiter , addnode );
					}
					break;
				}
				bstiter = bstiter->getRight();
			}
		}
	}
	else {
		AVLNode<Key, Value>* newroot = new AVLNode<Key, Value>(currentkey, replace, NULL);
		this->root_ = newroot;
	}
}


template<class Key, class Value>
void AVLTree<Key, Value>::removefix( AVLNode <Key,Value>* p , int8_t difference )
{
	if (p == NULL ) {
		return;
	}
	AVLNode<Key, Value>* pparent = p->getParent();
	int8_t nextdiff;
	if ( pparent != NULL ) { //if p is the root_ of the tree
		if ( pparent->getLeft() == p ) { //if p is right child of pparent
			nextdiff = 1;
		}
		else { //if p is left child of pparent
			nextdiff = -1;
		}
	}
	//based on the balances of the difference which is passed in and balance of parent
	//determine whether or not to zig-zig or zig-zag and what the new balances should be
	int8_t pbalance = p->getBalance();
	int8_t tbalance = pbalance + difference;
	if ( tbalance == -2 || tbalance == 2 ) { //two cases to rotate if total balance is -2 or 2
		if ( tbalance == -2 ) { //if tbalance == -2
			AVLNode<Key, Value>* pleft = p->getLeft();
			int8_t pleftbal = pleft->getBalance();
			if ( pleftbal == -1 ) { //if left child has another child
				rotateright(p);
				p->setBalance(0);
				pleft->setBalance(0);
				removefix(pparent , nextdiff);
			}
			else if ( pleftbal == 0 ) { //if no children
				rotateright(p);
				p->setBalance(-1);
				pleft->setBalance(1);
			}
			else if ( pleftbal == 1 ) { //if left child has another child
				AVLNode<Key, Value>* pleft_right = pleft->getRight();
				rotateleft(pleft);
				rotateright(p);
				int8_t plrbal = pleft_right->getBalance();
				if ( plrbal == 1 ) {
					p->setBalance(0);
					pleft->setBalance(-1);
					pleft_right->setBalance(0);
				}
				else if ( plrbal == 0 ) {
					p->setBalance(0);
					pleft->setBalance(0);
					pleft_right->setBalance(0);
				}
				else if ( plrbal == -1 ) {
					p->setBalance(1);
					pleft->setBalance(0);
					pleft_right->setBalance(0);		
				}
				removefix(pparent, nextdiff); //call removefix again to update parents balance
			}
			
		}
		else { //if tbalance == 2, case if total balance is 2, do opposite as if total balance was -2
			AVLNode<Key, Value>* pright = p->getRight();
			int8_t prightbal = pright->getBalance();
			if ( prightbal == 1 ) {
				rotateleft(p);
				p->setBalance(0);
				pright->setBalance(0);
				removefix(pparent , nextdiff);
			}
			else if ( prightbal == 0 ) {
				rotateleft(p);
				p->setBalance(1);
				pright->setBalance(-1);
			}
			else if ( prightbal == -1 ) {
				AVLNode<Key, Value>* pright_left = pright->getLeft();
				rotateright(pright);
				rotateleft(p);
				int8_t prlbal = pright_left->getBalance();
				if ( prlbal == -1 ) {
					p->setBalance(0);
					pright->setBalance(1);
					pright_left->setBalance(0);
				}
				else if ( prlbal == 0 ) {
					p->setBalance(0);
					pright->setBalance(0);
					pright_left->setBalance(0);
				}
				else if ( prlbal == 1) {
					p->setBalance(-1);
					pright->setBalance(0);
					pright_left->setBalance(0);		
				}
				removefix(pparent, nextdiff);
			}
			
		}
	}
	else if ( tbalance == -1 || tbalance == 1) {
		if ( tbalance == -1 ) {
			p->setBalance(-1);
			return;
		}
		else {
			p->setBalance(1);
			return;
		}
	}
	else if ( tbalance == 0 ) {
		
		removefix( pparent , nextdiff ); //recursive call up the tree
		p->updateBalance(difference);
		
	}
	
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
			if ( this->root_ != NULL) {
			AVLNode<Key, Value> *remover = (AVLNode<Key, Value>*)this->root_;
			while ( true ) {
			Key check = remover->getKey();
			if ( check == key ) { //if we found the key
				if ( remover->getLeft() == NULL && remover->getRight() == NULL ) { //if node has no childre
					if ( remover == this->root_ ) {
						remover->setBalance(0);
						this->root_ = NULL;
						delete this->root_;
						break;
					}
					AVLNode<Key, Value> *parent = remover->getParent();
					if ( parent->getRight() == remover ) { //if remover is right child
						parent->setRight(NULL);
						removefix(parent , -1); //call removefix function to rotate and update balances
					}
					else if ( parent->getLeft() == remover ) { //if remover is left child
						parent->setLeft(NULL);
						removefix(parent , 1);//call removefix function to rotate and update balances
					}
					remover->setParent(NULL);
					delete remover;
					break;
				}
				else if ( remover->getLeft() == NULL || remover->getRight() == NULL ) { //if node has one child
					if ( remover->getLeft() == NULL ) { //if the left node is NULL, right child exists
						AVLNode<Key, Value> *rightchild = remover->getRight();
						if ( remover->getParent() == NULL ) { //checking if the current node is the root_
							remover->setBalance(0);
							this->root_ = rightchild;
							rightchild->setParent(NULL);
							remover->setParent(NULL);	//remove locations of remover
							remover->setRight(NULL);
							break;
						}
						AVLNode<Key, Value> *parent = remover->getParent();
						if ( remover == parent->getRight() ) { //if remover is the right child of its parent
							parent->setRight(rightchild);
							rightchild->setParent(parent);
							removefix(parent , -1);//call removefix function to rotate and update balances
							
						}	
						else{ //if remover is the leftchild of its parent
							parent->setLeft(rightchild);
							rightchild->setParent(parent);
							removefix(parent , 1);//call removefix function to rotate and update balances
						}		
						remover->setParent(NULL);	//remove locations of remover
						remover->setRight(NULL);
					}
					else if ( remover->getRight() == NULL ) { //if the right node is NULL, left child exists
						AVLNode<Key, Value> *leftchild = remover->getLeft();
						if ( remover->getParent() == NULL ) { //checking if the current node is the root_
							remover->setBalance(0);
							this->root_ = leftchild;
							leftchild->setParent(NULL);
							remover->setParent(NULL);	//remove locations of remover
							remover->setLeft(NULL);
							break;
						}
						AVLNode<Key, Value> *parent = remover->getParent();
						if ( remover == parent->getRight() ) { //if remover is the right child of its parent
							parent->setRight(leftchild);
							leftchild->setParent(parent);		
							removefix(parent , -1);//call removefix function to rotate and update balances
						}	
						else{ //if remover is the left child of its parent
							parent->setLeft(leftchild);
							leftchild->setParent(parent);
							removefix(parent , 1);//call removefix function to rotate and update balances
						}	
						remover->setParent(NULL); //remove locations of remover
						remover->setLeft(NULL);	
					}
					delete remover;
					break;
				}
				else { //if node has both children
					AVLNode<Key, Value> *pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(remover));
					
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
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
