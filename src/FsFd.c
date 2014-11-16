#include <stdio.h>
#include "FsFd.h"
#include "StringObject.h"
#include "string.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Interpret.h"
#include "ExtractValue.h"

/**
 *	FSFD
 *	
 *	To generate the opcode based on the operand1 and operand2. The operand2 is 
 *	to get the value and shifted to left 16 times and return. The operand1 is 
 *	to get the value and return.
 *
 *	Input 	:
 *		arguments
 *
 *	Return	:
 *		opcode
 **/
int FSFD(String *arguments){
	int operand1;
	int operand2;
	int opcode;
	
	operand1 = operand1ExtractValue(arguments);
	operand2 = operand1ExtractValue(arguments);
	
	return opcode = (0x0<<24) + (operand2<<16) + (0x0<<8) + (operand1);
}

