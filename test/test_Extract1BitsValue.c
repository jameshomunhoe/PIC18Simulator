#include "unity.h"
#include "mock_Extract.h"
#include "Extract1BitsValue.h"
#include "CException.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "Extract1BitsValue.h"

void setUp(void){}

void tearDown(void){}

void test_NS_operandExtract1BitsValue_should_mock_and_throw_error(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndThrow(str, 2);
	
	Try{
		value = operandExtract1BitsValue(str);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_ILLEGAL_ARGUMENT, e);
	}
	
}

void test_NS_operandExtract1BitsValue_ERR_EMPTY_ARGUMENT_should_mock_and_return_0(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndThrow(str, 3);
	value = operandExtract1BitsValue(str);
	
	TEST_ASSERT_EQUAL(value, 0);
	
}

void test_NS_operandExtract1BitsValue_ERR_NO_ARGUMENT_should_mock_and_return_0(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndThrow(str, 4);
	value = operandExtract1BitsValue(str);
	
	TEST_ASSERT_EQUAL(value, 0);
	
}

void test_NS_operandExtract1BitsValue_should_mock_and_return_1(void){
	int value;
	int e;
	
	Text *text = textNew("135");
	String *str = stringNew(text);
	
	extractValue_ExpectAndReturn(str, 0x31);
	value = operandExtract1BitsValue(str);
	
	TEST_ASSERT_EQUAL_HEX8(value, 1);
	
}