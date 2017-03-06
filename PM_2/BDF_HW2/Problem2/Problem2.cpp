/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Meth. II
Homework #2
Problem #2
*/

/*
Using the pseudo-code, trace the recursive calls for N=4.
*/

//------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
//------------------------------------------------------------------------------------
int steps;   //Create global variable to hold number of steps
void solveTowers(int count, char source, char destination, char spare){
  if(count==1){
    std::cout<<"Move top disk from pole "<<source;
    std::cout<<" to pole "<<destination<<"\n";
    steps++; //Can uncomment the cout section to get the required moves
  }      //steps++ adds a step for each step taken
  else{
    solveTowers(count-1, source, spare, destination);
    solveTowers(1, source, destination, spare);
    solveTowers(count-1, spare, destination, source);
  }
}  //Pretty much just what was presented in class/textbook
//------------------------------------------------------------------------------------
int main(){
  int N=4; //Setting the value of N to 4
  char first = 'A'; //Initializing the characters used in function
  char second = 'B';
  char third = 'C';
  steps=0;
  solveTowers(N, first, second, third);
  std::cout<<"The number of steps was: "<<steps<<"\n";
}
//------------------------------------------------------------------------------------
