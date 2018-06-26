//VISHAL ANAND
//B16040
#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1

#include "GraphAdjacencyBase.hpp"
#ifndef Vector
#include <vector>
#endif

/*
 * 	Class AdjacencyList
 *	Can be used to represent a Graph using adjacency-list.
 */
class AdjacencyList : public GraphAdjacencyBase {

	int size, noOfEdges;
	std::vector<std::vector<int> > arr;
	std::vector<int> inDegree;

	public:
	AdjacencyList(int vertices){
		size = vertices;
		noOfEdges = 0;
		inDegree.resize(size+9);
		arr.resize(size+9);
		for(int i=0; i<size+9; i++)
			inDegree[i] = 0;
	}
	~AdjacencyList(){}

	/*
	 * Function: edgeExists
	 * Returns true if an edge exists between vertices i and j, false otherwise.
	 */
	 bool edgeExists(int i, int j){
	 	bool exists = false;
	 	for(int col=0; col<arr[i].size(); col++)
	 		if(arr[i][col]==j){
	 			exists = true;
	 			break;
	 		}
	 	return exists;
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
	 	arr[i].push_back(j);
	 	inDegree[j]++;
	 	noOfEdges++;
	 }
		/*
		 * Function: remove
		 * Deleted the edge between vertices i and j
		 */
	 void remove(int i, int j){
	 	for(int col=0; col<arr[i].size(); col++)
	 		if(arr[i][col]==j){
	 			arr[i].erase(arr[i].begin()+col);
	 			noOfEdges--;
	 			inDegree[j]--;
	 			break;
	 		}
	 }
		/*
		 * Function: degree
		 * Returns the degree of the vertex i
		 */
	 int degree(int i){
	 	return (inDegree[i]+arr[i].size());
	 }
		  	
};  	
#endif /* ifndef ADJACENCY_LIST */
