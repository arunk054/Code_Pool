function ast7
f=[1 2 3 4 5 6 7 6 5 4 3 2 1];

for i=1:length(f),
    n(i)=i-1;
end

%GIVEN x1(n)=2x(n-5)-3x(n+4)
%GIVEN x2(n)=x(3-n)+x(n)*x(n-2)

for i =1:length(f)
    %finding 2*x(n-5)
    nf1=n(i)-5;
    if nf1<0
        x1(i)=2*f(14+nf1);
    else
        x1(i)=2*f(mod(nf1,13)+1);
    end
    %finding 3*x(n+4) and thus computing x1(n)
    nf1=n(i)+4;
    x1(i)=x1(i)-(3*f(mod(nf1,13)+1));
    %finding x(3-n)
    nf1=3-n(i);
    if nf1<0
        x2(i)=f(14+nf1);
    else
        x2(i)=f(mod(nf1,13)+1);
    end
    %finding x(n)*x(n-2) and thus computing x2(n)
    nf1=n(i)-2;
    if nf1<0
        x2(i)=x2(i)+(f(n(i)+1)*f(14+nf1));
    else
        x2(i)=x2(i)+(f(n(i)+1)*f(mod(nf1,13)+1));
    end
    
end

subplot(3,1,1),stem(n,f);title('x(n)');
subplot(3,1,2),stem(n,x1);title('x1(n)');
subplot(3,1,3),stem(n,x2);title('x2(n)');
