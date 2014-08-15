#include "unity.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "Extract3BitsValue.h"

void setUp(void){}
void tearDown(void){}

void test_Extract_3bit_value1(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndThrow(string,2);
	Try{
		extract3BitsValue(string);
	}Catch(error){
		TEST_ASSERT_EQUAL(error,ERR_ILLEGAL_ARGUMENT);
		return;
	}
	TEST_FAIL_MESSAGE("No exception thrown.");
}

void test_Extract_3bit_value2(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	extractValue_ExpectAndThrow(string,4);
	
	Try{
		extract3BitsValue(string);
	}Catch(error){
		TEST_ASSERT_EQUAL(error,ERR_NO_ARGUMENT);
		return;
	}
	TEST_FAIL_MESSAGE("No exception thrown.");
}