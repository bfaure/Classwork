/*
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #4
*/

/*
Comparing the sorting algorithms again but this time with data
sets that have already been sorted into ascending order. Expect 
that Selection Sort will be the same as without previously sorted
data sets.  Insertion and Bubble sort will most likely be faster
because they have a different 'best case' complexity.
*/

/*
Structurally this code is very similar to Algorithms.cpp from Problem3, 
the only difference is in the way I create the filename to use in the 
read_file function because I add the _SORTED extension to ensure we are 
pulling from the already sorted data sets rather than the originals.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <iterator>

long long selectionCount;
long long insertionCount;
long long bubbleCount;

time_t beforeSelection;
time_t afterSelection;
double selectionTime;
time_t beforeInsertion;
time_t afterInsertion;
double insertionTime;
time_t beforeBubble;
time_t afterBubble;
double bubbleTime;

void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}
//---------------------------------------------------------------
//-------------------------Selection Sort------------------------
//---------------------------------------------------------------
int find_Index_of_Largest(std::vector<int> input, int size){
  int index = 0;
  for(int currentIndex=1; currentIndex<size; currentIndex++){
    selectionCount++;
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
//---------------------------------------------------------------
//-------------------------Insertion Sort------------------------
//---------------------------------------------------------------
void Insertion_Sort(std::vector<int> &input){
  int n = input.size();
  for(int unsorted=1; unsorted<n; unsorted++){
    int nextItem = input[unsorted];
    int loc = unsorted;
    while((loc>0) && (input[loc-1] > nextItem)){
      insertionCount++;
      int temp = input[loc];
      input[loc] = input[loc-1];
      input[loc-1] = temp;
      loc--;
    }
  }
}
//---------------------------------------------------------------
//--------------------------Bubble Sort--------------------------
//---------------------------------------------------------------
void Bubble_Sort(std::vector<int> &input){
  int n = input.size();
  bool sorted=false;
  int pass = 1;
  while(!sorted && (pass<n)){
    sorted = true;
    for(int index=0; index<(n-pass); index++){
      bubbleCount++;
      int nextIndex = index+1;
      if(input[index] > input[nextIndex]){
	std::swap(input[index], input[nextIndex]);
	sorted = false;
      }
    }
    pass++;
  }
}
//---------------------------------------------------------------
int main(){
  std::string filename;
  filename = "dus-";
  std::string fileExtension;
  fileExtension = "_SORTED.txt";  //The only change from Algorithms.cpp
  std::vector<std::string> content = {"2","4","6","8","10","12","16","20","24"};
  int fileNum = content.size();
  std::cout<<"File Name__________________Algorithm_______________Number of Steps_____________Duration\n\n";
  for(int i=0; i<fileNum; i++){
    selectionCount=0;
    insertionCount=0;
    bubbleCount=0;
    std::string file = filename+content[i]+fileExtension;
    std::vector<int> data;
    read_file(file, data);
    std::vector<int> data_copy = data;
    std::vector<int> data_copy_copy = data;
    
    beforeSelection = clock();
    Selection_Sort(data);
    afterSelection = clock();
    selectionTime = double(afterSelection-beforeSelection)/CLOCKS_PER_SEC;
    std::cout<<file<<"                 Selection Sort             "<<selectionCount<<"                    "<<selectionTime<<" Seconds\n";

    beforeInsertion = clock();
    Insertion_Sort(data_copy);
    afterInsertion = clock();
    insertionTime = double(afterInsertion-beforeInsertion)/CLOCKS_PER_SEC;
    std::cout<<file<<"                 Insertion Sort             "<<insertionCount<<"                    "<<insertionTime<<" Seconds\n";

    beforeBubble = clock();
    Bubble_Sort(data_copy_copy);
    afterBubble = clock();
    bubbleTime = double(afterBubble-beforeBubble)/CLOCKS_PER_SEC;
    std::cout<<file<<"                 Bubble Sort                "<<bubbleCount<<"                    "<<bubbleTime<<" Seconds\n";
  }
  std::cout<<"\n";  
}
