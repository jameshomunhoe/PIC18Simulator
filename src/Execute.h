#ifndef _EXECUTE_H_
#define _EXECUTE_H_

//easier to execute functions, input full opcode into parameter
int executeInstruction(int code);

//james
int executeBC(unsigned int code);
int executeBNC(unsigned int code);
int executeBNZ(unsigned int code);
int executeBRA(unsigned int code);
int executeBZ(unsigned int code);
int executeCALL(unsigned int code);

int executeConditionalBranch(unsigned int code);


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

#endif //_EXECUTE_H_