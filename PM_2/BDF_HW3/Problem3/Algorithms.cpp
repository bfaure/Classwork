/*
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #3
*/

/*
Individually loads each data set into a vector then
runs all 3 sorting algorithms on the vector while recording
the number of steps and runtime in seconds for each. Once
all 3 of the sorting algorithms have finished a data-set,
the program outputs the sorted vector from Selection Sort
into a new text file as a single column of integers, the
same as the format they were initially read in.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <iterator>

long long selectionCount;   //Initializing all of the counters
long long insertionCount;   //...
long long bubbleCount;      //...

time_t beforeSelection;     //Initializing all of the time variables
time_t afterSelection;      //...
double selectionTime;
time_t beforeInsertion;
time_t afterInsertion;
double insertionTime;
time_t beforeBubble;
time_t afterBubble;
double bubbleTime;          //...

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
/*
Pretty much the same selection sort as was in Problem2
*/
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
/*
Same as Problem2 Insertion Sort
*/
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
/*
Same as Problem2 Bubble Sort
*/
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
  std::string filename;            //Creating string to hold variable filename
  filename = "dus-";               //String will always have dus-'something'.txt
  std::string fileExtension;    
  fileExtension = ".txt";          //Always will end in .txt
  std::vector<std::string> content = {"2","4","6","8","10","12","16","20","24"}; //Vector of all file integer names
  int fileNum = content.size();    //Number of files to read = length of vector
  std::cout<<"File Name__________________Algorithm_______________Number of Steps_____________Duration\n\n";
  for(int i=0; i<fileNum; i++){
    /* 
each time through the loop: reads file into vector, copies vector twice, sorts vector
with all three sorting algorithms, writes selection sorted vector to file
    */
    selectionCount=0;    //Reset counters each time through loop
    insertionCount=0;
    bubbleCount=0;
    std::string file = filename+content[i]+fileExtension;   //Create entire file name
    std::vector<int> data;
    read_file(file, data);   //Read file name
    std::vector<int> data_copy = data;
    std::vector<int> data_copy_copy = data;  //Copy vector twice
    
    beforeSelection = clock();   //Clock functions the same as problem2
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

    std::string to_write = "./"+filename+content[i]+"_SORTED"+fileExtension;  //Save vector to its own file
    std::ofstream output_file(to_write);
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(data.begin(), data.end(), output_iterator);
  }
  std::cout<<"\n";  
}
