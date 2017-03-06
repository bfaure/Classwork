/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #2
Selection Sort w/Counter
*/

/*
Pretty much the same program as the selection sort
in problem 1 except this has a step counter and 
runtime counter inserted to help evaluate the efficiency
of this sorting algorithm.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>


long long counter = 0;   //Set counter to 0
time_t before;           //Set before time
time_t after;            //Set after time
double runTime;          //Set elapsed time (will hold runtime)

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
    counter++;   //Increment the counter here
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
  before = clock();
  Selection_Sort(data);
  after = clock();
  runTime = double(after-before)/CLOCKS_PER_SEC;  //Double holds total runtime
  for(int i=0; i<initial; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Total Steps Taken: "<<counter<<"\n";
  std::cout<<"Total Runtime of Algorithm: "<<runTime<<" Seconds\n\n";
}
