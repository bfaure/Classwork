/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #1
Bubble Sort
*/

/*
Basically the textbook implementation of Bubble Sort
with a function called read_file to take in integer values
from a file and load them into a vector. Main function used
to output vectors and call read_file and bubbleSort functions
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<int> read_file(std::string filename){
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}
/*
Function takes reference to a vector, alters vector
from within the function, by the end of bubbleSort,
the vector referenced should be sorted in ascending order.
This is almsot the same as the textbook version of
Bubble Sort except I use vectors rather than arrays.
*/

void bubbleSort(std::vector<int> &input){   //Pass reference
  int n = input.size();                     //Find vector length
  bool sorted=false;                        //Initialize sorted to false
  int pass = 1;                             //Initialize pass to 1
  while(!sorted && (pass<n)){
    sorted = true;
    for(int index=0; index<(n-pass); index++){
      int nextIndex = index+1;              //If change is needed, set sorted to false
      if(input[index] > input[nextIndex]){  //and run loop again
	std::swap(input[index], input[nextIndex]);
	sorted = false;
      }
    }
    pass++;
  }
}

int main(){
  std::vector<int> data = read_file("test.txt");
  int size = data.size();
  std::cout<<"\nOriginal Vector...\n";
  for(int i = 0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\nSorted Vector...\n";
  bubbleSort(data);
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n\n";
}
