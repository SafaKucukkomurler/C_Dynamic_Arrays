#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "vectorIntType.h"

static bool setCapacity(HVECTOR hVector, size_t capacity);

HVECTOR CreateVectorWithCapacity(size_t capacity) {

	HVECTOR hVector;

	if ((hVector = (HVECTOR) malloc(sizeof(VECTOR))) == NULL)
		return NULL;

	if ((hVector->pArray = (int *) malloc(sizeof(int) * capacity)) == NULL)
	{
		free(hVector);
		return NULL;
	}

	hVector->capacity = capacity;
	hVector->size = 0;

	return hVector;
}

HVECTOR CreateVector() {
	return CreateVectorWithCapacity(DEFAULT_CAPACITY);
}

void CloseVector(HVECTOR hVector) {
	free(hVector->pArray);
	free(hVector);
}

bool AddItem(HVECTOR hVector, int val) {

	if (hVector->size == hVector->capacity && !setCapacity(hVector, hVector->capacity * 2))
		return false;

	hVector->pArray[hVector->size++] = val;
	return true;
}

bool InsertItem(HVECTOR hVector, size_t index, int val) {

	if (index > hVector->size)
		return false;

	if (hVector->size == hVector->capacity)
		if(!setCapacity(hVector, hVector->capacity * 2))
			return false;

	memmove(hVector->pArray + index + 1, hVector->pArray + index, (hVector->size - index) * sizeof(int));
	
	hVector->pArray[index] = val; // *(hVector->pArray + index) = val;
	hVector->size++;

	return true;
}

bool DeleteItem(HVECTOR hVector, size_t index) {

	if (index >= hVector->size)
		return false;

	memmove(hVector->pArray + index, hVector->pArray + index + 1, (hVector->size - index - 1) * sizeof(int));
	hVector->size--;

	return true;
}

size_t FindItem(HVECTOR hVector, int val)
{
	size_t i;
	for (i = 0; i < hVector->size; i++)
		if (val == hVector->pArray[i])
			return i;

	return ((size_t)(-1));
}

void Clear(HVECTOR hVector) {
	hVector->size = 0;
}

#ifndef USE_MACROS
int GetItem(HVECTOR hVector, size_t index) {//is add index overflow control?
	return hVector->pArray[index];
}

void SetItem(HVECTOR hVector, size_t index, int val) {//is add index overflow control?
	hVector->pArray[index] = val;
}

int* GetArray(HVECTOR hVector) {
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

	int* pTemp;
	size_t newCapacity;

	newCapacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;
	pTemp = (int*) malloc(sizeof(int) * newCapacity);

	if (pTemp==NULL)
		return false;

	if(hVector->size)
		memcpy(pTemp, hVector->pArray, hVector->size * sizeof(int));

	free(hVector->pArray);
	hVector->pArray = pTemp;
	hVector->capacity = newCapacity;

	return true;
}

/* Test Kodu */
#if 1 

void DispVector(HVECTOR hVector) {

	size_t i, size = Getsize(hVector);

	for (i = 0; i < size; ++i)
		printf("%d ", GetItem(hVector, i));
	printf("\nsize = %lu, Capacity = %lu\n", (unsigned long)Getsize(hVector), (unsigned long)GetCapacity(hVector));
	printf("------------------------\n");
}

int main(void) {

	HVECTOR hVector;
	int i;

	if ((hVector = CreateVector()) == NULL)
	{
		fprintf(stderr, "Cannot create vector!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; ++i)
		AddItem(hVector, i);
	DispVector(hVector);

	int item = 25000;
	InsertItem(hVector, 5, item);
	DispVector(hVector);

	DeleteItem(hVector, 5);
	DispVector(hVector);

	InsertItem(hVector, 5, item);
	DispVector(hVector);

	size_t findedOfIndex = FindItem(hVector, item);
	printf("Item %d index is %d\n", item, findedOfIndex);
	printf("%d. item is: %d\n", findedOfIndex, GetItem(hVector, findedOfIndex));
	printf("------------------------\n");

	CloseVector(hVector);

	return 0;
}

#endif
