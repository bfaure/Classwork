% Brian Faure
% Week Eleven Recitation
%% Problem One
% Part A
ti=[250 260 270 280 290 300 310 320 330 340 350];
p1=[260 504 1184 2910 3913 9462 18841 16952 41529 86903 77537];
plot(ti,p1)

log(P)=A-(B/(C+T));
A=1;
B=1000;
C=-1;
nlinfit(T,P,A-(B/(C+T)),beta0)
%% Part B
ti=[250 260 270 280 290 300 310 320 330 340 350];
p1=[260 504 1184 2910 3913 9462 18841 16952 41529 86903 77537];
first=polyfit(ti,p1,1)
second=polyfit(ti,p1,2)
x=250:350;
y=260:77537;
t2=polyval(first,x);
p2=polyval(second,y);
plot(x,y,'b',x,t2,'r',x,p2,'g')

%% Problem Two
% Part B
xi=[1,1.4,1.9,2.1,2.7,3.0,3.3,3.9,4.2];
yi=[0.18,0.21,0.21,0.2,0.2,0.19,0.18,0.16,0.16];
plot(xi,yi,'o')
p=polyfit(xi,yi,3);
hold on
x=1:0.1:4.2;
y=0.0070*x.^3 - 0.0655*x.^2 + 0.1741*x + 0.0677;
plot(x,y,'r')
legend('Actual Values','Third Power')
xlabel('x')
ylabel('y')
hold off
clear all
% Part C
nlinfit(xi,yi,(1)/((a/x)+b*xi),beta0)







