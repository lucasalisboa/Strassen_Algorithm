#include<stdio.h>
#include<stdlib.h>

void print_result(int** result,int n1, int m2){
	FILE* out;
	out = fopen("out.txt","w");

  if(out == NULL){
		printf("File doesn't exist\n");
		return;
	}
	fprintf(out,"18110495\n");
	fprintf(out,"%d %d\n",n1,m2);

  int aux_1 = 0, aux_2 = 0;
    while(aux_1< n1)
    {
      if(aux_2 == (m2-1))
      {
        printf("%d\n",result[aux_1][aux_2] );
        aux_1++;
        aux_2 = 0;
      }
      else
      {
        printf("%d ",result[aux_1][aux_2]);
        aux_2++;
      }

    }
	fclose(out);
} 

int** check(int** matriz, int n)
{
	if(n == 1)
	{
		return matriz;
	}
	else
	{
		if((n % 2) == 0)
		{
			check(matriz, (n/2));
		}
		else
		{
			
		}
	}
}

int** strassen_multi(int** matriz_a,int** matriz_b,int n1,int m1, int n2, int m2)
{
	if(n1 == 1 && m1 == 1 && n2 == 1 && m2 == 1)
	{
		int result[1][1];
		result[0][0] = (matriz_a[0][0]*matriz_b[0][0]);
		return result;
	}
	else if(n1 == m1 && n2 == m2)
	{

	}
	/*
		int s1 = matriz_b[0][1] - matriz_b[1][1];
		int s2 = matriz_a[0][0] + matriz_a[0][1];
		int s3 = matriz_a[1][0] + matriz_a[1][1];
		int s4 = matriz_b[1][0] - matriz_b[0][0];
		int s5 = matriz_a[0][0] + matriz_a[1][1];
		int s6 = matriz_b[0][0] + matriz_b[1][1];
		int s7 = matriz_a[0][1] - matriz_a[1][1];
		int s8 = matriz_b[1][0] + matriz_a[1][1];
		int s9 = matriz_a[0][0] - matriz_a[1][0];
		int s10 = matriz_b[0][0] + matriz_b[0][1];

		int p1 = s1 * matriz_a[0][0];
		int p2 = s2 * matriz_b[1][1];
		int p3 = s3 * matriz_b[0][0];
		int p4 = s4 * matriz_a[1][1];
		int p5 = s5 * s6;
		int p6 = s7 * s8;
		int p7 = s9 * s10;

		int c[2][2];
		c[0][0] = p5 + p4 -p2 + p6;
		c[0][1] = p1 + p2;
		c[1][0] = p3 + p4;
		c[1][1] = p5 + p1 - p3 - p7;
	*/

}

int main()
{
  int n1,m1,n2,m2;

  FILE *in;
	in = fopen("in.txt", "r");

	if (in == NULL){
   		printf("File not found\n");
   		return 0;
	}

  fscanf(in,"%d %d %d %d\n",&n1,&m1,&n2,&m2);

  if(m1 != n2)
  {
    printf("Invalid Operation\n");
    return 0;
  }

  int matriz_a[n1][m1], matriz_b[n2][m2];

  int aux_1 = 0, aux_2 = 0;
  while(aux_1 < n1)
  {
    if (aux_2 == (m1-1)) {
      fscanf(in,"%d\n",&matriz_a[aux_1][aux_2]);
      aux_1++;
      aux_2 = 0;
    }
    else
    {
      fscanf(in,"%d ",&matriz_a[aux_1][aux_2]);
      aux_2++;
    }
  }
  fscanf(in,"\n");
  aux_1 = 0, aux_2 = 0;
  while (aux_1 < n2) {

    if (aux_2 == (m2-1)) {
      fscanf(in,"%d ",&matriz_b[aux_1][aux_2]);
      aux_1++;
      aux_2 = 0;
    }
    else
    {
      fscanf(in,"%d ",&matriz_b[aux_1][aux_2]);
      aux_2++;
  }

  int result [n1][m2] = strassen_multi(matriz_a,matriz_b,n1,m1,n2,m2);
  print_result(result,n1,m2);

  fclose(in);

  return 0;
}
