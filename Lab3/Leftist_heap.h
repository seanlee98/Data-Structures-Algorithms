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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;	//pointer to root node
		int heap_size;					//number of elements in heap

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;
		

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}



// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).

//returns true if heap is empty, false otherwise
template <typename Type>
bool Leftist_heap<Type>::empty() const{
	if (heap_size == 0){
		return true;
	}
	else{
		return false;
	}
	
}

//returns the number of nodes in the heap
template <typename Type>
int Leftist_heap<Type>::size() const{
	return heap_size;
}

//returns the null-path length of the root node
template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	return root_node->null_path_length();
}

//returns the number of instances of the argument in the heap
template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const{
	return root_node->count(obj);
}

//returns the element at the top of the heap. If the tree is empty, throw underflow exceptions
template <typename Type>
Type Leftist_heap<Type>::top() const{
	if (heap_size == 0) throw underflow();
	//return root_node;
	return root_node->retrieve();
}

//insert new element into heap by creating new leftist node and calling push on root node using root_node as a second argument
//increment heap size
template <typename Type>
void Leftist_heap<Type>::push(const Type &obj){
	Leftist_node<Type> *node = new Leftist_node<Type>(obj);
	root_node->push(node, root_node);
	++heap_size;
}

//pop the least element in the heap and delete its node (extracts min from the heap)
//if tree is empty, throw underflow exceptions
//otherwise, left sub-tree of root node is made the root node
//return the element in the popped node and decrement the heap size
template <typename Type>
Type Leftist_heap<Type>::pop(){
	//if heap is empty we throw underflow exceptions
	if(empty()) throw underflow();
	//otherwise store value of root node in temp node
	Type temp = root_node->retrieve();
	//if current heap size is 1 we clear heap and return temp
	if(heap_size == 1){
		clear();
		return temp;
	}
	//otherwise create new node that's set equal to root node. then make left-sub-tree the new root node and push right-sub-tree onto it
	//finally, delete temp new node, decrement heapsize, and return value stored in temp
	Leftist_node<Type> *tempRoot = root_node;
	root_node = tempRoot->left();
	root_node->push(tempRoot->right(), root_node);
	delete tempRoot;
	--heap_size;
	return temp;
}

template <typename Type>
void Leftist_heap<Type>::clear(){
	root_node->clear();
	root_node = nullptr;
	heap_size = 0;
}
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
