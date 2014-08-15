#include <stdio.h>
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "Extract3BitsValue.h"




int extract3BitsValue(String *arguments){
	ErrorCode error;
	int operand2;
	
	Try{
		operand2 = extractValue(arguments);
	}Catch(error){
		if(error == ERR_NO_ARGUMENT){
				Throw(error);
		}else if(error != ERR_EMPTY_ARGUMENT){
			if(error == ERR_ILLEGAL_ARGUMENT){
				Throw(error);
			}
		}
	}
	
	return operand2;
}