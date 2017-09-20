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

#include <iostream>
#include <limits>
#include "Exception.h"
#include "ece250.h"

using namespace std;


// include whatever classes you want

class Weighted_graph {
    private:
        // your implementation here
		static const double INF;
        int edges;					//number of edges
        int vertices;				//number of vertices in matrix
        int *degree_count;				//array to hold degree of each vertex
        double **matrix;			//stores all edges
        bool *table_Validity;		//indicates which vertices have been found
        double *table_Distance;		//stores all calculated distances

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );
		
	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n): 
edges(0) {
    
    if (n <= 0) 
        n = 1;
        
    vertices = n;
    table_Distance = new double [n];
    table_Validity = new bool [n];
    matrix = new double *[n];
    degree_count = new int [n];
        
    for (int i=0; i<n; i++) {
        matrix[i] = new double[n];
        table_Distance[i] = INF;
        table_Validity[i] = false;
        degree_count[i] = 0;
        for (int j=0; j<n; j++) {
            matrix[i][j] = INF;
        }
    }
}

Weighted_graph::~Weighted_graph() {
    for (int i=0; i<vertices; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] table_Distance;
    delete[] table_Validity;
    delete[] degree_count;
}

int Weighted_graph::degree(int n) const {
    if (n < 0 || n >= vertices) throw illegal_argument();
	
	//start with -1 since vertex will count itself
	int degree = -1; 
	//go to row n and return the number of non-INFand non-zeros
	for(int i = 0; i < vertices; i++){
		if (adjacent(n, i) < INF){
			degree++; //if edge exists
		}
	}
	return degree;
}

int Weighted_graph::edge_count() const {
    return edges;
}

double Weighted_graph::adjacent(int m, int n) const {
   //check vertex m and n to see if exists
	if (m < 0 || m >= vertices || n < 0 || n >= vertices) throw illegal_argument();
	if (m == n) return 0; 
	//larger vertex should be row
	if (m < n){
		return matrix[n][m];
	}
	else{
		return matrix[m][n];
	}
}

double Weighted_graph::distance(int m, int n) const {
    if (m >= vertices || n >= vertices || m < 0 || n < 0)
        throw illegal_argument();
    
    for (int i=0; i<vertices; i++) {
        table_Distance[i] = INF;
        table_Validity[i] = false;
    }
    
    double smallest;
	int small;
    table_Distance[m] = 0;
    //table_Validity[m] = true;
    
    for (int i=0; i<vertices; i++) {

		smallest = INF;

        //break if nth position is smallest
		if (table_Validity[n])
            break;

        //finding vertices with smallest weight
        for (int j=0; j<vertices; j++) {
            if (smallest > table_Distance[j] && !table_Validity[j]) {
                smallest = table_Distance[j];
				small = j;
            }
        }
        
        //setting adjacent node's distance
        for (int j=0; j<vertices; j++) {
            if (matrix[small][j] != INF && !table_Validity[j] && table_Distance[j] > table_Distance[small] + matrix[small][j]) {
                table_Distance[j] = table_Distance[small] + matrix[small][j];
            }
        }
        
		table_Validity[small] = true;
    }
    
    return table_Distance[n];
}

void Weighted_graph::insert(int m, int n, double w) {
    if (w <= 0 || m < 0 || m >= vertices || n < 0 || n >= vertices || m == n)
        throw illegal_argument();
    
    //if edge exists, add degree of m and n
    if (matrix[m][n] == INF) {
		degree_count[m]++;
		degree_count[n]++;
		edges++;
    }

    matrix[m][n] = w;
	matrix[n][m] = w;
}
std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}
#endif