/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #2
Insertion Sort w/Counter
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>

/*
Same program as the insertion sort from problem1
except with the addition of the step and runtime 
counters
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

void Insertion_Sort(std::vector<int> &input){
  int n = input.size();
  for(int unsorted=1; unsorted<n; unsorted++){
    int nextItem = input[unsorted];
    int loc = unsorted;
    while((loc>0) && (input[loc-1] > nextItem)){
      counter++;
      int temp = input[loc];
      input[loc] = input[loc-1];
      input[loc-1] = temp;
      loc--;
    }
  }
}

int main(){
  std::vector<int> data = read_file("dus-16.txt");
  std::cout<<"\nOriginal Vector...\n";
  int size = data.size();
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\nSorted Vector...\n";
  before = clock();
  Insertion_Sort(data);
  after = clock();
  runTime = double(after-before)/CLOCKS_PER_SEC;
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n";
  std::cout<<"Total Steps Taken: "<<counter<<"\n";
  std::cout<<"Total Runtime of Algorithm: "<<runTime<<" Seconds\n\n";
}
