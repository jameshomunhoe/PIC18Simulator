#include "unity.h"
#include "FBA.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "ExtractValue.h"
#include "Extract3BitsValue.h"
#include "Extract1BitsAccessBanked.h"

void setUp(void){}
void tearDown(void){}



void test_FBA_operand1_is_34_and_operand2_is_0_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);

	extractValue_ExpectAndReturn(string,0x34);
	extractValue_ExpectAndReturn(string,2);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	value = FBA(string);
	
	TEST_ASSERT_EQUAL_HEX32(value,0x434);
}

void test_FBA_operand1_is_34_and_operand2_is_10_and_operand3_is_NULL(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);

	extractValue_ExpectAndReturn(string,0x34);
	extractValue_ExpectAndReturn(string,0x11);
	extractACCESSBANKED_ExpectAndThrow(string,4);
	value = FBA(string);
	
	TEST_ASSERT_EQUAL_HEX32(value,0x234);
}

void test_FBA_operand1_is_34_and_operand2_is_10_and_operand3_is_1(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);

	extractValue_ExpectAndReturn(string,0x34);
	extractValue_ExpectAndReturn(string,0x11);
	extractACCESSBANKED_ExpectAndReturn(string,1);
	value = FBA(string);
	
	TEST_ASSERT_EQUAL_HEX32(value,0x334);
}




