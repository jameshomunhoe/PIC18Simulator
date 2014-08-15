#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "Types.h"
//easier to execute functions, input full opcode into parameter
uint32 executeInstruction(uint32 code);
uint32 getBitsAtOffset(uint32 data, int offset, int bitSize);
void setBitsAtOffset(uint32 *dataPtr, uint32 dataToWrite, int offset, int bitSize);

//shyanfeng
int getInfoFromOffset(unsigned int code);
int withdrawPreviousCarryForSUBWFB();
void setNegativeFlag();
void clearNegativeFlag();
void setOverFlowFlag();
void clearOverFlowFlag();
void setZeroFlag();
void clearZeroFlag();
void setDigitalCarryFlag();
void clearDigitalCarryFlag();
void setCarryFlag();
void clearCarryFlag();
void checkNegativeStatus(int newData);
void checkZeroStatus(int newData);
void checkCarryStatus(int newData);
void checkOverFlowStatus(int updataData, int overFlow);
void checkDigitalCarryStatus(int digitalCarry);
int storeDestination(int destination, int address, int access, int data);
void updateProgramCounter();
void updateProgramCounterSkipIfClear(int data);
void updateProgramCounterSkipIfSet(int data);
int withdrawCarryStatus();

//james
int executeBC(unsigned int code);
int executeBNC(unsigned int code);
int executeBNZ(unsigned int code);
int executeBRA(unsigned int code);
int executeBZ(unsigned int code);
int executeCALL(unsigned int code);

int executeNEGF(unsigned int code);
int executeRLCF(unsigned int code);
int executeRRNCF(unsigned int code);
int executeADDWF(unsigned int code);
int executeMOVWF(unsigned int code);

int executeConditionalBranch(unsigned int code);
int executeMOVWForNEGF(unsigned int code);


//shyanfeng

int executeBCF(unsigned int code);
int executeBSF(unsigned int code);
int executeBTFSC(unsigned int code);
int executeBTFSS(unsigned int code);
int executeBTG(unsigned int code);
int executeSUBWF(unsigned int code);
int executeSUBWFB(unsigned int code);
int executeSWAPF(unsigned int code);
int executeTSTFSZ(unsigned int code);
int executeXORWF(unsigned int code);

//kenmun
int executeADDWF(unsigned int code);
int executeADDWFC(unsigned int code);
int executeANDWF(unsigned int code);
int executeCLRF(unsigned int code);
int executeCOMF(unsigned int code);
int executeCPFSEQorexecuteCPFSLT(unsigned int code);
int executeCPFSGT(unsigned int code);
int executeCPFSEQ(unsigned int code);
int executeCPFSLT(unsigned int code);
int executeDECF(unsigned int code);
int executeDECFSZ(unsigned int code);
int executeDCFSNZ(unsigned int code);
int executeINCF(unsigned int code);
int executeINCFSZ(unsigned int code);
int executeINFSNZ(unsigned int code);
int executeIORWF(unsigned int code);
int executeMOVF(unsigned int code);
int executeMOVFF(unsigned int code);

#endif //_EXECUTE_H_