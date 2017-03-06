%% Brian Faure
% Recitation Problem One
% Part A
% Part A
n=1; 
v(n) = 0; 
T=0.001; 
C=0.004; 
A=20; 
while v(n)<=60 
    v(n+1) = (((A) - C*(v(n)^2))*(0.001)) + v(n); 
    n=n+1;
    v(n)=[v(n)];   %save as array
end
disp(v(n)) % max velocity
disp(0.001*n)  %time t60
t60=0:0.001:0.001*(n-1);
plot(t60,v)
hold on
xlabel('t (sec)'), ylabel('v (mph)')
axis([0 15 0 80])
hold off
%% Part B
clear all
n=1;
T=0.001;
v(n)=60;
A=-4;
C=0.004;
while v(n) > 0
    v(n+1) = (((A) - C*(v(n)^2))*(0.001)) + v(n); 
    n=n+1;
    v(n)=[v(n)];  % saves this as array 
end
disp(v(n))  % shows the smallest velocity 
disp(0.001*n) %time frame
t2=0:0.001:0.001*(n-1);
plot(t2,v)
%% Problem Two
a=[2 -1 2; 1 2 2; 0 -1 4];
b=[-9;2;-7];
% Part A
x=a\b

% Part B
I = eye(size(a));        
D = diag(diag(a));       

B = I - D\a;                  
c = D\b;                 

tol=1e-10;   
x=[1 2 3]';
k=1;   
X=x;         

while 1
   xnew = B*x + c;
   if norm(xnew-x) < tol    
      break;               
   end                    
   x = xnew;
   k = k+1;
   X = [X,x];       
end

k
x
norm(a*x-b) 

K=1:k;
plot(K,X')
axis([0 90 -4 5])
xlabel('iteration index, k')
legend('x1=-2','x2=3','x3=-1','location','e')

% Part C
p=max(abs(eig(B)))
%p is less then 1