
%% Q. 4 (Matlab)
%% (a) Generate uniformly distributed random variable x ~u(-1, 1). Quantize this data using
%% 2, 4, and 8 bits. In each case, compute the SQNR (noise in this case is difference between
%% the original signal and the quantized signal). Plot the SQNR (in dB) vs.
%% the number of bits.


clear all;
clc;

display('Executing assignment - 1 question 4(a)...');

%% The number of samples taken
display ('Taking 1000 samples of the uniformly distributed random variable.');
sample_size = 1000;

%% Create an array to store the signal samples
signal=[1:sample_size];

%% Generate the uniform signal using rand function between -1 and 1
signal = rand(size(signal))*2-1;

%% Create an array to hold the SQNR for the N=2,4,8
SQNR=[1:3];
N=[2;4;8];

%% First write a quantizer for mp = 1 and N = 2, 4, 8 bits
mp = 1;

display('Run a loop to find SQNR for 2,4 and 8 bits.');
display(' ');

%% Find delta first, = 2mp/L
for bits=1:size(N)
    L = 2 ^ N(bits);
    delta = 2 * mp / L;
    %% Create an array of size L, which holds the quantizer levels
    level=[1:L];
    %% Initialize the first quantization level
    level(1) = (-mp) + (delta/2);

    display('Determing the quantization levels ...');
    %% Now run a for loop to set the quantizer levels or boundaries
    for i=2:L
        level(i) = level(i-1) + (delta);
    end

    %Now for each value in the signal, we need to quantize it and store it
    %in Q and noise in noise
    Q = [1:sample_size];
    noise=[1:sample_size];

    display('Quantizing and computing the noise for each sample...');
    %%Here the idea is to find in which range the signal value falls into, and
    %%then we find the quantized value and compute the noise.
    for i=1:sample_size
        for j=1:L
            val = level(j)+(delta/2);
            if (signal(i) < val)
                Q(i) = level(j);
                %Just store the noise directly instead of storing the quantized value
                noise(i)=signal(i) - level(j);
                break;
            end;
        end;
    end;

    %Now find the mean of the signal power(S) and noise power (Nq)
    display('Finding the mean signal power (S) and mean noise power(Nq).');
    S = 0;
    Nq = 0;
    for i=1:sample_size
        S = S + signal(i)^2;
        Nq = Nq + noise(i)^2;
    end

    S
    Nq

    %Find the SQNR in DB
    SQNR(bits) = 10 * log10(S/Nq);
    %Repeat the loop for all values of N = 2, 4, 8
end

display('The SQNR for N = 2, 4, 8 is :');
SQNR

%% Plot the SQNR in DB vs no of bits

display ('Plot the quantized signal and original signal');

plot([1:sample_size], signal);

grid on;
zoom on;
hold on;

plot([1:sample_size], Q, 'r');

xlabel('Time ==>');
ylabel('Signal amplitude ==>');
title('Plot of quantized and original signal');
legend('Original signal','Quantized signal','Location','NorthOutside');

pause;
display(' ');
display ('Plot the SQNR in DB vs no of bits');

plot(N,SQNR);

grid on;
xlabel('No. of Bits ==>');
ylabel('SQNR in DB ==>');
title('Plot of SQNR vs no. of bits for a uniformly distributed signal using uniform quantization');
