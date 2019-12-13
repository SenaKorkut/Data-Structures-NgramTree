/** @file BST.cpp. */
#include <cstddef>   // definition of NULL
#include <new>       // for bad_alloc
#include "NgramTree.h" // header file
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

NgramTree::NgramTree() : root(NULL){
}  // end default constructor

NgramTree::NgramTree(const NgramTree& tree){
   copyTree(tree.root, root);
}  // end copy constructor

NgramTree::~NgramTree(){
   destroyTree(root);
}  // end destructor

void NgramTree::generateTree ( string fileName , int n ) {
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line)) {
		for (int i = 0; i < line.length()-n +1; i++) {
		string item = line.substr(i,n);
			if ( item.find(" ") == string::npos ) {
				addNgram( item );
			}
		}
	}
	file.close();
}

void NgramTree::addNgram(const string& newItem) {
		insertItem(root, newItem);
}

void NgramTree::insertItem(TreeNode *& treePtr, const string& newItem) {
		// Position of insertion found; insert after leaf

		if (treePtr == NULL) {
			treePtr = new TreeNode;
			treePtr-> item = newItem;
			treePtr->counts = 1;
			treePtr->leftChildPtr = NULL;
			treePtr->rightChildPtr = NULL;
		}

		else if ( treePtr->item == newItem) {
			treePtr->counts+= 1;
		}
		else if(newItem < treePtr->item) {
			insertItem(treePtr->leftChildPtr, newItem);
		}

		else {
			insertItem(treePtr->rightChildPtr, newItem);
		}

}

bool NgramTree::isComplete(){
	bool ctrl = isComplete2(root);
    return ctrl;

}

bool NgramTree::isComplete2( TreeNode*& treePtr) {

	if (treePtr == NULL) {
		return true;
	}
	int diffHeight = getHeight(treePtr->leftChildPtr) - getHeight(treePtr->rightChildPtr);
	if ( abs(diffHeight) == 0 || abs(diffHeight) == 1) {
		return isComplete2(treePtr->leftChildPtr)&&isComplete2(treePtr->rightChildPtr);
	}
	else {
		return false;
	}


}

bool NgramTree::isFull() {
	int nGrams = getTotalNgramCount();
	int height = getHeight(root);

	if ( height == 0) {
		return true;
	}
	if ( pow(2, height)-1 == nGrams) {
		return true;
	}
	else {
		return false;
	}
}

int NgramTree::getHeight( TreeNode*& treePtr) {
	if ( treePtr == NULL) {
		return 0;
	}
	return 1 + max(getHeight(treePtr->leftChildPtr), getHeight(treePtr->rightChildPtr));

}

int NgramTree::getTotalNgramCount() {

	int sum = getTotalNgramCount2(root);
	return sum;
}

int NgramTree::getTotalNgramCount2(TreeNode* treePtr) {
	if ( treePtr == NULL) {
		return 0;
	}
	return 1 + getTotalNgramCount2(treePtr->leftChildPtr) + getTotalNgramCount2(treePtr->rightChildPtr);
}

void NgramTree::inorder(TreeNode* treePtr) {
	if (treePtr != NULL) {
		inorder(treePtr->leftChildPtr);
		cout<< treePtr->item << " appears " << treePtr->counts << " time(s)" << endl;
		inorder(treePtr->rightChildPtr);
		}
}

void NgramTree::printNgramFrequencies() {
	inorder(root);
}

void NgramTree::destroyTree(TreeNode *& treePtr){
   // postorder traversal
   if (treePtr != NULL)
   {  destroyTree(treePtr->leftChildPtr);
      destroyTree(treePtr->rightChildPtr);
      delete treePtr;
      treePtr = NULL;
   }  // end if
}  // end destroyTree

void NgramTree::copyTree(TreeNode *treePtr,TreeNode *& newTreePtr) const{
   // preorder traversal
   if (treePtr != NULL)
   {  // copy node
      try
      {
	 newTreePtr = new TreeNode;
	 newTreePtr->item = treePtr->item;
	 newTreePtr->leftChildPtr = NULL;
	 newTreePtr->rightChildPtr = NULL;
	 newTreePtr->counts = treePtr->counts;
	 copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
	 copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
      }
      catch (bad_alloc e)
      {
   }
   }
   else
      newTreePtr = NULL;  // copy empty tree
  // end copyTree
}
