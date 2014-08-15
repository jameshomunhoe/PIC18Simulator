#include <stdio.h>
#include "S.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Extract.h"
#include "Extract1BitsValue.h"

int S(String *arguments){
	int operand1;
	int opcode;
	
	operand1 = operandExtract1BitsValue(arguments);
	
	return opcode = operand1;
}
