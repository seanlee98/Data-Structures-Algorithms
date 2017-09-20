#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "Pair.h"

class Priority_Queue {
	private:

		Pair *array;
		int left( int );
		int right( int );
		int parent( int );
		void heapify( int ); 
		int size;
		int maxSize;

	public:
		Priority_Queue( int );
		~Priority_Queue();

		void insert( int, double );
		//void decreaseKey( int , double );
		Pair getMin();
		Pair extractMin();
		void deleteMin();
		bool empty() const;
		void clear();
		bool checkVertex(int, double);
};


Priority_Queue::Priority_Queue( int n ){
	array = new Pair[n + 1];
	maxSize = n;
	size = 0;
}


Priority_Queue::~Priority_Queue(){	
	delete[] array;
	
}

bool Priority_Queue::empty() const {
	return size == 0;	
}

int Priority_Queue::left( int i ) {

	//Gets the index of the left child of a node in the array
	return 2 *i + 1;
}

int Priority_Queue::right( int i ) {

	//Gets index of the right child of a node in the array
	return 2 *i;
}

int Priority_Queue::parent( int i ) {
	
	//Gets the index of the parent of a node in the array
	//return std::max((i/ 2), 0);
	return i/2;
}
void Priority_Queue::clear() {
	size = 0;
}


void Priority_Queue::insert(int i, double key ) {
	if (size > maxSize || size < 0){
		return;
	}
	size++;
	Pair newVertex(i, key);
	array[size - 1] = newVertex;
	heapify(0);
}

bool Priority_Queue::checkVertex(int vertex, double distance){
	for(int i = 0; i < size; i++){
		if(array[i].vertex() > vertex){
			return false;
		}
		else if(array[i].vertex() == vertex && array[i].weight() == distance){
			return true;
		}
	}
	
	return false;
}
void Priority_Queue::heapify( int i ) {
	
	//Picks which nodes contains the smaller weight value and assigns the index to min
	//Intially assigned as current i
	int min = i;
	if(left(i) < size && (array[left(i)].weight() < array[i].weight())){
		min = left(i);
	}	
	if(right(i) < size && (array[right(i)].weight() < array[min].weight())){
		min = right(i);
	}
	//Swap the parent with the node which has a smaller weight value and recursivelt call heapify on that node 
	//to get the minimum valued node to the root
	if(min != i){
		//Swap
		Pair tmp = array[i];
		array[i] = array[min];
		array[min] = tmp;
		heapify(min);
	}	
	
}

Pair Priority_Queue::getMin() {	
	//Returns the minimum value (Root) node from the heap and assigns the last node of the array as the root and 
	//calls heapify on it to maintain correct heap structure
	Pair min = array[0];	
	return min;
}

void Priority_Queue::deleteMin(){
	if (size <= 0){
		return;
	}
	array[0] = array[size - 1];
	size--;
	if (size > 0){
		heapify(0);
	}	
}

#endif