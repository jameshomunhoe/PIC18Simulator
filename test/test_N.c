#include "unity.h"
#include "N.h"
#include "CException.h"
#include "mock_Extract.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "String.h"
#include "Text.h"
#include "ErrorCode.h"
#include "MaskTable.h"
#include "ExtractValue.h"

void setUp(void){}
void tearDown(void){}


void test_N(void){
	int value;
	
	Text *new = textNew("");
	String *string = stringNew(new);
	
	extractValue_ExpectAndReturn(string,0x11);
	value = N(string,7);

	TEST_ASSERT_EQUAL_HEX32(value,0x11);
}