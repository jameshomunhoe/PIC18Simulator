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
	
	//	ff + (7f * 2) + 2 = ff + fe + 2
	//					  = 1ff
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
	
	//	ff + (-2 * 2) + 2 = ff + (-4) + 2
	//					  = 0xfd
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
	uint32 code = 0xec45f123;
	
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
	uint32 code = 0xecffffff;


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
	uint32 code = 0xedffffff;


	fileRegisters[PCLATU] = 0xff;
	fileRegisters[PCLATH] = 0xff;
	fileRegisters[PCL] = 0xff;
	
	//for shadow register testing purpose
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

void test_ADDWF_should_save_answer_in_WREG(){
	clearAllFileRegisters();
	int code = 0x2401;

	fileRegisters[WREG] = 0x7f;
	fileRegisters[0x01] = 0x01;
	
	executeInstruction(code);

	// - - - N OV Z DC C
	//		 1  1 0  1 0
	
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
	//		 0  0 1  1 1
	
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
	//		 0  0 0  1 1
	
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
	//		 0  0 0  0 0
	
	TEST_ASSERT_EQUAL_HEX16(0x70,fileRegisters[0x01]);
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[STATUS]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL_HEX8(0x00,fileRegisters[PCLATH]);
	TEST_ASSERT_EQUAL_HEX8(0x02,fileRegisters[PCL]);
}
