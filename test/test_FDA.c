#include "unity.h"
#include "FDA.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "ExtractValue.h"
#include "Extract1BitsDestination.h"
#include "Extract1BitsAccessBanked.h"


void setUp(void){}
void tearDown(void){}


//TEST operand1 is not NULL 2,3 NULL


void test_FDA_operand1_is_34_operand2_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x34);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x234);
}

void test_FDA_operand1_is_85_operand2_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x85);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL(value,0x385);
}

void test_FDA_operand1_is_ff_operand2_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xff);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x3ff);
}

void test_FDA_operand1_is_ffe_operand2_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xffe);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x2fe);
}


//TEST operand1,2 is not NULL 3 NULL

void test_FDA_operand1_is_34_operand2_is_0_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x34);
	extractDestination_ExpectAndReturn(string,0);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x34);
}

void test_FDA_operand1_is_34_operand2_is_1_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x34);
	extractDestination_ExpectAndReturn(string,1);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x234);
}

void test_FDA_operand1_is_85_operand2_is_0_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x85);
	extractDestination_ExpectAndReturn(string,0);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x185);
}

void test_FDA_operand1_is_85_operand2_is_1_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x85);
	extractDestination_ExpectAndReturn(string,1);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x385);
}

void test_FDA_operand1_is_f01_operand2_is_0_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xf01);
	extractDestination_ExpectAndReturn(string,0);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x101);
}

void test_FDA_operand1_is_f01_operand2_is_1_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xf01);
	extractDestination_ExpectAndReturn(string,1);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x301);
}

void test_FDA_operand1_is_ffe_operand2_is_0_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xffe);
	extractDestination_ExpectAndReturn(string,0);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0xfe);
}

void test_FDA_operand1_is_ffe_operand2_is_1_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xffe);
	extractDestination_ExpectAndReturn(string,1);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x2fe);
}


//operand1and3 is not NULL and operand2 is NULL

void test_FDA_operand1_is_34_operand2_is_NULL_and_operand3_is_11(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x34);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndReturn(string,11);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x334);
}

void test_FDA_operand1_is_f01_operand2_is_NULL_and_operand3_is_10(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0xf01);
	extractDestination_ExpectAndThrow(string,4);
	extractACCESSBANKED_ExpectAndReturn(string,10);
	
	value = FDA(string);
		
	TEST_ASSERT_EQUAL_HEX32(value,0x201);
}

