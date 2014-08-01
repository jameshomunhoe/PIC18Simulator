#include <stdio.h>
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"


int executeBC(unsigned int code){
	signed char skipAmount = code & 0xff;
	int programCounter, carryBit = 0;
	
	programCounter = fileRegisters[PCLATU]<<16 + 
					 fileRegisters[PCLATH]<<8 + 
					 fileRegisters[PCL];
					 
	carryBit = fileRegisters[STATUS] & 0x1;
	
	if(carryBit)
		programCounter += 2 + (2*skipAmount);
	else
		programCounter += 2;
		
	fileRegisters[PCLATU] = (programCounter & 0xff0000) >> 16;
	fileRegisters[PCLATH] = (programCounter & 0xff00) >> 8;
	fileRegisters[PCL]	  = (programCounter & 0xff);
	
}

int executeBNC(unsigned int code){}
int executeBNZ(unsigned int code){}
int executeBRA(unsigned int code){}
int executeBZ(unsigned int code){}
int executeCALL(unsigned int code){}

int executeConditionalBranch(unsigned int code){

	int instruction = (code & 0xfc00)>>10;

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