%% 10) Mutual information is a statistical similarity measure is used in image retrieval. Given two images A and B , MI is computed as MI= H(A)+H(B)-H(A,B), where H(A) and H(B) are marginal entropies and H(A,B) is the joint entropy. 

%Given two images compute the marginal and joint entropies.

%Compute the mutual information

%plot the 2-D joint histogram.

%comment about the joint histogram's relation with the mutual information, when MI is maximized.

%note: entropy is given as H(A)=summation( p log p). Avoid log(0) by using H(A)=summation plot(p+1);

clear all;
clc;

display('Executing assignment question (10)...');

image_1 = double(imread('iiitb-logo.jpg'));
image_2 = double(imread('mst.jpg'));
sum = 0;

display ('Finding the size of image 1');

[a,b,c]=size(image_1);

%Compute the entropy for image 1\
display ('Compute the entropy for image 1');
for i=1:a
    for j=1:b
        for k = 1:c
            if(image_1(i,j,k) > 0)
                sum = sum +(image_1(i,j,k)*log10(image_1(i,j,k)));
            end
        end
    end
end

h1 = sum;

%Computing the same for image 2
display ('Compute the entropy for image 2');
sum = 0;

display ('Finding the size of image 2');
[a,b,c]=size(image_2);
a
b
c
for i=1:a
    for j=1:b
        for k = 1:c
            if(image_2(i,j,k) > 0)
                sum = sum +(image_2(i,j,k)*log10(image_2(i,j,k)));
            end
    end
end
end

h2 = sum;

display ('Following is the entropy for the two images');
h1
h2

display ('computing the 2-D joint histogram');
hist(h1);
pause
hist(h2);
display('Successfully completed assignment question (10)');
