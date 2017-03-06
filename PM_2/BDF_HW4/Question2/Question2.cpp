/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #4
Question #2
*/

/*
Q2. Implement a suitable counter of the number of operations for your
implementation of Quicksort.  Plot/Analyze the time taken for different
input sizes (use dataset from HW3).
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>
/*
Most of the contents of this code are taken from Question1.cpp
so anything not explained here is from there.
*/
void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}

bool check_left = false;
bool check_right = false;
long counter = 0;          //Set global counter to 0
int length;
/*
I have inserted the counter inside of the for loop below
such that it will count the number of comparisons that the
algorithm must make to the pivot value.  This should be a
good approximation of the complexity of the algorithm.
*/
int partition(std::vector<int> &theArray, int &first, int &last){
  check_left = false;
  check_right = false;
  int pivot = first + (last-first)/2;
  int p = theArray[pivot];
  //std::cout<<"The pivot value is: "<<p<<"\n";
  std::vector<int> lessthan;
  std::vector<int> greaterthan;
  std::vector<int> equalto;
  for(int i=0; i<theArray.size(); i++){
    counter++;
    if(theArray[i]<p){
      lessthan.push_back(theArray[i]);
    }
    if(theArray[i]>p){
      greaterthan.push_back(theArray[i]);
    }
    if(theArray[i]==p){
      equalto.push_back(theArray[i]);
    }
  }
  if(lessthan.size() >= 2){     
    check_left = true;          
  }
  if(greaterthan.size() >= 2){  
    check_right = true;
  }
  int pivotIndex = lessthan.size()+equalto.size()-1;
  length = equalto.size();
  //std::cout<<"The pivotIndex is: "<<pivotIndex<<"\n";
  if(lessthan.size()>0){
    for(int i=0; i<lessthan.size(); i++){
      //std::cout<<lessthan[i]<<" ";
    }
  }
  if(equalto.size()>0){
    //std::cout<<"[ ";
    for(int i=0; i<equalto.size(); i++){
      //std::cout<<equalto[i]<<" ";
    }
    //std::cout<<"] ";
  }
  if(greaterthan.size()>0){
    for(int i=0; i<greaterthan.size(); i++){
      //std::cout<<greaterthan[i]<<" ";
    }
  }
  //std::cout<<"\n";
  lessthan.insert(lessthan.end(), equalto.begin(), equalto.end());
  lessthan.insert(lessthan.end(), greaterthan.begin(), greaterthan.end());
  theArray = lessthan;
  //for(int i=0; i<theArray.size(); i++){
  //std::cout<<theArray[i]<<" ";
  //}
  //std::cout<<"\n";
  return pivotIndex;
}

void quickSort(std::vector<int> &theArray, int first, int last){
  //std::cout<<"-----------------------------\n";
  //std::cout<<"Entering quickSort...\n";
  if(last-first <= 1){
    if(last-first == 1){
      //std::cout<<"Length of 2.\n";
      if(theArray[last] < theArray[first]){
        //std::cout<<"Need to swap.\n";
        int temp = theArray[first];
        theArray[first] = theArray[last];
        theArray[last] = temp;
      }
    }
  }
  else{
    int pivotIndex = partition(theArray, first, last);
    //std::cout<<"Back from partition function.\n";
    if(check_left){
      //std::cout<<"Sorting left side.\n";
      quickSort(theArray, first, pivotIndex-length);
    }
    if(check_right){
      //std::cout<<"Sorting right side.\n";
      quickSort(theArray, pivotIndex+1, last);
    }
    //std::cout<<"-----------------------------\n";
  }
  
}
/*
The big changes to the code are in the main function.  I have 
created a for loop which loads in each file individually then
sorts it using the quickSort function.  During the process, it
tracks the number of steps used by quickSort and outputs that to
the terminal.  The program also saves the sorted vectors to files
to use in the Question #3 later.  Other than that, the only change
is the addition of the counter outlined above.
*/
int main(){
  std::cout<<"\n\n|--------------------------------------------------|\n";
  std::cout<<"|--------------Sorting with quickSort()------------|\n";
  std::cout<<"|----------FILE----------|----------STEPS----------|\n";
  std::string filePrefix = "dus-";
  std::string fileExtension = ".txt";
  std::vector<std::string> fileName = {"2","4","6","8","10","12","16","20","24"};
  int num_files = fileName.size();
  for(int i=0; i<num_files; i++){
    counter = 0;
    std::string file = filePrefix+fileName[i]+fileExtension;
    std::vector<int> theArray;
    read_file(file, theArray);
    int first = 0;
    int last = theArray.size()-1;
    quickSort(theArray, first, last);
    std::cout<<file<<"                     "<<counter<<"\n";
    //std::string to_write = "./"+filePrefix+fileName[i]+"_SORTED"+fileExtension;  //Save vector to its own file
    //std::ofstream output_file(to_write);
    //std::ostream_iterator<int> output_iterator(output_file, "\n");
    //std::copy(theArray.begin(), theArray.end(), output_iterator);
  }
}
