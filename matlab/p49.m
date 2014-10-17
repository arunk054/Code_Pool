function p49

%--List of variables used--
%==>num,den,t,y,z,p,k,temp,r<==

%First taking the z-transform on both sides of the given equation
%Then storing the coefficients of Y(Z) in 'den'and X(Z) in 'num' gives H(Z) = num/den
num = [1 -4 3];
den = [1 -1.7 1];

%finding poles
[z,p,k] = residue(num,den);
temp=1;
[angle,mag]=cart2pol(real(p),imag(p));

%testing system stability
for i= 1:length(mag)
if mag(i)>1
fprintf('\n   The real part of one of the poles is: %g hence it is an  \n\n                              UN-STABLE SYSTEM\n\n',mag(i));
fprintf('Press Any Key to view the impulse response ');
pause;
temp=0;
end
end
if temp 
fprintf('\n   The magnitude of all the poles lie on the unit circle hence it is a\n\n                       sMARGINALLY STABLE SYSTEM\n\n');
fprintf('Press Any Key to view the impulse response ');
pause;
end

%Taking the inverse z-transform of H(Z) gives h(k)
t=0:1:30;
y=dimpulse(num,den,t);

%ploting it at discrete values of n
stem(t,y);
title('Impulse response of the given difference equation');
xlabel('n  --->');
ylabel('h[n]  --->');

return