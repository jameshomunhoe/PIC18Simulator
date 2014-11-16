#include <stdio.h>
#include "Extract.h"
#include "StringObject.h"
#include "string.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "Extract1BitsValue.h"

int operandExtract1BitsValue(String *arguments){
	ErrorCode e;
	int operand1;
	
	Try{
		operand1 = extractValue(arguments);
	}Catch(e){ 
        if(e == ERR_NO_ARGUMENT || e == ERR_EMPTY_ARGUMENT){
			operand1 = 0;
			return operand1;
		}else if(e == ERR_ILLEGAL_ARGUMENT){
			Throw(e);
		}
	}
	
	operand1 = operand1 & 0x01;
	
	return operand1;
}