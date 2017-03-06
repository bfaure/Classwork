/* 
Brian Faure
Programming Methodology Lab
Lab 7
*/




#include <iostream>
#include <string>
#include <vector>

class Animal{
public:
  Animal(){}
  virtual float get_normalized_age(){
    return 0;
  }
  std::string species;
  std::string noise;
  virtual ~Animal(){}
protected:
  float base_age;
  
};

class Human: public Animal{

public:
  Human(float a){
    base_age = a;
    species = "Human";
    noise = "My name is Luis. I'm the Best";
  }
  float get_normalized_age(){
    return base_age;
  }
  ~Human(){}
					 
};

class Cow: public Animal{
public:
  Cow(float a){
    base_age = a;
    species = "Cow";
    noise = "Moo!";
  }
  float get_normalized_age(){
    return (base_age*3.64);
  }
  ~Cow(){}
};

class Cat: public Animal{
public:
  Cat(){}
  Cat(float a){
    base_age=a;
    species="Cat";
    noise="Meow";
  }
  float get_normalized_age(){
    return (base_age*3.2);
  }
  ~Cat(){}
};

class Bird: public Animal{
public:
  Bird(){}
  Bird(float a){
    base_age=a;
    species="Bird";
    noise="Chirp!";
  }
  float get_normalized_age(){
    return (base_age*5.33);
  }
  ~Bird(){}
};

class Lion: public Cat{
public:
  Lion(float a){
    base_age=a;
    species="Lion";
    noise="Roar!";
  }
  ~Lion(){}
};

class Chicken: public Bird{
public:
  Chicken(float a){
    base_age=a;
    species="Chicken";
    noise="Cluck!";
  }
  ~Chicken(){}
};


int main(){
  std::vector<Animal*> animals;
  float base_age = 24;
  animals.push_back(new Human(base_age));
  animals.push_back(new Cow(base_age));
  animals.push_back(new Cat(base_age));
  animals.push_back(new Bird(base_age));
  animals.push_back(new Lion(base_age));
  animals.push_back(new Chicken(base_age));
  for(Animal* a : animals){
      std::cout<<"*****************************************"<<std::endl;
      std::cout << "Species: "<< a->species<<std::endl;
      std::cout << "Normalized Age (base age="<<base_age<<") :  "<<a->get_normalized_age()<<std::endl;
      std::cout << "Animal Noise/Song/Call: "<<a->noise<<std::endl;
      std::cout<<"*****************************************"<<std::endl;
  }
  for(Animal* a: animals){
    delete a;
  }
  return 0;

}
