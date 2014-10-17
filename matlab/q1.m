
%% 1) Define a signal x = A * cos(wt)+cos(2wt) for t from 0 to 1000 in steps
%% of 0.01, w = 2*pi * [1, 3,5,7].
%% The value of omega(w) will be given by the user.

clear all;
clc;

display('Executing assignment question (1)...');

%% Create a function to define the required signal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
define_signal = @(A,w,t) A*(cos(w*t)+cos(2*w*t));
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

display ('Successfully defined the signal x = A*cos(wt)+cos(2wt) for the given frequency.');

% As per the question we have to define the four harmonics of the signal,
w=2*pi*[1,3,5,7];

for i=1:1:length(w)
    x_vect=define_signal(A, w(i),t);
    %plot(t,x_vect);
    %pause;
end

display ('Also successfully defined the signals for the four harmonics');

