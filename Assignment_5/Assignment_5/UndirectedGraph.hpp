//VISHAL ANAND
//B16040
#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH 1

#include "AbstractGraph.hpp"


/*
* A class to represent an UndirectedGraph
* Subclasses AbstractGraph
*/
class UndirectedGraph : public AbstractGraph {

	GraphAdjacencyBase *base;
  int *bfs_queue;
		
 	public:

    /*
    * Constructor: UndirectedGraph
    *
    * Parameters: mode
    * Used to decide which representation to use
    * 'm' for AdjacencyMatrix
    * 'l' for AdjacencyList
    */
    UndirectedGraph(int vertices, char mode){
    if(mode=='m')  base = new AdjacencyMatrix(vertices);
    else  base = new AdjacencyList(vertices);
    bfs_queue = new int[vertices+9];
  }
  /*
   * Destructor
   */
  	~UndirectedGraph(){} 
    /*
   * Function: edgeExists
   * Returns true if an edge exists between vertices i and j, false otherwise.
   */
  bool edgeExists(int i, int j){
    return base->edgeExists(i,j);
  }
  /*
   * Function: edges
   * Returns the number of edges in the adjacency structure.
   */
  int edges(){
    return base->edges();
  }
  /*
   * Function: vertices
   * Returns the number of vertices in the adjacency structure.
   */
  int vertices(){
    return base->vertices();
  }
  /*
   * Function add:
   * Adds an edge between vertices i and j
   */
  void add(int i, int j){
    base->add(i,j);
    base->add(j,i);
  }
  /*
   * Function: remove
   * Deleted the edge between vertices i and j
   */
  void remove(int i, int j){
    base->remove(i,j);
    base->remove(j,i);
  }
  /*
   * Function dfs:
   * Does a depth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  void dfs(void (*work)(int&), int node, int* visited){
    if(node<1 || node>base->vertices() ) return;
    visited[node] = 1;
    (*work)(node);
    for(int i=1; i<=base->vertices(); i++){
      if(!visited[i] && base->edgeExists(node,i)) dfs(work,i,visited);  //O(height*nodes)
    }
  }
  /*
   * Function bfs:
   * Does a breadth first traversal of the entire graph.
   * Runs the given function work, with the value of each vertex.
   */
  void bfs(void (*work)(int&), int node, int* visited){
    int b = 1, f = 1;
    bfs_queue[1] = node;
    visited[node] = 1;
    while(b<=f){
      (*work)(bfs_queue[b]);
      node = bfs_queue[b];
      for(int i=1; i<=base->vertices(); i++){
        if(!visited[i] && base->edgeExists(node,i)){
          visited[i] = 1;
          bfs_queue[++f] = i;
        }
      }
      b++;
    }
  }
    /*
    * Destructor
    */
  	
	};
	
#endif /* ifndef UNDIRECTED_GRAPH */
