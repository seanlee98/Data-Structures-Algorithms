/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s386lee@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree; 	//pointer to the left subtree
		Leftist_node *right_tree;	//pointer to the right subtree
		int heap_null_path_length;	//null path length of this node. Defined as the shortest path to a node that has an empty sub-tree (i.e. not full)
									//can be calculated as follows:
									//an empty node has a null-path length of -1
									//otherwise, null-path length of a node is 1 + minimum of the null-path lengths of the two children
										//a consequence of second point is that a node with no children (i.e. leaf node) or a node with exactly one child has a null-path length of 0

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const{
	return ( this == nullptr );
}

// You must implement everything

//return the element stored in this node
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}

//return address of the left sub-tree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const{
	return left_tree;
}

//return address of right sub-tree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const{
	return right_tree;
}

//return the member variable null-path length unless this is the null pointer, in which case, return -1
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
	//empty node
	if (empty()){
		return -1;
	}
	else {
		return heap_null_path_length;
	}
}

//return the number of instances of the argument in this sub-tree
template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const{
	int counter = 0;
	//recursively iterating through heap to count number of instances of obj
	if (this == nullptr){
		return 0;
	}
	if (retrieve() == obj){
		counter = 1;
	}
	if (!left_tree->empty()){
		counter = counter + left_tree->count(obj);
	}
	if (!right_tree->empty()){
		counter = counter + right_tree->count(obj);
	}
	
	return counter;
	
}


template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this){
	//if new heap is null, return
	if (new_heap == nullptr){
		return;
	}
	//otherwise, insert the new_heap into this heap: 1) if this is null, set the pointer to this to be the new heap and return
	else if(empty()) {
		ptr_to_this = new_heap;
		return;
	}
	//2) if the current node is storing a value less than or equal to the value stored in the root of the new heap, 
	//push the new node onto the right sub-tree with right_tree
	else if(retrieve() < new_heap->retrieve()){
		right()->push(new_heap, right_tree);
		++ptr_to_this->heap_null_path_length;
		//Now, update the null-path length and if the left-sub-tree has a smaller null-path length than the right sub-tree, swap the two sub-trees
		if(left_tree->null_path_length() < right_tree->null_path_length()){
			Leftist_node<Type> *temp = right_tree;
			right_tree = left_tree;
			left_tree = temp;
		}
	}
	//3) otherwise, set the pointer to this to be the new heap and push this node into the new heap (with appropriate 2nd argument)
	else {
		ptr_to_this = new_heap;
		new_heap->right()->push(this, new_heap->right_tree);
		++ptr_to_this->heap_null_path_length;
		
		//again if once push is complete and the left-sub-tree has a smaller null-path length than the right-sub-tree, we swap
		if(new_heap->left_tree->null_path_length() < new_heap->right_tree->null_path_length()){
			Leftist_node<Type> *temp = new_heap->right_tree;
			new_heap->right_tree = new_heap->left_tree;
			new_heap->left_tree = temp;
		}
	}
	
	//finally update current heap nullpathlength. if heap is empty return -1,
	//else we return 1 plus the minimum between the npl of the left-sub-tree and the right-sub-tree
	ptr_to_this->heap_null_path_length = empty() ? -1 : 1 + std::min(ptr_to_this->left()->null_path_length(), ptr_to_this->right()->null_path_length());
	
	return;
}


//if this is nullptr, return; otherwise, call clear on the left sub-tree, then on the right, and finally delete this
template <typename Type>
void Leftist_node<Type>::clear() {
	if (this == nullptr){
		return;
	}
	left_tree->clear();
	right_tree->clear();
	delete this;
	
}
#endif
