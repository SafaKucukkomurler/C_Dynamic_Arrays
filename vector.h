#ifndef VECTOR_H_ 
#define VECTOR_H_

#include <stddef.h>
#include <stdbool.h>

//#define USE_MACROS

#define DEFAULT_CAPACITY    (2)

/* Type Declarations */
typedef struct {
	void* pArray;
	size_t typeSize;
	size_t size;
	size_t capacity;
} VECTOR, *HVECTOR;

#ifdef USE_MACROS
#define GetItem(hVector, index)       ((hVector)->pArray[(index)])
#define GetSize(hVector)              ((hVector)->size)
#define GetCapacity(hVector)          ((hVector)->capacity)
#define SetItem(hVector, index, val)  ((hVector)->pArray[(index)] = (val))
#define Clear(hVector)                ((hVector)->size = 0)
#endif

/* Function Prototypes */
HVECTOR CreateVectorWithCapacity(size_t typeSize, size_t capacity);
HVECTOR CreateVector(size_t typeSize);
void CloseVector(HVECTOR hVector);
bool AddItem(HVECTOR hVector, const void* pVal);
bool InsertItem(HVECTOR hVector, size_t index, const void* pVal);
bool DeleteItem(HVECTOR hVector, size_t index);
size_t FindItem(HVECTOR hVector, const void* pVal);
//void* FindItem(HVECTOR hVector, const void* pVal);
void Clear(HVECTOR hVector);

#ifndef USE_MACROS
void GetItem(HVECTOR hVector, size_t index, void* pVal);
void SetItem(HVECTOR hVector, const void* pVal, size_t index);
void* GetArray(HVECTOR hVector);
size_t Getsize(HVECTOR hVector);
size_t GetCapacity(HVECTOR hVector);
#endif

bool SetCapacity(HVECTOR hVector, size_t capacity);

#endif
