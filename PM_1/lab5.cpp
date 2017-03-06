/*
Brian Faure
Lab 5 
Programming Methodology Lab
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Person{
public:
  std::string name;
  int age;
  int height;
};

int main() {
  std::string name;
  int age;
  int height;
  std::vector<Person> people;
  Person access;
  while(std::cin>>name>>age>>height) {
    access.name = name;
    access.age = age;
    access.height = height;
    people.push_back(access);
  }
  int min;
  int j,i;
  for(j=0; j<people.size()-1; j++) {
    min=j;
    for(i = (j+1);i<people.size();i++) {
      if(people[i].height<people[min].height) {
        min=i;
      } 
    }
    if(min!=j) {
      std::swap(people[j],people[min]);
    }
  }
  int j1,i1,k1;
  for(j1=0; j1<people.size()-1;j1++) {
    k1=j1+1;
    for(i1 = (j1+1); i1<people.size();i1++) {
      if(people[i1].name==people[j1].name) {
	std::swap(people[k1],people[i1]);
	k1=k1+1;
      }
    }
  }
  int min5;
  for(int x=0; x<people.size()-1; x++) {
    if(people[x].name==people[x+1].name) {
      if(people[x+1].age<people[x].age) {
	std::swap(people[x],people[x+1]);
      }
    }
  }      
  for(int k=0; k<people.size(); k++) {
    std::cout<<people[k].name;
    std::cout<<", ";
    std::cout<<people[k].age;
    std::cout<<", ";
    std::cout<<people[k].height;
    std::cout<<" ";
    std::cout<<"inches\n";
  }
}

      


