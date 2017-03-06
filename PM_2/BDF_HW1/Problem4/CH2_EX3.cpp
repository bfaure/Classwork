/*
Brian Faure
RUID:150003563
NetID:bdf39
Problem #4
Chapter 2
Exercise 3
*/

/*
Write a recursive function that will compute the sum of the first n integers in
an array of at least n integers.
*/

#include <iostream>
#include <string>
#include <vector>


int sum = 0;  //Initialize the function output to zero
int arraySum(int n, std::vector<int> input){  //Function will take 2 inputs
  if(n==1){  //Ending condition, return final sum
    return sum+input[0];
  }
  else{
    sum = sum + input[n-1]; //Add current value to total sum
    return(arraySum(n-1,input)); //Call function recursively if not complete
  }
}


//To check output...
/*
int main(){
  std::vector<int> input = {1,2,3,4,5};
  int in = 4;
  int output = arraySum(in,input);
  std::cout<<"The sum of the first "<<in<<" elements is: "<<output<<"\n";
}
*/
