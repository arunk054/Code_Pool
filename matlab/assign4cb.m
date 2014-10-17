
%% Q. 4 (Matlab)
%% Quantize the data (part (b)) using mu law quantizer and plot the SQNR
%% vs. the number of bits.
%% (a) Quantize this data using 2, 4, and 8 bits. In each case, compute the SQNR (noise in this 
%% case is difference between the original signal and the quantized signal). Plot the SQNR (in dB) vs.
%% the number of bits. (b) Repeat a for x~ N(0,1)


clear all;
clc;

display('Executing assignment - 1 question 4(c) for normal distribution...');

%% The number of samples taken is 1000
sample_size = 1000;

%% Create an array to store the signal samples and the clipped signals
signal=[1:sample_size];
compressed_signal = [1:sample_size];

%% Generate the random variable uniformaly distributed N(0,1)
display ('Taking 1000 samples of the normally distributed random variable.');
signal = randn(size(signal));

%% Create an array to hold the SQNR for the N=2,4,8
SQNR=[1:3];
N=[2;4;8];

%% First write a quantizer for mp = 1 and N = 2, 4, 8 bits
mp = 1;
%% Set the ymax for mu law.
Ymax = 1;

%% In mu law, we do not need to clip the signal, that is a great feeling

%% Find the Xmax of the signal, it will mostly be close to 1
Xmax = abs(signal(1));
for i=2:sample_size
    if (abs(signal(i)) > Xmax)
        Xmax = abs(signal(i));
    end
end

%% define the mu law compander formula
display(' ');
display('Defining the mu law compander and expander for mu = 255');
mu = 255;
mu_law_compander = @(x) Ymax*log(1+(mu*abs(x)/Xmax))/log(1+mu)
mu_law_expander = @(y) (Xmax/mu)*(exp(abs(y)*log(1+mu)/Ymax) - 1)

%% We compress the signal based on mu law

display('Compressing the signal');
for i=1:sample_size
    compressed_signal(i) = mu_law_compander(signal(i));
    % This check is for the signum function
    if (signal(i) <0)
        compressed_signal(i) = -compressed_signal(i);
    end
end

display('Run a loop to find SQNR for 2,4 and 8 bits.');
display(' ');
%% Find delta first, = 2mp/L
for bits=1:size(N)
    L = 2 ^ N(bits);
    delta = 2 * mp / L;
    %Create an array of size L, which holds the quantizer levels
    level=[1:L];
    %Initialize the first quantization level
    level(1) = (-mp) + (delta/2);
    
    display('Determing the quantization levels ...');
    %Now run a for loop to set the quantizer levels or boundaries
    for i=2:L
        level(i) = level(i-1) + (delta);
    end

    %Now for each value in the signal, we need to quantize it and store it
    %in Q, then store the noise in noise vector
    Q=[1:sample_size];
    noise=[1:sample_size];

    display('Quantizing and computing the noise for each sample...');
    %%Here the idea is to find in which range the signal value falls into, and
    %%then we find the quantized value and compute the noise.
    for i=1:sample_size
        for j=1:L
            val = level(j)+(delta/2);
            if (compressed_signal(i) < val)
                Q(i)=level(j);
                break;
            end;
        end;
    end;

    %Compute the noise by the diff between actual signal val and quanti val
     for i=1:sample_size
         % First apply the expander on the quantized value i.e. decoding
         decoded = mu_law_expander(Q(i));
         % This check is for the signum function
         if (Q(i) < 0)
             decoded=-decoded;
         end
         % FInding the noise as the diff between actual and decoded
         noise(i) = signal(i) - decoded;
         Q(i) = decoded;
     end
     
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
title('Plot of SQNR vs no. of bits for a normally distributed signal using mu law quantization');
