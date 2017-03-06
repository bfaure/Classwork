/*
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #4
*/

/*
Comparing only Insertion Sort and Bubble Sort with the 
already sorted data sets.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <iterator>

long long insertionCount;     //Used to hold Insertion Count, global
long long bubbleCount;        //Used to hold Bubble Count, global

time_t beforeInsertion;       //Used to find runtime...
time_t afterInsertion;        
double insertionTime;
time_t beforeBubble;
time_t afterBubble;
double bubbleTime;            //...

void read_file(std::string filename, std::vector<int> &array){
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
}
//---------------------------------------------------------------
//-------------------------Insertion Sort------------------------
//---------------------------------------------------------------
/*
This version of Insertion Sort is very similar to the one found 
in the textbook, there was an error in the way the textbook had
written it where the loc-- was actually outside the while loop,
causing an infinite while loop
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
Basically the same Bubble Sort algorithm presented in the 
textbook.
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
/*
Main function loops through all of the data sets, loads each one
into a vector, then runs that data set on both Insertion Sort and
Bubble Sort, then outputs algorithm step counts and runtimes for 
both Insertion Sort and Bubble Sort, then repeats with the next 
data set until the "content" vector is finished
*/
int main(){
  std::string filename;
  filename = "dus-";
  std::string fileExtension;
  fileExtension = "_SORTED.txt";
  std::vector<std::string> content = {"2","4","6","8","10","12","16","20","24"};
  int fileNum = content.size();
  std::cout<<"File Name__________________Algorithm_______________Number of Steps_____________Duration\n\n";
  for(int i=0; i<fileNum; i++){
    insertionCount=0;
    bubbleCount=0;
    std::string file = filename+content[i]+fileExtension;
    std::vector<int> data;
    read_file(file, data);
    std::vector<int> data_copy = data;
    std::vector<int> data_copy_copy = data;
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
