#include <stdio.h>
#include "utils.h"

/* Helper Functions */
void printStatement(Statement* statement) {
	printLabel(statement->lhs_label);
	printAssignmentOperator(statement->op);	
}

void printStatement(Label* label) {
	// If label name is NULL, it's a literal
	if (label->name == 0) {
		printf("LITERAL:\n");
	} else {
		printf("LABEL: %s\n", label->name);
	}
	
	// Check what kind of type it is
	switch(label->scalarType) {
		
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
