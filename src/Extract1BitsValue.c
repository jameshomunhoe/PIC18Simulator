#include <stdio.h>
#include "Extract1BitsValue.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "CException.h"
#include "CustomTypeAssert.h"
#include "Extract.h"
#include "Extract1BitsValue.h"

int operandExtract1BitsValue(String *arguments){
	int operand;
	int e;
	
	Try{
		operand = extractValue(arguments);
	}Catch(e){ 
        if(e == ERR_NO_ARGUMENT || e == ERR_EMPTY_ARGUMENT){
			operand = 0;
			return operand;
		}else if(e == ERR_ILLEGAL_ARGUMENT){
			Throw(e);
		}
	}
	
	operand = 0x01 & operand;
	
	return operand;
}