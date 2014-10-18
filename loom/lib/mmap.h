#ifndef __LOOM_MMMAP_H
#define __LOOM_MMAP_H
#define NULL 0

typedef enum {
	INT, LONG, DOUBLE, STRING, ARRAY, HASH, CODE, CALL, THREAD, IO
} EntityType;

typedef struct {
	char*	   name;
	void*	   data;
	EntityType type;
	int	   size;
} Entity;

Entity createIntegerEntity(int value);
Entity createLongEntity(long value);
Entity createDoubleEntity(double value);
Entity createStringEntity(char* value, int size);
Entity createArrayEntity(void* data, int size);
Entity createHashEntity(char** keys, void** values, int size, int valueSize);
#endif
