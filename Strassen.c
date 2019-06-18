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

  int result [n1][m2] = strassen_multi(matriz_a,matriz_b);
  print_result(result,n1,m2);

  fclose(in);

  return 0;
}
