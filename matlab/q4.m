%% 4)  Bring any peak to the center using fftshift

clear all;
clc;

display('Executing assignment question (4)...');

%% Create a function to define the required signal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
define_signal = @(A,w,t) A*(cos(w*t)+cos(2*w*t));
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Value of Amplitude(A) is 10
A = 10;

% Time varies in steps of 0.01 as given,
t = [1:0.01:1000];

% omega will be input by the user, for now just declare it
user_v = input('Enter the value of frequency  [1 3 5 7] : ');

user_w = 2*pi*user_v;

% Define a cosine signal as given in the question
x = define_signal(A, user_w, t);

display ('Successfully defined the signal x = A*cos(wt)+cos(2wt) for the given frequency.');

%Take fourier transform
%We take 1024 because the sample rate should be power of 2
f = fft(x, 1024);
x_vec = 1024*linspace(0,1,1024);

%Take the fftshift of f
f = fftshift(abs(f));

%Plot the transform with fftshift
plot(x_vec, f);

grid on;
zoom on;

%Set the axis labels for the plot
xlabel('Frequency (Hertz)');
ylabel('|fft|');
title('Fourier transform showing the peaks shifted to the center');
 

display ('Successfully showed the peaks of the fourier transform.');
    
%%%%End of Program%%%%%
