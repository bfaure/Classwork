/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Meth. II
Homework #2
Problem #1
*/

/*
Implement a recursive solution to the Towers of Hanoi using pseudo-code discussed
in class. It should be written to calculate the number of "moves" for an arbitrary
value of N, where N is the number of discs. How many moves are made for N=10? Plot
the number of moves as a function of N, for as many N as your computer/implementation
will allow.
*/

//------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
//------------------------------------------------------------------------------------
int steps;   //Create global variable to hold number of steps
void solveTowers(int count, char source, char destination, char spare){
  if(count==1){
    //std::cout<<"Move top disk from pole "<<source;
    //std::cout<<" to pole "<<destination<<"\n";
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
  std::cout<<"Enter an integer for count of disks: ";
  int input;
  std::cin>>input;
  char first = 'A'; //Initializing the characters used in function
  char second = 'B';
  char third = 'C';
  solveTowers(input,first,second,third);
  std::cout<<"Number of steps: "<<steps<<"\n";
  //N=0;
  //solveTowers(input, first, second, third);
  //std::cout<<"The number of steps was: "<<N<<"\n";
  /*
  for(int i=1; i<32; i++){ //31 was about the highest my program could go
    steps=0;  //Reset steps to 0 on each iteration
    solveTowers(i, first, second, third); //Call function to edit N variable
    //std::cout<<"For "<<i<<" discs, "<<N<<" steps were taken\n";
    std::cout<<steps<<"\n"; //Output N steps for each pass through
  } 
  */
}
//------------------------------------------------------------------------------------
