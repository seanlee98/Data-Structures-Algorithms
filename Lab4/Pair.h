#ifndef PAIR_H
#define PAIR_H

#include <iostream>

class Pair {
    private:
        

    public:
        Pair( int const = int(), double const = double());		
        double weight() const;
        int vertex() const;	
		double edge_weight;
        int adjacent_vertex;
};

Pair::Pair( int const e, double const p){
	edge_weight = p;
	adjacent_vertex = e;	
}

 double Pair::weight() const{
	 return edge_weight;
 }

 int Pair::vertex() const{
	 return adjacent_vertex;
 }
 
#endif