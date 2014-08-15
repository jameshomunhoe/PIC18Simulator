#include "unity.h"
#include "mock_Extract.h"
#include "S.h"
#include "CException.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "Extract1BitsValue.h"

void setUp(void){}

void tearDown(void){}

void test_s_operand1_should_mock_and_throw_error(void){
	int value;
	int e;
	
	Text *text = textNew("");
	String *str = stringNew(text);
	
	extractValue_ExpectAndThrow(str, 3);
	
	Try{
		value = S(str);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT, e);
		
	}
	
}

void test_s_operand1_0x11_should_mock_and_return_1(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x11);
	value = S(str);
	
	TEST_ASSERT_EQUAL_HEX8(value, 0x1);
	
}

void test_s_operand1_0xff_should_mock_and_return_1(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0xff);
	value = S(str);
	
	TEST_ASSERT_EQUAL_HEX8(value, 0x1);
	
}

void test_s_operand1_0xffe_should_mock_and_return_0(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0xffe);
	value = S(str);
	
	TEST_ASSERT_EQUAL_HEX8(value, 0x0);
	
}