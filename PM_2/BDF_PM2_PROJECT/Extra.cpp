/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Project #1
Extra Credit
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <random>

//----------------------------------------------------------------

class customer{
public:
  int departureTime;
  int waitTime;
  int arrivalTime;
  int transactionTime;
  customer(int A, int T){
    arrivalTime = A;
    transactionTime = T;
  }
};
int currentTime = 0;
bool tellerAvailable = true;
std::queue<customer> bankQueue;
std::vector<customer> finished;
std::vector<customer> atTeller;
int numCustomers;
bool arrivalsDone = false;

//----------------------------------------------------------------

int checkTeller(int numTellers){
  std::cout<<"There are now "<<atTeller.size()<<" customers at the Teller\n";
  if(atTeller.size()==0){
    return numTellers;
  }
  int empty = numTellers-atTeller.size();
  int free = 0;
  int i=0;
  while(i<atTeller.size()){
    customer temp = atTeller[i];
    if(currentTime==temp.departureTime){
      atTeller.erase(atTeller.begin()+i);
      std::cout<<"Customer has LEFT the Teller\n";
      temp.waitTime = currentTime-temp.arrivalTime-temp.transactionTime;
      finished.push_back(temp);
      numCustomers--;
      free++;
    }
    else{
      i++;
    }
  }
  return i+empty;
}
//----------------------------------------------------------------

int fromLine(int free_Tellers){
  std::cout<<"There are now "<<bankQueue.size()<<" customers in line\n";
  int lineSize = bankQueue.size();
  if(lineSize==0){
    return 0;
  }
  if(free_Tellers==0){
    return 0;
  }
  int moved = 0;
  int to_move = lineSize;
  if(free_Tellers<lineSize){
    to_move = free_Tellers;
  }
  
  if(free_Tellers>0 and lineSize!=0){
    for(int i=0; i<to_move; i++){
      std::cout<<"Customer is moving from the line to the bank Teller\n";
      customer temp = bankQueue.front();
      temp.departureTime = currentTime+temp.transactionTime;
      atTeller.push_back(temp);
      bankQueue.pop();
      moved++;
    }
  }
  return moved;
}

//----------------------------------------------------------------

bool isArrive(std::queue<customer> &arrivals){
  if(arrivals.size()==0){
    return false;  //False is there are no customers left
  }
  customer temp = arrivals.front();
  if(temp.arrivalTime==currentTime){
    return true;   //True if there is a customer arriving
  }
  return false;    //False if there is no one coming at that time
}

//----------------------------------------------------------------

bool arriveHandler(std::queue<customer> &arrivals, int free_Tellers, int fromLine, bool arrival){
  if(arrival==false){
    return false;
  }
  customer temp = arrivals.front();
  int tellers_Left = free_Tellers - fromLine;
  if(tellers_Left==0){
    std::cout<<"Customer arriving is going to end of line\n";
    arrivals.pop();
    bankQueue.push(temp);
    return false;
  }
  std::cout<<"Customer arriving is going straight to Bank Teller\n";
  arrivals.pop();
  temp.departureTime = currentTime + temp.transactionTime;
  atTeller.push_back(temp);
  return true;
}
    
//----------------------------------------------------------------

void simulation(std::queue<customer> &arrivals, int numTellers){
  std::cout<<"----------------------------------------------------------\n";
  std::cout<<"Current Time: "<<currentTime<<"\n";
  numCustomers = arrivals.size();
  customer temp = arrivals.front();
  currentTime = temp.arrivalTime;
  std::cout<<"----------------------------------------------------------\n";
  std::cout<<"Current Time: "<<currentTime<<"\n";
  std::cout<<"Customer has ARRIVED, moving to bank Teller\n";
  temp.departureTime = currentTime + temp.transactionTime;
  atTeller.push_back(temp);
  arrivals.pop();
  int running = 1;
  while(numCustomers!=0){
    std::cout<<"----------------------------------------------------------\n";
    currentTime++;
    std::cout<<"Current Time: "<<currentTime<<"\n";
    int free_Tellers = checkTeller(numTellers);
    int Line = fromLine(free_Tellers);
    bool arrive = isArrive(arrivals);
    bool end = arriveHandler(arrivals, free_Tellers, Line, arrive);
  }
  std::cout<<"----------------------------------------------------------\n";
}

//----------------------------------------------------------------

int main(){
  int num_cust = 100;
  std::cout<<"\nCenter of Poisson-Distributed Arrival Times: ";
  float pCenter;
  std::cin>>pCenter;
  std::cout<<"Center of Exponential-Distributed Transaction Times: ";
  float tCenter;
  std::cin>>tCenter;
  std::vector<int> arrivalTimes;
  std::vector<int> transactionTimes;
  std::queue<customer> arrival;
  std::default_random_engine generator;
  std::exponential_distribution<double> exponential(tCenter);
  std::poisson_distribution<int> poisson(pCenter);

  for(int i=0; i<num_cust; i++){
    double number = exponential(generator);
    number++;
    number = number*10;
    number = round(number);
    int temp = number;
    transactionTimes.push_back(temp);
  }
  arrivalTimes.push_back(1);
  for(int i=0; i<num_cust-1; i++){
    int last = arrivalTimes[i];
    int add = poisson(generator);
    add++;
    int next = last+add;
    arrivalTimes.push_back(next);
  }
  for(int i=1; i<=num_cust; i++){
    int j = arrivalTimes[i];
    int k = transactionTimes[i];
    customer temp(j,k);
    arrival.push(temp);
  }
  std::cout<<"Number of bank tellers: ";
  int number_of_tellers;
  std::cin>>number_of_tellers;
  simulation(arrival, number_of_tellers);
  std::cout<<"----------------------------------------------------------\n";
  std::cout<<"\n-----------------Simulation is Complete-------------------\n";
  std::cout<<"--------------------------Results-------------------------\n";
  int total_size = finished.size();
  int total_wait=0;
  for(int i=0; i<total_size; i++){
    customer temp = finished[i];
    total_wait = total_wait + temp.waitTime;
  }
  float all_cust = total_size;
  float all_wait = total_wait;
  float average_wait = all_wait/all_cust;
  std::cout<<"\n-----> AVERAGE WAIT TIME: "<<average_wait<<" Time Units\n";
  std::cout<<"-----> NUMBER OF CUSTOMERS: "<<total_size<<"\n";
  std::cout<<"-----> NUMBER OF BANK TELLERS: "<<number_of_tellers<<"\n\n";
  std::cout<<"----------------------------------------------------------\n\n";
}

