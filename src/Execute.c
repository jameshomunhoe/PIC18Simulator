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

	 *dataPtr =  *dataPtr &(~(maskTable[bitSize]<<offset));
	 *dataPtr = *dataPtr|((dataToWrite & maskTable[bitSize]) << offset);

}

void setNegativeFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x10;
}

void clearNegativeFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xef;
}

void setOverFlowFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x08;
}

void clearOverFlowFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xf7;
}

void setZeroFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x04;
}

void clearZeroFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfb;
}

void setDigitalCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x02;
}

void clearDigitalCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfd;
}

void setCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x01;
}

void clearCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfe;
}

void clearAllFlag(){
	clearNegativeFlag();
	clearOverFlowFlag();
	clearZeroFlag();
	clearDigitalCarryFlag();
	clearCarryFlag();
}

uint32 executeInstruction(uint32 code){
	
	if(code < 0x10000){
		executionTable[getBitsAtOffset(code,10,6)](code);
	}
	
	else if(code > 0xffff){		
		executionTable[getBitsAtOffset(code,26,6)](code);
	}
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

int executeRLCF(unsigned int code){
	// 0 to WREG 1 to fileReg
	//C,N,Z
	int fileAddress,accessBanked,destination,carryBit;
	unsigned int fileValue;
	
	fileAddress = getBitsAtOffset(code,0,8);
	accessBanked = getBitsAtOffset(code,8,1);
	destination = getBitsAtOffset(code,9,1);
	carryBit = getBitsAtOffset(fileRegisters[STATUS],0,1);
	
	fileValue = getFileRegData(fileAddress,accessBanked);
	fileValue = (fileValue << 1) + carryBit;
	
	if(destination == 1)
		setFileRegData(fileAddress,accessBanked,getBitsAtOffset(fileValue,0,8));
	else
		fileRegisters[WREG] = getBitsAtOffset(fileValue,0,8);
	
	clearAllFlag();
	
	if(getBitsAtOffset(fileValue,8,1))
		setCarryFlag();
	if(getBitsAtOffset(fileValue,7,1))
		setNegativeFlag();
	if(getBitsAtOffset(fileValue,0,8) == 0)
		setZeroFlag();

}

int executeRRNCF(unsigned int code){
	// 0 to WREG 1 to fileReg
	//N,Z
	int fileAddress,accessBanked,destination,lastBit;
	unsigned int fileValue;
	
	fileAddress = getBitsAtOffset(code,0,8);
	accessBanked = getBitsAtOffset(code,8,1);
	destination = getBitsAtOffset(code,9,1);
	
	fileValue = getFileRegData(fileAddress,accessBanked);
	lastBit = getBitsAtOffset(fileValue,0,1);
	fileValue = fileValue >> 1;
	setBitsAtOffset(&fileValue,lastBit,7,1);
	
	if(destination == 1)
		setFileRegData(fileAddress,accessBanked,getBitsAtOffset(fileValue,0,8));
	else
		fileRegisters[WREG] = getBitsAtOffset(fileValue,0,8);
	
	clearAllFlag();
	
	if(getBitsAtOffset(fileValue,7,1))
		setNegativeFlag();
	if(getBitsAtOffset(fileValue,0,8) == 0)
		setZeroFlag();

}

int executeCALL(unsigned int code){

	uint32 pcDestination,currentPC,topOfStack;
	int shadowBit;
	
	pcDestination = ((getBitsAtOffset(code,0,12))<<8 | getBitsAtOffset(code,16,8));
	shadowBit = getBitsAtOffset(code,24,1);
	currentPC = getProgramCounter();
	
	topOfStack = currentPC + 4;
	fileRegisters[TOSU] = getBitsAtOffset(topOfStack,16,5);
	fileRegisters[TOSH] = getBitsAtOffset(topOfStack,8,8);
	fileRegisters[TOSL] = getBitsAtOffset(topOfStack,0,8);
	
	setProgramCounter(pcDestination);



}
int executeADDWF(unsigned int code){}

int executeConditionalBranch(unsigned int code){

	int instruction;
	
	if(code < 0x10000)
		instruction = getBitsAtOffset(code,8,8);
	
	else if(code > 0xffff)
		instruction = getBitsAtOffset(code,24,8);
	

	
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