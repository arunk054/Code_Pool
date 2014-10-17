%% 8) Generate a random 10*10 matrix [Aij]= 1/(i+j+1) Hilbert Matrix.

%%a) Circularly shift the Hilbert matrix by ‘n’ steps.

%%b) Implement the circular shift without using predefined functions.

%%Find the condition number, LU Decomposition and SVD Decomposition of the matrix. Also find the determinant of the matrix using LU decomposition, Eigen value system and SVD decomposition.

clear all;
clc;

display('Executing assignment question (8)...');

%% First populate the matrix of size 10X10

mat_len = 10;
display('Populating hilbert matrix for size 10 x 10');
for i = 1:mat_len
    for j = 1:mat_len
        hilbert_matrix(i,j) = 1/(i + j + 1);
    end
end

hilbert_matrix

display ('Successfully generated the hilbert matrix');

%Now do a circular shift for n = 3 on the matrix using predefined function circshift

display ('Doing a circular shift on the matrix using predefined function circshift');
n = 3
cs = circshift (hilbert_matrix,n);
cs

display ('Now computing the circular shift for n=3 without using predefined function');

%shift logic
cs_mine = hilbert_matrix;


%shift circularly till n, in this case it is 3
for i= 1:n
    for j = 1:mat_len
        for k =1:mat_len
            if( j == 1) 
                temp_mat (1,k) = cs_mine(mat_len,k);
            end
            if(j >= 1 && j <mat_len)
                cs_mine(mat_len - j + 1,k) = cs_mine(mat_len -j,k);
            else
                cs_mine(1,k) = temp_mat(1,k);
            end 
       end 
    end
end
cs_mine

display('Finding the condition number of hilbert matrix:');
cond_matrix = cond(hilbert_matrix);
cond_matrix

display('Computing the lu decomposition of the matrix');
[lower,upper] = lu(hilbert_matrix);
lower
upper
display('Computing the Eigen vector and Eigen value of the matrix:');
[e_vec,e_val] = eig(hilbert_matrix);
e_vec
e_val


display ('Computing the Singular Value Decomposition (SVD) of matrix:');
[U,S,V] = svd(hilbert_matrix);
U
S
V

display('Computing the Determinant using LU Decomposition:');
determinant_lu = det(lower * upper);
determinant_lu

display('Computing the Determinant using eigen values:');
determinant_ev = abs(det(e_vec)*prod(diag(e_val)));
determinant_ev

display('Computing the Determinant using SVD Decomposition:');
determinant_svd = det(U * S * V);
determinant_svd

%% Next populate the matrix of size 2 X 2

mat_len = 2;
display('Populating hilbert matrix for size 2 x 2');
for i = 1:mat_len
    for j = 1:mat_len
        hilbert_matrix(i,j) = 1/(i + j + 1);
    end
end

hilbert_matrix

display ('Successfully generated the hilbert matrix');

%Now do a circular shift for n = 3 on the matrix using predefined function circshift

display ('Doing a circular shift on the matrix using predefined function circshift');
n = 3
cs = circshift (hilbert_matrix,n);
cs

display ('Now computing the circular shift for n=3 without using predefined function');

%shift logic
cs_mine = hilbert_matrix;


%shift circularly till n, in this case it is 3
for i= 1:n
    for j = 1:mat_len
        for k =1:mat_len
            if( j == 1) 
                temp_mat (1,k) = cs_mine(mat_len,k);
            end
            if(j >= 1 && j < mat_len)
                cs_mine(mat_len - j + 1,k) = cs_mine(mat_len -j,k);
            else
                cs_mine(1,k) = temp_mat(1,k);
            end 
       end 
    end
end
cs_mine

display('Finding the condition number of hilbert matrix:');
cond_matrix = cond(hilbert_matrix);
cond_matrix

display('Computing the lu decomposition of the matrix');
[lower,upper] = lu(hilbert_matrix);
lower
upper
display('Computing the Eigen vector and Eigen value of the matrix:');
[e_vec,e_val] = eig(hilbert_matrix);
e_vec
e_val


display ('Computing the Singular Value Decomposition (SVD) of matrix:');
[U,S,V] = svd(hilbert_matrix);
U
S
V

display('Computing the Determinant using LU Decomposition:');
determinant_lu = det(lower * upper);
determinant_lu

display('Computing the Determinant using eigen values:');
determinant_ev = abs(det(e_vec)*prod(diag(e_val)));
determinant_ev

display('Computing the Determinant using SVD Decomposition:');
determinant_svd = det(U * S * V);
determinant_svd

%% Next populate the matrix of size 5 X 5

mat_len = 5;
display('Populating hilbert matrix for size 2 x 2');
for i = 1:mat_len
    for j = 1:mat_len
        hilbert_matrix(i,j) = 1/(i + j + 1);
    end
end

hilbert_matrix

display ('Successfully generated the hilbert matrix');

%Now do a circular shift for n = 3 on the matrix using predefined function circshift

display ('Doing a circular shift on the matrix using predefined function circshift');
n = 3
cs = circshift (hilbert_matrix,n);
cs

display ('Now computing the circular shift for n=3 without using predefined function');

%shift logic
cs_mine = hilbert_matrix;


%shift circularly till n, in this case it is 3
for i= 1:n
    for j = 1:mat_len
        for k =1:mat_len
            if( j == 1) 
                temp_mat (1,k) = cs_mine(mat_len,k);
            end
            if(j >= 1 && j < mat_len)
                cs_mine(mat_len - j + 1,k) = cs_mine(mat_len -j,k);
            else
                cs_mine(1,k) = temp_mat(1,k);
            end 
       end 
    end
end
cs_mine

display('Finding the condition number of hilbert matrix:');
cond_matrix = cond(hilbert_matrix);
cond_matrix

display('Computing the lu decomposition of the matrix');
[lower,upper] = lu(hilbert_matrix);
lower
upper
display('Computing the Eigen vector and Eigen value of the matrix:');
[e_vec,e_val] = eig(hilbert_matrix);
e_vec
e_val


display ('Computing the Singular Value Decomposition (SVD) of matrix:');
[U,S,V] = svd(hilbert_matrix);
U
S
V

display('Computing the Determinant using LU Decomposition:');
determinant_lu = det(lower * upper);
determinant_lu

display('Computing the Determinant using eigen values:');
determinant_ev = abs(det(e_vec)*prod(diag(e_val)));
determinant_ev

display('Computing the Determinant using SVD Decomposition:');
determinant_svd = det(U * S * V);
determinant_svd

display ('Successfully completed question (8) for 10 X 10, 2 X 2, and 5 X 5 matrices');
%%%%%%% End of Program %%%%%%%%%%%%%%%%