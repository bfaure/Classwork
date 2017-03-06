%%
% Recitation Problem Number One
% Practice Exercise 5.1
% #1
x = linspace(0,2*pi,20);
y = sin(x);
plot(x,y)
% #2
title('Graph of sin(x) from 0,2pi')
xlabel('x axis')
ylabel('y axis')
%%
% #3
x = linspace(0,2*pi,20);
y1 = sin(x);
y2 = cos(x);
plot(x,y1,x,y2)
title('Graphs of sin(x) and cos(x)')
xlabel('x axis')
ylabel('y axis')
%%
% #4
x = linspace(0,2*pi,20);
y1 = sin(x);
y2 = cos(x);
plot(x,y1,'r--',x,y2,'g:')
title('Graphs of sin(x) and cos(x)')
xlabel('x axis')
ylabel('y axis')
% #5
legend('sin(x)','cos(x)')
% #6
axis([-1,2*pi + 1,-1.5,1.5])
%%
% #7
x = 0:0.1*pi:2*pi;
a = cos(x);
plot(a)
% This form of plotting uses all the values we specified from 0 to 2pi
%% Practice Exercise 5.2
% #1
subplot(2,1,1)
% #2
x = -1.5:0.1:1.5;
y = tan(x);
plot(x,y)
% #3
title('Graph of tan(x)')
xlabel('x axis')
ylabel('y axis')
% #4
subplot(2,1,2)
y2 = sinh(x);
plot(x,y2)
% #5
title('Graph of sinh(x)')
xlabel('x axis')
ylabel('y axis')
%% #6
subplot(1,2,1)
% #2
x = -1.5:0.1:1.5;
y = tan(x);
plot(x,y)
% #3
title('Graph of tan(x)')
xlabel('x axis')
ylabel('y axis')
% #4
subplot(1,2,2)
y2 = sinh(x);
plot(x,y2)
% #5
title('Graph of sinh(x)')
xlabel('x axis')
ylabel('y axis')
%% Practice Exercise 5.4
% #1
% Rectangular
subplot(4,1,1)
x = linspace(0,100,100);
y = 5*x + 3;
plot(x,y)
title('rectangular')
% Semilogx
subplot(4,1,2)
semilogx(x,y)
title('Semilogx')
% Semilogy
subplot(4,1,3)
semilogy(x,y)
title('Semilogy')
% Loglog
subplot(4,1,4)
loglog(x,y)
title('Loglog')
% For number 1 loglog and rectangular return straight lines
%%
% #2
subplot(4,1,1)
x = linspace(0,100,100);
y = 3*(x.^2);
plot(x,y)
title('rectangular')
% Semilogx
subplot(4,1,2)
semilogx(x,y)
title('Semilogx')
% Semilogy
subplot(4,1,3)
semilogy(x,y)
title('Semilogy')
% Loglog
subplot(4,1,4)
loglog(x,y)
title('Loglog')
% For number 2, loglog returns a straight line
%%
% #3
subplot(4,1,1)
x = linspace(0,100,100);
y = 12 * (exp(x + 2));
plot(x,y)
title('rectangular')
% Semilogx
subplot(4,1,2)
semilogx(x,y)
title('Semilogx')
% Semilogy
subplot(4,1,3)
semilogy(x,y)
title('Semilogy')
% Loglog
subplot(4,1,4)
loglog(x,y)
title('Loglog')
% For number 3, semilogy returns a straight line
%%
% #4
subplot(4,1,1)
x = linspace(0,100,100);
y = x.^-1;
plot(x,y)
title('rectangular')
% Semilogx
subplot(4,1,2)
semilogx(x,y)
title('Semilogx')
% Semilogy
subplot(4,1,3)
semilogy(x,y)
title('Semilogy')
% Loglog
subplot(4,1,4)
loglog(x,y)
title('Loglog')
% For number 4, loglog returns a straight line
%% Practice Exercise 5.5 (Using fplot)
% #1
subplot(4,1,1)
fplot('5*t.^2',[-10,10])
title('Prac Exercise 5.5 #1')
xlabel('X Axis')
ylabel('Y Axis')
% #2
subplot(4,1,2)
fplot('5.*(sin(t).^2) + (t.*(cos(t)).^2)',[-2*pi,2*pi])
title('Practice Exercise 5.5 #2')
xlabel('X Axis')
ylabel('Y Axis')
% #3
subplot(4,1,3)
fplot('t.*exp(t)',[0,1])
title('Practice Exercsie 5.5 #3')
xlabel('X Axis')
ylabel('Y Axis')
% #4
subplot(4,1,4)
fplot('log(t) + sin(t)',[-5,5])
title('Practice Exercise 5.5 #4')
xlabel('X Axis')
ylabel('Y Axis')
%% Practice Exercise 5.5 (using plot rather than fplot)
% #1
t1 = 0:1:20;
f1 = 5*t1.^2;
plot(t1,f1)
title('Graph of 5t1^2')
xlabel('X Axis')
ylabel('Y Axis')
%% #2
t = 0:400;
f2 = (5.*(sin(t)).^2)+(t.*(cos(t)).^2);
plot(t,f2)
title('Graph of 5*(sin(t2).^2) + t2*(cos(t2).^2)')
xlabel('X Axis')
ylabel('Y Axis')
%% #3
t = 600:800;
f3 = t.*(exp(t));
plot(t,f3)
title('Graph of t.*e^t')
xlabel('X Axis')
ylabel('Y Axis')
%% #4
t = -400:400;
f4 = log(t) + sin(t);
plot(t,f4)
title('Graph of ln(t) + sin(t)')
xlabel('X Axis')
ylabel('Y Axis')
%%
% Recitation Problem Number Two
% Figure 5.27
x = linspace(0,12*pi,768);
y = cos(x);
z = sin(x);
subplot(2,1,1)
plot3(x,y,z)
title('Graph Prob #2')
xlabel('Zero to 12pi')
ylabel('cosx')
zlabel('sinx')
subplot(2,1,2)
comet3(x,y,z)
%% Figure 5.30
x = [-2:0.2:2];
y = [-2:0.2:2];
[X,Y] = meshgrid(x,y);
Z = X.*exp(-X.^2 - Y.^2);
subplot(2,2,1)
mesh(X,Y,Z)
title('Mesh Plot'), xlabel('X Axis'), ylabel('Y Axis'), xlabel('Z Axis')
subplot(2,2,2)
surf(X,Y,Z)
title('Surface Plot'), xlabel('X Axis'), ylabel('Y Axis'), 
zlabel('Z Axis')
subplot(2,2,3)
contour(X,Y,Z)
title('Contour Plot'), xlabel('X Axis'), ylabel('Y Axis'),
zlabel('Z Axis')
subplot(2,2,4)
surfc(X,Y,Z)
title('Combination of Surface and Contour'), xlabel('X Axis'),
ylabel('Y Axis'), zlabel('Z Axis')
%% Figure 5.31
[x,y,z] = peaks;
subplot(2,2,1)
pcolor(x,y,z)
title('Psuedo Color Plot')
subplot(2,2,2)
pcolor(x,y,z)
shading interp
title('Interpolated Shading')
subplot(2,2,3)
pcolor(x,y,z)
shading interp
hold on 
contour(x,y,z,20,'k')
title('Overlaid Psuedo Color and Contour')
subplot(2,2,4)
contour(x,y,z)
title('Contour Plot')
%% 
% Recitation Problem Number Three
x = linspace(0.988,1.012,241);
y1 = x.^7 - (7*x.^6) + (21*x.^5) - (35*x.^4) + (35*x.^3) - (21*x.^2) + 7*x - 1;
y2 = (x - 1).^7;
plot(x,y1,'-c')
hold on
plot(x,y2,'--k')
title('Floating-Point Errors'), xlabel('X Axis'), ylabel('Y Axis')
legend('y1','y2')
%%
% Recitation Problem Number Four
x = [1971 1972 1974 1979 1982 1985 1989 1993 1996 1997 1997 1999 1999 1999 2000 2003 2003 2003 2004 2006 2006 2006 2006 2007 2006 2008 2010 2011];
y1 = [2300 2500 4500 29000 134000 275000 1200000 3100000 4300000 7500000 8800000 9500000 21300000 22000000 42000000 54300000 105900000 220000000 592000000 241000000 291000000 582000000 681000000 789000000 1700000000 2000000000 2300000000 2600000000];
semilogy(x,y1,'or')
title('Transistor Count - Moore''s Law')
xlabel('year')
grid on
ylabel('count')
hold on
y2 = 2300*(4.^((x - 1971)./4));
semilogy(x,y2,'-b')
legend('data','predicted')
%%
% Recitation Problem Number Four
x = [1:12];
y = [2345 2343; 4363 5766; 3212 4534; 4565 4719; 8776 3422; 7679 2200; 6532 3454; 2376 7865; 2238 6543; 4509 4508; 5643 2312; 1137 4566];
bar(x,y)
title('screw inventory')
xlabel('month')
ylabel('number of screws')
legend('2009','2010')



