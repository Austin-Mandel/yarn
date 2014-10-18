/* Mmap.c
 *
 * This file contains utilities for creating and refining memory structures from 
 * parsed code.
 */
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "mmap.h"
#include "MurmurHash3.h"

Entity createIntegerEntity(int value) {
	Entity entity;
	entity.data = malloc(sizeof(int));
	assert(entity.data != NULL);
	*(int*)entity.data = value;
	entity.size = sizeof(int);
	entity.type = INT;
	return entity;
}

Entity createLongEntity(long value) {
	Entity entity;
	entity.data = malloc(sizeof(long));
	assert(entity.data != NULL);
	*(long*)entity.data = value;
	entity.size = sizeof(long);
	entity.type = LONG;
	return entity;
}

Entity createDoubleEntity(double value) {
	Entity entity;
	entity.data = malloc(sizeof(double));
	assert(entity.data != NULL);
	*(double*)entity.data = value;
	entity.size = sizeof(double);
	entity.type = DOUBLE;
	return entity;
}

Entity createStringEntity(char* value, int size) {	
	Entity entity;
	entity.data = (void*)strdup(value);
	entity.size = size;
	entity.type = STRING;
	return entity;
}

Entity createArrayEntity(void* data, int size) {	
	Entity entity;
	entity.data = data;
	entity.size = size;
	entity.type = ARRAY;
	return entity;
}

// MurmurHash3_x64_128 ( const void * key, int len, uint32_t seed, void * out );

Entity createHashEntity(int size) {
	Entity entity;
	entity.data = malloc(size*2+1);
	srand((unsigned) time(&t));
	((unsigned int*)entity.data)[0] = rand();
	assert(entity.data != NULL);
	entity.size = size+1;
	entity.type = HASH;
	return entity;
}

void hash_put(Entity entity, char* key, void* value, int keyLength) {
	int code;
	MurmurHash3_x64_128(key, keyLength, (uint32_t)entity.data[0], code); 
}
