//Brian Faure
//Programming Methodology
//Homework 2
//RUID:150003563

#include "pm1vector.h"
#include <iostream>
#include <vector>


pm1::Vector::Vector(){
  data_ = new int[10];   //Creating generic vector of size ten
  mem_size_ = 10; 
  size_ = 0;   //No real values, just room in vector for them
}

pm1::Vector::Vector(unsigned int initial_size){
  if(0==initial_size){
    size_=0;
    mem_size_=0;
    data_=nullptr;
  }
  else{
    data_= new int[initial_size];
    mem_size_=initial_size;
    size_=initial_size;
  }
}
//Constructor with initial size and value...
pm1::Vector::Vector(unsigned int initial_size, int initial_value){
  if(0==initial_size){   //Zero size -> modifies values to reflect this
    size_=0;
    mem_size_=0;
    data_=nullptr;
  }
  else{
    data_ = new int[initial_size];   //size of data becomes initil_size 
    mem_size_=initial_size;
    size_=initial_size;
    for(int j=0;j<initial_size;j++){   //Filling in data_ with initial_value
      data_[j]=initial_value;
    }
  }
}

pm1::Vector::~Vector(){
  if(0!=mem_size_){
    delete[] data_;   //If destructor is called, deletes data content
  }
}

int& pm1::Vector::operator[](unsigned int offset){
  return data_[offset];   //Used to reference certain value in data_ vector
}

int& pm1::Vector::at(unsigned int offset){
  if(offset>=size_){
    throw std::out_of_range("Vector Index out of Range");
  }
  return data_[offset];
  //This is very similar to operator[] but called differently
}

pm1::Vector::iterator pm1::Vector::begin(){
  return data_;   //Returns address of first value in vector
}

pm1::Vector::iterator pm1::Vector::end(){
  return data_+size_;   //Returns address of last vector value
}

void pm1::Vector::increaseSize(){
  if(0==mem_size_){   //If there is no vector, create 10 sized vector
    mem_size_=10;
    size_=0;
    data_=new int[mem_size_];   //No contents of new vector
  }
  else{
    mem_size_ *= 2;   //mem_size_ redefined as double itself
    int* bigger = new int[mem_size_];
    for(int j=0;j<size_;j++){
      bigger[j]=data_[j];
    }
    delete[] data_;
    data_ = bigger;   //Data retains info, double the size
    //(This function can only be accessed by class members)
  }
}

//--------------------------------------------------

//Functions to modify the container...
void pm1::Vector::insert(pm1::Vector::iterator location, int value){
  if(begin()>location or end()<location){
    throw std::out_of_range("Requested Insert Location is out of Range");
  }
  if(size_+1 > mem_size_){   //Increasing memory if needed
    int offset = std::distance(begin(),location);  //or location - begin()
    increaseSize();
    location = data_+offset;
  }
  int offset = std::distance(begin(),location);
  int* inserted = new int[mem_size_];
  for(int j=0;j<offset;j++){   //filling in values up to insertion pt.
    inserted[j]=data_[j];
  }
  inserted[offset] = value;   //including insertion pt. value input by user
  for( ;offset<size_;offset++){   //filling in values after insertion
    inserted[offset+1]= data_[offset];
  }
  size_=size_+1;
  delete[] data_;
  data_=inserted;
}
void pm1::Vector::clear(){
  if(size_!=0){
    int* cleared = new int[10];
    delete[] data_;
    data_ = cleared;
    mem_size_=10;
    size_=0;
  }
}
void pm1::Vector::erase(pm1::Vector::iterator location){
  if(begin()>location or end()<location){
    throw std::out_of_range("Element to be erased is outside vector");
  }
  int* erased = new int[mem_size_];  //Creating new vector with smaller size
  int offset=std::distance(begin(),location);
  for(int j=0;j<offset;j++){   //Filling first half with original values
    erased[j]=data_[j];
  }   //Skip the erased data pt. and fill the rest
  for( ;offset<size_-1;offset++){
    erased[offset]=data_[offset+1];
  }
  delete[] data_;
  data_ = erased;
  size_=size_-1;
}
void pm1::Vector::push_back(int value){
  if(size_+1>mem_size_){   //Increase memory if needed
    increaseSize();
  }
  data_[size_]=value;   //Turning the new last value into input
  size_=size_+1;
}
void pm1::Vector::pop_back(){
  if(size_!=0){  //Making room for exception later in function
    int* pop = new int[mem_size_];  //New vector to take one less value
    for(int j=0;j<size_-1;j++){
      pop[j]=data_[j];   //Loading all values except last one
    }
    delete[] data_;   //Deleting old data_
    data_=pop;  //New data_ from pop vector
    size_=size_-1;  //New vector has everything but last value
  }
  else{  //Throwing exception if no values to pop
    throw std::out_of_range("Tried to pop non-existent value");
  }
}  
//End of functions to modify the container


//-----------------------------------------------------------

//Comparison Operators...
/*At first I was struggling with getting the operator declarations in
the class to work with their definitions here but online I found that
when an operator is declared in the class, it has an implied first input
under the name of this which is a pointer to a pm1::Vector object type.
All of the calls to 'this' in the following section pertain to that 
pointer.  I tested the operators with the testvector3 and I believe the
'this' pointer is working correctly.
 */
bool pm1::Vector::operator==(pm1::Vector& b){
  if(this->size() != b.size()){ //this-> accesses 'this' contents
    return false;
  }
  else{
    for(int i=0; i<this->size(); i++){
      if(this->data_[i] != b[i]){
	return false;
      }
    }
  }
  return true;   //Returns true if same size and contents
}
bool pm1::Vector::operator!=(pm1::Vector& b){
  if(*this==b){
    return false;   //Just the opposite of the == operator
  }
  return true; //True based on opposite of == operator
}
bool pm1::Vector::operator<(pm1::Vector& b){
  for(int j=0; j<(b.size()); j++){
    if(this->data_[j]!=b[j]){
      if(this->data_[j]<b[j]){
	return true;   //If a comp. of b > a than true
      }
      if(this->data_[j]>b[j]){
	return false;  //If a comp. of a>b than false
      }
    }
  }
  if(this->size()>=b.size()){
    return false;
  }
 
  return true;   //Otherwise return true
}
bool pm1::Vector::operator>(pm1::Vector& b){
  if(*this<b){  //Based on less than operator
    return false;
  }
  if(*this==b){
    return false;
  }
  return true;  //Otherwise it's true
}
bool pm1::Vector::operator<=(pm1::Vector& b){
  if(b<*this){
    return false;
  }
  return true;
} 
bool pm1::Vector::operator>=(pm1::Vector& b){
  if(b>*this){   //Greater than or equal to operator
    return false;
  }
  return true;
}
//End of Comparison Operators
	
//------------------------------------------------------

//Functions to check the number of elements...
unsigned int pm1::Vector::size(){  //Returns exact size
  return size_;
}
bool pm1::Vector::empty(){  //Returns true or false
  if(size_==0){
    return true;
  }
  return false;
}
//End of functions to check number of elements

  
    

      





