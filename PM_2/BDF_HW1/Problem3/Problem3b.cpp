/*
Brian Faure
RUID:150003563
NetID:bdf39
HW#1 Problem 3 (ii), Part 2
*/

/*
Implement the algorithm kSmall for two method for choosing the pivot:
(ii) Use the value that is at the "middle index" as the pivot.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


std::vector<int> read_file(std::string filename){   
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}


int kSmall(int k, std::vector<int> anArray, int first, int last){
  int pivot = (first+last)/2;                 //Changed pivot from the first position in vector
  int p = anArray[pivot];                     //Find current pivot value
  std::cout<<"The pivot value is: "<<p<<"\n"; //Output current pivot value
  std::vector<int> lessthan;                  //Create vector to hold values less than pivot
  std::vector<int> greaterthan;               //Create vector to hold values equal to pivot
  std::vector<int> equalto;                   //Create vector to hold values greater than pivot
  for(int i=0;i<anArray.size(); i++){         //Push smaller values into lessthan array
    if(anArray[i]<p){
      lessthan.push_back(anArray[i]);
    }
    if(anArray[i]>p){                         //Push values equal to pivot
      greaterthan.push_back(anArray[i]);
    }
    if(anArray[i]==p){                        //Push values greater than pivot
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
  int pivotIndex = lessthan.size()+equalto.size()-1;                        //Pivot index after partitioning
  //std::cout<<"The pivotIndex is: "<<pivotIndex<<"\n\n";
  lessthan.insert(lessthan.end(), equalto.begin(), equalto.end());          //Recombine all arrays 
  lessthan.insert(lessthan.end(), greaterthan.begin(), greaterthan.end());  //after partitioning
  anArray=lessthan;                                                         //is complete
  if(k < (pivotIndex-first+1)){                            //Logic behind kSmall from textbook pg.75...
    return kSmall(k, anArray, first, pivotIndex-1);        //
  }                                                        //
  else if(k==(pivotIndex-first+1)){                        //
    return anArray[pivotIndex];                            //Base Case                          
  }                                                        //...
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
  int size = data.size();
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

