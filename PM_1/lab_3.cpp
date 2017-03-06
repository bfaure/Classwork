/*
Brian Faure
RUID - 150003563
Programming Methodology Lab 3
Feb 5, 2015
Didn't understand how to incorporate the function given in the instructions, works the same without it though I think
*/

#include <iostream>
#include <vector>
#include <string>
#include <math.h> //Needed for power function

int main() {
  float val;
  std::cout<<"Please enter an even number of numerical inputs followed by a letter:\n";
  std::vector<float> inputs;
  std::vector<float> samples;
  std::vector<float> freqs;
  std::vector<float> discrete;
  std::vector<float> place;
  std::vector<float> vars2;
  //Initializing all Vectors to be used later
  while (std::cin>>val) {
    inputs.push_back(val);
  }
  if (inputs.size()%2 !=0) {
    std::cout<<"Require even amount of numerical inputs\n";
    return 0;
  }
  //Error in case of odd number of inputs
  std::cout<<'\n';
  std::cout<<"The sample values are:\n";

  for(int a=0; a<(inputs.size()/2); a++) {
    samples.push_back(inputs[a]);
    std::cout<<inputs[a];
    std::cout<<" ";
  }
  std::cout<<'\n';
  std::cout<<"The frequencies are:\n";
  for(int b=(inputs.size()/2); b<(inputs.size()); b++) {
    
    freqs.push_back(inputs[b]);
    std::cout<<inputs[b];
    std::cout<<" ";
  }
  std::cout<<'\n';
  int g=0;
  for(int d=(inputs.size()/2); d<(inputs.size());d++) {
    g=g+(inputs[d]);
  }
  std::cout<<"The discrete probability distribution is:\n";
  for(int z=(inputs.size()/2); z<(inputs.size()); z++) {
    discrete.push_back(inputs[z]/g);
    std::cout<<(inputs[z]/g);
    std::cout<<" ";
  }
  std::cout<<'\n';
  std::cout<<"The mean is ";
  float mean = 0;
  for(int y=0; y<(inputs.size()/2); y++) {
    mean = mean + (samples[y]*freqs[y]);
  }
  float mean1 = mean/g;
  std::cout<<mean1;
  std::cout<<".\n";
  float variance = 0;
  std::cout<<"The variance is ";
  for(int x=0; x<(inputs.size()/2); x++) {
    place.push_back(pow(inputs[x]-mean1,2));
    vars2.push_back(place[x]*freqs[x]);
    variance = variance + vars2[x];
  }
  float variance1 = variance/10;
  std::cout<<variance4;
  std::cout<<".\n";
  std::cout<<'\n';
  return 0;
}



