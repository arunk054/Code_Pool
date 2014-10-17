function sigshift

%--List of variables used--
%==>n3,x3,i,n,shift,ns,xs,temp<==

[x3,n3]=sigadd;

%Get the input of shift
shift=input('\n\nEnter n0 to plot the signal x3[n-n0] = ');

%Plot the added signal
n=0:1:n3-1;
subplot(2,1,1);
stem(n,x3);
title('The added signal x3 = x1+x2');
xlabel('n --->');

%Perform the shift  
temp=0;
if shift >=0
for i=n3+shift:-1:1
    ns(i)=i-1;
    xs(i)=x3(n3-mod(temp,n3));
    temp=temp+1;
end
else
for i=shift:1:n3-1
    temp=temp+1;
    ns(temp)=i;
    xs(temp)=x3(mod(temp-1,n3)+1);
end
end

%Plot the shifted signal
subplot(2,1,2);
stem(ns,xs);
title('The shifted signal x3[n-n0] is');
xlabel('n --->');

