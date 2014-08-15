#include <stdio.h>
#include "ExtractValue.h"
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"



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