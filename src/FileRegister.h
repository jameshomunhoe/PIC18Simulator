#ifndef _FILE_REGISTER_H_
#define _FILE_REGISTER_H_

#define	BSR 	0xFE0
#define PCLATU	0xFFB
#define PCLATH	0xFFA
#define PCL		0xFF9
#define STATUS	0xFD8
#define WREG	0xFE8
#define TOSU	0xfff
#define TOSH	0xffe
#define TOSL	0xffd

#include "Types.h"

typedef struct ShadowRegisters{
  uint8 WREGS;
  uint8 STATUSS;
  uint8 BSRS;
} ShadowRegisters;

extern unsigned char fileRegisters[4096];
extern ShadowRegisters shadowRegister;



int getFileRegData(int address, int access);
int setFileRegData(int address, int access, int data);
int findActualFileRegister(int address, int access);
void clearAllFileRegisters();
int getProgramCounter();
void setProgramCounter (unsigned int programCounter);

#endif //_FILE_REGISTER_H_