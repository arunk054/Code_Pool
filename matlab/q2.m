%% 2) Plot this signal, put grid on; zoom on

clear all;
clc;

display('Executing assignment question (2)...');

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

    
    %Set grid and zoom on
    grid on;
    zoom on;

    %Plot the signal
    plot(t,x);
    %Set the axis labels for the plot
    xlabel('time (seconds)');
    ylabel('Amplitude');
    title('Plot of the requested signal ');

display ('Successfully plotted the signal.');
    
%%%%End of Program%%%%%
