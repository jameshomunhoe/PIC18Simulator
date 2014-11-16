#include <stdio.h>
#include "FDA.h"
#include "Interpret.h"
#include "StringObject.h"
#include "string.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ExtractValue.h"
#include "Extract1BitsDestination.h"
#include "Extract1BitsAccessBanked.h"

/*
*	FDA 
*	
*	Operation:
*		operand1 take LSB 0 to 7 bit value
*		operand2 take LSB bit 8 value
*		operand3 take LSB bit 9 value
*
*	Return:
*		opcode value
*
*/
int FDA(String *arguments){
	int operand1,operand2,operand3;
	int opcode;
	ErrorCode error;
		
	operand1 = operand1ExtractValue(arguments);
	operand2 = extract1BitsDestination(arguments);
	operand3 = extract1bitsACCESSBANKED(arguments,operand1);

	
	operand1 = operand1&0xff;
	
	
	if(operand2%2 != 0){
		operand2 = 0x1;
	}else{
		operand2 = 0x0;
	}

	if(operand3%2 != 0){
		operand3 = 0x1;
	}else{
		operand3 = 0x0;
	}
	

	opcode = operand1 + (operand3<<8) + (operand2<<9) ;
		
	return opcode ;
}
















