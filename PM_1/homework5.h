/*
Brian Faure
Programming Methodology 
Homework 5
*/

#ifndef __HOMEWORK5_H__
#define __HOMEWORK5_H__

#include <string>
#include <utility>
#include <vector>
#include <iterator>

//-------------------------------------------------------------------------
//Problem One
template <typename T>
std::pair<T,T> problem1(T beg, T end){
  T smallest;
  T largest;
  int large = 0;
  int small = 10000000;
  for( ; beg!=end; beg++){
    if(*beg<small){
      small = *beg;
      smallest = beg;
    }
    if(*beg>large){
      large = *beg;
      largest = beg;
    }
  }
  std::pair<T,T> output;
  output = std::make_pair(smallest,largest);
  return output;
} 
  
//-------------------------------------------------------------------------
//Problem Two
template <typename T>
std::pair<int,int> problem2(std::vector<std::vector<T>> input, T sample){
  int size = input.size();
  std::pair<int,int> output;
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      if(input[i][j]==sample){
	output = std::make_pair(i,j);
	return output;
      }
    }
  }
  output = std::make_pair(-1,-1);
  return output;
}

//-------------------------------------------------------------------------
//Problem Three
int problem3(std::vector<int>::iterator begin, std::vector<int>::iterator end, int value){
  int steps = 1;
  std::vector<int>::iterator start = begin;
  std::vector<int>::iterator stop = end;
  while(start!=stop){
    int dist = std::distance(start,stop);
    std::vector<int>::iterator middle = start;
    std::advance(middle,dist/2);
    if(*middle==value){
      return steps;
    }
    else if (*middle < value){
      start = ++middle;
    }
    else{
      stop = middle;
    }
    steps += 1;
  }
  return steps;
}

//-------------------------------------------------------------------------
//Problem Four
template <typename T>
class problem4{
 public:
  T data;
  problem4(){
    data = 0;
  }
  void save(T input){
    data=data+input;
  }
  T spend(){
    T temp;
    temp = data;
    data = 0;
    return temp;
  }
};
    
//-------------------------------------------------------------------------
//Problem Five
std::string problem5(std::string a, std::string b) {
	return a+" "+b;
}

template<typename T,typename... others>
  std::string problem5(T a,T b, others... rest){
  return problem5(a,b)+" "+problem5(rest...);
}
  
//-------------------------------------------------------------------------
//Problem Six
template<int N>
bool problem6(const int input){
  if(input%N==0){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------------
//Problem Seven
template<typename T,typename A>
void problem7(T beg,T end, A func){
  std::sort(beg,end,func);
}
    
//-------------------------------------------------------------------------    
    
    


#endif


