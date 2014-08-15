#include "unity.h"
#include "FileRegister.h"
#include "MaskTable.h"
#include "ExecutionTable.h"
#include "Execute.h"

void setUp(void){}
void tearDown(void){}

// executionTable[(0xFC00 & code)>>10](code);

void test_setBitsAtOffset(){
	int value = 0x1E36;
	setBitsAtOffset(&value,0x15,4,5);
	
	TEST_ASSERT_EQUAL_HEX32(0x1F56,value);
}

void test_withdrawPreviousCarryForSUBWFB_fileRegisters_STATUS_0x01_should_return_0x0(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x01;

	data = withdrawPreviousCarryForSUBWFB();
	
	TEST_ASSERT_EQUAL(0x0, data);
	
}

void test_withdrawPreviousCarryForSUBWFB_fileRegisters_STATUS_0x0_should_return_0x1(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x0;

	data = withdrawPreviousCarryForSUBWFB();
	
	TEST_ASSERT_EQUAL(0x1, data);
	
}

void test_setNegativeFlag_fileRegisters_STATUS_0x0f_should_return_0x1f(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x0f;

	setNegativeFlag();
	
	TEST_ASSERT_EQUAL(0x1f, fileRegisters[STATUS]);
	
}

void test_clearNegativeFlag_fileRegisters_STATUS_0x13_should_return_0x03(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x13;

	clearNegativeFlag();
	
	TEST_ASSERT_EQUAL(0x03, fileRegisters[STATUS]);
	
}

void test_setOverFlowFlag_fileRegisters_STATUS_0x17_should_return_0x1d(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x15;

	setOverFlowFlag();
	
	TEST_ASSERT_EQUAL(0x1d, fileRegisters[STATUS]);
	
}

void test_clearOverFlowFlag_fileRegisters_STATUS_0x0e_should_return_0x06(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x0e;

	clearOverFlowFlag();
	
	TEST_ASSERT_EQUAL(0x06, fileRegisters[STATUS]);
	
}

void test_setZeroFlag_fileRegisters_STATUS_0x03_should_return_0x07(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x03;

	setZeroFlag();
	
	TEST_ASSERT_EQUAL(0x07, fileRegisters[STATUS]);
	
}

void test_clearZeroFlag_fileRegisters_STATUS_0x1c_should_return_0x18(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x1c;

	clearZeroFlag();
	
	TEST_ASSERT_EQUAL(0x18, fileRegisters[STATUS]);
	
}

void test_setDigitalCarryFlag_fileRegisters_STATUS_0x11_should_return_0x13(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x11;

	setDigitalCarryFlag();
	
	TEST_ASSERT_EQUAL(0x13, fileRegisters[STATUS]);
	
}

void test_clearDigitalCarryFlag_fileRegisters_STATUS_0x0b_should_return_0x09(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x0b;

	clearDigitalCarryFlag();
	
	TEST_ASSERT_EQUAL(0x09, fileRegisters[STATUS]);
	
}

void test_setCarryFlag_fileRegisters_STATUS_0x14_should_return_0x15(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x14;

	setCarryFlag();
	
	TEST_ASSERT_EQUAL(0x15, fileRegisters[STATUS]);
	
}

void test_clearCarryFlag_fileRegisters_STATUS_0x05_should_return_0x04(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[STATUS] = 0x05;

	clearCarryFlag();
	
	TEST_ASSERT_EQUAL(0x04, fileRegisters[STATUS]);
	
}

void test_storeDestination_should_return_data_and_store_in_file_register(){
	int data;
	int address;
	int access;
	int destination;
	clearAllFileRegisters(fileRegisters);
	address = 0x76;
	access = 0x0;
	destination = 0x1;
	data = 0x72;

	data = storeDestination(destination, address, access, data);
	
	TEST_ASSERT_EQUAL(0x72, data);
	TEST_ASSERT_EQUAL(0x72, fileRegisters[address]);
	
}

void test_storeDestination_should_return_data_and_store_in_WREG(){
	int data;
	int address;
	int access;
	int destination;
	clearAllFileRegisters(fileRegisters);
	address = 0x33;
	access = 0x0;
	destination = 0x0;
	data = 0x41;

	data = storeDestination(destination, address, access, data);
	
	TEST_ASSERT_EQUAL(0x41, data);
	TEST_ASSERT_EQUAL(0x41, fileRegisters[WREG]);
	
}

void test_updateProgramCounter_should_return_program_counter(){
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	updateProgramCounter();
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4,fileRegisters[PCL]);
	
}

void test_updateProgramCounterSkipIfClear_should_return_program_counter_plus_4(){
	int data;
	clearAllFileRegisters(fileRegisters);
	data = 0;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	updateProgramCounterSkipIfClear(data);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x6,fileRegisters[PCL]);
	
}

void test_updateProgramCounterSkipIfClear_should_return_program_counter_plus_2(){
	int data;
	clearAllFileRegisters(fileRegisters);
	data = 0x1;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	updateProgramCounterSkipIfClear(data);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4,fileRegisters[PCL]);
	
}

void test_updateProgramCounterSkipIfSet_should_return_program_counter_plus_2(){
	int data;
	clearAllFileRegisters(fileRegisters);
	data = 0x0;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	updateProgramCounterSkipIfSet(data);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4,fileRegisters[PCL]);
	
}

void test_updateProgramCounterSkipIfSet_should_return_program_counter_plus_4(){
	int data;
	clearAllFileRegisters(fileRegisters);
	data = 0x1;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	updateProgramCounterSkipIfSet(data);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x6,fileRegisters[PCL]);
	
}

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
	
		// ff + (7f * 2) + 2 = ff + fe + 2
						  // = 1ff
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
	
		// ff + (-2 * 2) + 2 = ff + (-4) + 2
						  // = 0xfd
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
	
		// ff + (7f * 2) + 2 = ff + fe + 2
						  // = 1ff
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
	
		// ff + (-2 * 2) + 2 = ff + (-4) + 2
						  // = 0xfd
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

void test_BZ_should_increase_ProgramCounter_by_4(){
	clearAllFileRegisters();
	
	int code = 0xe001, data;
	fileRegisters[STATUS] = 0x4; //set zero bit to 1
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x04,fileRegisters[PCL]);
	
}

void test_BZ_should_increase_ProgramCounter_from_0xFF_to_0x1ff(){
	clearAllFileRegisters();
	
	int code = 0xe07f, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x4; //set zero bit to 1
	
	data = executeInstruction(code);
	
		// ff + (7f * 2) + 2 = ff + fe + 2
						  // = 1ff
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
}

void test_BZ_should_decrease_ProgramCounter_from_0xFF_to_0xFD(){
	clearAllFileRegisters();
	
	int code = 0xe0fe, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x4; //set zero bit to 1
	
	data = executeInstruction(code);
	
		// ff + (-2 * 2) + 2 = ff + (-4) + 2
						  // = 0xfd
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xfd,fileRegisters[PCL]);
	
}

void test_BZ_should_increase_2_ProgramCounter_with_zeroBit(){
	clearAllFileRegisters();
	
	int code = 0xe050, data;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xff;
	
	fileRegisters[STATUS] = 0x0; //set zero bit to 0
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
	
		// ff + (7f * 2) + 2 = ff + fe + 2
						  // = 1ff
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
	
		// ff + (-2 * 2) + 2 = ff + (-4) + 2
						  // = 0xfd
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xfd,fileRegisters[PCL]);
	
}

void test_BNZ_should_increase_2_ProgramCounter_with_no_zeroBit(){
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

void test_BRA_should_increase_ProgramCounter_by_4(){
	clearAllFileRegisters();
	
	int code = 0xd001, data;
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x04,fileRegisters[PCL]);
	
}

void test_BRA_should_decrease_ProgramCounter_by_0xa_to_0x6(){
	clearAllFileRegisters();
	
	int code = 0xd7fd, data; 	// 111 1111 1101 > 000 0000 0011 = -3 (2nd compliment's)
								// -3x2 + 2 = -6 + 2 = -4 in total
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xa;
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x06,fileRegisters[PCL]);
	
}
void test_NEGF_should_invert_fileData_from_0xff_to_0x01(){
	clearAllFileRegisters();
	
	int code = 0x6c50;
	unsigned char data; 	
	fileRegisters[0x50] = 0xff;
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x01,fileRegisters[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x01,data);
}

void test_NEGF_should_invert_fileData_from_0xf0_to_0x10(){
	clearAllFileRegisters();
	
	int code = 0x6c50;
	unsigned char data; 	
	fileRegisters[0x50] = 0xf0;
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x10,data);
}

void test_NEGF_should_invert_fileData_from_0x80_remains_0x80(){
	clearAllFileRegisters();
	
	int code = 0x6c50;
	unsigned char data; 	
	fileRegisters[0x50] = 0x80;
	
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x80,fileRegisters[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x80,data);
}

void test_getBitsAtOffset_should_return_0x4(){

	uint32 bits = getBitsAtOffset(0x1234,0,4);
	
	TEST_ASSERT_EQUAL_HEX32(0x4,bits);
}

void test_getBitsAtOffset_should_return_0x1(){

	uint32 bits = getBitsAtOffset(0x1234,12,4);
	
	TEST_ASSERT_EQUAL_HEX32(0x1,bits);
}


void test_getBitsAtOffset_should_return_0x12345678(){

	uint32 bits = getBitsAtOffset(0x12345678,0,100);
	
	TEST_ASSERT_EQUAL_HEX32(0x12345678,bits);
}

void test_getBitsAtOffset_should_return_0x1_MSB(){

	uint32 bits = getBitsAtOffset(0x87654321,100,100);
	
	TEST_ASSERT_EQUAL_HEX32(0x1,bits);
}

void test_MOVWF_should_move_value_of_50_to_fileRegisters_0x01(){
	clearAllFileRegisters();
	
	int code = 0x6e01;
	fileRegisters[WREG] = 0x50;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0x50,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_MOVWF_should_move_value_of_60_to_fileRegisters_0xf00(){
	clearAllFileRegisters();
	
	int code = 0x6f00;
	fileRegisters[BSR] = 0xf;
	fileRegisters[WREG] = 0x60;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0x60,fileRegisters[0xf00]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_RLCF_should_return_0xfe(){
	clearAllFileRegisters();
	int code = 0x3601;
	
	fileRegisters[0x01] = 0xff;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0xfe,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL(0x11,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
	
}

void test_RLCF_should_return_0x00(){
	clearAllFileRegisters();
	int code = 0x3601;
	
	fileRegisters[0x01] = 0x80;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX8(0x5,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
	
}

void test_RLCF_should_shift_in_from_carry(){
	clearAllFileRegisters();
	int code = 0x3601;
	
	setCarryFlag();
	fileRegisters[0x01] = 0x70;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0xE1,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX8(0x10,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
	
}

void test_RRNCF_should_shift_0x70_to_0x38(){
	clearAllFileRegisters();
	int code = 0x4001;
	
	fileRegisters[0x01] = 0x70;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0x38,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_RRNCF_should_shift_0x01_to_0x80(){
	clearAllFileRegisters();
	int code = 0x4001;
	
	fileRegisters[0x01] = 0x01;
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX8(0x80,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL_HEX8(0x10,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_CALL_should_update_PC_to_0x12345(){
	clearAllFileRegisters();
	uint32 code = 0xf345ec12;
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;

	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0x1,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x23,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x45,fileRegisters[PCL]);

	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[TOSL]);
}

void test_CALL_should_update_PC_to_0xfffff(){
	clearAllFileRegisters();
	uint32 code = 0xffffecff;


	fileRegisters[PCLATU] = 0xff;
	fileRegisters[PCLATH] = 0xff;
	fileRegisters[PCL] = 0xff;
	
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0xf,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[TOSL]);
}

void test_CALL_should_update_shadowRegister(){
	clearAllFileRegisters();
	uint32 code = 0xffffedff;


	fileRegisters[PCLATU] = 0xff;
	fileRegisters[PCLATH] = 0xff;
	fileRegisters[PCL] = 0xff;
	
	// for shadow register testing purpose
	fileRegisters[WREG] = 0x01;
	fileRegisters[BSR] = 0x02;
	fileRegisters[STATUS] = 0x03;
	
	executeInstruction(code);
	
	TEST_ASSERT_EQUAL_HEX16(0xf,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xff,fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[TOSH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[TOSL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x01,shadowRegister.WREGS);
	TEST_ASSERT_EQUAL_HEX16(0x02,shadowRegister.BSRS);
	TEST_ASSERT_EQUAL_HEX16(0x03,shadowRegister.STATUSS);
}

/*void test_ADDWF_should_save_answer_in_WREG(){
	clearAllFileRegisters();
	int code = 0x2401;

	fileRegisters[WREG] = 0x7f;
	fileRegisters[0x01] = 0x01;
	
	executeInstruction(code);

	// - - - N OV Z DC C
			 // 1  1 0  1 0
	
	TEST_ASSERT_EQUAL_HEX16(0x80,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x1A,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_ADDWF_should_save_answer_in_fileRegister(){
	clearAllFileRegisters();
	int code = 0x2601;

	fileRegisters[WREG] = 0xff;
	fileRegisters[0x01] = 0x01;
	
	executeInstruction(code);

	// - - - N OV Z DC C
			 // 0  0 1  1 1
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX16(0x07,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_ADDWF_should_not_have_OV(){
	clearAllFileRegisters();
	int code = 0x2601;

	fileRegisters[WREG] = 0xff;
	fileRegisters[0x01] = 0x11;
	
	executeInstruction(code);

	// - - - N OV Z DC C
			 // 0  0 0  1 1
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}

void test_ADDWF_should_not_have_any_StatusFlag(){
	clearAllFileRegisters();
	int code = 0x2601;

	fileRegisters[WREG] = 0x50;
	fileRegisters[0x01] = 0x20;
	
	executeInstruction(code);

	// - - - N OV Z DC C
			 // 0  0 0  0 0
	
	TEST_ASSERT_EQUAL_HEX16(0x70,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}*/

void test_executeBCF_0xf1_access_should_clear_bit7_and_return_0x71(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x46] = 0xf1;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2;
	
	code = 0x9E46;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x71, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4,fileRegisters[PCL]);
	
}

void test_executeBCF_0x64_access_should_clear_bit5_and_return_0x44(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x67] = 0x64;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4;
	
	code = 0x9A67;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x44, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x6,fileRegisters[PCL]);
	
}

void test_executeBCF_0x72_access_should_clear_bit1_and_return_0x70(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x34] = 0x72;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x6;
	
	code = 0x9234;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x70, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x8,fileRegisters[PCL]);
	
}

void test_executeBCF_0x4f_banked_should_clear_bit3_and_return_0x47(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x0;
	fileRegisters[0xe1] = 0x4f;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x8;
	
	code = 0x97e1;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x47, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x0a,fileRegisters[PCL]);
	
}

void test_executeBCF_0xc3_banked_should_clear_bit6_and_return_0x83(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x0;
	fileRegisters[0xb6] = 0xc3;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x0a;
	
	code = 0x9db6;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x83, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x0c,fileRegisters[PCL]);
	
}

void test_executeBSF_0x71_access_should_set_bit7_and_return_0xf1(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x46] = 0x71;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x0c;
	
	code = 0x8E46;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xf1, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x0e,fileRegisters[PCL]);
	
}

void test_executeBSF_0xa7_access_over_range_should_set_bit4_and_return_0xb7(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xfc4] = 0xa7;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x0e;
	
	code = 0x88c4;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xb7, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[PCL]);
	
}

void test_executeBSF_0x56_access_over_range_should_set_bit3_and_return_0x5e(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xfd1] = 0x56;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x10;
	
	code = 0x86d1;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x5e, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x12,fileRegisters[PCL]);
	
}

void test_executeBSF_0xd7_banked_should_set_bit3_and_return_0xdf(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x4;
	fileRegisters[0x412] = 0xd7;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x12;
	
	code = 0x8712;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xdf, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x14,fileRegisters[PCL]);
	
}

void test_executeBSF_0xb2_banked_over_range_should_set_bit0_and_return_0xb3(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x72;
	fileRegisters[0x263] = 0xb2;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x8163;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xb3, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0x4e_access_should_set_bit5_and_return_0x6e(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x7a] = 0x4e;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x7a7a;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x6e, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0xe9_access_should_set_bit3_and_return_0xe1(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x2a] = 0xe9;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x762a;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xe1, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0x39_access_over_range_should_set_bit3_and_return_0x31(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xfe2] = 0x39;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x76e2;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x31, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0xf7_access_over_range_should_set_bit6_and_return_0xd7(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xf99] = 0xf7;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x7c99;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xb7, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0xb6_banked_should_set_bit7_and_return_0x36(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x6;
	fileRegisters[0x6a3] = 0xb6;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x7fa3;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x36, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTG_0x8e_banked_over_range_should_set_bit3_and_return_0x86(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf2;
	fileRegisters[0x27a] = 0x8e;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x14;
	
	code = 0x777a;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x86, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0x8e_access_test_bit_7_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x34] = 0x8e;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x23;
	
	code = 0xbe34;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x25,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0x2a_access_test_bit_3_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x72] = 0x2a;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x65;
	
	code = 0xb672;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x67,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xd3_access_over_range_test_bit_4_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xfc2] = 0xd3;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x45;
	
	code = 0xb8c2;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x47,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xc3_access_test_bit_5_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x45] = 0xc3;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x56;
	
	code = 0xba45;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x5a,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xe5_access_over_range_test_bit_1_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xf12] = 0xe5;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x72;
	
	code = 0xb212;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x76,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xc2_banked_test_bit_6_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x2;
	fileRegisters[0x268] = 0xc2;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x87;
	
	code = 0xbd68;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x89,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xf7_banked_test_bit_2_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x6;
	fileRegisters[0x673] = 0xf7;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x10;
	
	code = 0xbf73;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x12,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xbe_banked_over_range_test_bit_5_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x75;
	fileRegisters[0x5ae] = 0xbe;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x92;
	
	code = 0xbbae;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x94,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xce_banked_test_bit_4_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x4;
	fileRegisters[0x4ee] = 0xce;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x33;
	
	code = 0xb9ee;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x37,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xbb_banked_test_bit_2_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x5;
	fileRegisters[0x5bb] = 0xbb;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x55;
	
	code = 0xb5bb;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x59,fileRegisters[PCL]);
	
}

void test_executeBTFSC_0xde_banked_over_range_test_bit_0_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x3;
	fileRegisters[0x3de] = 0xde;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x62;
	
	code = 0xb1de;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x66,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x44_access_test_bit_5_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x21] = 0x44;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x3a;
	
	code = 0xaa21;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x3c,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x5b_access_test_bit_2_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x57] = 0x5b;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x2a;
	
	code = 0xa457;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x2c,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0xe2_access_over_range_test_bit_4_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xba] = 0xe2;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xa5;
	
	code = 0xa8ba;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xa7,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x2c_banked_test_bit_1_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x5;
	fileRegisters[0x53a] = 0x2c;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xc1;
	
	code = 0xa33a;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xc3,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x72_banked_test_bit_7_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x3;
	fileRegisters[0x345] = 0x72;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x66;
	
	code = 0xaf45;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x68,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x98_access_test_bit_4_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x45] = 0x98;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x45;
	
	code = 0xa845;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x49,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0x79_access_test_bit_0_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x41] = 0x79;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xab;
	
	code = 0xa041;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xaf,fileRegisters[PCL]);
	
}

void test_executeBTFSS_0xeb_banked_test_bit_6_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x7;
	fileRegisters[0x722] = 0xeb;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xda;
	
	code = 0xad22;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xde,fileRegisters[PCL]);
	
}

void test_executeTSTFSZ_0x22_access_test_is_1_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x45] = 0x22;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x55;
	
	code = 0x6645;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x57,fileRegisters[PCL]);
	
}

void test_executeTSTFSZ_0_access_test_is_0_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0xda] = 0;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xe1;
	
	code = 0x66da;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xe5,fileRegisters[PCL]);
	
}

void test_executeTSTFSZ_0x35_banked_test_not_0_should_not_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x3;
	fileRegisters[0x345] = 0x35;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xa1;
	
	code = 0x6745;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xa3,fileRegisters[PCL]);
	
}

void test_executeTSTFSZ_0_banked_test_is_0_should_skip_and_return_pc(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x3;
	fileRegisters[0xf22] = 0x35;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x6722;
	data = executeInstruction(code);
	
	// printf("%x\n", fileRegisters[PCL]);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbe,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0x53_access_should_swap_and_return_0x35_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x55] = 0x53;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x3a55;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x35, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0xfa_access_should_swap_and_return_0xaf_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x78] = 0xfa;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x3a78;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xaf, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0x23_access_should_swap_and_return_0xaf_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x54] = 0x23;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x3954;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x32, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0xbc_banked_should_swap_and_return_0xcb_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x2;
	fileRegisters[0x25a] = 0xbc;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x395a;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xcb, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0x2e_banked_should_swap_and_return_0xe2_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x6;
	fileRegisters[0x642] = 0x2e;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x3942;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xe2, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeSWAPF_0x56_banked_should_swap_and_return_0xe2_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x7;
	fileRegisters[0x721] = 0x56;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0xba;
	
	code = 0x3921;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x65, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0xbc,fileRegisters[PCL]);
	
}

void test_executeXORWF_0xab_access_should_xor_and_return_0x10_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0xb4;
	fileRegisters[0xff1] = 0xa4;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4a;
	
	code = 0x1af1;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x10, data);
	TEST_ASSERT_EQUAL(0xb4, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4c,fileRegisters[PCL]);
	
}

void test_executeXORWF_0x14_access_should_xor_and_return_0x57_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x43;
	fileRegisters[0x3e] = 0x14;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4a;
	
	code = 0x183e;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x57, data);
	TEST_ASSERT_EQUAL(0x14, fileRegisters[0x3e]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4c,fileRegisters[PCL]);
	
}

void test_executeXORWF_0xab_banked_should_xor_and_return_0x23_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x4;
	fileRegisters[WREG] = 0x61;
	fileRegisters[0x425] = 0x42;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4a;
	
	code = 0x1b25;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x23, data);
	TEST_ASSERT_EQUAL(0x61, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4c,fileRegisters[PCL]);
	
}

void test_executeXORWF_0xc2_banked_should_xor_and_return_0xb8_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x4;
	fileRegisters[WREG] = 0x5a;
	fileRegisters[0x4e1] = 0xc2;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4a;
	
	code = 0x19e1;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x98, data);
	TEST_ASSERT_EQUAL(0xc2, fileRegisters[0x4e1]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4c,fileRegisters[PCL]);
	
}

void test_executeSUBWFB_0x19_access_should_sub_with_borrow_and_return_0x0c_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x0d;			//	0000 1101
	fileRegisters[0x23] = 0x19;			//	0001 1001
	fileRegisters[STATUS] = 0x1;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x72;
	
	code = 0x5a23;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x0c, data);
	TEST_ASSERT_EQUAL(0x0d, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x01, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x74,fileRegisters[PCL]);
	
}

void test_executeSUBWFB_0x19_access_should_sub_with_borrow_and_return_0x0d_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x16;			//	0001 0110
	fileRegisters[0x51] = 0x24;			//	0010 0100
	fileRegisters[STATUS] = 0x0;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x72;
	
	code = 0x5851;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x0d, data);
	TEST_ASSERT_EQUAL(0x24, fileRegisters[0x51]);
	TEST_ASSERT_EQUAL(0x01, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x74,fileRegisters[PCL]);
	
}

void test_executeSUBWFB_0x1a_banked_should_sub_with_borrow_and_return_0x0_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x2;
	fileRegisters[WREG] = 0x1a;			//	0001 1100
	fileRegisters[0x267] = 0x1b;		//	0001 1101
	fileRegisters[STATUS] = 0x0;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x72;
	
	code = 0x5967;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x0, data);
	TEST_ASSERT_EQUAL(0x1b, fileRegisters[0x267]);
	TEST_ASSERT_EQUAL(0x07, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x74,fileRegisters[PCL]);
	
}

void test_executeSUBWFB_0x03_banked_should_sub_with_borrow_and_return_0x0_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x9;
	fileRegisters[WREG] = 0x0e;			//	0000 1110
	fileRegisters[0x931] = 0x03;		//	0000 0011
	fileRegisters[STATUS] = 0x1;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x72;
	
	code = 0x5b31;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xf5, data);
	TEST_ASSERT_EQUAL(0x0e, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x74,fileRegisters[PCL]);
	
}


void test_executeSUBWF_0x03_access_should_sub_and_return_0x01_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x02;			//	0000 0010
	fileRegisters[0x51] = 0x03;			//	0000 0011
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4c;
	
	code = 0x5e51;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x01, data);
	TEST_ASSERT_EQUAL(0x02, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x03, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4e,fileRegisters[PCL]);
	
}

void test_executeSUBWF_0x12_access_should_sub_and_return_0x0e_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x4;			//	0000 0100
	fileRegisters[0x41] = 0x12;			//	0001 0010
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4c;
	
	code = 0x5c41;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x0e, data);
	TEST_ASSERT_EQUAL(0x12, fileRegisters[0x41]);
	TEST_ASSERT_EQUAL(0x01, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4e,fileRegisters[PCL]);
	
}

void test_executeSUBWF_0x00_access_should_sub_and_return_0x0_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0x00;			//	0000 0000
	fileRegisters[0x41] = 0x00;			//	0000 0010
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x6a;
	
	code = 0x5c41;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[0x41]);
	TEST_ASSERT_EQUAL(0x04, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x6c,fileRegisters[PCL]);
	
}

void test_executeSUBWF_0x02_banked_should_sub_and_return_0x0_and_store_in_file_register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0x2;	
	fileRegisters[WREG] = 0x02;			//	0000 0010
	fileRegisters[0x263] = 0x02;		//	0000 0010
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4c;
	
	code = 0x5f63;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0x0, data);
	TEST_ASSERT_EQUAL(0x02, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x07, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4e,fileRegisters[PCL]);
	
}

void test_executeSUBWF_0x02_banked_should_sub_and_return_0xff_and_store_in_WREG(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;	
	fileRegisters[WREG] = 0x02;			//	0000 0010
	fileRegisters[0xf31] = 0x01;		//	0000 0001
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x4c;
	
	code = 0x5d31;
	data = executeInstruction(code);
	
	// printf("%x\n", data);
	
	TEST_ASSERT_EQUAL(0xff, data);
	TEST_ASSERT_EQUAL(0x01, fileRegisters[0xf31]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x4e,fileRegisters[PCL]);
	
}

void test_executeADDWFC_is_in_FileRegister_and_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[WREG] = 0x89;
	fileRegisters[0xf31] = 0x19;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	fileRegisters[STATUS] = 0x01;
	
	code = 0x2331;
	data = executeInstruction(code);
	

	
	TEST_ASSERT_EQUAL(0xA3, data);
	TEST_ASSERT_EQUAL(0x89, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x12, fileRegisters[STATUS]);
}


void test_executeANDWF_is_in_FileRegister_and_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[WREG] = 0x01;
	fileRegisters[0xf31] = 0x01;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x1731;
	data = executeInstruction(code);
	

	
	TEST_ASSERT_EQUAL(0x01, data);
	TEST_ASSERT_EQUAL(0x01, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[STATUS]);	
}

void test_executeANDWF_is_in_FileRegister_and_ACCESS(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[WREG] = 0xA1;
	fileRegisters[0x31] = 0x90;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;

	code = 0x1731;
	data = executeInstruction(code);
	
		
	TEST_ASSERT_EQUAL(0x80, data);
	TEST_ASSERT_EQUAL(0xA1, fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
}

void test_executeCLRF_is_in_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x1A;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x6A31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x04, fileRegisters[STATUS]);
}

void test_executeCLRF_is_in_ACCESS(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x31] = 0x21;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;

	code = 0x6A31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x04, fileRegisters[STATUS]);
}


void test_executeCOMF_is_in_FileRegister_and_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x13;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x1F31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0xEC, data);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
}

void test_executeCOMF_is_in_FileRegister_and_ACCESS(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[0x31] = 0xFF;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x1F31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[PCLATU]); 
	TEST_ASSERT_EQUAL(0x03, fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x04, fileRegisters[STATUS]);
}

void test_executeCPFSEQ_is_in_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x1A;
	fileRegisters[WREG] = 0x1A;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x6331;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x1A, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[PCL]);
}


void test_executeCPFSGT_is_in_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x1A;
	fileRegisters[WREG] = 0x2A;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x6531;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x1A, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[PCL]);
}

void test_executeCPFSLT_is_in_BANKED(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x2A;
	fileRegisters[WREG] = 0x1A;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x6131;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x2A, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[PCL]);
}

void test_executeDECF_0x11_no_status(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x11;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x0731;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x10, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x0A, fileRegisters[STATUS]);
}

void test_executeDECF_0x01_zero_status(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x01;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x0731;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x0E, fileRegisters[STATUS]);
}



void test_executeDECFSZ_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x11;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x2F31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x10, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[PCL]);
}

void test_executeDCFSNZ_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x11;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x4F31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x10, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x05,fileRegisters[PCL]);

}

void test_executeINCF(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x1F;	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	code = 0x2B31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x20, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x02, fileRegisters[STATUS]);
}

void test_executeINCFSZ_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0xff;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x3F31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
}

void test_executeINFSNZ_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0xff;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x4B31;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x00, data);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
}

void test_executeIORWF_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x13;
	fileRegisters[WREG] = 0x91;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x1331;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x93, data);
	TEST_ASSERT_EQUAL(0x91,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x10, fileRegisters[STATUS]);
}

void test_executeMOVF_BANKED_and_File_Register(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);
	fileRegisters[BSR] = 0xf;
	fileRegisters[0xf31] = 0x13;
	fileRegisters[WREG] = 0x91;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;	

	code = 0x5331;
	data = executeInstruction(code);
	
	TEST_ASSERT_EQUAL(0x13, data);
	TEST_ASSERT_EQUAL(0x13,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX16(0x03,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00, fileRegisters[STATUS]);
}
void test_executeMOVFF(){
	int code;
	int data;
	clearAllFileRegisters(fileRegisters);

	fileRegisters[0x131] = 0x13;
	fileRegisters[0x132] = 0x91;
	
	code = 0xF132C131;
	data = executeInstruction(code);
	
	
	TEST_ASSERT_EQUAL(0x13, fileRegisters[0x131]);
	TEST_ASSERT_EQUAL(0x13, fileRegisters[0x132]);
}

