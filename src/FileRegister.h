#ifndef _FILE_REGISTER_H_
#define _FILE_REGISTER_H_

#define	BSR 	0xFE0
#define PCLATU	0xFFB
#define PCLATH	0xFFA
#define PCL		0xFF9
#define STATUS	0xFD8
extern unsigned char fileRegisters[4096];

int getFileRegData(int address, int access);
int setFileRegData(int address, int access, int data);
int findActualFileRegister(int address, int access);
void clearAllFileRegisters();
int getProgramCounter();
void setProgramCounter (int programCounter);

#endif //_FILE_REGISTER_H_