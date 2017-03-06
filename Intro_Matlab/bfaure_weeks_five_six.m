% Brian Faure Weeks 5/6 Recitation Problems

%% Problem #1 with a=0.5 b=2 and c=3
f =@(x,a,b,c) exp(-a.*x)*cos(b.*x)+cos(c.*x);
a=.5; b=2; c=3;
g=@(x) f(x,a,b,c);
fplot(g,[0,4])
hold on
xlabel('x');, axis([0 4 -1.5 2]);
title('Problem 1 (part 1)')
grid on
[xmin1,ymin1]=fminbnd(g, 0, 2);
[xmin2,ymin2]=fminbnd(g, 2, 4);
plot(xmin1,ymin1, 'ro', xmin2,ymin2, 'ro');
xz1=fzero(g,1);
xz2=fzero(g,2);
xz3=fzero(g,3);
plot(xz1,0, 'go', xz2,0,'go', xz3,0,'go')
[xmax1,fmax1]=fminbnd(@(x) -g(x),0,2);
[xmax2,fmax2]=fminbnd(@(x) -g(x),2,4);
plot(xmax1,-fmax1, 'ro', xmax2,-fmax2, 'ro');
hold off

%% Problem #1 with a=1 b=4 and c=2
f =@(x,a,b,c) exp(-a.*x)*cos(b.*x)+cos(c.*x);
a=1; b=4; c=2;
g=@(x) f(x,a,b,c);
fplot(g,[0,4])
hold on
xlabel('x');, axis([0 4 -1.5 2]);
title('Problem 1 (part 2)')
grid on
[xmin1,ymin1]=fminbnd(g, 0, 4);
plot(xmin1,ymin1, 'ro');
xz1=fzero(g,1);
xz2=fzero(g,2);
plot(xz1,0, 'go', xz2,0,'go')
[xmax1,fmax1]=fminbnd(@(x) -g(x),0,2);
[xmax2,fmax2]=fminbnd(@(x) -g(x),2,4);
plot(xmax1,-fmax1, 'ro', xmax2,-fmax2, 'ro');
hold off
%% Problem #2
t=linspace(0,30,30000);
f=height(t);
plot(t,f), title('Rocket Trajectory'), xlabel('time [sec]'), ylabel('altitude [m]')
hold on
axis([0 35 0 1500])
ht=@(t) -4.9.*t.^2 + 125.*t + 500;
ground=fzero(ht,20);
plot(ground,0,'.r')
[fmax,imax]=max(f);
xmax=t(imax);
plot(xmax,fmax,'go')
legend('height','ground','max','Location','NE')
hold off

%% Problem #3
%% Part A
fclose('all');
fid = fopen('rec0506.dat');
fgetl(fid); 
fgetl(fid);
table = fscanf(fid,'%f %*s %f %*s %f')
table = reshape(table,4,3)
x = table(:,1)
y = table(:,2)
z = table(:,3)
%% Part B
fclose('all');
part_b = fopen('rec0506.dat');
fgetl(part_b);
fgetl(part_b);
C = textscan(part_b,'%f %s %f %s %f')
X = C{1}
Y = C{3}
B = C{4}
A = C{2}
Z = C{5}
% Part C
Y_Ascend = sort(Y,'ascend')
% I don't know what it means in the instructions when it refers
% to sorting the other colums (X,A,B, and Z) based on the sorting 
% index of Y.  I have successfully sorted y in ascending order so I will
% reconstruct the table using that column value
fclose('all');
part_c = fopen('rec0506.dat');
fgetl(part_c);
fgetl(part_c);
fprintf(' A      X      Y       Z      B\n')
fprintf('---------------------------------\n')
fprintf('%s %6.3f %6.5f %6.2f %s\n',A,X,Y_Ascend,Z,B)
% This final fprintf function returns an error because I am 
% inputing a cell apparently





