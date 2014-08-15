#include <stdio.h>
#include "Extract.h"
#include "StringObject.h"
#include "String.h"
#include "CustomTypeAssert.h"
#include "CException.h"
#include "ErrorCode.h"
#include "Extract1BitsAccessBanked.h"

int extract1bitsACCESSBANKED(String *arguments,int fileReg){
	ErrorCode error;
	int operand3;

	Try{
		operand3 = extractACCESSBANKED(arguments);
	}Catch(error){
		if(error == ERR_NO_ARGUMENT){
			if((fileReg >= 0x00 && fileReg <= 0x80)||(fileReg >= 0xff0 && fileReg <= 0xfff)){
				operand3 = 0;
			}else{
				operand3 = 1;
			}
		}else if(error != ERR_EMPTY_ARGUMENT){
			if(error == ERR_ILLEGAL_ARGUMENT){
				Throw(error);
			}
		}
	}
	
	return operand3;
}