/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #4
Question #3
*/

/*
Q3. Running QuickSort on the previously sorted data-set outputs from
Q2.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iterator>
/*
Code is the same as Question2.cpp, the only difference is in the naming
of the files to read into the read_file function.
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
    std::string file = filePrefix+fileName[i]+"_SORTED"+fileExtension;
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
