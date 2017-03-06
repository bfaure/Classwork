/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #2
Bubble Sort w/Counter
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>

/*
Same program as Bubble sort form problem1 except
addition of the step counter and runtime counter
*/

long long counter = 0;
time_t before;
time_t after;
double runTime;

std::vector<int> read_file(std::string filename){
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}

void bubbleSort(std::vector<int> &input){
  int n = input.size();
  bool sorted=false;
  int pass = 1;
  while(!sorted && (pass<n)){
    sorted = true;
    for(int index=0; index<(n-pass); index++){
      counter++;
      int nextIndex = index+1;
      if(input[index] > input[nextIndex]){
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
  before = clock();
  bubbleSort(data);
  after = clock();
  runTime = double(after-before)/CLOCKS_PER_SEC;
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Total Steps Taken: "<<counter<<"\n";
  std::cout<<"Total Runtime of Algorithm: "<<runTime<<" Seconds\n\n";
}
