/*
Brian Faure
Programming Methodology Lab
Lab #6
February 26&27, 2015
*/


#include <iostream>
#include <vector>
#include <string>


class Time {
public:
	int day;
	int hours;
	int minutes;
	int seconds;
  Time(int d, int h, int m, int s);
  long totseconds() {
    return seconds + 60*minutes + 3600*hours + 86400*day;
  }
};

Time::Time(int d,int h,int m,int s) {
  day=d;
  hours=h;
  minutes=m;
  seconds=s;
}

Time backtootime(long seconds) {
  int d = seconds/86400;
  int h = seconds%86400/3600;
  int m = seconds%3600/60;
  int s = seconds%60;
  if (s<0) {
    m=m-1;
    s=s+60;
  }
  if (m<0) {
    h=h-1;
    m=m+60;
  }
  if (h<0) {
    d=d-1;
    h=h+24;
  }
  return Time(d,h,m,s);
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
	os<<t.day<<"d:"<<t.hours<<"h:"<<t.minutes<<"m:"<<t.seconds<<"s";
	return os;
}

Time operator+(Time a, Time b) {
  return backtootime(a.totseconds()+b.totseconds());
}
Time operator-(Time a, Time b) {
  return backtootime(a.totseconds()-b.totseconds());
}
Time operator*(Time a, Time b) {
  return backtootime(a.totseconds()*b.totseconds());
}
Time operator/(Time a, Time b) {
  return backtootime(a.totseconds()/b.totseconds());
}


int main(){

        int a,b,c,d;
	std::cout<<"**********Enter Values for Time1**********\n";
	std::cout<<"day:";
	std::cin>>a;
	std::cout<<"hours:";
	std::cin>>b;
	std::cout<<"minutes:";
	std::cin>>c;
	std::cout<<"seconds:";
	std::cin>>d;
	std::cout<<'\n';
	Time Time1(a,b,c,d);
	int a1,b1,c1,d1;
	std::cout<<"**********Enter Values for Time2**********\n";
	std::cout<<"day:";
	std::cin>>a1;
	std::cout<<"hours:";
	std::cin>>b1;
	std::cout<<"minutes:";
	std::cin>>c1;
	std::cout<<"seconds:";
	std::cin>>d1;
	std::cout<<'\n';
	Time Time2(a1,b1,c1,d1);
	


	
	std::cout<<Time1<<" + "<<Time2<<" = "<<Time1+Time2<<'\n';
	std::cout<<Time1<<" - "<<Time2<<" = "<<Time1-Time2<<'\n';
	std::cout<<Time1<<" * "<<Time2<<" = "<<Time1*Time2<<'\n';
	std::cout<<Time1<<" / "<<Time2<<" = "<<Time1/Time2<<'\n';
	
	
	
	
	
}
