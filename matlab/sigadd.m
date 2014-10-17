function [x3,n3]=sigadd

%--List of variables used--
%==>n1,x1,n2,x2,i,n3,x3,n<==

%Get the input of period of first discrete sequence 
n1 = input('\nEnter the period of discrete sequence x1: ');

%Get the value of x1 for different x values
for i=1:n1
    fprintf('\nEnter the value of x1(%g): ',i-1);
   x1(i)=input('');
end

%Get the input of period of second discrete sequence 
n2 = input('\nEnter the period of discrete sequence x2: ');

%Get the value of x2 for different x values
for i=1:n2
    fprintf('\nEnter the value of x2(%g): ',i-1);
   x2(i)=input('');
end

%Compute the addition of the signals
n3=lcm(n1,n2);%this is the period of the resultant signal
for i=1:n3
     x3(i)=x1(mod((i-1),n1)+1)+x2(mod((i-1),n2)+1);
end
 
%Displaying the period of the added signal
fprintf('\nThe period of the added signal(x3) = %g\n\n',n3);
fprintf('Press Any Key to view the added signal ');
pause;

%Plot the resultant signal
n=0:1:n3-1;
stem(n,x3);
title('The added signal x3 = x1+x2');
xlabel('n --->');