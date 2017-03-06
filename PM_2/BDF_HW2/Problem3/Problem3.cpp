/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Meth. II
Homework #2
Problem #3
*/

/*
Implement an iterative solution to the Towers of Hanoi.
*/

/*
Credit for some of the rules I used should go to Randolph Franklin at 
Rensselaer Polytechnic Institute...
http://www.ecse.rpi.edu/~wrf/p/28-sigplan84-hanoi.pdf

-->   3 Rules are as follows:
#1) Move odd-numbered disks only CW and even-numbered disks only CCW
#2) Do not move the same disk twice in succession
#3) Do not place a larger disk on top of a smaller one

Implemented these 3 simple rules in the following functions and loops... 
*/

//------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>
//------------------------------------------------------------------------------------
int lastDisc = 0;   //Initialize global variable to hold last disc moved
std::string rules(std::vector<int> input, int last){
  int top;   //Function to evaluate whether top should break left or right
  if(input.size()==0){  //Return small if pole has no contents
    return "small";
  }
  top = input.back();
  if(top==last){  //Return notAGAIN if top was last disc moved
    return "notAGAIN";
  }
  int remainder = top%2;
  if(remainder == 0){
    return "LEFT";  //Evaluate left or right options
  }
  return "RIGHT";
}
//------------------------------------------------------------------------------------
std::string fair(std::vector<int> check, std::vector<int> right, std::vector<int> left, std::string direction){
  int rSIZE = right.size();
  int lSIZE = left.size();
  int rTOP = 100000; //Set to abitrarily chosen large number...
  int lTOP = 100000; //...(never going to have over 100000 discs)
  int cTOP = check.back(); //Top of the current pole
  if(rSIZE != 0){
    rTOP = right.back();
  }
  if(lSIZE != 0){
    lTOP = left.back();
  }
  if(direction == "LEFT"){ //This function evaluates whether the findings of the rules
    if(cTOP<lTOP){         //function will fit with the fact that a larger disc
      return "FAIR";       //cannot be placed on a smaller one
    }
    else{
      return "notFAIR";
    }
  }
  if(direction == "RIGHT"){
    if(cTOP<rTOP){
      return "FAIR";  
    }
    else{
      return "notFAIR";
    }
  }
  return "ERROR"; //Used when troubleshooting errors
}
//------------------------------------------------------------------------------------
std::string findMove(std::vector<int> SRC, std::vector<int> DEST, std::vector<int> SPR, int LDISC){
  std::string aMOVE = rules(SRC, LDISC);  //These 3 calls find which direction (if any) 
  std::string bMOVE = rules(DEST, LDISC); //the disc should be moved in
  std::string cMOVE = rules(SPR, LDISC);
  std::string aFAIR = "notFAIR";
  std::string bFAIR = "notFAIR";
  std::string cFAIR = "notFAIR";
  if(aMOVE!="small" and aMOVE!="notAGAIN"){
    aFAIR = fair(SRC, DEST, SPR, aMOVE);  //If the move passed the rules function
  }                                       //it is double-checked with the fair function
  if(bMOVE!="small" and bMOVE!="notAGAIN"){
    bFAIR = fair(DEST, SPR, SRC, bMOVE);
  }
  if(cMOVE!="small" and cMOVE!="notAGAIN"){
    cFAIR = fair(SPR, SRC, DEST, cMOVE);
  }
  std::string move;
  if(aFAIR == "FAIR"){
    move = "SRC"+aMOVE;  //findMove will only ever find one legal move to make
    return move;         //when it is found, concatenate the moves ie...
  }                      //"Pole moved" + "move direction" and output that to the
  if(bFAIR == "FAIR"){   //Overall solveTowers function to make the needed changes
    move = "DEST"+bMOVE; //and output the results
    return move;
  }
  if(cFAIR == "FAIR"){
    move = "SPR"+cMOVE;
    return move;
  }
  return "ERROR";
  //std::cout<<"\nThere was an ERROR in the findMove function\n";
}
//------------------------------------------------------------------------------------
void solveTowers(int count, char source, char destination, char spare){
  int numSteps;
  numSteps = pow(2,count);  //We know the number of moves will be constant 
  numSteps--;               //based on the number of discs involved 
  std::vector<int> sourceStack;
  std::vector<int> destinationStack;
  std::vector<int> spareStack;
  //std::cout<<source<<": ";
  for(int i=count; i>0; i--){ //Load up the source vector initially
    sourceStack.push_back(i); //with the number of discs specified
    //std::cout<<i<<" ";
  }
  //std::cout<<"\n";
  for(int i=1; i<=numSteps; i++){  //Start loop to evaluate moves
    std::string next = findMove(sourceStack, destinationStack, spareStack,lastDisc);
    //std::cout<<"The next move will be: "<<next<<"\n";
    std::cout<<"Move top disk from pole ";
    int top;
    if(next=="SRCRIGHT"){
      std::cout<<source<<" to pole "<<destination<<"\n";
      top = sourceStack.back();
      sourceStack.pop_back();                      //These comparisons evaluate the findings
      destinationStack.push_back(top);             //of the findMove function and basically 
    }                                              //do the book-keeping of the 3 poles as well
    if(next=="SRCLEFT"){                           //as outputting each step along the way
      std::cout<<source<<" to pole "<<spare<<"\n";
      top = sourceStack.back();
      sourceStack.pop_back();
      spareStack.push_back(top);
    }
    if(next=="DESTRIGHT"){
      std::cout<<destination<<" to pole "<<spare<<"\n";
      top = destinationStack.back();
      destinationStack.pop_back();
      spareStack.push_back(top);
    }
    if(next=="DESTLEFT"){
      std::cout<<destination<<" to pole "<<source<<"\n";
      top = destinationStack.back();
      destinationStack.pop_back();
      sourceStack.push_back(top);
    }
    if(next=="SPRRIGHT"){
      std::cout<<spare<<" to pole "<<source<<"\n";
      top = spareStack.back();
      spareStack.pop_back();
      sourceStack.push_back(top);
    }
    if(next=="SPRLEFT"){
      std::cout<<spare<<" to pole "<<destination<<"\n";
      top = spareStack.back();
      spareStack.pop_back();
      destinationStack.push_back(top);
    }
    lastDisc = top;
    //int asize = sourceStack.size();
    //int bsize = destinationStack.size();
    //int csize = spareStack.size();
    //std::cout<<"A size: "<<asize<<"\n"<<destination<<" size is: "<<bsize<<"\n"<<spare<<" size is: "<<csize<<"\n";
  }
}
//------------------------------------------------------------------------------------     
int main(){
  std::cout<<"Enter the number of discs: ";
  int numDiscs;
  std::cin>>numDiscs;
  char first = 'A';
  char second = 'B';
  char third = 'C';
  if(numDiscs%2==0){         //With the rules I used, I found that in order to 
    char fourth = second;    //always have the destination be "B", I needed to 
    second = third;          //evaluate whether or not the number of discs was 
    third = fourth;          //even or odd before calling the function
  }
  solveTowers(numDiscs, first, second, third);   //Call the function to start the puzzle
}
//------------------------------------------------------------------------------------
