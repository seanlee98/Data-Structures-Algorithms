/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s386lee @uwaterloo.ca
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
 *    -jj2park for tester files
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations
		
		//helper function to resize array
		void resize_stack_array(int size);


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

//destructor that deletes memory allocated for array
Dynamic_range_stack::~Dynamic_range_stack() {
	// Enter your implementation here.
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;

}

//returns top of stack, can throw underflow error
int Dynamic_range_stack::top() const {
	// Enter your implementation here.
	if (entry_count == 0) throw underflow();
	return stack_array[entry_count - 1];
}

//Return the maximum object currently in the stack. It may throw an underflow exception
int Dynamic_range_stack::maximum() const {
	// Enter your implementation here.
	if (max_count == 0) throw underflow();
	return maximum_array[max_count - 1];
}

//returns minimum object currently in the stack. May throw underflow exception
int Dynamic_range_stack::minimum() const {
	// Enter your implementation here.
	if (min_count == 0) throw underflow();
	return minimum_array[min_count - 1];
	
}

//returns size of array
int Dynamic_range_stack::size() const {
	// Enter your implementation here.
	return entry_count;
}

//checks if stack is empty
//returns true if empty, false otherwise
bool Dynamic_range_stack::empty() const {
	// Enter your implementation here.
	if (entry_count == 0){
		return true;
	}
	else {
		return false;
	}
	return 0;
}

//returns current capactity of the arrays
int Dynamic_range_stack::capacity() const {
	// Enter your implementation here.
	return current_capacity;
}


/*If the stack array is full, create three new arrays which are
double in size, copy over all the entries, and delete the old arrays. Push the argument onto
the top of the stack_array, and update the other stacks if needed. Assume that push
function is not called for an item that is already in the stack (no duplicate) */
void Dynamic_range_stack::push( int const &obj ) {
	// Enter your implementation here.

	//if stack array is full, new one is created double in size, pointer points to it
	if (entry_count == current_capacity){
		resize_stack_array(2*current_capacity);
		current_capacity = current_capacity*2;
	}
	
	stack_array[entry_count] = obj;
	entry_count++;
	
	//deciding if to push elements onto max/min arrays
	//if max_array is empty, first element is pushed
	if(max_count == 0){
		maximum_array[max_count] = obj;
		max_count++;
	}
	//if next element being pushed is greater than current top element in max_array, push to stack
	if(obj > maximum_array[max_count - 1]){
		maximum_array[max_count] = obj;
		max_count++;
	}
	//if min_array is empty, first element is pushed
	if(min_count == 0){
		minimum_array[min_count] = obj;
		min_count++;
	}
	//if next element being pushed is less than current top element in min_array, push to stack
	if(obj < minimum_array[min_count - 1]){
		minimum_array[min_count] = obj;
		min_count++;
	}

}

/*Pop the top element off of the stack(s) by removing it from the stack array and
update other stacks if needed. This may throw an underflow exception*/
int Dynamic_range_stack::pop() {
	// Enter your implementation here.
	if (entry_count == 0) throw underflow();
	
	//check if array size has gone down to 1/4 capacity, if so capacity/2
	if (entry_count <= current_capacity/4 && current_capacity > initial_capacity) {
		resize_stack_array (current_capacity/2);
		current_capacity = current_capacity/2;		
	}
	//if current top element of main stack being popped matches the top element of min/max array, decrement min/max stacks
	if((entry_count == min_count) || (top() == minimum_array[min_count - 1])){
		min_count--;
	}
	if((entry_count == max_count) || (top() == maximum_array[max_count - 1])){
		max_count--;
	}
	entry_count--;
	
	return stack_array[entry_count];
}

/*Empties the stacks by resetting the member variables. If the current array
size does not equal the initial size, delete the arrays and create three new arrays equal to
the initial size*/
void Dynamic_range_stack::clear() {
	// Enter your implementation here.

	if(current_capacity != initial_capacity){
		delete[] stack_array;
		delete[] maximum_array;
		delete[] minimum_array;
		stack_array = new int[initial_capacity];
		maximum_array = new int[initial_capacity];
		minimum_array = new int[initial_capacity];

		current_capacity = initial_capacity;
		
		
	}
	entry_count = 0;
	max_count = 0;
	min_count = 0;
	initial_capacity = 10;
	current_capacity = 10;
	
}

//helper function to resize array
void Dynamic_range_stack::resize_stack_array(int size){
	//temp stacks to carry over entries in resized arrays
	int* stackTemp = new int[size];
	int* maxTemp = new int[size];
	int* minTemp = new int[size];

	for (int i = 0; i< entry_count; i++){
		stackTemp[i] = stack_array[i];
		maxTemp[i] = maximum_array[i];
		minTemp[i] = minimum_array[i];
	}
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
	stack_array = stackTemp;
	maximum_array = maxTemp;
	minimum_array = minTemp;
	
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
