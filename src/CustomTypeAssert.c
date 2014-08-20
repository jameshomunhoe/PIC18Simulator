#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "unity.h"
#include "Token.h"
#include "CustomTypeAssert.h"

void assertStringEqual(const char *expected, String *actual, int line, const char *msg) {
	int i;
	const char *str = &actual->text->string[actual->start];

	if(strlen(expected) != actual->length)
		UNITY_TEST_FAIL(line, "Both strings are not of the same length.");

	for(i = 0; expected[i] != 0 && expected[i] == str[i]; i++);
	if(expected[i] != 0)
		UNITY_TEST_FAIL(line, "Both strings are not the same.");
}

void assertOperatorEqual(OperatorID expectedID,Token *token,int line,const char* msg){
	TokenType tokenType;
	Operator *op;
	OperatorInfo *info;
	OperatorID id;
	UNITY_TEST_ASSERT_NOT_NULL(token,line,"Expected Non-NULL");
	tokenType=(TokenType)token->type;
	UNITY_TEST_ASSERT_EQUAL_INT(tokenType,OPERATOR_TOKEN,line,NULL);
	op=(Operator*)token;
	UNITY_TEST_ASSERT_NOT_NULL(op,line,"Expected Non-NULL");
	info=(OperatorInfo*)op->info;
	UNITY_TEST_ASSERT_NOT_NULL(info,line,"Expected Non-NULL");
	id=(OperatorID)info->id;
	UNITY_TEST_ASSERT_NOT_NULL(&id,line,"Expected Non-NULL");
	UNITY_TEST_ASSERT_EQUAL_INT(expectedID,id,line,"Wrong operator");
}

void assertNumberEqual(int expectedValue,Token *token,int line,const char* msg){
	TokenType tokenType;
	int value;
	Number *num;
	UNITY_TEST_ASSERT_NOT_NULL(token,line,"Expected Non-NULL");
	tokenType=(TokenType)token->type;
	UNITY_TEST_ASSERT_EQUAL_INT(tokenType,NUMBER_TOKEN,line,NULL);
	num=(Number*)token;
	UNITY_TEST_ASSERT_NOT_NULL(num,line,"Expected Non-NULL");
	value=num->value;
	UNITY_TEST_ASSERT_NOT_NULL(&value,line,"Expected Non-NULL");
	UNITY_TEST_ASSERT_EQUAL_INT(expectedValue,value,line,"Wrong number");
}
