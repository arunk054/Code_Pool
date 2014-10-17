

void prod(int row, int col, int a[][10], int b[][10], int c[][10]){

	int i,j,k;

	if (row!=col || row>10)
		return;

	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			c[i][j]=0;
			for (k = 0; k < row; ++k) {
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}


int main(){

	//Test Case 1
	{
		int row = 3, col = 3;
		int p[][10] = {  {1, 1, 1}, {2,2,2}, {3,3,3}  };
		int q[][10] = {  {1, 1, 1}, {1, 1, 1}, {1, 1, 1}  };
		int r[10][10],i,j;

		prod(row, col, p, q, r);

		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
					printf("%d  ", r[i][j]);
			}
			printf("\n");
		}
	}

}
