#include <stdio.h>
#include "FsFd.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Extract.h"
#include "ExtractValue.h"

int FSFD(String *arguments){
	int operand1;
	int operand2;
	int opcode;
	
	operand1 = operand1ExtractValue(arguments);
	operand2 = operand1ExtractValue(arguments);
	
	return opcode = (0x0<<24) + (operand2<<16) + (0x0<<8) + (operand1);
}

