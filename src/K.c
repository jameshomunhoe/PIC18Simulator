#include <stdio.h>
#include "K.h"
#include "Interpret.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ExtractValue.h"

/*
*	K
*	
*	Operation:
*		operand1 take LSB 0 to 7 bit value
*
*	Return:
*		opcode value
*
*/
int K(String *arguments){
	int operand1,operand2,operand3;
	int opcode;
	ErrorCode error;
		
	operand1 = operand1ExtractValue(arguments);

	operand1 = operand1&0xff;

	return opcode = operand1;
}