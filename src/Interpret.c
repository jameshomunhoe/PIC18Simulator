#include <stdio.h>
#include <malloc.h>
#include "unity.h"
#include "Interpret.h"
#include "String.h"
#include "CException.h"
#include "StringObject.h"
#include "Token.h"
#include "Text.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CustomTypeAssert.h"
#include "FA.h"
#include "FBA.h"
#include "FDA.h"
#include "FsFd.h"
#include "K.h"
#include "N.h"
#include "NS.h"
#include "S.h"
#include "Extract1BitsValue.h"
#include "ExtractValue.h"
#include "mock_Evaluate.h"


#define INSTRUCTION_TABLE_SIZE	(sizeof(instructions)/sizeof(instructionTable))


/**
*	This is the instructions table
**/
instructionTable instructions[] = {
	{.instructionName = "ADDWF" , .opCode = 0x2400 , .type = FDA_TYPE},
	{.instructionName = "ADDWFC" , .opCode = 0x2000 , .type = FDA_TYPE},
	{.instructionName = "ANDWF" , .opCode = 0x1400 , .type = FDA_TYPE},
	{.instructionName = "COMF" , .opCode = 0x1C00 , .type = FDA_TYPE},
	{.instructionName = "DECF" , .opCode = 0x0400 , .type = FDA_TYPE},
	{.instructionName = "DECFSZ" , .opCode = 0x2C00 , .type = FDA_TYPE},
	{.instructionName = "DCFSNZ" , .opCode = 0x4C00 , .type = FDA_TYPE},
	{.instructionName = "INCF" , .opCode = 0x2800 , .type = FDA_TYPE},
	{.instructionName = "INCFSZ" , .opCode = 0x3C00 , .type = FDA_TYPE},
	{.instructionName = "INFSNZ" , .opCode = 0x4800 , .type = FDA_TYPE},
	{.instructionName = "IORWF" , .opCode = 0x1000 , .type = FDA_TYPE},
	{.instructionName = "MOVF" , .opCode = 0x5000 , .type = FDA_TYPE},
	{.instructionName = "RLCF" , .opCode = 0x3400 , .type = FDA_TYPE},
	{.instructionName = "RLNCF" , .opCode = 0x4400 , .type = FDA_TYPE},
	{.instructionName = "RRCF" , .opCode = 0x3000 , .type = FDA_TYPE},
	{.instructionName = "RRNCF" , .opCode = 0x4000 , .type = FDA_TYPE},
	{.instructionName = "SUBFWB" , .opCode = 0x5400 , .type = FDA_TYPE},
	{.instructionName = "SUBWF" , .opCode = 0x5C00 , .type = FDA_TYPE},
	{.instructionName = "SUBWFB" , .opCode = 0x5800 , .type = FDA_TYPE},
	{.instructionName = "SWAPF" , .opCode = 0x3800 , .type = FDA_TYPE},
	{.instructionName = "XORWF" , .opCode = 0x1800 , .type = FDA_TYPE},
	{.instructionName = "CLRF" , .opCode = 0x6A00 , .type = FA_TYPE},
	{.instructionName = "CPFSEQ" , .opCode = 0x6200 , .type = FA_TYPE},
	{.instructionName = "CPFSGT" , .opCode = 0x6400 , .type = FA_TYPE},
	{.instructionName = "CPFSLT" , .opCode = 0x6000 , .type = FA_TYPE},
	{.instructionName = "MOVWF" , .opCode = 0x6E00 , .type = FA_TYPE},
	{.instructionName = "MULWF" , .opCode = 0x0200 , .type = FA_TYPE},
	{.instructionName = "NEGF" , .opCode = 0x6C00 , .type = FA_TYPE},
	{.instructionName = "SETF" , .opCode = 0x6800 , .type = FA_TYPE},
	{.instructionName = "TSTFSZ" , .opCode = 0x6600 , .type = FA_TYPE},
	{.instructionName = "BCF" , .opCode = 0x9000 , .type = FBA_TYPE},
	{.instructionName = "BSF" , .opCode = 0x8000 , .type = FBA_TYPE},
	{.instructionName = "BTFSC" , .opCode = 0xB000 , .type = FBA_TYPE},
	{.instructionName = "BTFSS" , .opCode = 0xA000 , .type = FBA_TYPE},
	{.instructionName = "BTG" , .opCode = 0x7000 , .type = FBA_TYPE},
	{.instructionName = "MOVFF" , .opCode = 0xF000C000 , .type = FSFD_TYPE},
	{.instructionName = "BC" , .opCode = 0xE200 , .type = N8_TYPE},
	{.instructionName = "BN" , .opCode = 0xE600 , .type = N8_TYPE},
	{.instructionName = "BNC" , .opCode = 0xE300 , .type = N8_TYPE},
	{.instructionName = "BNN" , .opCode = 0xE700 , .type = N8_TYPE},
	{.instructionName = "BNOV" , .opCode = 0xE500 , .type = N8_TYPE},
	{.instructionName = "BNZ" , .opCode = 0xE100 , .type = N8_TYPE},
	{.instructionName = "BOV" , .opCode = 0xE400 , .type = N8_TYPE},
	{.instructionName = "BRA" , .opCode = 0xD000 , .type = N11_TYPE},
	{.instructionName = "BZ" , .opCode = 0xE000 , .type = N12_TYPE},
	{.instructionName = "GOTO" , .opCode = 0xF000EF00 , .type = N12_TYPE},
	{.instructionName = "RCALL" , .opCode = 0xD800 , .type = N11_TYPE},
	{.instructionName = "CALL" , .opCode = 0xF000EC00 , .type = NS_TYPE},
	{.instructionName = "RETFIE" , .opCode = 0x0010 , .type = S_TYPE},
	{.instructionName = "RETURN" , .opCode = 0x0012 , .type = S_TYPE},
	{.instructionName = "RETLW" , .opCode = 0x0C00 , .type = K_TYPE},
	{.instructionName = "ADDLW" , .opCode = 0x0F00 , .type = K_TYPE},
	{.instructionName = "ANDLW" , .opCode = 0x0B00 , .type = K_TYPE},
	{.instructionName = "IORLW" , .opCode = 0x0900 , .type = K_TYPE},
	{.instructionName = "MOVLB" , .opCode = 0x0100 , .type = K_TYPE},
	{.instructionName = "MOVLW" , .opCode = 0x0E00 , .type = K_TYPE},
	{.instructionName = "MULLW" , .opCode = 0x0C00 , .type = K_TYPE},
	{.instructionName = "SUBLW" , .opCode = 0x0C00 , .type = K_TYPE},
	{.instructionName = "XORLW" , .opCode = 0x0C00 , .type = K_TYPE},
	{.instructionName = "LFSR" , .opCode = 0xF000EE00 , .type = FK_TYPE}

};


/**
*	Top module to extract the whole string into final OpCode
*
* Input:
*	String	instructions,with appropriate arguments
*
* Return OpCode in int type
*/
unsigned int interpret(String *instruction){
	stringTrimLeft(instruction);
	String *instString = stringRemoveWordNotContaining(instruction," ");
	char *instChar = stringSubstringInChar(instString,0,instString->length);
	instructionTable inst = getInstruction(instChar);

	if(inst.type == FDA_TYPE)
		return inst.opCode | FDA(instruction);
	else if(inst.type == FBA_TYPE)
		return inst.opCode | FBA(instruction);
	else if(inst.type == FA_TYPE)
		return inst.opCode | FA(instruction);
	else if(inst.type == FSFD_TYPE)
		return inst.opCode | FSFD(instruction);
	else if(inst.type == N8_TYPE)
		return inst.opCode | N8(instruction);	
	else if(inst.type == N11_TYPE)
		return inst.opCode | N11(instruction);	
	else if(inst.type == N12_TYPE)
		return inst.opCode | N12(instruction);
	else if(inst.type == NS_TYPE)
		return inst.opCode | NS(instruction);
	else if(inst.type == S_TYPE)
		return inst.opCode | S(instruction);
	else if(inst.type == K_TYPE)
		return inst.opCode | K(instruction);
	else
		Throw(ERR_ILLEGAL_ARGUMENT);
}


/**
* To assist interpret to get the instructionInfo by name from the table
*
* Input:
*	char	the instruction name
*
* Return the instructions in instructionTable type
*/
instructionTable getInstruction(char *instructionName){
	int i;

	for(i=0;i < INSTRUCTION_TABLE_SIZE; i++){
		if(strcmp(instructions[i].instructionName,instructionName) == 0){
			return instructions[i];
		}
	}
	Throw(ERR_ILLEGAL_ARGUMENT);
}


/**
* To extract the argument of address
*
* Input:
*	String	the whole argument
*
* Return the value of the address
* Throw if value is invalid
*/
int extractValue(String *arguments){

	char *returnChar;
	int returnInt;
	String *string;
	stringTrimLeft(arguments);

	if(stringCharAt(arguments,0) == ',')
		stringRemoveChar(arguments);

	if(stringCharAt(arguments,0) == ';' || stringLength(arguments) == 0)
		Throw(ERR_NO_ARGUMENT);

	string = stringRemoveWordNotContaining(arguments,",;");
	stringTrim(string);

	if(stringLength(string) == 0)
		Throw(ERR_EMPTY_ARGUMENT);

	returnChar = stringSubstringInChar(string,0,string->length);
	returnInt = evaluate(returnChar);


	free(string);

	return returnInt;
} //pass to jason


/**
* To extract the argument of location to save
*
* Input:
*	String	the whole argument
*
* Return the value of the location
* Throw if value is invalid
*/
int extractDestination(String *arguments){


	char location;
	char *returnChar;
	int returnInt;
	String *string;

	if(stringCharAt(arguments,0) == ',')
		stringRemoveChar(arguments);

	if(stringLength(arguments) == 0 ||stringCharAt(arguments,0) == ';')
		Throw(ERR_NO_ARGUMENT);

	stringTrimLeft(arguments);

	if(stringLength(arguments) == 0 || stringCharAt(arguments,0)== ';')
		Throw(ERR_EMPTY_ARGUMENT);

	string = stringRemoveWordNotContaining(arguments,",;");
	stringTrim(string);

	if(stringLength(string) == 0){
		if(stringCharAt(arguments,0) == ',')
			stringRemoveChar(arguments);
		Throw(ERR_EMPTY_ARGUMENT);
	}

	else if(stringLength(string) == 1){
		location = stringCharAt(string,0);
		if(location == 'F')
			returnInt = 1;
		else if(location == 'W')
			returnInt = 0;
		else{
			returnChar = stringSubstringInChar(string,0,string->length);
			returnInt =  evaluate(returnChar);
		}
	}
	else{
		returnChar = stringSubstringInChar(string,0,string->length);
		returnInt = evaluate(returnChar);
	}


	free(string);
	return returnInt;


}//if f, return 1, w is 0


/**
* To extract the argument of access or banked
*
* Input:
*	String	the whole argument
*
* Return the value of access/banked
* Throw if value is invalid
*/
int extractACCESSBANKED(String *arguments){
	char location;
	char *returnChar;
	int returnInt;
	String *string;
	String *banked = stringNew(textNew("BANKED")); //1
	String *access = stringNew(textNew("ACCESS")); //0

	if(stringCharAt(arguments,0) == ',')
		stringRemoveChar(arguments);

	if(stringLength(arguments) == 0 ||stringCharAt(arguments,0) == ';')
		Throw(ERR_NO_ARGUMENT);

	stringTrimLeft(arguments);

	if(stringLength(arguments) == 0 ||stringCharAt(arguments,0) == ';')
		Throw(ERR_EMPTY_ARGUMENT);

	string = stringRemoveWordNotContaining(arguments,",;");

	stringTrim(string);

	if(stringLength(string) == 0){
		if(stringCharAt(arguments,0) == ',')
			stringRemoveChar(arguments);
		Throw(ERR_EMPTY_ARGUMENT);
	}

	else if(stringLength(string) == 6){

		if(stringIsEqual(string,banked))
			returnInt = 1;
		else if(stringIsEqual(string,access))
			returnInt = 0;
		else{
			returnChar = stringSubstringInChar(string,0,string->length);
			returnInt =  evaluate(returnChar);
		}
	}
	else{
		returnChar = stringSubstringInChar(string,0,string->length);
		returnInt = evaluate(returnChar);
	}

	if(stringCharAt(arguments,0) == ',')
		stringRemoveChar(arguments);

	free(string);
	return returnInt;

}