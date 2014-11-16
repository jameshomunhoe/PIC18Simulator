#include <stdio.h>
#include "S.h"
#include "StringObject.h"
#include "string.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Interpret.h"
#include "Extract1BitsValue.h"

/**
 *	S
 *	
 *	To generate the opcode based on the operand1. The operand1 is to get the 
 *	value and return.
 *
 *	Input 	:
 *		arguments
 *
 *	Return	:
 *		opcode
 **/
int S(String *arguments){
	int operand1;
	int opcode;
	
	operand1 = operandExtract1BitsValue(arguments);
	
	
	return opcode = operand1;
}
