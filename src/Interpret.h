#ifndef Interpret_H
#define Interpret_H

#include "StringObject.h"
typedef enum{
	NO_TYPE,
	FDA_TYPE,
	FBA_TYPE,
	FA_TYPE,
	FSFD_TYPE,
	N8_TYPE,
	N11_TYPE,
	N12_TYPE,
	NS_TYPE,
	S_TYPE,
	K_TYPE,
	FK_TYPE
} InstructionType;


typedef struct {
  char *instructionName;
  unsigned int opCode;
  InstructionType type;
} instructionTable;

unsigned int runProgram(String *instruction);
unsigned int interpret(String *instruction);
instructionTable getInstruction(char *instruction);

int extractValue(String *arguments);
int extractDestination(String *arguments);
int extractACCESSBANKED(String *arguments);

#endif // Interpret_H




//throw not in table
//rethrow from them
//combine op code

//mock
// FA, FSFD, N, NS, S, K, FDA, FBA