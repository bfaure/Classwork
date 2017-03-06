/*
Brian Faure
RUID:150003563
NetID:bdf39
HW#1 Problem 3 (i)
*/

/*
Implement the algorithm kSmall for two method for choosing the pivot:
(i) Use the first value of the array as the pivot
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> read_file(std::string filename){ //Function to read file into vector
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}

int kSmall(int k, std::vector<int> anArray, int first, int last){
  int pivot = first; //Set pivot to the first value input
  int p = anArray[pivot];
  std::cout<<"The pivot value is: "<<p<<"\n";
  std::vector<int> lessthan; //Set up vectors to hold partitioned vector components
  std::vector<int> greaterthan;
  std::vector<int> equalto;
  for(int i=0;i<anArray.size(); i++){ //Push values smaller than pivot
    if(anArray[i]<p){
      lessthan.push_back(anArray[i]);
    }
    if(anArray[i]>p){ //Push values larger than pivot
      greaterthan.push_back(anArray[i]);
    }
    if(anArray[i]==p){ //Push values equal to pivot
      equalto.push_back(anArray[i]);
    }
  }
  /*if(equalto.size()>1){
    for(int i=0; i<equalto.size(); i++){
      equalto.pop_back();
    }
  }  
  std::cout<<"\n";
  for(int i=0; i<equalto.size(); i++){
    std::cout<<equalto[i]<<"\n";
  }
  */
  int pivotIndex = lessthan.size()+equalto.size()-1; //Set pivotIndex to the partition location
  //std::cout<<"The pivotIndex is: "<<pivotIndex<<"\n\n";
  lessthan.insert(lessthan.end(), equalto.begin(), equalto.end());  //Append all three vectors into new vector
  lessthan.insert(lessthan.end(), greaterthan.begin(), greaterthan.end());
  anArray=lessthan; //Reassign the anArray vector after partitioning
  if(k < (pivotIndex-first+1)){  //kSmall logic from textbook
    return kSmall(k, anArray, first, pivotIndex-1);
  }
  else if(k==(pivotIndex-first+1)){
    return anArray[pivotIndex];
  }
  else{
    return kSmall(k-(pivotIndex-first+1), anArray, pivotIndex+1, last);
  }
}

/*
void checker(int k, int output, std::vector<int> input){
  std::vector<int> temp = input;
  std::sort(temp.begin(), temp.end());
  //temp.erase(unique(temp.begin(), temp.end()), temp.end());
  std::cout<<"Actual value: "<<temp[k-1]<<"\n";
  if(output == temp[k-1]){
    std::cout<<"kSmall worked!\n";
  }
  else{
    std::cout<<"kSmall did not work.\n";
  }
}
*/
    
int main(){
  std::vector<int> data = read_file("hw2-data.txt");
  //int size = data.size();
  /*
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<"\n";
  }
  */
  int first = 0;
  int last = data.size()-1;
  //std::cout<<"What value would you like to find?\n";
  //int user;
  //std::cin>>user;
  int value = kSmall(42, data, first, last);
  std::cout<<"kSmall output: "<<value<<"\n";
  //checker(42, value, data);
}
