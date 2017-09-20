#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  s386lee
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count; //number of elements currently in the hashtable
		int power; //associated with the capacity of the hashtable (array_size = 2^power)
		int array_size; //capacity of hashtable
		T *array; //array of objecs of type T. Contains values placed in the hashtable
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ): //construtor takes argument m and creates hashtable with 2^m bins, indexed from 0 to 2^m -1. 
//default value of m is 5
//notice that you need to allocate and initialize two arrays, one for storing values in the hashtable and one for storing status of the bins
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

//destructor: deletes memory allocated for hashtable
//notice that hashtable is represented with two arrays, both must be deleted
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// enter your implemetation here 
	delete[] array;
	delete[] array_state;
}

//Return the number of elements currently stored in the hashtable
template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implemetation here 
	return count;
}

//return the number of bins in the hashtable
template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implemetation here 
	return array_size;
}


//return true if hashtable is empty, false otherwise
template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implemetation here 
	if(size() == 0){
		return true;
	}
	else{
		return false;
	}
}

//hash functions
//first hash function statically casts the obj(input) to an int; if obj's value is negative it will take the modulo M of the obj and then add M
//otherwise it will just take modulo M of the obj, where M is equal to the array size
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// enter your implemetation here 
	int i = static_cast<int>(obj);
	
	//if negative
	if((i%array_size)< 0){
		return (i%array_size) + array_size;
	}
	else{
		return i%array_size;
	}
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// enter your implemetation here 
	//obj is statically cast as int
	int i = static_cast<int>(obj);
	
	//checks if (i/M)%M returns negative value, add M if it is
	//then checks if(i/M)%M returns even value, if so it adds 1 to make it odd
	
	if(((i/array_size)%array_size) < 0){
		return ((i/array_size)%array_size) + array_size;
	}
	if(((i/array_size)%array_size)%2 == 0){
			return ((i/array_size)%array_size) + 1;
		}
	else{
		return (i/array_size)%array_size;
	}
}

//Return true if the object obj is in the hashtable and false otherwise
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// enter your implemetation here 
	bool isThere = false;
	int position;
	int probe = h1(obj);
	int offset = h2(obj);
	
	//checking at proper index if obj is contained
	for (int i = 0; i <array_size; i ++){
		position = ((probe+(i*offset)) % (array_size));
		if (array[position]==(obj) && array_state[position]==OCCUPIED){
			isThere = true;
			break;
		}
	}
	
	return isThere;
}

//return the entry in bin n, behaviour of function is undef if the bin is not filled
//will only be used to test the class with the expected locations
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implemetation here 
	return array[n];
}

//Insert new object into the hashtable in the appropriate bin as determined by the two aforementioned hash functions and the rule of double hashing
//if table is full, throw overflow exception
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 // enter your implemetation here 	
	 if(size() == array_size) throw overflow();
	 int probe = h1(obj);
	 int offset = h2(obj);
	 
	 //traversing through hashtable only while array_state at the probe is occupied
	 //when empty bin is found, the obj is inserted
	 
	while(array_state[probe] == OCCUPIED){
		//finding new index to insert obj by offset
		probe = (probe+offset)%array_size;
	}
	array[probe] = obj;
	array_state[probe] = OCCUPIED;
	count++;
		 
}

//remove the object from the hashtable if it is in the hashtable by setting the corresponding flag of the bin to be deleted
//returning false if it is not
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implemetation here 	
	int probe = h1(obj);
	int offset = h2(obj);
	bool flagValue = false;
	//traversing through hash table with double hash function
	//loop ends when every bin has been probed by double hash function
	
	if(count == 0){
		return false;
	}
	for(int i = 0; i < array_size; i++){
		int position = (probe + i*offset)%array_size;
		
		//deletes desired obj when obj at the probe is found and when state is occupied
		if(array[position] == obj && array_state[position] == OCCUPIED){
			array_state[position] = DELETED;
			count--;
			flagValue = true;
			break;
		}
	}
	return flagValue;
}

//remove all the elements in the hashtable
template<typename T >
void DoubleHashTable<T >::clear() {
	 // enter your implemetation here 	
	 for(int i = 0; i < array_size; i++){
		 array_state[i] = EMPTY;
	 }	
	 count = 0;
}

//function used to print the class for debugging purposes
//will not be tested
template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here 	
	return;
}

#endif
