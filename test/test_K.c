#include "unity.h"
#include "K.h"
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


void test_operand1ExtractValue_it_is_value(void){
	int value,error;
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x123);
	value = operand1ExtractValue(string);
			
			
	TEST_ASSERT_EQUAL(value,0x123);
}