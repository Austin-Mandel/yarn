#include <stdio.h>
#include "utils.h"

/* Helper Functions */
void printStatement(Statement* statement) {
	printLabel(statement->lhs_label);
	printAssignmentOperator(statement->op);	
}


void printArray(void* array) {

}

void printHash(void *hash) {

}

void printCall(void *call) {

}

void printCodeBlockMeta(void *code) {

}

void printLabel(Label* label) {
	// If label name is NULL, it's a literal
	if (label->name == 0) {
		printf("LITERAL:\n");
	} else {
		printf("LABEL: %s\n", label->name);
	}
	
	// Check what kind of type it is
	switch(label->type) {
	case INT_T:
		// Integer (signed)
		printf("VALUE: %d\n", (int) *label->scalar);
		break; 
	case LONG_T:
		// Long Integer (unsigned)
		printf("VALUE: %lu\n", (int) *label->scalar);
		break;
	case DOUBLE_T:
		// Double floating point value
		printf("VALUE: %e\n", (double) *label->scalar);
		break;
	case STRING_T:
		// A string
		printf("VALUE: %s\n", (char*) label->scalar);
		break;
	case ARRAY_T:
		// An array, so this is the length.
		printf("ARRAY.\nLENGTH: %u", (unsigned int) *label->scalar);
		// Print the array data
		printArray(label->data);
		break;
	case HASH_T:
		// A hash, so this is it's size.
		printf("HASH.\n# OF ENTRIES: %u", (unsigned int) *label->scalar);
		// Print the hash out
		printHash(label->data);
		break;
	case CALL_T:
		// This is a call, so check if it has a thread
		if (label->scalar == 0) {
			printf("LOCAL CALL:\n");
		} else {
			printf("CALL ON THREAD:");
			Label* thread_lbl = (Label*) label->scalar;
			printf("%s\n", (char*) thread_lbl->scalar);
		}
		// Print the call data
		printCall(label->data);
		break;
	case CODE_T:
		// A block of code.
		if (label->scalar == 0) {
			printf("ANONYMOUS CODE BLOCK:\n");
		} else {
			printf("CODE BLOCK: %s:\n", (char*) label->scalar);
		}
		// Print some metadata
		printCodeBlockMeta(label->data);
		break;
	case THREAD_T:
		printf("THREAD: %s\n", (char*) label->scalar);
		break; 
	default:
		printf("UNKNOWN LABEL TYPE.");	
	}
}

void printAssignmentOperator(AssignmentOperator op) {
	switch(op) {
	case VOID:
		printf("\tVOID ASSIGNMENT\n");
		break;
	case ASSIGN:
		printf("\tASSIGNED TO:\n");
		break;
	case APPEND:
		printf("\tAPPENDED WITH:\n");
		break;
	case REMOVE:
		printf("\tREMOVE:\n");
		break;
	case SLICE:
		printf("\tSLICED BY:\n");
		break;
	case MULTIPLY:
		printf("\tMULTIPLIED BY:\n");
		break;
	default:
		printf("\tUNKOWN OPERATION.\n");
	}
}
