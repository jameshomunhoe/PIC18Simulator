#include <stdio.h>
#include "FBA.h"
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "ExtractValue.h"
#include "Extract3BitsValue.h"
#include "Extract1BitsAccessBanked.h"




int FBA(String *arguments){
	int operand1,operand2,operand3;
	int opcode;
	ErrorCode error;
		
	operand1 = operand1ExtractValue(arguments);
	operand2 = extract3BitsValue(arguments);
	operand3 = extract1bitsACCESSBANKED(arguments,operand1);


	operand1 = operand1&0xff;

	operand2 = operand2&7;

	if(operand3%2 != 0){
		operand3 = 1;
	}else{
		operand3 = 0;
	}
	opcode = operand1 + (operand3<<8) + (operand2<<9) ;
	return opcode;
}