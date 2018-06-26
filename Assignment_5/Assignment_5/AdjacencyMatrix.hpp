//VISHAL ANAND
//B16040
#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1
#ifndef inc
#include "GraphAdjacencyBase.hpp"
#endif
/*
 * 	Class AdjacencyMatrix
 *	Can be used to represent a Graph using adjacency-matrix.
 */
class AdjacencyMatrix : public GraphAdjacencyBase {
	
	int size, **arr, noOfEdges;

	public:
		AdjacencyMatrix(int vertices){
			noOfEdges = 0;
			size = vertices;
			arr = new int*[size+9];
			for(int i=0; i<size+9; i++){
				arr[i] = new int[size+9];
				for(int j=0; j<size+9; j++)	arr[i][j] = 0;
			}
		}
		~AdjacencyMatrix(){}

		bool edgeExists(int i, int j){
			return (arr[i][j]==1?true:false);
		}
		/*
		 * Function: vertices
		 * Returns the number of vertices in the adjacency structure.
		 */
	   	int vertices(){
	   		return size;
	  	}
		/*
		 * Function: edges
		 * Returns the number of edges in the adjacency structure.
		 */
	   	int edges(){
	   		return noOfEdges;
	  	}
		/*
		 * Function add:
		 * Adds an edge between vertices i and j
		 */
	  	void add(int i, int j){
	  		arr[i][j] = 1;
	  		noOfEdges++;
	  	}
		/*
		 * Function: remove
		 * Deleted the edge between vertices i and j
		 */
	   	void remove(int i, int j){
	   		arr[i][j] = 0;
	   		noOfEdges--;
	  	}
		/*
		 * Function: degree
		 * Returns the degree of the vertex i
		 */
	   	int degree(int i){
	   		int deg = 0;
	   		for(int j=0; j<size+9; j++){
	   			if(arr[i][j]==1)	deg++;
	   			if(arr[j][i]==1)	deg++;
	   		}
	   		return deg;
	  	}
};

#endif /* ifndef ADJACENCY_MATRIX */
