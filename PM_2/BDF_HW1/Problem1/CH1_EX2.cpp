/*
Brian Faure
RUID:150003563
NetID:bdf39
Problem #1 Exercise #2
Chapter 1
Exercise 2
*/

/*
a.)
Purpose...
   Create a class member function for the "Date" class which will increment the stored day
by 1 whilst following the rules of the Gregorian calender.

Agruments...
   The months range from 1 to 12, the days range from 1 to 31, the year has no limit to its 
range.  I will most likely also create a function that converts the month integer to it's string
equivalent to make the output more recognizable.

Description...
    If given this task I would first narrow down what would change in the data of the
"date" class if the day was progressed by 1.  If the day previously stored in the instance
of the class was the last day in the month, then the month would be incremented by one and
the day would be reset back to one.  If the day stored in the instance of the class was
the last day of the year then the year would be incremented by one and both the month and the
day would be reset back to one.  By following this logic, the class member function would
consist of several "if" statements which filter out the months by their number of days, then
apply the logic to see if the day is at the end of the month etc. 
    Another way to do it which might be faster would be to figure out which month has the 
least number of days, February with 28, then have a base "if" statement which first tests to 
see if the day is less than 28. If it is indeed less than 28, the function can just add 1 to
the day and be done with it.  If the number is greater than or equal to 28, the function
would branch off into the 2 or 3 if statements explained in the last paragraph.

b.)
*/
#include<iostream>
#include <string>

class Date{ //Creating generic Date class
public:
  int day=4;
  int month=7;
  int year=1776;
  void Advance(); //Creating Advance member class
};

std::string Int_to_Month(int month){
  std::string smonth;  //Function to transform output to english
  if(month==1){
    smonth="January";
  }
  if(month==2){
    smonth="February";
  }
  if(month==3){
    smonth="March";
  }
  if(month==4){
    smonth="April";
  }
  if(month==5){
    smonth="May";
  }
  if(month==6){
    smonth="June";
  }
  if(month==7){
    smonth="July";
  }
  if(month==8){
    smonth="August";
  }
  if(month==9){
    smonth="September";
  }
  if(month==10){
    smonth="October";
  }
  if(month==11){
    smonth="November";
  }
  if(month==12){
    smonth="December";
  }
  return smonth;
}
    
void Date::Advance(){
  std::cout<<"\nCurrent day is...\n"; //First output current day
  std::string current_month = Int_to_Month(month); //Use function to transform output
  std::cout<<current_month<<" "<<day<<", "<<year<<"\n";
  if((month==1||month==3||month==5||month==7||month==8||month==10) and day==31){
    day=1;
    month++;
  }   //Go through if statements to filter out different required results
  else{
    if((month==4||month==6||month==9||month==11) and day==30){
      day=1;
      month++;
    }
    else{
      if(month==2 and day==28){
	day=1;
	month++;
      }
      else{
	if(month==12 and day==31){
	  day=1;
	  month=1;
	  year++;
	}
	else{
	  day++;
	}
      }
    }
  }
  std::cout<<"New day is...\n";
  std::string new_month = Int_to_Month(month);  //Output new date incremented by one day
  std::cout<<new_month<<" "<<day<<", "<<year<<"\n\n";
}
//To check results...
/*
int main(){
  Date test;
  for(int i =0; i<365; i++){
    
  test.Advance();
  }
}
*/
