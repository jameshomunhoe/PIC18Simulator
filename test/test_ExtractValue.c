#include "unity.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "ExtractValue.h"

void setUp(void){}
void tearDown(void){}

void test_operand1ExtractValue(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndThrow(string,3);
	
	Try{
		operand1ExtractValue(string);
	}Catch(error){
		TEST_ASSERT_EQUAL(error,ERR_EMPTY_ARGUMENT);
		return;
	}
	TEST_FAIL_MESSAGE("No exception thrown.");
}


void test_operand1ExtractValue_it_is_value(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x123);
	value = operand1ExtractValue(string);
			
			
	TEST_ASSERT_EQUAL(value,0x123);
}