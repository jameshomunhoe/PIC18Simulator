#include <stdio.h>
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"



int executeInstruction(int code){
	
	executionTable[(code & 0xFC00)>>10](code);

}

int executeBC(unsigned int code){
	signed char skipAmount = code & 0xff;
	int programCounter, carryBit = 0;
	
	
	programCounter = getProgramCounter();
	carryBit = fileRegisters[STATUS] & 0x1;
	
	if(carryBit)
		programCounter += 2 + (2*skipAmount);
	else
		programCounter += 2;
		
	setProgramCounter(programCounter);
	
	return programCounter;
	
}

int executeBNC(unsigned int code){}
int executeBNZ(unsigned int code){}
int executeBRA(unsigned int code){}
int executeBZ(unsigned int code){}
int executeCALL(unsigned int code){}

int executeConditionalBranch(unsigned int code){

	int instruction = (code & 0xff00)>>8;	
	
	switch(instruction){
	
	case 0xe2:
	executeBC(code);
	break;
	
	case 0xe3:
	executeBNC(code);
	break;
	
	case 0xe1:
	executeBZ(code);
	break;
	
	case 0xec:
	executeCALL(code);
	break;
	
	case 0xed:
	executeCALL(code);
	break;
	
	}
}





int executeBCF(unsigned int code){

}

int executeBSF(unsigned int code){

}

int executeBTFSC(unsigned int code){

}

int executeBTFSS(unsigned int code){

}

int executeBTG(unsigned int code){

}

int executeSUBWF(unsigned int code){

}

int executeSUBWFB(unsigned int code){

}

int executeSWAPF(unsigned int code){

}

int executeTSTFSZ(unsigned int code){

}

int executeXORWF(unsigned int code){

}