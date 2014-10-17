%%6) Define a new signal y = x + A * sin(3.1*wt) for the same w
%%Repeat steps 2 through 5 for y
%%Plot both dB plots on the same graph, using hold on and different colours; Use pause() command to wait between steps.
%%Extra credit, change the length of this signal, and TIME the FFT to see N*log(N) behavior if possible

clear all;
clc;

display('Executing assignment question (2)...');

%% Create a function to define the required signal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
define_signal = @(A,w,t) A*(cos(w*t)+cos(2*w*t));
define_signal_y = @(x,A,w,t) x + (A * sin(3.1*w*t));
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Value of Amplitude(A) is 10
A = 10;

% Time varies in steps of 0.01 as given,
t = [1:0.01:1000];

% omega will be input by the user, for now just declare it
user_w = input('Enter the value of frequency  [1 3 5 7] : ');

user_w = 2*pi*user_w;

% Define a cosine signal as given in the question
x = define_signal(A, user_w, t);
y = define_signal_y(x, A, user_w, t);

display ('Successfully defined the signal y = x + (A * sin(3.1*w*t) for the given frequency.');


%Signal has been defined, now we perform step -2 which is to plot
    %Set grid and zoom on
    grid on;
    zoom on;

    %Plot the signal
    plot(t,y);
    %Set the axis labels for the plot
    xlabel('time (seconds)');
    ylabel('Amplitude');
    title('Plot of the requested signal ');

display ('Successfully plotted the signal.');

%Wait before showing the next output
pause

%Now performing step - 3.
%Take Fourier Transform, show the peak

%We take 1024 because the sample rate should be power of 2
f = fft(y, 1024);
x_vec = 1024*linspace(0,1,1024);

plot (x_vec, abs(f(1:1024)));

grid on;
zoom on;

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('Absolute values of Fourier transform');
title('Fourier transform with sampling frequency of 1000 Hz');
 
pause

%Show the peak of the transform
plot (max(abs(f(1:1024))), '*', 'MarkerSize', 15);

grid on;
zoom on;

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('Peak of the Fourier Transform');
title('Fourier transform with sampling frequency of 1000 Hz');
 
display ('Successfully shown the peak of the signal');

%Doing step - 4.  Bring any peak to the center using fftshift
pause

%Take the fftshift of f
fp = fftshift(abs(f));

%Plot the transform with fftshift
plot(x_vec, fp);

grid on;
zoom on;

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('|fft|');
title('Fourier transform showing the peaks shifted to the center');

%Now performing step-5. Take 20*log10(abs()) to show dB
pause

fb = 20*log10(abs(f));

%Plot the transform in DB
plot(x_vec, fb);

grid on;
zoom on;

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('|fft| in DB');
title('Fourier transform in DeciBels');

%Now plotting the DB plots on the same graph
pause;
%Finding the db plot of the signal x
%We take 1024 because the sample rate should be power of 2
f = fft(x, 1024);
x_vec = 1024*linspace(0,1,1024);

%First take the fftshift
f = fftshift(abs(f));

%And then take the log show DB plot
f = 20*log10(abs(f));

%Plot the transform in DB
plot(x_vec, f);

grid on;
zoom on;
hold on;

plot(x_vec,fb,'r');

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('|fft| in DB');
title('Fourier transform in DeciBels');
legend('DB plot of signal x = A.cos(wt)+cos(2wt)','DB plot of signal y = x + A * sin(3.1*wt)','Location','NorthOutside');

display('Successfully performed the assignment question 6');



%%%%End of Program%%%%%
