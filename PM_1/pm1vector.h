//Brian Faure
//Programming Methodology
//Homework 2
//RUID:150003563

#ifndef PM1VECTOR_H  //Checks if already in use
#define PM1VECTOR_H

namespace pm1{  //Defining custom namespace
  class Vector{
  public:
    typedef int* iterator;
    //Defining iterator to point at vector values
    Vector();
    //Default constructor
    Vector(unsigned int initial_size);
    //Construct only vector, no inputs
    
    Vector(unsigned int initial_size, int initial_value);
    //Constructor with initial size and value
    
    ~Vector();
    //Destructor
    int& operator[](unsigned int offset);
    //Creating vector[] function to call member of vector
    int& at(unsigned int offset);
    //Almost the same at the operator[], called differently
    iterator begin();
    //Provides the address of first vector value
    iterator end();
    //Provides the address of last vector value

    //----------------------------------------------------

    //Functions to modify the container...
    void insert(pm1::Vector::iterator location, int value);
    //Insert integer at certain location in vector
    void clear();
    //Clear the vector of its current values
    void erase(pm1::Vector::iterator location);
    //Clears the one value and decreases size by one
    void push_back(int value);
    //Add one value to end of vector
    void pop_back();
    //Delete that value at end of vector
    //End of Functions to modify the container

    //-----------------------------------------------

    //Functions to check the number of elements...
    unsigned int size();
    //Returns the number of elements in the container
    bool empty();
    //Returns true if vector is empty, false otherwise
    //End of functions to check the number of elements

    //----------------------------------------------

    //Declaration of Comparison Operators...
    /* As explained in the cpp file, these only have one
       input because there in an implied first input of 
       pointer type 'this'
    */
    bool operator==(pm1::Vector& b);
    bool operator!=(pm1::Vector& b);
    bool operator<(pm1::Vector& b);
    bool operator>(pm1::Vector& b);
    bool operator<=(pm1::Vector& b);
    bool operator>=(pm1::Vector& b);
    //End of Comparison Operators

    //--------------------------------------------- 
      
  private:
    int* data_;   //Pointer to data 
    unsigned int mem_size_;   //Integer used to verify size of vector stored
    unsigned int size_;   //How many actual values are stored
    void increaseSize();  //Doubles memory size available
  };
}
#endif

