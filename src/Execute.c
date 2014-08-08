#include <stdio.h>
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"
#include "Types.h"


uint32 maskTable[32] = { 	0x0, 
							0x1, 0x3, 0x7, 0xf, 
							0x1f, 0x3f, 0x7f, 0xff,
							0x1ff, 0x3ff, 0x7ff, 0xfff, 
							0x1fff, 0x3fff, 0x7fff, 0xffff, 
							0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 
							0x1fffff, 0x3fffff, 0x7fffff, 0xffffff, 
							0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff, 
							0x1fffffff, 0x3fffffff, 0x7fffffff
						};

uint32 getBitsAtOffset(uint32 data, int offset, int bitSize){
	
	if(offset >= 0 && bitSize > 0){
		if(offset >31)
			offset = 31;
		if(bitSize > 31)
			bitSize = 31;
		
		data = (data >> offset) & maskTable[bitSize];
		
		return data;
	}
	else
		return 0;
}

void setBitsAtOffset(uint32 *dataPtr, uint32 dataToWrite, int offset, int bitSize){

}

int executeInstruction(int code){

	executionTable[(code & 0xFC00)>>10](code);

}

int executeBC(unsigned int code){
	signed char skipAmount = getBitsAtOffset(code,0,8);
	int programCounter, carryBit = 0;
	
	
	programCounter = getProgramCounter();
	carryBit = getBitsAtOffset(fileRegisters[STATUS],0,1);
	
	if(carryBit)
		programCounter += 2 + (2*skipAmount);
	else
		programCounter += 2;
		
	setProgramCounter(programCounter);
	
	return programCounter;
	
}

int executeBNC(unsigned int code){
	signed char skipAmount = getBitsAtOffset(code,0,8);
	int programCounter, carryBit = 0;
	
	
	programCounter = getProgramCounter();
	carryBit = getBitsAtOffset(fileRegisters[STATUS],0,1);
	
	if(carryBit)
		programCounter += 2;
	else
		programCounter += 2 + (2*skipAmount);
		
	setProgramCounter(programCounter);
	
	return programCounter;
	
}
	
int executeBZ(unsigned int code){
	signed char skipAmount = getBitsAtOffset(code,0,8);
	int programCounter, zeroBit = 0;
	
	
	programCounter = getProgramCounter();
	zeroBit = getBitsAtOffset(fileRegisters[STATUS],2,1);
	
	if(zeroBit)
		programCounter += 2 + (2*skipAmount);
	else
		programCounter += 2;
		
	setProgramCounter(programCounter);
	
	return programCounter;

}

int executeBNZ(unsigned int code){
	signed char skipAmount = getBitsAtOffset(code,0,8);
	int programCounter, zeroBit = 0;
	
	
	programCounter = getProgramCounter();
	zeroBit = getBitsAtOffset(fileRegisters[STATUS],2,1);
	
	if(zeroBit)
		programCounter += 2;
	else
		programCounter += 2 + (2*skipAmount);
		
	setProgramCounter(programCounter);
	
	return programCounter;
	
}

int executeBRA(unsigned int code){
	int skipAmount = getBitsAtOffset(code,0,11);
	int programCounter = getProgramCounter();
	int negativeValue = ((~skipAmount) + 1) & 0x3ff;
		
	if((skipAmount & 0x400)>>10 == 1)
		programCounter = programCounter + 2 - (2*negativeValue);
	else
		programCounter = programCounter + 2 + (2*skipAmount);
	
	setProgramCounter(programCounter);
	
	return programCounter;
}

int executeMOVWF(unsigned int code){

	fileRegisters[findActualFileRegister(getBitsAtOffset(code,0,8),
				  getBitsAtOffset(code,8,1))] 
				  = fileRegisters[WREG];

}

int executeNEGF(unsigned int code){
	
	int fileValue,fileAddress,accessBanked;
	fileAddress = getBitsAtOffset(code,0,8);
	accessBanked = getBitsAtOffset(code,8,1);
	
	fileValue = getFileRegData(fileAddress,accessBanked);
	fileValue = ~fileValue+1;
	setFileRegData(fileAddress,accessBanked,fileValue);
	
	return fileValue;
}

int executeCALL(unsigned int code){}
int executeRLCF(unsigned int code){}
int executeRRNCF(unsigned int code){}
int executeADDWF(unsigned int code){}

int executeConditionalBranch(unsigned int code){

	int instruction = (code & 0xff00)>>8;	
	
	switch(instruction){
	
	case 0xe2:
	executeBC(code);
	break;
	
	case 0xe3:
	executeBNC(code);
	break;
	
	case 0xe0:
	executeBZ(code);
	break;
	
	case 0xe1:
	executeBNZ(code);
	break;
	
	case 0xec:
	executeCALL(code);
	break;
	
	case 0xed:
	executeCALL(code);
	break;
	
	}
}

int executeMOVWForNEGF(unsigned int code){
	int instruction = (code & 0xff00)>>8;
	
	switch(instruction){
	
	case 0x6e:
	executeMOVWF(code);
	break;
	
	case 0x6f:
	executeMOVWF(code);
	break;
	
	case 0x6c:
	executeNEGF(code);
	break;
	
	case 0x6d:
	executeNEGF(code);
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