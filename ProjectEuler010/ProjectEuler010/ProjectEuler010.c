#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#define MAX 2000000 
#define TRUE 1
#define FALSE 0
typedef int BOOL;

void initArray(BOOL *ptr);
unsigned long long primeNumber(BOOL *ptr, unsigned long long sum);
void main(void)
{
	unsigned long long sum = 0;
	BOOL *ptr = (BOOL*)malloc(sizeof(BOOL)*MAX);
	initArray(ptr);
	sum = primeNumber(ptr, sum);
	printf("200만 이하의 소수의 합 : %llu\n", sum);
	system("pause");
}

void initArray(BOOL *ptr)
{
	int i;
	for (i = 2; i < MAX; i++)
	{
		ptr[i] = TRUE;
	}
}

unsigned long long primeNumber(BOOL *ptr, unsigned long long sum)
{
	int i;
	int j;
	for (i = 2; i < MAX; i++)
	{
		for (j = i+i; j < MAX; j += i)
			ptr[j] = FALSE;
		if (ptr[i] == TRUE)
			sum += i;
	}
	return sum;
}