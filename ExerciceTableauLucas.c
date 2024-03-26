#include <stdio.h> //printf
#include <stdlib.h> //rand
#include <time.h> //time

typedef struct IntArray
{
	int* pContent;
	int iSize;
	int iCapacity;
} IntArray;

void Init(IntArray* pIntArray)
{
	pIntArray->iCapacity = 1;
	pIntArray->iSize = 0;
	pIntArray->pContent = (int*)malloc(sizeof(int) * pIntArray->iCapacity);
	if (pIntArray == NULL) {
		exit(1);
	}
}

void Add(IntArray* pIntArray, int iValue)
{

	pIntArray->pContent[pIntArray->iSize] = iValue;
	pIntArray->iSize++;
	
}

void Insert(IntArray* pIntArray, int iValue, int iIndex)
{

	if (pIntArray->iSize > pIntArray->iCapacity)
	{
		pIntArray->iCapacity *= 2;
		int* temp = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);
		pIntArray->pContent = temp;
	}

	pIntArray->iSize++;

	for (int i = pIntArray->iSize; i > iIndex; i--) {
		pIntArray->pContent[i] = pIntArray->pContent[i - 1];
	}
	pIntArray->pContent[iIndex] = iValue;
}

void Remove(IntArray* pIntArray, int iIndex)
{
	for (int i = iIndex; i > pIntArray->iSize; i++) {
		pIntArray->pContent[i] = pIntArray->pContent[i + 1];
	}
	pIntArray->iSize--;
	
}

void Print(IntArray* pIntArray)
{
	for (int i = 0; i < pIntArray->iSize; i++) {
		printf("%d \n", pIntArray->pContent[i]);
	}
}

void Get(IntArray* pIntArray, int iIndex) {
	return pIntArray->pContent[iIndex];
}

void Destroy(IntArray* pIntArray)
{	
	free(pIntArray->pContent);
}

int main()
{

	IntArray oArray;
	Init(&oArray);
	Add(&oArray, 1);
	Add(&oArray, 2);
	Add(&oArray, 3);
	Remove(&oArray, 2);
	Print(&oArray);
	return 0;
}

