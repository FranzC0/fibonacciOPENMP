#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n) {
	int i, j;
	if (n < 2) {
		return n;
	}
	else {
#pragma omp task shared(i)
		i = fib(n - 1);
#pragma omp task shared(j)
		j = fib(n - 2);
#pragma omp taskwait
		return i + j;
	}
}

void imprimir(int n) {
	
	int i,j;
	int a[50];
	i = 2;
	j = 0;
	while (n > 1) {
		if (n % i == 0) {
			n = n / i;
			a[j] = i;
			j++;
			i = 2;
		}
		else {
			i++;
		}
	}
	for (i = 0; i < j; i++) {
		if (i == 0) {
			printf("%d ",a[i]);
		}
		else {
			printf("* %d ", a[i]);
		}
	}
}


int main(int argc, char** argv) {
	int n, result, i;
	char* a = argv[1];
	n = atoi(a);
	i = 0;
	while (i != n+1) {
#pragma omp parallel
		{
#pragma imp single
			result = fib(i);				
		}
#pragma omp critical
		printf("Numero %d:", i);
		imprimir(result);
		printf(" = %d\n", result);
		i++;
	}
}