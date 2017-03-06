function [ S ] = fsum( N,m )
if m==5 % analytical formula
    
 S=(1/2)*N*(N+1);

elseif m==1
    for n=1:N;
    a(n)=(1/2).*n.*(1+n);
    end
    S=a(N);
elseif m==2 %conventional while loop
    n=0;
    while n<N
    n=n+1;
    S=(1/2).*n.*(n+1);
    end
elseif m==3 %forever while loop
    n=0;
    while 1
         if n==N
             break
         end
    n=n+1;
    S=(1/2).*n.*(n+1);
    end
else  %vectorized sum
    n=0:(N+1);
    a=(1/2).*n.*(1+n);
    S=a(N+1);
end