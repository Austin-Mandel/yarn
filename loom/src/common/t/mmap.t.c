#include "mmap.h"
#include <stdlib.h>
#include <stdio.h>

// Entity createIntegerEntity(char* name, int value)

int main() {
	printf("Testing mmap.c\n");
	printf("Testing Entity createIntegerEntity()\n");
	Entity testIntEnt = createIntegerEntity(128);
	printf("%d\n", *((int*)testIntEnt.data));

	printf("Testing Entity createLongEntity()\n");
	Entity testLongEnt = createLongEntity(128*128*128*128*2);
	printf("%ld\n", *((long*)testLongEnt.data));

	printf("Testing Entity createDoubleEntity()\n");
	Entity testDoubleEnt = createDoubleEntity(3.14);
	printf("%f\n", *((double*)testDoubleEnt.data));

	printf("Testing Entity createStringEntity()\n");
	Entity testStringEnt = createStringEntity("hello world", 12);
	printf("%s\n", (char*) testStringEnt.data);

	printf("Testing Entity createArrayEntity()\n");
	char* testarr[] = {"abc", "332", "test"};
	Entity testArrayEnt = createArrayEntity(testarr, 3);
	printf("\t0: %s\n", ((char**)testArrayEnt.data)[0]);
	printf("\t1: %s\n", ((char**)testArrayEnt.data)[1]);
	printf("\t2: %s\n", ((char**)testArrayEnt.data)[2]);

	printf("Testing Entity createArrayEntity()\n");
	char* testarr[] = {"abc", "332", "test"};
	Entity testArrayEnt = createArrayEntity(testarr, 3);
	printf("\t0: %s\n", ((char**)testArrayEnt.data)[0]);
	printf("\t1: %s\n", ((char**)testArrayEnt.data)[1]);
	printf("\t2: %s\n", ((char**)testArrayEnt.data)[2]);

	printf("Testing Entity createHashEntity()\n");
	char* testarr[] = {"abc", "332", "test"};
	Entity testArrayEnt = createArrayEntity(testarr, 3);
	printf("\t0: %s\n", ((char**)testArrayEnt.data)[0]);
	printf("\t1: %s\n", ((char**)testArrayEnt.data)[1]);
	printf("\t2: %s\n", ((char**)testArrayEnt.data)[2]);

	return 0;
}
