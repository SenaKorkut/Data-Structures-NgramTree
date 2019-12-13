#ifndef NGRAMTREE_H_INCLUDED
#define NGRAMTREE_H_INCLUDED
#include <string>
using namespace std;
	struct TreeNode{
	string item;
	int counts;
	TreeNode *leftChildPtr;
	TreeNode *rightChildPtr;
};
class NgramTree{
private:
	TreeNode *root;
public:
NgramTree();
NgramTree(const NgramTree& tree);
~NgramTree();
bool isEmpty() const;
void addNgram(const string& newItem);
void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const;
void destroyTree(TreeNode *& treePtr);
int getTotalNgramCount ();
int getTotalNgramCount2(TreeNode* treePtr);
void printNgramFrequencies ();
bool isComplete ();
bool isFull ();
void generateTree ( std::string fileName , int n );
void inorder( TreeNode* treePtr);
bool isComplete2( TreeNode*& treePtr);
int getHeight( TreeNode*& treePtr);
void insertItem(TreeNode * &treePtr,const string& item);
};
#endif // NGRAMTREE_H_INCLUDED
