/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Project #1
Problem #3
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

/*
I first create a class named 'customer' to hold all
of the details we will need to keep pertaining to 
each customer who visits the bank. These include their
departure time from bank (departureTime), their total
elapsed time in the bank (waitTime), the time they arrive 
at the bank (arrivalTime), and finally how long it will take 
for their transaction to complete once they gain access to
one of the bank tellers (transactionTime).

All of these customer objects will be put together
into a queue later to be input into the simulator.

Before the simulator is run, the customer objects are
loaded with arrivalTime and transactionTime. Once 
the customer has gotten to the teller, the departureTime
is calculated.  Once the customer is able to leave the 
bank, the waitTime is calculated
*/
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
/*
The checkTeller function below serves multiple purposes.
It is the first function called on every iteration of the
while loop inside the main simulation function.

It goes through the vector that holds the customers 
currently being helped by the teller(s) (atTeller) and checks
to see if any of the customers departureTimes coincide with
the currentTime value.  If so that customer is removed from
the atTeller vector and placed into the finished vector.  If
so the number of remaining customers (numCustomers), is
decremented to signify that one customer has been completed.

Along with the above function, checkTeller also returns a
boolean value coinciding with whether or not there will be
an availability at the teller for another customer to move up.
If there is an opeing, checkTeller returns true and if all of
the tellers are occupied, checkTeller returns false.

This includes the customer who just finished. Thus, if there
are 3 tellers and they are all helping customers, if one of
those customers has is leaving on this exact step of 
currentTime, checkTeller will return true because after that person
is gone, there will be an availability at the checker. 
*/
bool checkTeller(int numTellers){
  std::cout<<"There are now "<<atTeller.size()<<" customers at the Teller\n";
  if(atTeller.size()==0){
    return true;
  }
  int i = 0;
  bool run = true;
  while(run){
    customer temp = atTeller[i];
    if(currentTime==temp.departureTime){
      atTeller.erase(atTeller.begin()+i);
      std::cout<<"Customer has LEFT the Teller\n";
      temp.waitTime = currentTime-temp.arrivalTime-temp.transactionTime;
      finished.push_back(temp);
      numCustomers--;
      return true;
    }
    i++;
    if(i==atTeller.size()){
      if(i<numTellers){
	return true;
      }
      return false;
    }
  }
  return true;
}
/*
The fromLine function below is also called on every iteration
of the main simulation. Its function is...

#1.) Check if there are any customers in the line for the teller:

-->If not, return false.
-->If so, continue in function

#2.) Check if the output of the Teller function above is true
of false. Recall that the Teller function returning true
basically means that there is an availability at the teller to
allow for another customer to move up.

-->If not, return false.
-->If so, move the person at the front of the line up to the open
teller position, ensuring to update the customer object with its
respective departureTime value and return true.
 */
bool fromLine(bool Teller){
  std::cout<<"There are now "<<bankQueue.size()<<" customers in line\n";
  int lineSize = bankQueue.size();
  if(lineSize==0){
    return false;
  }
  if(Teller==true and lineSize!=0){
    std::cout<<"Customer is moving from the line to the bank Teller\n";
    customer temp = bankQueue.front();
    temp.departureTime = currentTime+temp.transactionTime;
    atTeller.push_back(temp);
    bankQueue.pop();
    return true;
  }
  return false;
}
/*
The isArrive function below has a fairly simple job compared
to the other functions in the simulation.  The job of this 
function is to first check if there are any customers who still
have not arrived at the bank.  If all the customers have arrived
the function returns false.  If there are still customers who
need to arrive, the function pulls up the arrivalTime for the
next customer who is coming and checks if that is the same as
the currentTime.  If so, the function returns true, if not
it returns false.
*/
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
/*
The arrive_to_teller function below is used to figure out
if the person currently arriving is going to be able to go
straight to the teller or if they need to head to the back
of the line.  Basically the function checks if there is a
line, if so, obviously the customer is not going to be able
to skip the line so they must head to the back of it. If this
is the case (they need to go to the end of the line), the
function does not do anything.  If the customer IS able to
head straight to the teller, the function pops the customer
off of the arrivals queue and moves them over the the atTeller
vector while calculating their appropriate departure time
based on their arrival time and their transaction time.
*/
void arrive_to_teller(std::queue<customer> &arrivals){
  customer temp = arrivals.front();
  std::cout<<"Customer arriving is going straight to bank Teller\n";
  arrivals.pop();
  temp.departureTime = currentTime + temp.transactionTime;
  atTeller.push_back(temp);
}
/*
The arrive_to_line function is the exact opposite of the
arrive_to_teller function and is only called if it is not
possible for the person who just arrived to go straight to
the teller.  If this is the case, the function places them
at the end of the line.
 */
void arrive_to_line(std::queue<customer> &arrivals){
  customer temp = arrivals.front();
  std::cout<<"Customer arriving is going to end of line\n";
  arrivals.pop();
  bankQueue.push(temp);
}
/*
The simulation function below is basically the function that
handles the entire bank simulation itself.  I tried to keep
most of the comparators and evaluations in the other functions
so that this one would remain relatively simple.

The values passed to this function are the queue of customers
who will be arriving (they have arrival and transaction duration
times already loaded into them) and the number of bank tellers.

Before entering the main while loop, the function goes through
and places the first customer at the bank teller while also loading
in that customers correct departure time and popping that customers
value off of the arrivals queue.

Inside the while loop, the function increments the currentTime
then calls a series of functions, all of which are explained above.
The first function is the checkTeller function which moves a
customer from the teller if they are done there.  The checkTeller
function also returns whether or not there is an opening at the 
teller booth for another customer.

The loop then calls the fromLine function to see if it should
move a customer from the line to the teller.

The loop then calls the isArrive function to see if there is
going to be a customer arriving on this clock tick.

The function then calls the arrive_to_teller and arrive_to_line
functions to move the new customer (if there is one) to either
the teller or back of the line based on whether or not there 
already is a line in front of the teller.

Every time a person departs, the total number of customers 
remaining is decremented by one so the loop and function are
done once the number of customers remaining is zero. At this
point simulation returns true.
 */
bool simulation(std::queue<customer> &arrivals, int numTellers){
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
    bool Teller = checkTeller(numTellers);
    bool Line = fromLine(Teller);
    bool arrive = isArrive(arrivals);
    if(Teller==true and Line==false and arrive==true){
      arrive_to_teller(arrivals);
    }
    else{
      if(arrive==true){
	arrive_to_line(arrivals);
      }
    }
  }
  std::cout<<"----------------------------------------------------------\n";
  return true;
}
/*
The purpose of the main function is to take the specified
number of customers, their arrival times and transaction times
and turn that into a queue of customers.  The main function
also has the responsibility of calling the simulation function
and outputting the results of the simulation.  
 */    
int main(){
  std::cout<<"\nNumber of customers: ";
  int num_cust;
  std::cin>>num_cust;
  std::queue<customer> arrival;
  for(int i=1; i<=num_cust; i++){
    customer temp(i,10);
    arrival.push(temp);
    //temp.print();
  }
  std::cout<<"Number of bank tellers: ";
  int number_of_tellers;
  std::cin>>number_of_tellers;
  bool done = simulation(arrival, number_of_tellers);
  std::cout<<"----------------------------------------------------------\n";
  if(done == true){
    std::cout<<"\n-----------------Simulation is Complete-------------------\n";
    std::cout<<"--------------------------Results-------------------------\n";
  }
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

