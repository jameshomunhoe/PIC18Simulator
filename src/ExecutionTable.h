#ifndef _EXECUTION_TABLE_H_
#define _EXECUTION_TABLE_H_

typedef int (*ExecutionTable)(unsigned int code);
extern ExecutionTable executionTable[64];

#endif //_EXECUTION_TABLE_H_