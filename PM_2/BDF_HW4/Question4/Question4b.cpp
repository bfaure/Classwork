/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #4
Question #4b
*/

/*
MergeSort implementation with in-place sorting
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

long counter = 0;
/*
To create the in-place version of mergeSort, I basically looked
at my Question4a.cpp merge function and tried to think of a way
to replicate the function without ever needing to create a new
temp array.  I managed to complete it by just performing the same
operations on the original array and managing the 
 */

void merge(std::vector<int> &theArray, int first, int mid, int last){
  //std::cout<<"merge called\n";
  int first1 = first;            
  int last1 = mid;
  int first2 = mid+1;
  int last2 = last;
  int index = first1;
  while((first1<=last1) && (first2<=last2)){
    //counter++;
    if(theArray[first2]<=theArray[first1]){
      int temp = theArray[first2];
      theArray.emplace(theArray.begin()+first1, temp);
      theArray.erase(theArray.begin()+first2+1);
      first1++;
      first2++;
    }
    else{
      first1++;
    }
  }
}
void mergeSort(std::vector<int> &theArray, int first, int last){
  counter++;
  //std::cout<<"mergeSort #"<<counter<<"\n";
  if(first<last){
    int mid = first + (last-first)/2;
    mergeSort(theArray, first, mid);
    mergeSort(theArray, mid+1, last);
    merge(theArray, first, mid, last);
  }
}

int main(){
  std::cout<<"\n\n|--------------------------------------------------|\n";
  std::cout<<"|--------------Sorting with mergeSort()------------|\n";
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
    mergeSort(theArray, first, last);
    std::cout<<file<<"                     "<<counter<<"\n";
    //std::string to_write = "./"+filePrefix+fileName[i]+"_SORTED"+fileExtension;  //Save vector to its own file
    //std::ofstream output_file(to_write);
    //std::ostream_iterator<int> output_iterator(output_file, "\n");
    //std::copy(theArray.begin(), theArray.end(), output_iterator);
  }
}

