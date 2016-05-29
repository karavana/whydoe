#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>
#include <iomanip>      // std::setw

using namespace std;

template <class Object>
class BinaryNode
{
public:
   Object element;   // this is the item stored in the node
   BinaryNode *left;
   BinaryNode *right;

   BinaryNode( const Object& theElement, BinaryNode *lt, BinaryNode *rt ): 
		element( theElement ), left( lt ), right( rt ) { } 

};


/**
 * Method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t )
{
  if( t == NULL )
	  return NULL;
  else if( x < t->element )
	  return find( x, t->left );
  else if( t->element < x )
	  return find( x, t->right );
  else
	  return t;    // Match
}

/**
 * method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
BinaryNode<Comparable> *
findMin( BinaryNode<Comparable> *t ) 
{
   if( t == NULL )
	   return NULL;
   if( t->left == NULL )
	   return t;
   return findMin( t->left );
}

/**
 *method to find the largest item in a subtree t.
 *Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable> *
findMax( BinaryNode<Comparable> *t ) 
{
  if( t != NULL )
	while( t->right != NULL )
	   t = t->right;
  return t;
}

/* method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void insert( const Comparable & x, BinaryNode<Comparable> * & t ) 
{
   if( t == NULL )
	  t = new BinaryNode<Comparable>( x, NULL, NULL );
   else if( x < t->element )
	  insert( x, t->left );
   else if( t->element < x )
	  insert( x, t->right );
   else
	  ;  // Duplicate; do nothing
}

template <class Comparable>
void remove( const Comparable & x, BinaryNode<Comparable> * & t ) 
{
   if( t == NULL )
	  return;   // Item not found; do nothing
   if( x < t->element )
	  remove( x, t->left );
   else if( t->element < x )
	  remove( x, t->right );
   else if ( t->left != NULL && t->right != NULL) {
	   t->element = findMin( t->right )->element;
	   remove( t->element, t->right );
   }
   else   {
	  BinaryNode<Comparable> *oldNode = t;
	  t = ( t->left != NULL ) ? t->left : t->right;
	  delete oldNode;
	}
}

template <class Comparable>
void deleteNode(BinaryNode<Comparable> * t)
{
	if ( !t )	return;
	if ( t->left )	deleteNode(t->left);
	if ( t->right )	deleteNode(t->right);
	delete 	t; 
}

template <class Comparable>
int nodeCount(BinaryNode<Comparable> * t){
	if(t==NULL) return 0;
	return 1 + nodeCount(t->left) + nodeCount(t->right);
}

template <class Comparable>
void preorder(BinaryNode<Comparable> * t )
{
	if (t != NULL)
	{
		cout << t->element << endl;
		preorder(t->left);
		preorder(t->right);
	}
}

template <class Comparable>
void preorderList(BinaryNode<Comparable> *t, vector<string>& result)
{
	if (t != NULL)
	{
		result.push_back(t->element);
		preorderList(t->left, result);
		preorderList(t->right, result);	
	}
}

template <class Comparable>
void postorder(BinaryNode<Comparable> * t )
{
	if (t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		cout << t->element << endl;
	}
}

template <class Comparable>
void postorderList(BinaryNode<Comparable> *t, vector<string>& result)
{
	if (t != NULL)
	{
		postorderList(t->left, result);
		postorderList(t->right, result);
		result.push_back(t->element);
	}
}

template <class Comparable>
int maxDepth(BinaryNode<Comparable> * t) 
{
   if (t==NULL) 
	   return 0;
   else
   {
	   /* compute the depth of each subtree */
	   int lDepth = maxDepth(t->left);
	   int rDepth = maxDepth(t->right);
 
	   /* use the larger one */
	   if (lDepth > rDepth) 
		   return(lDepth+1);
	   else return(rDepth+1);
   }
} 

template <class Comparable>
void printTree(BinaryNode<Comparable> * t, int indent=0)
{    
	if(t != NULL) {
		if(t->right) {
			printTree(t->right, indent+4);
		}
		if (indent) {
			cout << setw(indent) << ' ';
		}
		if (t->right) cout<<" /\n" << setw(indent) << ' ';
		cout<< t->element << "\n ";
		if(t->left) {
			cout << setw(indent) << ' ' <<" \\\n";
			printTree(t->left, indent+4);
		}
	}
	else{
		cout << "***NULL***" << endl;
	}
}

template <class Comparable>
void inorder(BinaryNode<Comparable> * t )
{
	if (t != NULL)
	{
		inorder(t->left);
		cout << t->element << endl;
		inorder(t->right);
	}
}

template <class Comparable>
void levelorder(BinaryNode<Comparable> * t )
{

	std::queue<BinaryNode<Comparable> *> myQueue;
	BinaryNode<Comparable> * tmp;

	if (t != NULL) myQueue.push(t);

	while (! myQueue.empty())
	{	
		tmp=myQueue.front();
		cout << tmp->element << endl;

		myQueue.pop();
		
		if (tmp-> left != NULL) myQueue.push(tmp->left);
		if (tmp-> right != NULL) myQueue.push(tmp->right);
	}
}


template <class Comparable>
void iterativePreorder(BinaryNode<Comparable> * t )
{

	std::stack<BinaryNode<Comparable> *> myStack;
	BinaryNode<Comparable> * tmp;

	if (t != NULL) myStack.push(t);

	while (! myStack.empty())
	{	
		tmp=myStack.top();
		cout << tmp->element << endl;

		myStack.pop();
		
		if (tmp-> right != NULL) myStack.push(tmp->right);
		if (tmp-> left != NULL) myStack.push(tmp->left);
	}
}

template <class Comparable>
void iterativePostorder(BinaryNode<Comparable> * t )
{
	std::stack<BinaryNode<Comparable> *> myStack;
	BinaryNode<Comparable> * curr;
	BinaryNode<Comparable> * prev = NULL;


	if (t == NULL) return;

	myStack.push(t);

	while (! myStack.empty())
	{
		curr = myStack.top();

		if ((!prev) || (prev -> left == curr) || (prev->right == curr))
		{
			if (curr->left) myStack.push(curr->left);
			else if (curr->right) myStack.push(curr->right);
			else { 
				cout << curr->element << endl;
				myStack.pop();
			}
		}

		else if (curr->left == prev) {
			if (curr->right) myStack.push(curr->right);
			else {
				cout << curr->element << endl;
				myStack.pop();
			}
		}

		else if (curr->right == prev) {	
			cout << curr->element << endl;
			myStack.pop();
		}

		prev = curr;
	}
}

template <class Comparable>
void iterativeInorder(BinaryNode<Comparable> * t )
{
	std::stack<BinaryNode<Comparable> *> myStack;
	BinaryNode<Comparable> * tmp = t;

	while ((tmp) || (! myStack.empty()))
	{

		if (tmp) {
			myStack.push(tmp);
			tmp = tmp -> left;
		}

		else {
			tmp = myStack.top();
			myStack.pop();
			cout << tmp->element << endl;
			tmp = tmp -> right;
		}
	}
}

template <class Comparable>
int getHeight(BinaryNode<Comparable> * t)
{
   if (t == NULL)
   {
      return -1;
   }

   int left = getHeight(t->left);
   int right = getHeight(t->right); 

   return 1 + max(left, right);
}


template <class Comparable>
void getLine(const BinaryNode<Comparable> * t, int depth, vector<Comparable>& elements)
{
		string placeholder = "XXX";
        if (depth <= 0 && t != nullptr) {
                elements.push_back(t->element);
                return;
        }
        if (t->left != nullptr)
                getLine(t->left, depth-1, elements);
        else if (depth-1 <= 0)
                elements.push_back(placeholder);
        if (t->right != nullptr)
                getLine(t->right, depth-1, elements);
        else if (depth-1 <= 0)
                elements.push_back(placeholder);
}

template <class Comparable>
void printRow(const BinaryNode<Comparable> *t, const int height, int depth)
{
	string placeholder = "XXX";
    vector<string> vec;
    getLine(t, depth, vec);
    cout << setw((height - depth)*2); // scale setw with depth
    bool toggle = true; // start with left
    if (vec.size() > 1) {
            for (string v : vec) {
                    if (v != placeholder) {
                            if (toggle)
                                    cout << "/" << "   ";
                            else
                                    cout << "\\" << "   ";
                    }
                    toggle = !toggle;
            }
            cout << endl;
            cout << setw((height - depth)*2);
    }
    for (string v : vec) {
            if (v != placeholder)
                    cout << v << "   ";
    }
    cout << endl;
}

// create a pretty vertical tree
template <class Comparable>
void prettyPrint(BinaryNode<Comparable> *t)
{
  int height = getHeight(t) * 2;
  for (int i = 0 ; i < height; i ++) {
     printRow(t, height, i);
  }
}

#endif