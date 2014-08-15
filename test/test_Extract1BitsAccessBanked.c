#include "unity.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "Extract1BitsAccessBanked.h"

void setUp(void){}
void tearDown(void){}

void test_extract1bitsACCESSBANKED_is_empty_argument(void){
	int value,error;

	Text *new = textNew("");
	String *string = stringNew(new);
	

	extractACCESSBANKED_ExpectAndThrow(string,2);
	Try{
		extract1bitsACCESSBANKED(string,0);
	}Catch(error){
		TEST_ASSERT_EQUAL(error,ERR_ILLEGAL_ARGUMENT);
		return;
	}
	TEST_FAIL_MESSAGE("No exception thrown.");
}


void test_extract1bitsACCESSBANKED_is_not_empty_argument(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	

	extractACCESSBANKED_ExpectAndThrow(string,4);
	value = extract1bitsACCESSBANKED(string,0x20);


	TEST_ASSERT_EQUAL(value,0x0);
}

void test_extract1bitsACCESSBANKED_is_not_empty_argument1(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	

	extractACCESSBANKED_ExpectAndThrow(string,4);
	value = extract1bitsACCESSBANKED(string,0x81);


	TEST_ASSERT_EQUAL(value,0x1);
}