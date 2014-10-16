/* Helper Functions */
void printStatement(Statement* statement) {
	printf("\tLABEL: %s\n", temp->lhs_label);
	printAssignmentOperator(temp->op);	
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
