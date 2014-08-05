#include "unity.h"
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"

void setUp(void){}
void tearDown(void){}

//executionTable[(0xFC00 & code)>>10](code);



void test_BC_should_increase_ProgramCounter_by_4(){
	clearAllFileRegisters();
	
	int code = 0xe201, data;
	fileRegisters[STATUS] = 0x01; //set carry bit to 1
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x04,fileRegisters[PCL]);
	
}

void test_BC_should_increase_ProgramCounter_from_0xFF_to_0x1ff(){
	clearAllFileRegisters();
	
	int code = 0xe27f, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x01; //set carry bit to 1
	
	data = executeInstruction(code);
	
	//	ff + (7f * 2) + 2 = ff + fe + 2
	//					  = 1ff
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
}

void test_BC_should_decrease_ProgramCounter_from_0xFF_to_0xFD(){
	clearAllFileRegisters();
	
	int code = 0xe2fe, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x01; //set carry bit to 1
	
	data = executeInstruction(code);
	
	//	ff + (-2 * 2) + 2 = ff + (-4) + 2
	//					  = 0xfd
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xfd,fileRegisters[PCL]);
	
}

void test_BC_should_increase_2_ProgramCounter_with_no_carry(){
	clearAllFileRegisters();
	
	int code = 0xe250, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x00; //set carry bit to 0	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCL]);
	
}

void test_BNC_should_increase_ProgramCounter_by_4(){
	clearAllFileRegisters();
	
	int code = 0xe301, data;
	fileRegisters[STATUS] = 0x00; //set carry bit to 0
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x04,fileRegisters[PCL]);
	
}

void test_BNC_should_increase_ProgramCounter_from_0xFF_to_0x1ff(){
	clearAllFileRegisters();
	
	int code = 0xe37f, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x0; //set carry bit to 0
	
	data = executeInstruction(code);
	
	//	ff + (7f * 2) + 2 = ff + fe + 2
	//					  = 1ff
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
}

void test_BNC_should_decrease_ProgramCounter_from_0xFF_to_0xFD(){
	clearAllFileRegisters();
	
	int code = 0xe3fe, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x0; //set carry bit to 0
	
	data = executeInstruction(code);
	
	//	ff + (-2 * 2) + 2 = ff + (-4) + 2
	//					  = 0xfd
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xfd,fileRegisters[PCL]);
	
}

void test_BNC_should_increase_2_ProgramCounter_with_carry(){
	clearAllFileRegisters();
	
	int code = 0xe350, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x01; //set carry bit to 1
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCL]);
	
}

void test_BNZ_should_increase_ProgramCounter_by_4(){
	clearAllFileRegisters();
	
	int code = 0xe101, data;
	fileRegisters[STATUS] = 0x0; //set zero bit to 0
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x04,fileRegisters[PCL]);
	
}

void test_BNZ_should_increase_ProgramCounter_from_0xFF_to_0x1ff(){
	clearAllFileRegisters();
	
	int code = 0xe17f, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x0; //set zero bit to 0
	
	data = executeInstruction(code);
	
	//	ff + (7f * 2) + 2 = ff + fe + 2
	//					  = 1ff
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
}

void test_BNZ_should_decrease_ProgramCounter_from_0xFF_to_0xFD(){
	clearAllFileRegisters();
	
	int code = 0xe1fe, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x0; //set zero bit to 0
	
	data = executeInstruction(code);
	
	//	ff + (-2 * 2) + 2 = ff + (-4) + 2
	//					  = 0xfd
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xfd,fileRegisters[PCL]);
	
}

void test_BNZ_should_increase_2_ProgramCounter_with_zeroBit(){
	clearAllFileRegisters();
	
	int code = 0xe150, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x4; //set zero bit to 1
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCL]);
	
}