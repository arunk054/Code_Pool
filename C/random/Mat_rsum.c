
#define MAX_COL 9

void genSum(int row, int col, int a[][MAX_COL], int rs[MAX_COL], int rFlag){

	int i,j;

	if (col >MAX_COL)
		return;

	for (i = 0; i < row; ++i) {
		rs[i]=0;
		for (j = 0; j < col; ++j) {
			if (rFlag)
				rs[i] += a[i][j];
			else
				rs[i] += a[j][i];
		}
	}

}

void rsum(int row, int col, int a[][MAX_COL], int rs[MAX_COL]) {
	genSum(row,col,a,rs,1);
}

void csum (int row, int col, int a[][MAX_COL], int cs[MAX_COL]) {
	genSum(row,col,a,cs,0);
}

int sum (int row, int col, int a[][MAX_COL]) {
	int i,j, sum=0;

	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			sum+=a[i][j];
		}
	}
	return sum;
}

int main(int argc, char **argv) {
	return 0;
}
