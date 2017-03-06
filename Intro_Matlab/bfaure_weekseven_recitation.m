% Brian Faure Recitation Problems Week 7
%% Problem 1.
% Part A
A = [1 5 50 30; 10 8 40 20; 40 80 9 8; 6 20 10 9];
B = [1 4 7; 2 10 20; 3 15 30];
C = [10 25 5 35];
A2 = A>20 %returns 1 or 0 values 
A3 = find(A>20) %Position in matrix (reads down the columns)
B2 = B>20
B3 = find(B>20)
C2 = C>20
C3 = find(C>20)
%% Part B
A = [1 5 50 30; 10 8 40 20; 40 80 9 8; 6 20 10 9];
B = [1 4 7; 2 10 20; 3 15 30];
C = [10 25 5 35];
A(A>20) = 200
B(B>20) = 200
C(C>20) = 200
%% Part C
A = [1 5 50 30; 10 8 40 20; 40 80 9 8; 6 20 10 9];
B = [1 4 7; 2 10 20; 3 15 30];
C = [10 25 5 35];
A1 = A>10
A2 = A<30
A3 = A1 & A2
A4 = find(A3)
C1 = C>10
C2 = C<30
C3 = C1 & C2
C4 = find(C3)
B1 = B>10
B2 = B<30
B3 = B1 & B2
B4 = find(B3)
%% Part D
A = [1 5 50 30; 10 8 40 20; 40 80 9 8; 6 20 10 9];
B = [1 4 7; 2 10 20; 3 15 30];
C = [10 25 5 35];
a1 = A>0;
a2 = A<10;
a3 = a1 & a2;
a4 = A>70;
a5 = A<80;
a6 = a4 & a5;
a7 = a3 | a6;
a8 = find(a7);
a9 = length(a8) % This returns the number of values in Matrix A that 
%fit the requirements
b1 = B>0;
b2 = B<10;
b3 = b1 & b2;
b4 = B>70;
b5 = B<80;
b6 = b4 & b5;
b7 = b3 | b6;
b8 = find(b7);
b9 = length(b8)
c1 = C>0;
c2 = C<10;
c3 = C1 & C2;
c4 = C>70;
c5 = C<80;
c6 = c4 & c5;
c7 = c3 | c6;
c8 = find(c7);
c9 = length(c8)
%% Problem 2 (Problem 8.1 in text)
% Part A
too_hot = tub>105;
too_hot1 = find(too_hot)
% Part B
too_hot2 = length(too_hot1) 
% Part C
times = too_hot1 - 26 % this returns the different times throughout the 
%day wherein the temperature was above 105
% Part D
too_cold = tub<102;
too_cold1 = tub>24;
too_cold2 = too_cold & too_cold1;
too_cold3 = find(too_cold2);
too_cold4 = length(too_cold3) 
% too_cold4 returns the number of times throughout the day; the temperature
% is below 102
% Part E
times2 = too_cold3 - 26
%times2 will return the times in the day when the temperature is below 102
% Part F
perfect = tub>=102;
perfect1 = tub<=105;
perfect3 = perfect & perfect1;
perfect4 = find(perfect3);
perfect5 = perfect4 - 26
%perfect 5 is the answer (returns times when the temperature fits the
%requirements)
% Part G
temps = tub(:,2);
[hottest_temp,time] = max(temps)
% This will return the hottest temperature along with the time it occurs
%% Problem 3 
% Part A
% (The functions)
% Part B
t = 0:0.01:70;
i = hfun(t);
j = find(i==0);
rocket_grounded = j(:,2)
% Part C
top = max(i)
top_time = find(i==top)
% Part F
vel = vfun(t);
max_vel = max(vel)
max_vel_time = find(vel==max_vel)
% Part G
subplot(2,1,1)
plot(t,hfun(t))
xlabel('time (sec)')
ylabel('height (m)')
title('Height Profile of a Rocket')
hold on 
plot(40.51,1470.2,'or')
hold on
plot(63.03,0,'ok')
hold on
plot(21.04,753.8099,'og')
subplot(2,1,2)
plot(t,vfun(t))
xlabel('time (sec)')
ylabel('v (m/sec)')
title('Velocity Profile of a Rocket')
hold on
plot(63.03,-124.9728,'ok')
hold on
plot(40.51,0,'or')
hold on
plot(21.04,56.0230,'og')













