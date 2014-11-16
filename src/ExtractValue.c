#include <stdio.h>
#include "ExtractValue.h"
#include "Interpret.h"
#include "StringObject.h"
#include "string.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"


/*
*	Extract 8bit Value to operand1
*	
*	Operation:
*		if nothing is throw
*
*  Return:
*		operand1 value
*
*/
int operand1ExtractValue(String *arguments){
	ErrorCode error;
	int operand1;
	
	Try{
		operand1 = extractValue(arguments);
	}Catch(error){
			Throw(error);
	}
	
	return operand1;
}