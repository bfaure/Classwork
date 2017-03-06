/*
Brian Faure
Programming Methodology Lab
Lab #11
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Student{
public:
  std::string name;
  int age;
  Student(std::string n, int a){
    name=n;
    age=a;
  }
};
class Sum{
public:
  float sum;
  Sum(){
    sum=0;
  }
  void operator () (Student* s){
    sum += s->age;
  };
};
bool Old(Student *s){
  if(s->age > 30){
    return true;
  }
  else{
    return false;
  }
}
int main() {
    std::vector<Student *>::iterator it;
    std::vector<Student *> v;
    Student * s1 = new Student("Luis", 24);
    v.push_back(s1);
    Student * s2 = new Student("Bob", 21);
    v.push_back(s2);
    Student * s3 = new Student("Alice", 29);
    v.push_back(s3);
    Student * s4 = new Student("Jane", 25);
    v.push_back(s4);
    Student * s5 = new Student("Lauren", 23);
    v.push_back(s5);
    Sum s = std::for_each(v.begin(), v.end(), Sum()); 
    float avgAge = s.sum/v.size();
    it = std::find_if(v.begin(), v.end(), Old);
    std::cout<<"The average age of the students is: "<<avgAge<<std::endl;
    if (it == v.end()) {
    std::cout<<"There is no person older than 30.\n";
    }  
    else {
    std::cout<<"The first 30+ year old we found in this list is "<<(*it)->name<<std::endl;
    }
}
 
