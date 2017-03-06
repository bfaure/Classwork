/*
Brian Faure
RUID:150003563
Programming Methodology I
Homework 3
*/

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

//First defining Number class
template<typename T>   //Creating generic template T
class Number{
 protected:
  T value;   //Defining variable "value" of generic type "T"
 public:
  Number(){}; //Default constructor
  T getValue(); //Returns stored 'value' from protected
  void setValue(T a); //Sets value to input 'a'
  virtual std::string toString();  //Returns string rep. 
};


//Now to define complex number class
template<typename T>  //Carrying generic type 'T'
class ComplexNumber: public Number<T>{  //Inheriting the public of 'Number' 
 protected:
  T imag_value;  //New variable to store imaginary value
 public:
  ComplexNumber(){};
  void setImaginary(T a); 
  T getImaginary();
  std::string toString();
};


//--------------------------------------------------------
//Number class function definitions

template<typename T>  //Carrying generic type 'T'
T Number<T>::getValue(){  //Defining getValue function for Number class
  return value;  //returns the value stored in protected
}
template<typename T>
void Number<T>::setValue(T a){  //Defining the setValue function for Number class
  value=a;  //Sets the protected value to the input of function
}
template<typename T>
std::string Number<T>::toString(){  //Defining the toString function for Num. class
  std::string string_value;  //New string called string_value 
  string_value=std::to_string(value);  //Assigning value to string_value
  return string_value;  //Returns string form of protected 'value'
}

//End Number class function definitions
//--------------------------------------------------------



//--------------------------------------------------------
//ComplexNumber class function definitions

template<typename T>
void ComplexNumber<T>::setImaginary(T a){
  imag_value=a;  //protected 'imag_value' will now equal input 'a'
}
template<typename T>
T ComplexNumber<T>::getImaginary(){
  return imag_value; //returns imag_value stored in protected
}
template<typename T>
std::string ComplexNumber<T>::toString(){
  T real_part= Number<T>::getValue(); //Fetching real value stored
  T imag_part= getImaginary(); //Fetching imag value stored
  std::string real_string = std::to_string(real_part); //Turning into string
  std::string imag_string = std::to_string(imag_part);
  std::string output; //Creating string to hold output
  output.append(real_string); //adding the real part
  if(imag_part>=0){ //If imag part positive, will need addition sign
    output.append("+");
  }
  output.append(imag_string); //adding the imag part
  output.append("i");
  return output; //Returning finished string output
}

//End ComplexNumber class function definitions
//--------------------------------------------------------



//--------------------------------------------------------
//Operator definitions

template<typename T> //ComplexNumber times ComplexNumber
ComplexNumber<T> operator*(ComplexNumber<T> &x, ComplexNumber<T> &y){
  T a = x.getValue(); //Fetching real & imag values from both complex numbers
  T b = x.getImaginary();
  T c = y.getValue();
  T d = y.getImaginary();
  T imag_sum = ((a*d)+(b*c)); //Formulas for calculating complex mult... 
  T real_sum = ((a*c)-(b*d)); //...Found online
  ComplexNumber<T> output; //Creating output complex number
  output.setValue(real_sum); //loading in the real part
  output.setImaginary(imag_sum); //loading in the imag part
  return output; //returning the finished complex number with the product stored
}
template<typename T> //Number times Number
Number<T> operator*(Number<T> &a, Number<T> &b){  
  T valueA = a.getValue(); //Retrieving values stored in 'Numbers'
  T valueB = b.getValue();
  Number<T> output; //creating new number
  T product;
  product = valueA*valueB;
  output.setValue(product); //store product as new value
  return output; //Returns new Number with product as its stored value
}
template<typename T> //Number times ComplexNumber
ComplexNumber<T> operator*(Number<T> &x, ComplexNumber<T> &y){
  T a = x.getValue(); //Real part of "Number"
  T b = 0; //Imaginary part of "Number" is zero
  T c = y.getValue(); //Real part of ComplexNumber
  T d = y.getImaginary(); //Imag part of ComplexNumber
  T imag_sum = ((a*d)+(b*c)); //Using same formula as mult. of 2 ComplexNumbers
  T real_sum = ((a*c)-(b*d));
  ComplexNumber<T> output;
  output.setValue(real_sum); //Loading in the values for real and imag.
  output.setImaginary(imag_sum);
  return output;
}
template<typename T> //ComplexNumber time Number
ComplexNumber<T> operator*(ComplexNumber<T> &x, Number<T> &y){
  T a = x.getValue(); //Real part of complex
  T b = x.getImaginary();//Imag part of complex
  T c = y.getValue();//Real part of Number
  T d = 0; //Imag. part of Number is zero
  T imag_sum = ((a*d)+(b*c));
  T real_sum = ((a*c)-(b*d));
  ComplexNumber<T> output;
  output.setValue(real_sum); //Loading in the values for real and imag.
  output.setImaginary(imag_sum);
  return output;
}

//End Operator definitions
//--------------------------------------------------------


//--------------------------------------------------------
//complexSum Function
template<typename T> 
ComplexNumber<T> complexSum(std::vector<Number<T>*> input){
  T real_sum = 0; //creating variables to store imag
  T imag_sum = 0; //and real sums
  for(int j=0;j<input.size();j++){
    if(ComplexNumber<T>* a=dynamic_cast<ComplexNumber<T>*>(input[j])){
      //If statement to check if complex sum first
      T real;
      T imag;
      real=a->getValue(); //Fetching values stored in vector element
      imag=a->getImaginary();
      real_sum += real; //Adding values to total
      imag_sum += imag;
    }
  }
  ComplexNumber<T> sum; //Creating sum ComplexNumber to be output
  sum.setValue(real_sum); //Storing sums in ComplexNumber output
  sum.setImaginary(imag_sum);
  return sum; //Returning the finished complex number
}
    
