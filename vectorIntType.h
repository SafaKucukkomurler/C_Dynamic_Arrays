#ifndef VECTOR_INT_TYPE_H_ 
#define VECTOR_INT_TYPE_H_
 
#include <stddef.h>
#include <stdbool.h>

//#define USE_MACROS
 
#define DEFAULT_CAPACITY    (2)
 
/* Type Declarations */ 
typedef struct {     
	int *pArray;     
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
HVECTOR CreateVectorWithCapacity(size_t capacity); 
HVECTOR CreateVector(void); 
void CloseVector(HVECTOR hVector); 
bool AddItem(HVECTOR hVector, int val); 
bool InsertItem(HVECTOR hVector, size_t index, int val); 
bool DeleteItem(HVECTOR hVector, size_t index);
size_t FindItem(HVECTOR hVector, int val);
void Clear(HVECTOR hVector); 

#ifndef USE_MACROS
int GetItem(HVECTOR hVector, size_t index); 
void SetItem(HVECTOR hVector, size_t index, int val); 
int *GetArray(HVECTOR hVector); 
size_t Getsize(HVECTOR hVector); 
size_t GetCapacity(HVECTOR hVector); 
#endif

bool SetCapacity(HVECTOR hVector, size_t capacity); 

#endif