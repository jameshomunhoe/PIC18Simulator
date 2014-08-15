#include <stdio.h>
#include "K.h"
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ExtractValue.h"


int K(String *arguments){
	int operand1,operand2,operand3;
	int opcode;
	ErrorCode error;
		
	operand1 = operand1ExtractValue(arguments);

	operand1 = operand1&0xff;

	return opcode = operand1;
}