#include<stdio.h>
#include<stdlib.h>

int** createZeroMatrix(int n){
	int ** array = (int**)malloc(n*sizeof(int *));
	int i,j;
	for(i = 0;i < n; i++) {
	    	array[i] = (int*)malloc(n*sizeof(int));
   	 	for(j = 0; j < n; j++) {
	        	array[i][j] = 0.0;
	    	}
	}
	return array;
}


void compose(int** matrix,int** result,int row,int col,int n){
	int i,j,r=row,c=col;
	for(i=0;i<n;i++){
		c=col;
		for(j=0;j<n;j++){
			result[r][c]=matrix[i][j];
			c++;
		}
		r++;
	}
}

int** divide(int** matrix,int n, int row,int col) {
	int n_new=n/2;

	int ** array = createZeroMatrix(n_new);
	int i,j,r=row,c=col;
	for(i = 0;i < n_new; i++) {
		c=col;
   	 	for(j = 0; j < n_new; j++) {
        		array[i][j] = matrix[r][c];
			c++;
    		}
		r++;
	}
	return array;
}

int ** addMatrix(int** matrixA,int** matrixB,int n){
	int ** res = createZeroMatrix(n);
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			res[i][j]=matrixA[i][j]+matrixB[i][j];

	return res;
}

int** subMatrix(int** matrixA,int** matrixB,int n){
	int ** res = createZeroMatrix(n);
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			res[i][j]=matrixA[i][j]-matrixB[i][j];

	return res;
}


int ** create(int new_n,FILE *in,int m,int n){
	int ** array = createZeroMatrix(new_n);
	int i,j;
	int k;
	for(i = 0;i < m; i++) {
   	 	for(j = 0; j < n; j++) {
	    		fscanf(in,"%d",&k);
	    		array[i][j] = k;
			}
	}
	return array;
}

void printMatrix(int ** matrix,int n,int n1,int m2){
	int i,j;
	FILE* out;
	out = fopen("out.txt","w");

	fprintf(out,"18110495\n");
	fprintf(out,"%d %d\n",n1,m2);
	for(i=0;i<n1;i++){
		for(j=0;j<m2;j++){
			if (j != 0){
				fprintf(out, " ");
			}
			fprintf(out,"%d",matrix[i][j]);
		}
		fprintf(out,"\n");
	}
	fclose(out);
}

int** strassen(int** matrixA, int** matrixB,int n){
	int** result = createZeroMatrix(n);

	if(n>1) {

		int** a11 = divide(matrixA, n, 0, 0);
		int** a12 = divide(matrixA, n, 0, (n/2));
		int** a21 = divide(matrixA, n, (n/2), 0);
		int** a22 = divide(matrixA, n, (n/2), (n/2));
		int** b11 = divide(matrixB, n, 0, 0);
		int** b12 = divide(matrixB, n, 0, n/2);
		int** b21 = divide(matrixB, n, n/2, 0);
		int** b22 = divide(matrixB, n, n/2, n/2);

		int** m1= strassen(addMatrix(a11,a22,n/2),addMatrix(b11,b22,n/2),n/2);
		int** m2= strassen(addMatrix(a21,a22,n/2),b11,n/2);
		int** m3= strassen(a11,subMatrix(b12,b22,n/2),n/2);
		int** m4= strassen(a22,subMatrix(b21,b11,n/2),n/2);
		int** m5= strassen(addMatrix(a11,a12,n/2),b22,n/2);
		int** m6= strassen(subMatrix(a21,a11,n/2),addMatrix(b11,b12,n/2),n/2);
		int** m7= strassen(subMatrix(a12,a22,n/2),addMatrix(b21,b22,n/2),n/2);

		int** c11 = addMatrix(subMatrix(addMatrix(m1,m4,n/2),m5,n/2),m7,n/2);
		int** c12 = addMatrix(m3,m5,n/2);
		int** c21 = addMatrix(m2,m4,n/2);
		int** c22 = addMatrix(subMatrix(addMatrix(m1,m3,n/2),m2,n/2),m6,n/2);

		compose(c11,result,0,0,n/2);
		compose(c12,result,0,n/2,n/2);
		compose(c21,result,n/2,0,n/2);
		compose(c22,result,n/2,n/2,n/2);
	}
	else {
		result[0][0]=matrixA[0][0]*matrixB[0][0];
	}
	return result;
}


int main() {
	int i=0,j=0,n=0;
	int n1,m1,n2,m2;
	int new_n = 1;

	FILE *in;
	in = fopen("in.txt", "r");

	if (in == NULL){
   		printf("FILE NOT FOUND\n");
   		return 0;
	}

	fscanf(in,"%d %d %d %d",&n1,&m1,&n2,&m2);

	if (m1 != n2){
		printf("INVALID OPERATION\n");
		return 0;
	}

	else if(n1== 1 && m2 == 1)
	{
		int a,b;
		fscanf(in,"%d\n%d\n",&a,&b);
		printf("18110495\n");
		printf("1 1\n");
		printf("%d\n",(a*b) );
	}

	else
	{
		if(n1 >= m1 && n1 >= n2 && n1 >= m2){
			n = n1;
		}else if(m1 >= n2 && m1 >= m2){
			n = m1;
		}else if(n2 >= m2){
			n = n2;
		}else{
			n = m2;
		}

		while(new_n < n){
			new_n *= 2;
		}

		int** matrixA = create(new_n,in,n1,m1);
		int** matrixB = create(new_n,in,n2,m2);
		n = new_n;

		int ** strassens_Res = strassen(matrixA,matrixB,n);
		printMatrix(strassens_Res,n,n1,m2);
	}

	fclose(in);
	return 0;
}
