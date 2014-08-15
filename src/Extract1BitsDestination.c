#include <stdio.h>
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "Extract1BitsDestination.h"

int extract1BitsDestination(String *arguments){
	ErrorCode error;
	int operand2;
	
	Try{
		operand2 = extractDestination(arguments);
	}Catch(error){
		if(error == ERR_NO_ARGUMENT){
				operand2 = 0x1;
		}else if(error != ERR_EMPTY_ARGUMENT){
			if(error == ERR_ILLEGAL_ARGUMENT){
					Throw(error);
			}
		}
	}
	
	return operand2;
}