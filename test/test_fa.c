#include "unity.h"
#include "mock_Extract.h"
#include "FA.h"
#include "CException.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "ExtractValue.h"
#include "Extract1BitsAccessBanked.h"

void setUp(void){}

void tearDown(void){}

void test_FA_should_return_0x35_and_store_in_ACCESS(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x35);
	extractACCESSBANKED_ExpectAndReturn(str, 0);
	
	value = FA(str);

	TEST_ASSERT_EQUAL_HEX16(value, 0x035);
}

void test_FA_should_return_0x34_and_store_in_BANKED(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x134);
	extractACCESSBANKED_ExpectAndReturn(str, 1);
	
	value = FA(str);

	TEST_ASSERT_EQUAL_HEX16(value, 0x134);
}

void test_FA_with_ERR_EMPTY_ARGUMENT_0x40_should_return_0x40_and_store_in_ACCESS(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x40);
	extractACCESSBANKED_ExpectAndThrow(str, 3);
	
	value = FA(str);

	TEST_ASSERT_EQUAL_HEX16(0x40,value);
}

void test_FA_with_ERR_NO_ARGUMENT_0xff6_should_return_0xf6_and_store_in_ACCESS(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0xff6);
	extractACCESSBANKED_ExpectAndThrow(str, 4);
	
	value = FA(str);

	TEST_ASSERT_EQUAL_HEX16(value, 0xf6);
}

void test_FA_operand1_empty_value_should_mock_and_throw_error(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndThrow(str, 3);
	
	Try{
		value = FA(str);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT, e);
		
	}
}

void test_FA_operand2_ERR_ILLEGAL_ARGUMENT_should_mock_and_throw_error(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x35);
	extractACCESSBANKED_ExpectAndThrow(str, 2);
	
	Try{
		value = FA(str);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_ILLEGAL_ARGUMENT, e);
		
	}
}
