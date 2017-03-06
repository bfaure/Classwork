%% Week 8 Recitation
% Brian Faure 
%% Problem 1
% Part A
% For - Loop
for n=1:100;
a(n)=(1/2).*n.*(1+n);
end
sum_For_Loop = a(100)
% While - Loop
clear all
n=0;
while n<100
    n=n+1;
    s(n)=(1/2).*n.*(n+1);
end;
sum_while_loop = s(100)
% Forever While - Loop
clear all
n=0;
while 1
    if n==100
        break
    end
    n=n+1;
    s(n)=(1/2).*n.*(n+1);
end;
sum_forever_while_loop = s(100)
% Vectorized Sum
n=0:101; 
a=(1/2).*n.*(1+n);
vectorized_sum = a(101)
% Analytical Formula
N=100;
s=(1/2)*N*(N+1);
analytical_sum = s
%% Problem 1 Part B (function file)
%% Problem 1 Part C
% using forever-while loop
N=0;
S=0;
while 1
    if S>10^5
        break
    end
N=N+1;
S=fsum(N,5);
end
forever_while = N
% using conventional-while loop
clear all
N=0;
S=0;
while S<=10^5;
    N = N+1;
    S = fsum(N,5);
end
conventional_while = N
%% Problem 2
% Part A
tol=10^(-10);
x(1)=1;
k=1;
while 1
    x=@(k) exp(-1*(k));
    if abs(x(k+1) - x(k))<tol
        break
    end
    k = k+1
end
k=[0:23];
plot(k,abs(x(k+1)-x(k)))
clear all
% Part B
k=0;
while k<22
    x=@(k) exp(-1*(k));
    abs(x(k+1) - x(k))
    k = k+1;
end
% Part C
clear all
f=@(x) x-exp(-x);
fzero(f,[0 23])
% Part D
clear all
x=[0:02:2]
y=x;
y1=exp(-x);
plot(x,y)
hold on
plot(x,y1)
%% Problem 3
% Part A
f=@(k) (k^2)/(2^k);
fplot(@(k)f(k),[1 50 0 1.2])
ylabel('f(k)')
xlabel('k')

% using fzero
%%
% Part B
clear all
S(1)=0.5;
k=2;
while 1
    S=@(k) S(k-1) + (k.^2)/(2.^k);
    tol = (k.^2)/(2.^k);
    if abs(S(k) - S(k-1))<=tol
        break
    end
    k = k+1
end
   
%Part C
clear all
s(1)=0.5;
k=2;
while abs(s(k)-s(k-1))<=tol
    tol = (k.^2)/(2.^k);
    S=@(k) S(k-1) + (k.^2)/(2.^k);
    k = k+1
end

    





