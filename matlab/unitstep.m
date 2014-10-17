function unitstep

%--List of variables used--
%==>n,un,s,temp<==

%Plot the unit step
temp=1;
len=-25;
for i=len:1:abs(len)
    n(temp)=i;
    if i<0
        un(temp)=0;
    else
        un(temp)=1;
    end
    temp=temp+1;
end
stem(n,un);

while 1   
    n=0;

    %Get the input of n
    n = input('\nEnter the value n to plot u(n): ');

    %evaluate u(n) and display output
    if n<0
    fprintf('\nu(%g) = 0\n',n);
else
    fprintf('\nu(%g) = 1\n',n);
    end

    %get input to repeat again
    s=input('\nDo you want to continue y/n [y]: ','s');
    if isempty(s)
    s='y';    
    end
if s=='n' | s=='N'
    break
end
end