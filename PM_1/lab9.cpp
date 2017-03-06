/*
Brian Faure
Programming Methodology Lab
Lab 9
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>

template<typename T>
class myQueue{
protected:
  std::stack<T> input_stack;
  std::stack<T> output_stack;
public:
  void push(T);
  void pop();
  T front();
  T back();
  int size();
  bool empty();
  void swap(myQueue<T> *other);
};

//myQueue function definitions

template<typename T>
void myQueue<T>::push(T a){
  input_stack.push(a);
}


template<typename T>
void myQueue<T>::pop(){
  std::stack<T> temp;
    while(!input_stack.empty()){
      temp.push(input_stack.top());
      input_stack.pop();
    }
    while(!output_stack.empty()){
      input_stack.push(output_stack.top());
      output_stack.pop();
    }
    while(!input_stack.empty()){
      temp.push(input_stack.top());
      input_stack.pop();
    }
    while(!temp.empty()){
      input_stack.push(temp.top());
      temp.pop();
    }
    while(!input_stack.empty()){
      output_stack.push(input_stack.top());
      input_stack.pop();
  }
  output_stack.pop();
}

template<typename T>
T myQueue<T>::back(){
  std::stack<T> temp;
  T newest;
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!output_stack.empty()){
    input_stack.push(output_stack.top());
    output_stack.pop();
  }
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!temp.empty()){
    input_stack.push(temp.top());
    temp.pop();
  }
  newest = input_stack.top();
  while(!input_stack.empty()){
    output_stack.push(input_stack.top());
    input_stack.pop();
  }
  return newest;
}

template<typename T>
T myQueue<T>::front(){
  std::stack<T> temp;
  T oldest;
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!output_stack.empty()){
    input_stack.push(output_stack.top());
    output_stack.pop();
  }
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!temp.empty()){
    input_stack.push(temp.top());
    temp.pop();
  }
  while(!input_stack.empty()){
    output_stack.push(input_stack.top());
    input_stack.pop();
  }
  oldest = output_stack.top();
  return oldest;
}


template<typename T>
int myQueue<T>::size(){
  int size = input_stack.size() + output_stack.size();
  return size;
}

template<typename T>
bool myQueue<T>::empty(){
  int size = input_stack.size() + output_stack.size();
  if(size==0){
    return true;
  }
  return false;
}

template<typename T>
void myQueue<T>::swap(myQueue<T> *other){
  std::stack<T> temp;
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!output_stack.empty()){
    input_stack.push(output_stack.top());
    output_stack.pop();
  }
  while(!input_stack.empty()){
    temp.push(input_stack.top());
    input_stack.pop();
  }
  while(!temp.empty()){
    input_stack.push(temp.top());
    temp.pop();
  }
  while(!input_stack.empty()){
    output_stack.push(input_stack.top());
    input_stack.pop();
  }
  while(!output_stack.empty()){
    temp.push(output_stack.top());
    output_stack.pop();
  }
  while(!other->empty()){
    input_stack.push(other->front());
    other->pop();
  }
  while(!input_stack.empty()){
    output_stack.push(input_stack.top());
    input_stack.pop();
  }
  while(!temp.empty()){
    other->push(temp.top());
    temp.pop();
  }
}




int main(){
    myQueue<int> q1, q2, q3;
    std::vector<int> a = {2, 4, 1, 7, 8, 9 ,0}, b = {1, 0, 4, 3, 8, 9, 10, 13, 7, 6, 5, 14, 11};
    for(int i = 0; i < a.size(); ++i){
      q1.push(a[i]);
    }
    for(int i = 0; i < b.size(); ++i){
      q2.push(b[i]);
    }
    std::cout<< "Initial Queue:"<<std::endl;
    while(!q1.empty()){
      std::cout << q1.front() << " " ;
      q3.push(q1.front());
      q1.pop();
    }
    std::cout<<std::endl;
    std::cout<<std::endl<<"Size of Q3 (Q1 Reversed): "<<q3.size()<<std::endl;
    std::cout<<"Back element of Q3: "<<q3.back()<<std::endl;
    q3.swap(&q2); //Needed to pass by reference in order to change value of q2
    std::cout<<std::endl<<"Size of Q3 (after swap): "<<q3.size();
    std::cout<<std::endl<<"Size of Q2 (after swap): "<<q2.size()<<std::endl;

    //Code for min and max of Q3
    int max = 0;
    int min = 100000;
    while(!q3.empty()){   
      int temp = q3.front();
      if(temp>max){
	max = temp;
      }
      if(temp<min){
	min = temp;
      }
      q3.pop();
    }
    std::cout<<std::endl;
    std::cout<<"Max of Q3: "<<max<<std::endl;
    std::cout<<"Min of Q3: "<<min<<std::endl;   
}


