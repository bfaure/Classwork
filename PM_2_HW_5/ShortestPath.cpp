/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methology II
Homework #5
Problem #4
Shortest-Path Algo.
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>

/*
The code I have written for Dijkstra's shortest path algorithm
is somewhat similar to the implementation in the textbook but I
formulated most of it by reading up on Dijkstra's algorithm
directly rather than translating the pseudocode from the textbook.
The function ShortestPath takes 2 array inputs, the first is the
2-D adjacency matrix for the problem and the second is the initial
value (&weight)[7] array for the distances from the origin to the
other vertices.  At first I set all of the non-attached vertex 
distances to 10,000 because the sum of the distances in this problem
is nowhere near that so it functions just fine instead of infinity.
 */
void ShortestPath(int (&adjacency)[7][7], int (&weight)[7]){
  int num_vert = 7;
  for(int i=0; i<num_vert; i++){
    weight[i]=adjacency[0][i];
  }
  /*
First sets the weight array equal to the first row of the 
adjacency matrix which corresponds to all of the vertices that
are directly connected to the origin vertex.  All other vertices
will still have 10,000 for their weights until something smaller
is discovered by the while loop.
   */
  std::vector<int> unvisited{1,2,3,4,5,6};
  std::vector<int> visited{0};
  bool solved = false;
  int current_vertex=1;
  int current_index=0;
  /*
Before entering the while loop I have initialized the function
to have already visited vertex zero such that the next vertex to
check is known to be vertex 1.
   */
  while(!solved){
    int base_to_current = weight[current_vertex];
    for(int i=0; i<unvisited.size(); i++){
      if(unvisited[i]==current_vertex){
      }
      /*
If the current vertex is pulled up, the above if statement
will ensure it does not cause problems. This is a problem
because I don't remove the current vertex from the list of
unvisited vertices until the last steps of the while loop.
       */
      else{
	/*
If the value in the unvisited[i] is NOT the current vertex
than it enters the else portion where it checks to see if it
should replace the value of the unvisited[i] distance from the
origin based on whether or not it has just discovered
a more efficient path. Recall that at first every path will
be more efficient because its compared to a distance of 10000.
	 */
        int looking_at = unvisited[i];
        int weight_to = adjacency[current_vertex][looking_at];
        int new_dist = base_to_current+weight_to;
        if(new_dist<weight[looking_at]){
	  weight[looking_at] = new_dist;
	  //Set new distance
	}
      }
    }
    int next_closest=100000;
    /*
Add the current vertex to visited and remove it from unvisited.
     */
    visited.push_back(current_vertex); 
    unvisited.erase(unvisited.begin()+current_index); 
    if(visited.size()==7){
      /*
The algorithm is complete once it has visited every vertex.
At this point it outputs all of the values in weight[].
       */
      for(int i=0; i<num_vert; i++){
	std::cout<<"Shortest Path to Vertex "<<i<<" = "<<weight[i]<<"\n";
      }
      std::cout<<"\n";
      return;
    }
    /*
Here I calculate which vertex to visit next based on which
of the unvisited vertices has the smallest distance so far.
     */
    for(int i=0; i<unvisited.size(); i++){
      int new_vert = unvisited[i];
      if(weight[new_vert]<next_closest){
	next_closest = weight[new_vert];
	current_vertex = new_vert;
	current_index = i;
      }
    }
  }
}

int main(){
  std::cout<<"\n";
  int adjacency[7][7] = {
    {0,2,4,6,10000,10000,10000},
    {10000,10000,5,10000,3,10000,10000},
    {10000,10000,10000,2,2,10000,10000},
    {10000,10000,1,10000,5,3,10000},
    {10000,10000,3,10000,10000,5,1},
    {10000,10000,10000,10000,1,10000,10000},
    {10000,10000,10000,10000,10000,2,10000}
  };
  int weight[7] = {10000,10000,10000,10000,10000,10000,10000};
  ShortestPath(adjacency, weight);
}

