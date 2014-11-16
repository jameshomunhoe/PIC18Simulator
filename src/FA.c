#include <stdio.h>
#include "FA.h"
#include "StringObject.h"
#include "string.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Interpret.h"
#include "ExtractValue.h"
#include "Extract1BitsAccessBanked.h"

/**
 *	FA
 *	
 *	To generate the opcode based on the operand1 and operand2. The operand2 is 
 *	to get the value and shifted to left 8 times and return. The operand1 is 
 *	to get the value and mask and return.
 *
 *	Input 	:
 *		arguments
 *
 *	Return	:
 *		opcode
 **/
int FA(String *arguments){
	int operand1;
	int operand2;
	int opcode;
	
	operand1 = operand1ExtractValue(arguments);
	operand2 = extract1bitsACCESSBANKED(arguments, operand1);
	
	operand1 = operand1 & 0xff;
	
	if(operand2%2 != 0){
		operand2 = 0x1;
	}else{
		operand2 = 0x0;
	}

	
	return opcode = operand1 + (operand2<<8);
}

