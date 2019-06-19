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

int** new_matriz(int** matriz, int new_n, int n, int m)
{	
		int new_matriz[new_n][new_n];

		int aux_1 = 0, aux_2 = 0;
		while(aux_1 < new_n)
		{
			if(aux_2 >= new_n)
			{
				aux_1++;
				aux_2 = 0;
			}
			else 
			{
				if(aux_1 >= n||aux_2 >= m)
				{
					new_matriz[aux_1][aux_2] = 0;
				}
				else
				{
					new_matriz[aux_1][aux_2] = matriz[aux_1][aux_2];
				}
				aux_2++;
			}
		}
		return new_matriz;
}

int check(int n, int aux, int p)
{
	if(n == 1)
	{
		return n;
	}
	else
	{
		if((n % 2) != 0)
		{
			
			n = n + p;
			aux++;
			p = p*2 ;

		}

		check(n, (aux/2), p);
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
	
	else
	{
	int n;	

	if(n1 >= m1 && n1 >= n2 && n1 >= m2)
	{
		n = n1;
	}
	else if(m1 >= n2 && n2 >= m2)
	{
		n = m1;
	}
	else if(n2 >= m2)
	{
		n = n2;
	}
	else
	{
		n = m2;
	}
	 	int new_n = check(n,n,1); 
	 	int new_matriz_a[new_n][new_n] = new_matriz(matriz_a,new_n,n1,m1);
		int new_matriz_b[new_n][new_n] = new_matriz(matriz_b,new_n,n2,m2);
		int result[new_n][new_n];

		int aux_1 = 0, aux_2 = 0;
		while(aux_1 < new_n)
		{
			if(aux_2 >= new_n)
			{
				aux_1 = aux_1 + 2;
				aux_2 = 0;
			}
			else
			{
				int s1 = new_matriz_b[aux_1][aux_2 + 1] - new_matriz_b[aux_1+1][aux_2 + 1];
				int s2 = new_matriz_a[aux_1][aux_2] + new_matriz_a[aux_1][aux_2 + 1];
				int s3 = new_matriz_a[aux_1 + 1][aux_2] + new_matriz_a[aux_1 + 1][aux_2 + 1];
				int s4 = new_matriz_b[aux_1+1][aux_2] - new_matriz_b[aux_1][aux_2];
				int s5 = new_matriz_a[aux_1][aux_2] + new_matriz_a[aux_1 + 1][aux_2 + 1];
				int s6 = new_matriz_b[aux_1][aux_2] + new_matriz_b[aux_1+1][aux_2 + 1];
				int s7 = new_matriz_a[aux_1][aux_2 + 1] - new_matriz_a[aux_1 + 1][aux_2 + 1];
				int s8 = new_matriz_b[aux_1+1][aux_2] + new_matriz_a[aux_1 + 1][aux_2 + 1];
				int s9 = new_matriz_a[aux_1][aux_2] - new_matriz_a[aux_1 + 1][aux_2];
				int s10 = new_matriz_b[aux_1][aux_2] + new_matriz_b[aux_1][aux_2 + 1];

				int p1 = s1 * new_matriz_a[aux_1][aux_2];
				int p2 = s2 * new_matriz_b[aux_1+1][aux_2 + 1];
				int p3 = s3 * new_matriz_b[aux_1][aux_2];
				int p4 = s4 * new_matriz_a[aux_1 + 1][aux_2 + 1];
				int p5 = s5 * s6;
				int p6 = s7 * s8;
				int p7 = s9 * s10;

				result[aux_1][aux_2] = p5 + p4 -p2 + p6;
				result[aux_1][aux_2 + 1] = p1 + p2;
				result[aux_1 + 1][aux_2] = p3 + p4;
				result[aux_1 + 1][aux_2 +1] = p5 + p1 - p3 - p7;

				aux_2 = aux_2 + 2;	
			}
		}
			
	return result;
	}	

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
	}

  int result [n1][m2] = strassen_multi(matriz_a,matriz_b,n1,m1,n2,m2);
  print_result(result,n1,m2);

  fclose(in);

  return 0;

}
