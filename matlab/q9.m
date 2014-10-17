%% Perform the above problem for matrixes of order 2*2 and 5*5 also.

%9) Take a waveform (sine or square or triangular…) 

%a. Plot the original waveform 

%b. Plot only the lower part of the assumed waveform. 

%c. Plot only the upper part of the assumed waveform



clear all;
clc;

display('Executing assignment question (9)...');

n = 50
t = 0:1:n;
A = 1;

display('Computing a square waveform');
y = square(t);
%% Polulate the upper part first
display('Computing the upper of the square waveform');
for i = 1:n+1
    if(y(i) > 0)
        upper(i) = y(i);
    else
         upper(i) = 0;
    end
end

display('Computing the lower of the square waveform');
for i = 1:n+1
    if(y(i) < 0)
        lower(i) = y(i);
    else
        lower(i) = 0;
    end
end

% First plot the original waveform
%subplot(1,2,1)
grid on;
zoom on;

plot(t,y);
xlabel('time');
ylabel('Amplitude');
title('The Original waveform - square');

pause


%plot the upper wave form
%plot the lower wave form

grid on;
zoom on;

plot(t,upper);
hold on;
plot(t,lower, 'r');

xlabel('time');
ylabel('Amplitude');
title('The upper and lower waveforms of the square wave shown in different colors');

legend('Upper Wave form','Lower Wave Form', 'Location' ,'NorthOutside');

display ('Successfully computed the question (9)');
