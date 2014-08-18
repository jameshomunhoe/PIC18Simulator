#include <stdio.h>
#include "NS.h"
#include "Extract1BitsValue.h"
#include "ExtractValue.h"
#include "Interpret.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"

/**
 *	NS
 *	
 *	To generate the opcode is based on the operand1 and operand2. The operand1
 *	is get the value and shifted to left 16 times and return. After that get the 
 *	operand1 and mask with 0xff and return. The operand2 is get the value and 
 *	shifted to left 8 times and return. Shift 0 to left 24 times
 *
 *	Input 	:
 *		arguments
 *
 *	Return	:
 *		opcode
 **/
int NS(String *arguments){
	int operand1;
	int operand2;
	int opcode;
	
	operand1 = operand1ExtractValue(arguments);
	operand2 = operandExtract1BitsValue(arguments);
	
	return opcode = ((operand1&0xfff00)<<8) | (operand2<<8) | (operand1 & 0xff);


}


