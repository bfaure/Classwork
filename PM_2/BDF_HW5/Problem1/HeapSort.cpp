/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methology II
Homework #5
Problem #1
HeapSort Implmentation
*/

/*
1. Implement HeapSort. Using the data set from earlier sorting 
homeworks, plot and analyze the runtime performance of HeapSort.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>

void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}
long long counter;  //Global step counter for complexity

bool isLeaf(int rootIndex, int HEAP_SIZE){
  //std::cout<<"isLeaf_start\n";
  int lastIndex = HEAP_SIZE-1;
  int leftChildIndex = (2*rootIndex)+1;
  if(leftChildIndex>lastIndex){
    counter++;
    //std::cout<<"isLeaf_end\n";
    return true;
  }
  //std::cout<<"isLeaf_end\n";
  return false;
}
bool hasRightChild(int rootIndex, int HEAP_SIZE){
  //std::cout<<"hasRightChild_start\n";
  int lastIndex = HEAP_SIZE-1;
  int rightChildIndex = (2*rootIndex)+2;
  if(rightChildIndex<=lastIndex){
    counter++;
    //std::cout<<"hasRightChild_end\n";
    return true;
  }
  //std::cout<<"hasRightChild_end\n";
  return false;
}
void heapRebuild(int rootIndex, std::vector<int> &HEAP, int HEAP_SIZE){
  //std::cout<<"heapRebuild_start\n";
  if(!isLeaf(rootIndex, HEAP_SIZE)){
    int largerChildIndex=(2*rootIndex)+1;
    if(hasRightChild(rootIndex, HEAP_SIZE)){
	int rightChildIndex=largerChildIndex+1;
	if(HEAP[rightChildIndex]>HEAP[largerChildIndex]){
	  counter++;
	  largerChildIndex=rightChildIndex;
	}
    }
    if(HEAP[rootIndex]<HEAP[largerChildIndex]){
      counter++;
      int temp = HEAP[rootIndex];
      HEAP[rootIndex]=HEAP[largerChildIndex];
      HEAP[largerChildIndex]=temp;
      heapRebuild(largerChildIndex, HEAP, HEAP_SIZE);
    }
  }
  //std::cout<<"heapRebuild_end\n";
}

void heapSort(std::vector<int> &input, int n){
  //std::cout<<"Entered heapsort\n";
  for(int index=n/2; index>=0; index--){
    heapRebuild(index, input, n);
  }
  int temp = input[0];
  input[0] = input[n-1];
  input[n-1] = temp;
  int heapSize = n-1;
  while(heapSize>1){
    heapRebuild(0, input, heapSize);
    temp = input[0];
    input[0] = input[heapSize-1];
    input[heapSize-1] = temp;
    heapSize--;
  }
}
/*
int main(){
  std::vector<int> data {3,2,6,4,1,9,6,4,8};
  std::cout<<"\nORIGINAL INPUT VECTOR...\n";
  for(int i=0; i<data.size(); i++){
    std::cout<<data[i]<<" ";
  }
  heapSort(data, data.size());
  std::cout<<"\n\nSORTED OUTPUT...\n";
  for(int i=0; i<data.size(); i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n\n";
}
*/

int main(){
  std::cout<<"\n|------------------------------------------|\n";
  std::cout<<"|----------Sorting with HeapSort()---------|\n";
  std::cout<<"|------FILE------|----------STEPS----------|\n";
  std::string filePrefix = "dus-";
  std::string fileExtension = ".txt";
  std::vector<std::string> fileName = {"2","4","6","8","10","12","16","20","24"};
  int num_files = fileName.size();
  for(int i=0; i<num_files; i++){
    counter = 0;
    std::string file = filePrefix+fileName[i]+fileExtension;
    std::vector<int> theArray;
    read_file(file, theArray);
    heapSort(theArray, theArray.size());
    std::cout<<"    "<<file;
    for(int i=22; i>file.length(); i--){
      std::cout<<" ";
    }
    std::cout<<counter<<"\n";
  }
  std::cout<<"\n";
}     


    
