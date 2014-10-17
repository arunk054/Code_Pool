#include<stdio.h>

int fibonaciRecursive(int n) {
	if (n<=1)
		return n;
	return (fibonaciRecursive(n-1) + fibonaciRecursive(n-2))%10;
}

int fibonaciIntrative(int n){
	int a,b,ret,i;
	if (n<=1)
		return 1;
	a=0;
	b=1;
	ret=a+b;
	for (i = 2; i < n; ++i) {
		a=b;
		b=ret;
		ret=(a+b)%10;
	}
	return ret;
}

void prod(int row, int col, int a[][2], int b[][2], int c[][2]){

	int i,j,k;

	if (row!=col || row>10)
		return;

	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			c[i][j]=0;
			for (k = 0; k < row; ++k) {
				c[i][j]+=(a[i][k]*b[k][j])%10;
			}
		}
	}
}

int matrixPow(int a[][2], int n){

	int b[2][2],i,j;
	int result[2][2]={{1,0},{0,1}};
	int temp[2][2];

	while(n) {
		if (n&1){
			prod(2,2,a,result,temp);
			for (i = 0; i < 2; ++i) {
				for (j = 0; j < 2; ++j) {
					result[i][j]=temp[i][j];
				}
			}
		}
		n=n>>1;
		if (n){
			prod(2,2,a,a,temp);
			for (i = 0; i < 2; ++i) {
				for (j = 0; j < 2; ++j) {
					a[i][j]=temp[i][j];
				}
			}
		}
	}
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < 2; ++j) {
			a[i][j]=result[i][j];
		}
	}
	return 0;

}

int fibonaciMatrix(int n) {
	int a[2][2]={{1,1},{1,0}};
	matrixPow(a,n);
	return a[1][0];
}

int main(int argc, char **argv) {
	//recursive - 45 takes 2mins
	//printf("%d\n", fibonaciRecursive(6));
	//iterative - Max upto ?? because of limit in int
	printf("%d\n", fibonaciIntrative(40002090));
	printf("%d\n", fibonaciMatrix(40002090));
	return 0;
}
