/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #1
Selection Sort
*/

/*
In this case, the textbook implementation of
selection sort breaks the program up into 2
seperate functions.  The first is the main 
Selection_Sort function, the second is the 
find_Index_of_Largest function, this function is
used to go through what is left of the unsorted vector
and find the position of the largest element.  This value
is returned to the main Selection_Sort function 
at which point the program performs a swap of the
last value in the vector with the largest value
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

int find_Index_of_Largest(std::vector<int> input, int size){
  int index = 0;
  for(int currentIndex=1; currentIndex<size; currentIndex++){
    if(input[currentIndex]>input[index]){
      index = currentIndex;
    }
  }
  return index;
}

void Selection_Sort(std::vector<int> &input){
  int n = input.size();
  for(int last = n-1; last>=1; last--){
    int largest;
    largest = find_Index_of_Largest(input, last+1);
    std::swap(input[last], input[largest]);
  }
}

int main(){
  std::vector<int> data = read_file("test.txt");
  std::cout<<"\nOriginal Vector...\n";
  int initial = data.size();
  for(int i=0; i<initial; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\nSorted Vector...\n";
  Selection_Sort(data);
  for(int i=0; i<initial; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n\n";
}
