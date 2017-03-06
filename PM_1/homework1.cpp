/*
Brian Faure
Programming Methodology
Homework #1
RUID:150003563
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
int main(int argc,char ** argv) {
  if(argc == 1) {
    return 1;   //Error when called w/o arguments
  }
  std::string sum ("sum");
  std::string mean ("mean");
  std::string mode ("mode");
  std::string odd ("odd");
  std::string even ("even");   //Identifying all possible input strings
  std::vector<float> inVec;
  if(sum.compare(argv[1])==0) {   //First case that user asks for sum
    float input;   //Create vector of numerical inputs (used for every correct input)
    while(std::cin>>input) {
      inVec.push_back(input);
    }
    if(inVec.size()==0) {   //If input vector contains no numbers, return 3
      return 3;
    }
    float s;
    for(int i=0; i<inVec.size(); i++) {
      s = s + inVec[i];
    }
    std::cout<<s;   //Output sum
    std::cout<<'\n';
    return 0;
  }
  else if(mean.compare(argv[1])==0) {   //Second case that user asks for mean
    float input;
    while(std::cin>>input) {   //Establish vector of inputs
      inVec.push_back(input);
    }
    if(inVec.size()==0) {   //Return 3 if no numerical inputs
      return 3;
    }
    float s;
    for(int i=0; i<inVec.size(); i++) {
      s=s+inVec[i];   //Re-establish the value of sum
    }
    int num_inputs = inVec.size();   //Establish the number of inputs
    float mean1=s/num_inputs;
    std::cout<<mean1;   //Output the mean
    std::cout<<'\n';
    return 0;
  }
  else if(mode.compare(argv[1])==0) {   //Third case that user asks for mode
    float input;
    while(std::cin>>input) {   //Establish vector of inputs
      inVec.push_back(input);
    }
    if(inVec.size()==0) {   //Return 3 if no numerical inputs
      return 3;
    }
    std::vector<int> count;   //Create counting vector
    for(int i=0; i<inVec.size(); i++) {
      int cnt = 0;
      for(int a=i+1;a<inVec.size();a++) {   //Loop that compares values in input vector stream
	if(inVec[i]==inVec[a]) {
	  cnt++;
	}
      }
      count.push_back(cnt);   //Input count values to new count vector
    }
    int high = 0;
    float x = 0;
    for(int p=0; p<count.size(); p++) {   //Find the highest value in count vector
      if(count[p] > high) {
	x=inVec[p];
	high=count[p];
      }
    }
    std::cout<<x;   //Output the mode
    std::cout<<'\n';
    return 0;
  }
  else if(odd.compare(argv[1])==0) {   //Fourth case that user asks for odd
    float input;
    while(std::cin>>input) {   //Establish vector of inputs
      inVec.push_back(input);
    }
    if(inVec.size()==0) {   //Return 3 if no numerical inputs
      return 3;
    }
    int num_odd = 0;
    for(int i=0; i<inVec.size(); i++) {
      if(fmod(inVec[i],2) != 0) {   //Using modulo 2 to test for odds
	num_odd = num_odd+1;
      }
    }
    std::cout<<num_odd;   //Output number of odds
    std::cout<<'\n';
    return 0;	
  }
  else if(even.compare(argv[1])==0) {   //Fifth case that user asks for even count
    float input;
    while(std::cin>>input) {   //Establish vector of inputs
      inVec.push_back(input);
    }
    if(inVec.size()==0) {   //Return 3 if no numerical inputs
      return 3;
    }
    int num_ev = 0;
    for(int i=0; i<inVec.size(); i++) {
      if(fmod(inVec[i],2)==0) {   //Using modulo 2 to test for evens
	num_ev = num_ev+1;
      }
    }
    std::cout<<num_ev;   //Output number of evens
    std::cout<<'\n';
    return 0;
  }
  else {  //Return 2 if input not recognized
    return 2;
  }
}




		      
      
   
   

  
  




