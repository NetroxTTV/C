#include <stdlib.h>
#include <stdio.h>

typedef struct IntArray
{

	int* pContent; //contenu du tableau
	int iSize; //taille du tableau
	int iCapicity; //nombre de bloc alloué

}IntArray;

void Init(IntArray* pIntArray) {
	pIntArray->iCapicity = 1;
	pIntArray->iSize = 0;
	pIntArray->pContent = (int*)malloc(sizeof(int) * pIntArray->iCapicity);
	if (pIntArray == NULL)
	{
		exit(1);
	}

}

void Add(IntArray* pIntArray, int iValue) {

	if (pIntArray->iSize > pIntArray->iCapicity)
	{
		pIntArray->iCapicity *= 2;
		pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapicity);
	}
	pIntArray->pContent[pIntArray->iSize] = iValue;
	pIntArray->iSize++;
}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
	if (iIndex < 0 || iIndex > pIntArray->iSize)
	{
		printf("Please insert a valid index !");
	}
	else {
		if (pIntArray->iSize > pIntArray->iCapicity)
		{
			pIntArray->iCapicity *= 2;
			pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapicity);
		}
		pIntArray->iSize++;
		for (int i = pIntArray->iSize; i > iIndex; i--) {
			pIntArray->pContent[i] = pIntArray->pContent[i - 1];
		}

		pIntArray->pContent[iIndex] = iValue;

	}
}

void Remove(IntArray* pIntArray, int iIndex) {

	if (iIndex < 0 || iIndex > pIntArray->iSize)
	{
		printf("Please insert a valid index !");
		return;
	}

	if (pIntArray->iSize < pIntArray->iCapicity / 2)
	{
		pIntArray->iCapicity /= 2;
		pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapicity);
	}

	for (int i = iIndex; i > pIntArray->iSize; i++) {
		pIntArray->pContent[i] = pIntArray->pContent[i + 1];
	}
	pIntArray->iSize--;
}

int Get(IntArray* pIntArray, int iIndex) {
	if (iIndex < 0 || iIndex > pIntArray->iSize)
	{
		printf("Please insert a valid index !");
	}
	else {
		return pIntArray->pContent[iIndex];
	}
}

void Print(IntArray* pIntArray) {
	printf("[ ");
	for (int i = 0; i < pIntArray->iSize; i++) {
		printf(" %d  ", pIntArray->pContent[i]);
	}
	printf(" ]\n");
}

void Destroy(IntArray* pIntArray) {
	free(pIntArray->pContent);
}

int main() {
	IntArray oArray;
	Init(&oArray);
	Print(&oArray);
	Add(&oArray, 5);
	Print(&oArray);
	Insert(&oArray, 2, 0);
	Print(&oArray);
	Remove(&oArray, 0);
	Print(&oArray);
	Destroy(&oArray);
	return 0;
}
