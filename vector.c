#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "vector.h"

static bool setCapacity(HVECTOR hVector, size_t capacity);

HVECTOR CreateVectorWithCapacity(size_t typeSize, size_t capacity) {

	HVECTOR hVector;

	if ((hVector = (HVECTOR)malloc(sizeof(VECTOR))) == NULL)
		return NULL;

	if ((hVector->pArray = malloc(typeSize * capacity)) == NULL)
	{
		free(hVector);
		return NULL;
	}

	hVector->typeSize = typeSize;
	hVector->capacity = capacity;
	hVector->size = 0;

	return hVector;
}

HVECTOR CreateVector(size_t typeSize) {
	return CreateVectorWithCapacity(typeSize, DEFAULT_CAPACITY);
}

void CloseVector(HVECTOR hVector) {
	free(hVector->pArray);
	free(hVector);
}

bool AddItem(HVECTOR hVector, const void* pVal) {

	char* pDest;
	
	if (hVector->size == hVector->capacity && !setCapacity(hVector, hVector->capacity * 2))
		return false;

	pDest = (char*)hVector->pArray + hVector->typeSize * hVector->size;
	memcpy(pDest, pVal, hVector->typeSize);
	hVector->size++;

	return true;
}

bool InsertItem(HVECTOR hVector, size_t index, const void* pVal) {
	
	if (index > hVector->size)
		return false;

	if (hVector->size == hVector->capacity)
		if (!setCapacity(hVector, hVector->capacity * 2))
			return false;

	memmove((char*)hVector->pArray + (index + 1) * hVector->typeSize, (char*)hVector->pArray + index * hVector->typeSize, (hVector->size - index) * hVector->typeSize);

	memcpy((char*)hVector->pArray + index * hVector->typeSize, pVal, hVector->typeSize);
	hVector->size++;

	return true;
}

bool DeleteItem(HVECTOR hVector, size_t index) {  
	
	if (index >= hVector->size)
		return false;

	memmove((char*)hVector->pArray + index * hVector->typeSize, (char*)hVector->pArray + (index + 1) * hVector->typeSize, (hVector->size - index - 1) * hVector->typeSize);
	hVector->size--;

	return true;
}

size_t FindItem(HVECTOR hVector, const void* pVal)
{
	size_t i;
	char* pTemp;

	for (i = 0; i < hVector->size; i++)
	{
		pTemp = (char*)hVector->pArray + hVector->typeSize * i;
		if(memcmp(pTemp, pVal, hVector->typeSize) == 0) return i;
	}

	return ((size_t)(-1));
}

/*

void* FindItem(HVECTOR hVector, const void* pVal)
{
	size_t i;
	char* pTemp;

	for (i = 0; i < hVector->size; i++)
	{
		pTemp = (char*)hVector->pArray + hVector->typeSize * i;
		if (memcmp(pTemp, pVal, hVector->typeSize) == 0) return pTemp;
	}

	return NULL;
}

*/

void Clear(HVECTOR hVector) {
	hVector->size = 0;
}

#ifndef USE_MACROS
void GetItem(HVECTOR hVector, size_t index, void* pVal) {//is add index overflow control?
	char* pSource = (char*)hVector->pArray + index * hVector->typeSize;     
	memcpy(pVal, pSource, hVector->typeSize);
}

void SetItem(HVECTOR hVector, const void* pVal, size_t index) {//is add index overflow control?
	char* pDest = (char*)hVector->pArray + index * hVector->typeSize;     
	memcpy(pDest, pVal, hVector->typeSize);
}

void* GetArray(HVECTOR hVector) {
	return hVector->pArray;
}

size_t Getsize(HVECTOR hVector) {
	return hVector->size;
}

size_t GetCapacity(HVECTOR hVector) {
	return hVector->capacity;
}
#endif

bool SetCapacity(HVECTOR hVector, size_t capacity) {

	if (capacity < hVector->size)
		return false;

	if (capacity != hVector->capacity)
		return setCapacity(hVector, capacity);

	return true;
}

static bool setCapacity(HVECTOR hVector, size_t capacity) {

	void* pTemp;
	size_t newCapacity;

	newCapacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;
	pTemp = malloc(hVector->typeSize * newCapacity);

	if (pTemp == NULL)
		return false;

	if (hVector->size)
		memcpy(pTemp, hVector->pArray, hVector->size * hVector->typeSize);

	free(hVector->pArray);
	hVector->pArray = pTemp;
	hVector->capacity = newCapacity;

	return true;
}

/* Test Kodu */
#if 1 

void DispVector(HVECTOR hVector) {

	size_t i, size = Getsize(hVector);
	int val; 

	for (i = 0; i < size; ++i)
	{
		GetItem(hVector, i, &val);
		printf("%d ", val);
	}
		
	printf("\nsize = %lu, Capacity = %lu\n", (unsigned long)Getsize(hVector), (unsigned long)GetCapacity(hVector));
	printf("------------------------\n");
}

int main(void) {

	HVECTOR hVector;
	int i, val;

	if ((hVector = CreateVector(sizeof(int))) == NULL)
	{
		fprintf(stderr, "Cannot create vector!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; ++i)
		AddItem(hVector, &i);
	DispVector(hVector);

	val = 25000;
	InsertItem(hVector, 5, &val);
	DispVector(hVector);

	DeleteItem(hVector, 5);
	DispVector(hVector);

	InsertItem(hVector, 5, &val);
	DispVector(hVector);

	size_t findedOfIndex = FindItem(hVector, &val);
	printf("Item %d index is %d\n", val, findedOfIndex);
	printf("%d. item is: %d\n", findedOfIndex, *((int*)((char*)hVector->pArray + findedOfIndex * hVector->typeSize)));
	printf("------------------------\n");

	CloseVector(hVector);

	return 0;
}

#endif