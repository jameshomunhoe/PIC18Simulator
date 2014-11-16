#include "unity.h"
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"
#include "StringObject.h"
#include "string.h"
#include "Text.h"

void setUp(void){}
void tearDown(void){}

void test_findActualFileRegister_should_return_address_0x23_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x23, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x23, address);

}

void test_findActualFileRegister_should_return_address_0x67_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x67, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x67, address);

}

void test_findActualFileRegister_should_return_address_0xff2_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0xff2, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0xff2, address);

}

void test_findActualFileRegister_over_range_should_mask_and_return_address_0x30_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x830, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x30, address);

}

void test_findActualFileRegister_over_range_should_mask_and_return_address_0x56_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x256, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x56, address);

}

void test_findActualFileRegister_over_range_after_mask_still_over_range_should_return_address_0x95_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x895, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0xf95, address);

}

void test_findActualFileRegister_over_range_after_mask_still_over_range_should_return_address_0xf84_when_access_is_0(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	address = findActualFileRegister(0x84, 0);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0xf84, address);

}

void test_findActualFileRegister_BSR_is_0_should_return_actual_address_0x86_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x0;
	address = findActualFileRegister(0x86, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x86, address);

}

void test_findActualFileRegister_BSR_should_return_actual_address_0x856_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x8;
	address = findActualFileRegister(0x156, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x856, address);

}

void test_findActualFileRegister_BSR_should_return_actual_address_0x482_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x4;
	address = findActualFileRegister(0x82, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x482, address);

}

void test_findActualFileRegister_BSR_should_return_actual_address_0x612_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x6;
	address = findActualFileRegister(0xf12, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x612, address);

}

void test_findActualFileRegister_BSR_0x73_should_return_actual_address_0x313_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x73;
	address = findActualFileRegister(0x13, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x313, address);

}

void test_findActualFileRegister_BSR_0x7_with_address_0xff90_should_return_actual_address_0x790_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0x7;
	address = findActualFileRegister(0xff90, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0x790, address);

}

void test_findActualFileRegister_BSR_0xf_with_address_0xf88_should_return_actual_address_0xf88_when_access_is_1(){
	int address;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[BSR] = 0xf;
	address = findActualFileRegister(0xf88, 1);
	// printf("%x", address);
	
	TEST_ASSERT_EQUAL(0xf88, address);

}

void test_getFileRegData_should_get_data_from_address_in_file_register(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x33] = 0x23;
	data = fileRegisters[0x33];
	data = getFileRegData(0x33, 0);
	
	TEST_ASSERT_EQUAL(0x23, data);
}

void test_getFileRegData_should_get_data_with_access_with_address_0x79(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x79] = 0x12;
	data = fileRegisters[0x79];
	data = getFileRegData(0x79, 0);
	
	TEST_ASSERT_EQUAL(0x12, data);
}

void test_getFileRegData_should_get_data_with_access_with_address_0xf86(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0xf86] = 0x56;
	data = fileRegisters[0xf86];
	data = getFileRegData(0xf86, 0);
	
	TEST_ASSERT_EQUAL(0x56, data);
}

void test_getFileRegData_should_get_data_from_bank4_0x123(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x123] = 0xa5;
	data = fileRegisters[0x123];
	fileRegisters[BSR] = 0x4;
	data = getFileRegData(0x123, 1);
	
	TEST_ASSERT_EQUAL(0, data);
}

void test_getFileRegData_should_get_data_from_bank8_0x3d1(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x3d1] = 0x4a;
	data = fileRegisters[0x3d1];
	fileRegisters[BSR] = 0x8;
	data = getFileRegData(0x3d1, 1);
	
	TEST_ASSERT_EQUAL(0, data);
}

void test_setFileRegData_access_should_set_data_into_address_0x45(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x45] = 0x3c;
	data = fileRegisters[0x45];
	data = setFileRegData(0x45, 0, 0x3c);
	
	TEST_ASSERT_EQUAL(0x3c, data);
	
}

void test_setFileRegData_access_should_set_data_into_address_0x7e(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x7e] = 0xc8;
	data = fileRegisters[0x7e];
	data = setFileRegData(0x7e, 0, 0xc8);
	
	TEST_ASSERT_EQUAL(0xc8, data);
	
}

void test_setFileRegData_banked_should_set_data_into_address_0x298(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0x298] = 0x34;
	data = fileRegisters[0x288];
	fileRegisters[BSR] = 0x4;
	data = setFileRegData(0x288, 1, 0x34);
	
	TEST_ASSERT_EQUAL(0x34, data);
	
}

void test_setFileRegData_banked_should_set_data_into_address_0xf71(){
	int data;
	
	clearAllFileRegisters(fileRegisters);
	
	fileRegisters[0xf71] = 0x62;
	data = fileRegisters[0xf71];
	fileRegisters[BSR] = 0x4;
	data = setFileRegData(0xf71, 1, 0x62);
	
	TEST_ASSERT_EQUAL(0x62, data);
	
}

void test_getProgramCounter_should_able_to_retrive_current_value_0x010203(){
	
	clearAllFileRegisters();
	
	fileRegisters[PCLATU] = 0x01;
	fileRegisters[PCLATH] = 0x02;
	fileRegisters[PCL] = 0x03;
	
	int pc = getProgramCounter();
	
	TEST_ASSERT_EQUAL_HEX32(0x10203,pc);

}

void test_getProgramCounter_should_able_to_retrive_current_value_0xff00ff(){
	
	clearAllFileRegisters();
	
	fileRegisters[PCLATU] = 0xff;
	fileRegisters[PCLATH] = 0x0;
	fileRegisters[PCL] = 0xff;
	
	int pc = getProgramCounter();
	
	TEST_ASSERT_EQUAL_HEX32(0xff00ff,pc);

}

void test_setProgramCounter_should_able_to_set_value_0xabcdef(){
	
	clearAllFileRegisters();
	
	int pc = 0xabcdef;
	setProgramCounter(pc);
	
	TEST_ASSERT_EQUAL_HEX16(0xab,fileRegisters[PCLATU] );
	TEST_ASSERT_EQUAL_HEX16(0xcd,fileRegisters[PCLATH] );
	TEST_ASSERT_EQUAL_HEX16(0xef,fileRegisters[PCL] );

}

void test_getProgramCounter_and_setProgramCounter_should_able_to_get_and_update_pc(){
	
	clearAllFileRegisters();
	
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x01;
	
	int pc = getProgramCounter();
	pc += 0x5;
	setProgramCounter(pc);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATU] );
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[PCLATH] );
	TEST_ASSERT_EQUAL_HEX16(0x06,fileRegisters[PCL] );

}
