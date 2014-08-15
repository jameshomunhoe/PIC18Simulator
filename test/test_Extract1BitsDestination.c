#include "unity.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "Extract1BitsDestination.h"

void setUp(void){}
void tearDown(void){}

void test_extract1BitsValue_is_empty_argument(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	


	extractDestination_ExpectAndThrow(string,2);
	Try{
		extract1BitsDestination(string);
	}Catch(error){
		TEST_ASSERT_EQUAL(error,ERR_ILLEGAL_ARGUMENT);
		return;
	}
	TEST_FAIL_MESSAGE("No exception thrown.");
	
}

void test_extract1BitsValue_is_not_empty_argument(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	

	extractDestination_ExpectAndThrow(string,4);
	value = extract1BitsDestination(string);


	TEST_ASSERT_EQUAL(value,0x1);
	
}