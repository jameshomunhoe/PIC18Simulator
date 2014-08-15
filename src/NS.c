#include <stdio.h>
#include "NS.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Extract.h"
#include "ExtractValue.h"
#include "Extract1BitsValue.h"

int NS(String *arguments){
	int operand1;
	int operand2;
	int opcode;
	
	operand1 = operand1ExtractValue(arguments);
	operand2 = operandExtract1BitsValue(arguments);
	
	return opcode = (0x0<<24) + (operand1<<16) + (operand2<<8) + (operand1 & 0xff);


}


