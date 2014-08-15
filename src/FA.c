#include <stdio.h>
#include "FA.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Extract.h"
#include "ExtractValue.h"
#include "Extract1BitsAccessBanked.h"

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

