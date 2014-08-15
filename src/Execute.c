#include <stdio.h>
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"
#include "Types.h"

int address;
int access;
int bit;
int data;
int destinationBit;
int programCounter;
int carry;
int digitalCarry;
int overFlow;
int updateData;

typedef unsigned int uint32;
typedef unsigned short int uint16;

typedef struct afInstruction{
 union{
	uint32 raw;
	struct{
		uint32 address:8;
		uint32 access:1;
		uint32 opcode:7;
		uint32 undefined:16;
	}fragments;
 }code;
}afInstruction;

typedef struct dafInstruction{
 union{
	uint32 raw;
	struct{
		uint32 address:8;
		uint32 access:1;
		uint32 destinationBit:1;
		uint32 opcode:6;
		uint32 undefined:16;
	}fragments;
 }code;
}dafInstruction;

typedef struct bafInstruction{
 union{
	uint32 raw;
	struct{
		uint32 address:8;
		uint32 access:1;
		uint32 bits:3;
		uint32 opcode:4;
		uint32 undefined:16;
	}fragments;
 }code;
}bafInstruction;

typedef struct ffInstruction{
 union{
	uint32 raw;
	struct{
		uint32 srcAddress:12;
		uint32 opcode:4;
		uint32 destAddress:12;
		uint32 nop:4;
	}fragments;
 }code;
}ffInstruction;

/**
*	Table to mask off certain bits for getBitsAtOffset and setBitsAtOffset use
*/
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


/**
*	To get certain amount of Bits from a variable
*
*	Input:
*		Variable to extract the value out
*		Starting bit
*		Size to crop
*
*	A universal function to decode and execute the opCode (for execution use)
*/
uint32 getBitsAtOffset(uint32 data, int offset, int bitSize){

	//set and cap at maximum valid value
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

/**
 *
 *	Not the carry flag of fileRegisters[STATUS] according to the operation of SUBWFB. If
 *	the carry flag of fileRegisters[STATUS] is 0x01 then it should not it become 0x00. If
 *	the carry flag of fileRegisters[STATUS] is 0x00 then it should not it become 0x01.
 *
 *	Return :
 *		carry
 *
 **/
int withdrawPreviousCarryForSUBWFB(){

	fileRegisters[STATUS] = getBitsAtOffset(fileRegisters[STATUS], 0, 1);
	if(fileRegisters[STATUS] == 1){
		carry = 0;
	}else if(fileRegisters[STATUS] == 0){
		carry = 1;
	}

	return carry;
}

/**
 *
 *	Set the carry flag of fileRegisters[STATUS] to 1
 *
 **/
void setNegativeFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x10;
}

/**
 *
 *	Clear the carry flag of fileRegisters[STATUS] to 0
 *
 **/
void clearNegativeFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xef;
}

/**
 *
 *	Set the over flow flag of fileRegisters[STATUS] to 1
 *
 **/
void setOverFlowFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x08;
}

/**
 *
 *	Clear the over flow flag of fileRegisters[STATUS] to 0
 *
 **/
void clearOverFlowFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xf7;
}

/**
 *
 *	Set the zero flag of fileRegisters[STATUS] to 1
 *
 **/
void setZeroFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x04;
}

/**
 *
 *	Clear the zero flag of fileRegisters[STATUS] to 0
 *
 **/
void clearZeroFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfb;
}

/**
 *
 *	Set the digital carry flag of fileRegisters[STATUS] to 1
 *
 **/
void setDigitalCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x02;
}

/**
 *
 *	Clear the digital carry flag of fileRegisters[STATUS] to 0
 *
 **/
void clearDigitalCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfd;
}

/**
 *
 *	Set the carry flag of fileRegisters[STATUS] to 1
 *
 **/
void setCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] |= 0x01;
}

/**
 *
 *	Clear the carry flag of fileRegisters[STATUS] to 0
 *
 **/
void clearCarryFlag(){
	// - - - N OV Z DC C
	fileRegisters[STATUS] &= 0xfe;
}

/**
 *
 *	Get the fileRegisters[STATUS] for negative according to newData. If the newData is 0 then
 *	should go to setNegativeFlag() else should go to clearNegativeFlag().
 *
 *	Input :
 *		newData is the data after the operation
 *
 **/
void checkNegativeStatus(int newData){

	// Negative
	if(getBitsAtOffset(newData, 7, 1) == 1){
		setNegativeFlag();
	}else{
		clearNegativeFlag();
	}

}

/**
 *
 *	Get the fileRegisters[STATUS] for zero according to newData. If the newData is 0 then
 *	should go to setZeroFlag() else should go to clearZeroFlag().
 *
 *	Input :
 *		newData is the data after the operation
 *
 **/
void checkZeroStatus(int newData){

	// Zero
	if(getBitsAtOffset(newData, 0, 8) == 0){
		setZeroFlag();
	}else{
		clearZeroFlag();
	}

}

/**
 *
 *	Get the fileRegisters[STATUS] for carry according to newData. If the newData bit 8 is 1 then
 *	should go to setCarryFlag() else should go to clearCarryFlag().
 *
 *	Input :
 *		newData is the data after the operation
 *
 **/
void checkCarryStatus(int newData){

	// Carry
	if(getBitsAtOffset(newData, 8, 1) == 1){
		setCarryFlag();
	}else{
		clearCarryFlag();
	}
}

void checkOverFlowStatus(int updataData, int overFlow){
	if((updataData >> 8) == 1){
		if(overFlow == 1){
			clearOverFlowFlag();
		}else{
			setOverFlowFlag();
		}
	}else{
		if(overFlow == 1){
			setOverFlowFlag();
		}else{
			clearOverFlowFlag();
		}
	}
}

void checkDigitalCarryStatus(int digitalCarry){
	if(digitalCarry == 1){
		setDigitalCarryFlag();
	}else{
		clearDigitalCarryFlag();
	}
}

/**
*	Clear all status flag
*
*	Input:
*		-
*
*	To clear all STATUS flag bits before setting
*/
void clearAllFlag(){
	clearNegativeFlag();
	clearOverFlowFlag();
	clearZeroFlag();
	clearDigitalCarryFlag();
	clearCarryFlag();
}

/**
*	To execute an instructions
*
*	Input:
*		full opcode
*
*	A universal function to decode and execute the opCode (for execution use)
*/
uint32 executeInstruction(uint32 code){

		executionTable[getBitsAtOffset(code,10,6)](code);

}

/**
 *
 *	Store to destination according to destination bit. If the destinationBit
 *	is 0 (WREG) then the data is stored into the WREG. If is 1 (fileRegister)
 *	then data is stored into the specific fileRegister
 *
 *	Input	:
 *		destinationBit	is the d bit (WREG or fileRegister)
 *		address is the address of fileRegister
 *		access is the a bit(access or banked)
 *		data is the data to write
 *
 *	Return 	:
 *		data
 *
 **/
int storeDestination(int destinationBit, int address, int access, int data){

	if(destinationBit == 0){
		fileRegisters[WREG] = data;
		data = fileRegisters[WREG];
	}else{
		fileRegisters[address] = data;
		data = fileRegisters[address];
		data = setFileRegData(address, access, data);
	}

	return data;

}

/**
 *
 *	Update the program counter + 2 from previous program counter
 *
 **/
void updateProgramCounter(){
	int programCounter;
	
	programCounter = getProgramCounter();
	programCounter += 2;
	setProgramCounter(programCounter);

}

/**
 *
 *	Update the program counter + 4 from previous program counter if data is 0
 *	otherwise update program counter + 2
 *
 *	Input :
 *		data is the data after the operation
 *
 **/
void updateProgramCounterSkipIfClear(int data){
	int programCounter;
	
	programCounter = getProgramCounter();

	if(data == 0){
		programCounter += 4;
	}else{
		programCounter += 2;
	}

	setProgramCounter(programCounter);

}

/**
 *
 *	Update the program counter + 2 from previous program counter if data is 0
 *	otherwise update program counter + 4
 *
 *	Input :
 *		data is the data after the operation
 *
 **/
void updateProgramCounterSkipIfSet(int data){
	int programCounter;
	
	programCounter = getProgramCounter();

	if(data == 0){
		programCounter += 2;
	}else{
		programCounter += 4;
	}

	setProgramCounter(programCounter);

}

/**
*	To execute BNZ instructions
*
*	Input:
*		full opcode
*
*	set the program counter according to the amount from opcode if the CARRY flag is 1
*/
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

/**
*	To execute BNC instructions
*
*	Input:
*		full opcode
*
*	set the program counter according to the amount from opcode if the CARRY flag is 0
*/
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

/**
*	To execute BZ instructions
*
*	Input:
*		full opcode
*
*	set the program counter according to the amount from opcode if the ZERO flag is 1
*/
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

/**
*	To execute BNZ instructions
*
*	Input:
*		full opcode
*
*	set the program counter according to the amount from opcode if the ZERO flag is 0
*/
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

/**
*	To execute BRA instructions
*
*	Input:
*		full opcode
*
*	Set the program counter by adding or subtracting according to the amount given in the opcode
*/
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

/**
*	To execute MOVWF instructions
*
*	Input:
*		full opcode
*
*	Move the value from working register (WREG) to fileRegisters
*/
int executeMOVWF(unsigned int code){

	fileRegisters[findActualFileRegister(getBitsAtOffset(code,0,8),
				  getBitsAtOffset(code,8,1))]
				  = fileRegisters[WREG];

	setProgramCounter(getProgramCounter() + 2);

}

/**
*	To execute NEGF instructions
*
*	Input:
*		full opcode
*
*	2nd's compliment the fileRegister's value
*/
int executeNEGF(unsigned int code){

	int fileValue,fileAddress,accessBanked;
	fileAddress = getBitsAtOffset(code,0,8);
	accessBanked = getBitsAtOffset(code,8,1);

	fileValue = getFileRegData(fileAddress,accessBanked);
	fileValue = ~fileValue+1;
	setFileRegData(fileAddress,accessBanked,fileValue);

	setProgramCounter(getProgramCounter() + 2);

	return fileValue;
}

/**
*	To execute RLCF instructions
*
*	Input:
*		full opcode
*
*	Rotate the fileRegister's value to the left with carryBit in and carryBit out if value exceed 16 bits MSB.
*/
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

	//Status update
	clearAllFlag();

	//C
	if(getBitsAtOffset(fileValue,8,1))
		setCarryFlag();
	//N
	if(getBitsAtOffset(fileValue,7,1))
		setNegativeFlag();
	//Z
	if(getBitsAtOffset(fileValue,0,8) == 0)
		setZeroFlag();

	setProgramCounter(getProgramCounter() + 2);

}

/**
*	To execute RRNCF instructions
*
*	Input:
*		full opcode
*
*	Rotate the fileRegister's value to the right without carryBit.
*/
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

	//Status update
	clearAllFlag();

	//N
	if(getBitsAtOffset(fileValue,7,1))
		setNegativeFlag();
	//Z
	if(getBitsAtOffset(fileValue,0,8) == 0)
		setZeroFlag();

	setProgramCounter(getProgramCounter() + 2);

}

/**
*	To execute CALL instructions
*
*	Input:
*		full opcode
*
*	Set the program counter to the value input, while saving current program counter in TopOfStack.
*/
int executeCALL(unsigned int code){

	uint32 pcDestination,currentPC,topOfStack;
	int shadowBit;

	pcDestination = ((getBitsAtOffset(code,0,8))<<12 | getBitsAtOffset(code,16,12));
	shadowBit = getBitsAtOffset(code,8,1);
	currentPC = getProgramCounter();

	topOfStack = currentPC + 4;
	fileRegisters[TOSU] = getBitsAtOffset(topOfStack,16,5);
	fileRegisters[TOSH] = getBitsAtOffset(topOfStack,8,8);
	fileRegisters[TOSL] = getBitsAtOffset(topOfStack,0,8);
	
	setProgramCounter(pcDestination);

	//shadowRegister part 's = 1'
	if(shadowBit == 1){
	shadowRegister.WREGS = fileRegisters[WREG];
	shadowRegister.BSRS = fileRegisters[BSR];
	shadowRegister.STATUSS = fileRegisters[STATUS];
	}
}

/**
*	To execute ADDWF instructions
*
*	Input:
*		full opcode
*
*	Add the value of the address in opcode with WREG,
*	and save to either one of them depending on the destination requested
*/
int executeADDWF(unsigned int code){

	int fileValue,fileAddress,accessBanked,destination;
	int carryBit8,carry6to7,carry3to4;
	fileAddress = getBitsAtOffset(code,0,8);
	accessBanked = getBitsAtOffset(code,8,1);
	destination = getBitsAtOffset(code,9,1);

	fileValue = getFileRegData(fileAddress,accessBanked);

	//for OV and DC checking
	carryBit8 = (fileValue + fileRegisters[WREG]) >> 8;
	carry6to7 = (getBitsAtOffset(fileValue,0,7) + getBitsAtOffset(fileRegisters[WREG],0,7))>>7;
	carry3to4 = (getBitsAtOffset(fileValue,0,4) + getBitsAtOffset(fileRegisters[WREG],0,4))>>4;

	fileValue += fileRegisters[WREG];

	if(destination == 1)
		setFileRegData(fileAddress,accessBanked,getBitsAtOffset(fileValue,0,8));
	else
		fileRegisters[WREG] = getBitsAtOffset(fileValue,0,8);

	//Status flag
	clearAllFlag();
	//C
	if(carryBit8 == 1)
		setCarryFlag();
	//DC
	if(carry3to4 == 1)
		setDigitalCarryFlag();
	//Z
	if(getBitsAtOffset(fileValue,0,8) == 0)
		setZeroFlag();
	//OV
	if((carryBit8 == 0 && carry6to7 == 1) || (carryBit8 == 1 && carry6to7 == 0))
		setOverFlowFlag();
	//N
	if(getBitsAtOffset(fileValue,7,1))
		setNegativeFlag();

	setProgramCounter(getProgramCounter() + 2);
}

/**
*	To execute all ConditionalBranch due to address clashing in table
*
*	Input:
*		full opcode
*
*	Choose the function to execute if opcode matches
*/
int executeConditionalBranch(unsigned int code){

	int instruction;

		instruction = getBitsAtOffset(code,8,8);


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

/**
*	To execute MOVWF or NEGF due to address clashing in table
*
*	Input:
*		full opcode
*
*	Choose the function to execute if opcode matches
*/
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

/**
 *
 *	Bit Clear f
 *
 *	Operation :
 *		0-> f<b>
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		data
 *
 **/
int executeBCF(unsigned int code){
	int data;
	
	bafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = data & (~(1<<inst.code.fragments.bits));
	data = setFileRegData(inst.code.fragments.address, inst.code.fragments.access, data);

	updateProgramCounter();

	return data;

}

/**
 *
 *	Bit Set f
 *
 *	Operation :
 *		1-> f<b>
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		data
 *
 **/
int executeBSF(unsigned int code){
	int data;
	
	bafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = data | (1<<inst.code.fragments.bits);
	data = setFileRegData(inst.code.fragments.address, inst.code.fragments.access, data);

	updateProgramCounter();

	return data;

}

/**
 *
 *	Bit Test f, skip if clear
 *
 *	Operation :
 *		skip if f<b> = 0
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		data
 *
 **/
int executeBTFSC(unsigned int code){
	int programCounter;
	int data;
	
	bafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = ((data & (1<<inst.code.fragments.bits))>>inst.code.fragments.bits);

	updateProgramCounterSkipIfClear(data);

	return programCounter;
}

/**
 *
 *	Bit Test f, skip if set
 *
 *	Operation :
 *		skip if f<b> = 1
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		data
 *
 **/
int executeBTFSS(unsigned int code){
	int programCounter;
	int data;
	
	bafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = ((data & (1<<inst.code.fragments.bits))>>inst.code.fragments.bits);

	updateProgramCounterSkipIfSet(data);

	return programCounter;
}

/**
 *
 *	Bit Toggle f
 *
 *	Operation :
 *		~f<b> ->f<b>
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		data
 *
 **/
int executeBTG(unsigned int code){
	int programCounter;
	int data;
	
	bafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = data ^ (1<<inst.code.fragments.bits);
	data = setFileRegData(inst.code.fragments.address, inst.code.fragments.access, data);

	updateProgramCounter();

	return data;

}

/**
 *
 *	Subtract WREG from f
 *
 *	Operation :
 *		f - W ->dest
 *
 *	Status Affected	:
 *		N, OV, Z, DC, C
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		newData
 *
 **/
int executeSUBWF(unsigned int code){
	int data;
	int newData;
	int overFlowCheck;
	int digitalCarryCheck;
	dafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	newData = (int )data + ((~(fileRegisters[WREG]) + 1) & 0xff);

	overFlowCheck = ((((int )data & 0x7f) + ((~(fileRegisters[WREG]) + 1) & 0x7f))>>7);
	digitalCarryCheck = ((((int )data & 0x0f) + ((~(fileRegisters[WREG]) + 1) & 0x0f))>>4);

	checkNegativeStatus(newData);
	checkZeroStatus(newData);
	checkCarryStatus(newData);
	checkOverFlowStatus(newData, overFlowCheck);
	checkDigitalCarryStatus(digitalCarryCheck);

	newData = storeDestination(inst.code.fragments.destinationBit, inst.code.fragments.address, inst.code.fragments.access, newData);

	updateProgramCounter();

	return newData;
}

/**
 *
 *	Subtract WREG from f with borrow
 *
 *	Operation :
 *		f - W - C ->dest
 *
 *	Status Affected	:
 *		N, OV, Z, DC, C
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		newData
 *
 **/
int executeSUBWFB(unsigned int code){
	int data;
	int newData;
	int overFlowCheck;
	int digitalCarryCheck;
	int carry;
	dafInstruction inst;
	inst.code.raw = code;

	carry = withdrawPreviousCarryForSUBWFB();

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	newData = (int )data + ((~(fileRegisters[WREG]) + 1) & 0xff) + (-carry);

	overFlowCheck = ((((int )data & 0x7f) + ((~(fileRegisters[WREG]) + 1) & 0x7f) + (-carry))>>7);
	digitalCarryCheck = ((((int )data & 0x0f) + ((~(fileRegisters[WREG]) + 1) & 0x0f) + (-carry))>>4);

	checkNegativeStatus(newData);
	checkZeroStatus(newData);
	checkCarryStatus(newData);
	checkOverFlowStatus(newData, overFlowCheck);
	checkDigitalCarryStatus(digitalCarryCheck);

	newData = storeDestination(inst.code.fragments.destinationBit, inst.code.fragments.address, inst.code.fragments.access, newData);

	updateProgramCounter();

	return newData;
}

/**
 *
 *	Swap f
 *
 *	Operation :
 *		f<3:0> ->dest<7:4>
 *		f<7:4> ->dest<3:0>
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		newData
 *
 **/
int executeSWAPF(unsigned int code){
	int data;
	
	dafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	data = (((data & 0x0f)<<4) | ((data & 0xf0)>>4));

	data = storeDestination(inst.code.fragments.destinationBit, inst.code.fragments.address, inst.code.fragments.access, data);

	updateProgramCounter();

	return data;
}

/**
 *
 *	Test f, skip if 0
 *
 *	Operation :
 *		skip if f = 0
 *
 *	Status Affected	:
 *		None
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		newData
 *
 **/
int executeTSTFSZ(unsigned int code){
	int programCounter;
	int data;
	afInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);

	updateProgramCounterSkipIfClear(data);

	return programCounter;
}

/**
 *
 *	Exclusive OR W with f
 *
 *	Operation :
 *		W OR f ->dest
 *
 *	Status Affected	:
 *		N, Z
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Return :
 *		newData
 *
 **/
int executeXORWF(unsigned int code){
	int data;
	int newData;
	int overFlowCheck;
	int digitalCarryCheck;
	dafInstruction inst;
	inst.code.raw = code;

	data = getFileRegData(inst.code.fragments.address, inst.code.fragments.access);
	newData = (int )data ^ (fileRegisters[WREG] & 0xff);

	checkNegativeStatus(newData);
	checkZeroStatus(newData);

	newData = storeDestination(inst.code.fragments.destinationBit, inst.code.fragments.address, inst.code.fragments.access, newData);

	updateProgramCounter();

	return newData;
}

/**
 *
 * To check pervious data that had carry status!
 *
 **/
/*int withdrawPerviousCarryStatus(){
	fileRegisters[STATUS] = getBitsAtOffset(fileRegisters[STATUS],0,1);
	
	if(fileRegisters[STATUS] == 1){
		carry = 1;
	}else{
		carry = 0;
	}
	return carry;
}*/

/**
 *
 *	ADD W and Carry bit to f
 *
 *	Operation : 
 *		(W) + (f) + (C) -> dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z,C,OV,DC
 *
 **/
/*int executeADDWFC(unsigned int code){
	getInfoFromOffset(code);
	carry = withdrawPerviousCarryStatus();
	data = getFileRegData(address,access);
	updateData = data + (fileRegisters[WREG]) + carry;
	digitalCarry = (((data & 0x0f) + (fileRegisters[WREG] & 0x0f) + (carry))>>4);
	overFlow = ((data & 0x7f) + (fileRegisters[WREG] & 0x7f) + carry)>>7;
	
	checkOverFlowStatus(updateData,overFlow);
	checkCarryStatus(updateData);
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	checkDigitalCarryStatus(digitalCarry);
	
	updateData = storeDestination(destinationBit, address, access, updateData);								
	updateProgramCounter();
	
	return updateData;
	
	
}*/

/**
 *
 *	AND W with f
 *
 *	Operation : 
 *		(W) .AND. (f)->dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z
 *
 **/
/*int executeANDWF(unsigned int code){

	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	updateData = data & (fileRegisters[WREG]);
	
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Clear f
 *
 *	Operation : 
 *		000h->f
 *		1->Z
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		Z
 *
 **/
/*int executeCLRF(unsigned int code){
	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	updateData = data & 0x00000000;
	
	checkZeroStatus(updateData);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Complement f
 *
 *	Operation : 
 *		~(f)->dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z
 *
 **/
/*int executeCOMF(unsigned int code){

	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	updateData = ~(data);
	
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Compare f with W, skip if f=W
 *
 *	Operation : 
 *		(f)-(W)
 *		skip if (f) = (W)
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		data
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeCPFSEQ(unsigned int code){

	getInfoFromOffset(code);
	
	programCounter = getProgramCounter();
	
	data = getFileRegData(address,access);
	if(data == fileRegisters[WREG]){
		programCounter +=4;
		setProgramCounter(programCounter);
	}else{
		programCounter +=2;
		setProgramCounter(programCounter);
	}	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Compare f with W,skip if f<W
 *
 *	Operation : 
 *		(f)-(W),
 *		skip if (f)<(W)
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeCPFSLT(unsigned int code){

	getInfoFromOffset(code);
	
	programCounter = getProgramCounter();
	
	data = getFileRegData(address,access);
	if(data >= fileRegisters[WREG]){
		programCounter +=4;
		setProgramCounter(programCounter);
	}else{
		programCounter +=2;
		setProgramCounter(programCounter);
	}	
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Compare f with W,skip if f>W
 *
 *	Operation : 
 *		(f)-(W),
 *		skip if (f)>(W)
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeCPFSGT(unsigned int code){

	getInfoFromOffset(code);
	
	programCounter = getProgramCounter();
	
	data = getFileRegData(address,access);
	if(data <= fileRegisters[WREG]){
		programCounter +=4;
		setProgramCounter(programCounter);
	}else{
		programCounter +=2;
		setProgramCounter(programCounter);
	}	
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Decrement f
 *
 *	Operation : 
 *		(f)-1 ->dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		data
 *
 *	Status Affect:
 *		N,Z,C,OV,DC
 *
 **/
/*int executeDECF(unsigned int code){

	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	digitalCarry = ((data & 0x0f) +((~(0x01)+1) & 0x0f)>>4);
	overFlow = ((data & 0x7f) +((~(0x01)+1) & 0x7f))>>7;
	data -= 1;
	updateData = data;
	
	
	checkCarryStatus(updateData);
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	checkDigitalCarryStatus(digitalCarry);
	checkOverFlowStatus(updateData,overFlow);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Decrement f,skip if 0
 *
 *	Operation : 
 *		(f) - 1 ->dest
 * 		skip if result = 0
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeDECFSZ(unsigned int code){
	getInfoFromOffset(code);
	programCounter = getProgramCounter();
	data = getFileRegData(address,access);
	data -= 1;
	
	if(data == 0x00){
		programCounter +=2;
		setProgramCounter(programCounter);
	}else{
		programCounter +=4;
		setProgramCounter(programCounter);
	}
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Decrement f, skip if not 0
 *
 *	Operation : 
 *		(f) - 1 ->dest
 *      skip if result != 0
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeDCFSNZ(unsigned int code){
	getInfoFromOffset(code);
	programCounter = getProgramCounter();
	data = getFileRegData(address,access);
	data -= 1;
	
	if(data != 0x00){
		programCounter +=4;
		setProgramCounter(programCounter);
	}else{
		programCounter +=2;
		setProgramCounter(programCounter);
	}
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Increment f
 *
 *	Operation : 
 *		(f) + 1 -> dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z,C,DC,OV
 *
 **/
/*int executeINCF(unsigned int code){
	//dc ov
	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	digitalCarry = (((data & 0x0f) + 1)>>4);
	overFlow = (((data & 0x7f) + 1))>>7;
	data += 1;
	updateData = data;
	
	checkCarryStatus(updateData);
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	checkDigitalCarryStatus(digitalCarry);
	checkOverFlowStatus(updateData,overFlow);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	return updateData;
}*/

/**
 *
 *	Increment f, skip if 0
 *
 *	Operation : 
 *		(f) + 1 ->dest
 *		skip if result = 0
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeINCFSZ(unsigned int code){
	int value;
	getInfoFromOffset(code);
	programCounter = getProgramCounter();
	data = getFileRegData(address,access);
	data += 1;
	value = data & 0x000;
	
	if(value == 0x00){
		programCounter +=2;
		setProgramCounter(programCounter);
	}else{
		programCounter +=4;
		setProgramCounter(programCounter);
	}
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Increment f,skip if not 0
 *
 *	Operation : 
 *		(f) + 1 ->dest
 *		skip if result != 0
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeINFSNZ(unsigned int code){
	int value;
	getInfoFromOffset(code);
	programCounter = getProgramCounter();
	data = getFileRegData(address,access);
	data += 1;
	value = data & 0x000;
	
	if(value != 0x00){
		programCounter +=4;
		setProgramCounter(programCounter);
	}else{
		programCounter +=2;
		setProgramCounter(programCounter);
	}
	
	data = storeDestination(destinationBit, address, access, data);
	
	return data;
}*/

/**
 *
 *	Inclusive OR W with f
 *
 *	Operation : 
 *		(W).OR.(f) -> dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z
 *
 **/
/*int executeIORWF(unsigned int code){
	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	updateData = data | fileRegisters[WREG];
	
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Move f
 *
 *	Operation : 
 *		F->dest
 *
 *	Input :
 *		code is the opcode for instruction word
 *	
 *	Return :
 *		updateData
 *
 *	Status Affect:
 *		N,Z
 *
 **/
/*int executeMOVF(unsigned int code){
	getInfoFromOffset(code);

	data = getFileRegData(address,access);
	fileRegisters[WREG]  = data;
	updateData = fileRegisters[WREG];
	
	checkZeroStatus(updateData);
	checkNegativeStatus(updateData);
	
	updateData = storeDestination(destinationBit, address, access, updateData);
	updateProgramCounter();
	
	return updateData;
}*/

/**
 *
 *	Move source file to destination file
 *
 *	Operation : 
 *		Fs->Fd
 *
 *	Input :
 *		code is the opcode for instruction word
 *
 *	Status Affect:
 *		None
 *
 **/
/*int executeMOVFF(unsigned int code){

	unsigned int sourceAddress,destAddress;

	sourceAddress = getBitsAtOffset(code, 0, 12);
	destAddress = getBitsAtOffset(code, 16, 12);
	
	fileRegisters[destAddress] = fileRegisters[sourceAddress]; 
	updateProgramCounter();

	return 1;
}*/

/**
 *
 * To consider CPFSEQ or CPFSLT instruction to be taken!
 *
 **/
/*int executeCPFSEQorexecuteCPFSLT(unsigned int code){
	int instruction = (code&0xff00)>>8;
	
	switch(instruction){
		case 0x62:
		executeCPFSEQ(code);
		break;
		case 0x63:
		executeCPFSEQ(code);
		break;
		case 0x61:
		executeCPFSLT(code);
		break;
		case 0x60:
		executeCPFSLT(code);
		break;
	}
}*/

