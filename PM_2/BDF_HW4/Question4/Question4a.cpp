/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #4
Question #4a
*/

/*
MergeSort implementation with additional array/memory.
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
int SIZE;
/*
My implementation of mergeSort with the additional temporary
array is mostly taken from the textbook.  I have made several
changes to the code though including dynamically allocating the
memory for the temp array and using vectors to hold all values
besides the temp array rather than using strictly arrays.
 */
void merge(std::vector<int> &theArray, int first, int mid, int last){
  //std::cout<<"merge called\n";
  int* tempArray = new int[SIZE]; //Allocate temp array size based on
  int first1 = first;             //the size of the input array
  int last1 = mid;
  int first2 = mid+1;
  int last2 = last;
  int index = first1;
  while((first1<=last1) && (first2<=last2)){
    //counter++;
    if(theArray[first1]<=theArray[first2]){
      tempArray[index] = theArray[first1];
      first1++;
    }
    else{
      tempArray[index] = theArray[first2];
      first2++;
    }
    index++;
  }
  while(first1<=last1){
    tempArray[index] = theArray[first1];
    first1++;
    index++;
  }
  while(first2<=last2){
    tempArray[index] = theArray[first2];
    first2++;
    index++;
  }
  for(index = first; index<=last; index++){
    theArray[index] = tempArray[index];
  }
  delete[] tempArray; //Free up the space used by the temp array when done
}
/*
I decided to place the counter nested right inside the main
mergeSort function because it must be called on every iteration
so it should provide a fairly good estimate of the complexity
of the algorithm.
*/
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
    /*
The main function is identical to the main function in
Question3.cpp except that it calls the mergeSort function
rather than the quickSort function obviously
    */
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
    SIZE = theArray.size();
    mergeSort(theArray, first, last);
    std::cout<<file<<"                     "<<counter<<"\n";
    //std::string to_write = "./"+filePrefix+fileName[i]+"_SORTED"+fileExtension;  //Save vector to its own file
    //std::ofstream output_file(to_write);
    //std::ostream_iterator<int> output_iterator(output_file, "\n");
    //std::copy(theArray.begin(), theArray.end(), output_iterator);
  }
}
