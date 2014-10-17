%% 7) Generate 1000 column vectors of size 1000x1 such that its elements
%% are random. Combine those 1000 column vector to form a single matrix of 1000*1000 matrix.

%%Now the resultant matrix is A - 8 MB space required

%%a)Find Eigen values of A, eigenvectors.

%%b)Find Determinant of A - does it overflow? Use logs


clear all;
clc;

display('Executing assignment question (7)...');

%% Create a function to get a column vector of size n and range or randum
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
get_vector = @(n, r) r*rand(n,1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Create the n column vectors with values between 0 -> r
n=1000;
r=0.1;
%% First declare two column vectors, so , that we can concatenate them
display('Creating 1000 column vectors and concatenating them');
c_vect_1 = get_vector(n,r);
c_vect = get_vector(n,r);

 for i = 1:n-1
    c_vect = cat(2,c_vect,c_vect_1);
    c_vect_1 = get_vector(n,r);
 end
 display('Computing the eigen value and eigen vector for the 1000 X 1000 matrix');
 
[e_vec,e_val] = eig(c_vect);


display ('The value of determinant for the matrix is:');
determinant = det(c_vect);
determinant

display('=========Successfully completed the assignment question (7)=========');

%%%%%%% End of Program %%%%%%%%%%%%%%%%