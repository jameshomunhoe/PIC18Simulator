#include <stdio.h>
#include "Extract.h"
#include "StringObject.h"
#include "string.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "Extract1BitsDestination.h"

/*
*	Extract Destination to operand2
*	
*	Operation:
*		To Catch No Argument and Empty Argument Value,extract value
*
*	Data:
*		Make operand2 to default value 0x1;
*
*  Return:
*		operand2 value
*
*/
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