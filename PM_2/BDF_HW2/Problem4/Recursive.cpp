/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Meth. II
Homework #2
Problem #2
*/

/*
Compare the timings of your iterative and recursive implementations, as a function of N.
*/

//------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
//------------------------------------------------------------------------------------
time_t before; //Global before and after time variables
time_t after;
double seconds;
void solveTowers(int count, char source, char destination, char spare){
  if(count==1){
    //std::cout<<"Move top disk from pole "<<source;
    //std::cout<<" to pole "<<destination<<"\n";
  }     
  else{
    solveTowers(count-1, source, spare, destination);
    solveTowers(1, source, destination, spare);
    solveTowers(count-1, spare, destination, source);
  }

}
//------------------------------------------------------------------------------------
int main(){
  char first = 'A';
  char second = 'B';
  char third = 'C';
  for(int i=1; i<=22; i++){
    before = clock();
    solveTowers(i, first, second, third);
    after = clock();
    seconds = double(after-before)/CLOCKS_PER_SEC;
    std::cout<<seconds<<"\n";
  }
}
//------------------------------------------------------------------------------------
