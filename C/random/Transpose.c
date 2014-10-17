
void transpose(int col, int row, int value[][9], int result[][9]) {
	int i,j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			result[j][i]=value[i][j];
		}
	}
}


int main(int argc, char **argv) {
	return 0;
}
