#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int numNodes(Node* node) {
	if (node == nullptr) {//base case to check if the tree has no nodes
		return 0;
	}

	//need to set variables to find amount of nodes on both the left and right of the given node
	//the recursion will continuosly move through the tree until hitting the basecase
	//continuously recurse through the node
	int greatest = 0;
	int left = numNodes(node->left);
	int right = numNodes(node->right);
	if (right <= left ) { //if the right is less than the left, set the greatest variable to the height of the left side
		greatest = left;
	}
	else if ( right >= left) {//if the right is greater than the left, set the greatest variable to the height of the right side
		greatest = right;
	}
	//since you recurse to the end, you need to account for that node as well
	//therefore iterate greatest once to return the number of nodes in the path
	greatest++;
	return greatest;

}

bool equalPaths(Node * root)
{
    if ( root == nullptr) { //base case if root has no nodes
      return true;
    }
		else if (root->right == nullptr && root->left != nullptr) { //the case for if the root only has left nodes
			return equalPaths(root->left);
		}
		else if ( root->right != nullptr && root->left == nullptr) { //the case for if the root only has right nodes
			return equalPaths(root->right);
		}
		else { //if the root has both right and left nodes
			//if both the right and left node exist, recurse through the nodes
			//find if the number of nodes on both the right and left equal each other
			//if not return false, else return true
			int nodeleft = numNodes(root->left);
			int noderight = numNodes(root->right);
			if (nodeleft != noderight) {
				return false;
			}
		}
		return true;

}


