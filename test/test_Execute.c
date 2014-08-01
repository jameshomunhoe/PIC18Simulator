#include "unity.h"
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"

void setUp(void){}
void tearDown(void){}

//executionTable[(0xFC00 & code)>>10](code);

void test_BC(){
	int code = 0xE205;
	
}