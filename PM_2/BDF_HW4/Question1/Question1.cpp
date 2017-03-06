/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #4
Question #1
*/

/*
Q1. Implement the Quicksort algorithm. Please ensure it is complete
--namely, it has both the select pivot and sorting phases.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

std::vector<int> read_file(std::string filename){
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}
/*
The globabl variables check_left and check_right will be used inside
of the partition function to decide whether or not the left partition
(less than pivot) and the right partition (greater than pivot) should
be called again in the quickSort funciton.  Basically if the length of
the left or right partition is 1 because it only contains 1 element, it
obviously does not need to be sorted.  I added this because I was getting
some infinite loops where the function was trying to sort vectors of
length 1.
*/
bool check_left = false;
bool check_right = false;
int length;
/*
The partition function does exactly as you would expect, it takes the input
and splits it approximately in half.  At this point it puts all of the values
larger than the pivot value in a vector called greaterthan and all of the
values smaller than the pivot value in a vector called lessthan. The function
then combines those two vectors with a vector called equalto which contains
the pivotvalue and any copies of it present in the original vector. At the end
the function returns the location (index) of the pivot value after the combination
of vectors has occured.
 */
int partition(std::vector<int> &theArray, int &first, int &last){
  check_left = false;
  check_right = false;
  int pivot = first + (last-first)/2;
  int p = theArray[pivot];
  std::cout<<"The pivot value is: "<<p<<"\n";
  std::vector<int> lessthan;
  std::vector<int> greaterthan;
  std::vector<int> equalto;
  for(int i=0; i<theArray.size(); i++){
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
  if(lessthan.size() >= 2){      //Set the check_left variable true if lessthan
    check_left = true;           //vector has more than 1 element
  }
  if(greaterthan.size() >= 2){   //Same with check_right
    check_right = true;
  }
  int pivotIndex = lessthan.size()+equalto.size()-1;
  length = equalto.size();
  std::cout<<"The pivotIndex is: "<<pivotIndex<<"\n";
  if(lessthan.size()>0){
    for(int i=0; i<lessthan.size(); i++){
      std::cout<<lessthan[i]<<" ";
    }
  }
  if(equalto.size()>0){
    std::cout<<"[ ";
    for(int i=0; i<equalto.size(); i++){
      std::cout<<equalto[i]<<" ";
    }
    std::cout<<"] ";
  }
  if(greaterthan.size()>0){
    for(int i=0; i<greaterthan.size(); i++){
      std::cout<<greaterthan[i]<<" ";
    }
  }
  std::cout<<"\n";
  lessthan.insert(lessthan.end(), equalto.begin(), equalto.end());
  lessthan.insert(lessthan.end(), greaterthan.begin(), greaterthan.end());
  theArray = lessthan;
  for(int i=0; i<theArray.size(); i++){
    std::cout<<theArray[i]<<" ";
  }
  std::cout<<"\n";
  return pivotIndex;
}
/*
My quickSort function is very similar to the one presented in the 
textbook.  The first difference is that I implement the check_left
and check_right functions explained earlier.  The other big difference
is that the textbook uses insertionSort() if the length of the vector
at that step is less than some preset MIN_SIZE, instead of this, I just
set the MIN_SIZE to 2 and swap the contents if required and do nothing
if not.  This is basically the base case of the recursive function but
it is not necessarily the last step of the function. Another thing
I added is the length variable, instead of just subtracting 1 from
the pivot index when calling quickSort to sort the left side, my 
program subtracts the length of the equalto vector.  This allows the
function to fun with inputs that have multiples of the same integer.
*/
void quickSort(std::vector<int> &theArray, int first, int last){
  std::cout<<"-----------------------------\n";
  std::cout<<"Entering quickSort...\n";
  
  if(last-first <= 1){
    if(last-first == 1){
      std::cout<<"Length of 2.\n";
      if(theArray[last] < theArray[first]){
        std::cout<<"Need to swap.\n";
        int temp = theArray[first];
        theArray[first] = theArray[last];
        theArray[last] = temp;
      }
    }
  }
  else{
    int pivotIndex = partition(theArray, first, last);
    std::cout<<"Back from partition function.\n";
    if(check_left){
      std::cout<<"Sorting left side.\n";
      quickSort(theArray, first, pivotIndex-length);
    }
    if(check_right){
      std::cout<<"Sorting right side.\n";
      quickSort(theArray, pivotIndex+1, last);
    }
    std::cout<<"-----------------------------\n";
  }
  
}
/*
The main function controls the flow of the function calling.
First it calls the read_file function to load in the data from
a file then calls the quickSort function to sort it.  For this
implementation Question 1, I have included a simple test.txt file
just to make sure my program is working correctly.
 */
int main(){
  std::vector<int> theArray = read_file("test.txt");
  int size = theArray.size();
  std::cout<<"\nOriginal Vector...\n";
  for(int i = 0; i<size; i++){
    std::cout<<theArray[i]<<" ";
  }
  std::cout<<"\n\n";
  int first = 0;
  int last = theArray.size()-1;
  quickSort(theArray, first, last);
  std::cout<<"\nSorted Vector...\n";
  for(int i=0; i<size; i++){
    std::cout<<theArray[i]<<" ";
  }
  std::cout<<"\n\n";
}
