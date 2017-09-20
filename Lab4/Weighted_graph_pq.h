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
#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Priority_Queue.h"
#include "ece250.h"
#include "Exception.h"
#include "Pair.h"

// include whatever classes you want

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
		double **matrix;
		int *degree_count;
		int number_of_edges;
		int number_of_vertices;
		double* D;
		Priority_Queue *pqueue;

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int size ){
degree_count = new int[size];
number_of_edges = 0;
number_of_vertices = size;
matrix = new double *[size];
for (int rowIndex = 0; rowIndex < number_of_vertices; ++rowIndex){
	matrix[rowIndex] = new double[number_of_vertices];
	for (int colIndex = 0; colIndex < number_of_vertices; ++colIndex){
		matrix[rowIndex][colIndex] = INF;
	}
}
D = new double[size];
pqueue = new Priority_Queue(number_of_vertices + 1);


	//std::cout << "m ->" << m << std::endl;
}

Weighted_graph::~Weighted_graph(){
	delete[] degree_count;
	for(int i = 0; i < number_of_vertices; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;	
	delete[] D;
	delete pqueue;
	
}

int Weighted_graph::degree(int v) const {
	if (v < 0 || v >= number_of_vertices) throw illegal_argument();
	return degree_count[v];
}

int Weighted_graph::edge_count() const {
	return number_of_edges; 
}

//Takes two input arguements, m and n
//Throws illegal arguement exception if the input arguements, m and n, are negative or greater then the total
//Returns whether or not the two points are adjascent to each other
double Weighted_graph::adjacent(int m, int n) const {
	if(m < 0 || m >= number_of_vertices || n < 0 || n >= number_of_vertices) throw illegal_argument();
	if(m == n){
		return 0;
	}
	//larger vertex should be row
	return matrix[n][m];
	/*if (m < n){
		return matrix[n][m];
	}
	else{
		return matrix[m][n];
	}*/
}

//Takes point m and point n, two points on the graph, as the input arguements
//Assumes both points m and n exists as a node on the graph
double Weighted_graph::distance(int m, int n) {
	if(m >= number_of_vertices || n >= number_of_vertices || m < 0 || n < 0) throw illegal_argument();
	if(m == n)	{return 0.0;}

	Pair u;	
	//Initialize both the heap and the distance array to infinity since the distances to any given point are not known, except for start to start.
	for(int i = 0; i < number_of_vertices; i++){
		//pqueue->insert(i, INF);
		D[i] = INF;
	}
	//assigns the distance from point a to point a as 0 to both distance matrix and the heap
	D[m] = 0;
	pqueue->insert(m, 0);
	
	//Loop until every node has been visited inside the heap or has reached to the required end node 
	while(!pqueue->empty()) {
		u = pqueue->getMin();
		pqueue->deleteMin();//u is a pair of values (vertex, weight)

			for(int j = 0; j < number_of_vertices; ++j){
				//Adds the distance at the minimum vertex to the one adjacent to it from the matrix
				//And updates it as the new minimum distance if it happens to be smaller then the existing one from point n to point j
				//double adjValue = matrix[u.vertex()][j];		//ensuring there is adjacency between the current node and the node we're working with
				double newDist =  D[u.vertex()] + matrix[u.vertex()][j];
					if(newDist < D[j]){
						D[j] = newDist;
						//don't need to add the vertex back in if it's already there
						if(!pqueue->checkVertex(j, newDist)){
							pqueue->insert(j, newDist);	
						}
					}
			}			
	}
	//pqueue->clear();//Reset size of heap to 0	
	return D[n];
}

//Takes m, start point n and point m along with v, the weight associated with them as the arguements 
//Throws illegal arguement exeption if the input arguements are negative
void Weighted_graph::insert(int m, int n, double v) {

	if(v <= 0 || n < 0 || m < 0 ||(m == n) || m >= number_of_vertices || n >= number_of_vertices)
		throw illegal_argument();

	//Adds the adjacent nodes and the weight associated with them to the matrix
	if(matrix[m][n] == INF || matrix[n][m] == INF){
		number_of_edges++;
		degree_count[m]++;		
		degree_count[n]++;		
	}
	
	matrix[m][n] = v;
	matrix[n][m] = v;

}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif