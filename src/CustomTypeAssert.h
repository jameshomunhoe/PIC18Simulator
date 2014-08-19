#ifndef __CUSTOM_TYPE_ASSERT_H__
#define __CUSTOM_TYPE_ASSERT_H__

#include "StringObject.h"
#include "Token.h"

#define TEST_ASSERT_EQUAL_String(expected, actual)										\
		UNITY_TEST_ASSERT_EQUAL_String((expected), (actual), __LINE__, NULL)

#define UNITY_TEST_ASSERT_EQUAL_String(expected, actual, line, msg)		\
												assertStringEqual(expected, actual, line, msg)

#define TEST_ASSERT_EQUAL_OPERATOR(expectedID,token) \
										assertOperatorEqual(expectedID,token,__LINE__,NULL);

#define TEST_ASSERT_EQUAL_NUMBER(expectedValue,token) \
										assertNumberEqual(expectedValue,token,__LINE__,NULL);

void assertStringEqual(const char *expected, String *actual, int line, const char *msg);

void assertOperatorEqual(OperatorID expectedID,Token *token,int line,const char* msg);

void assertNumberEqual(int expectedValue,Token *token,int line,const char* msg);

#endif	// __CUSTOM_TYPE_ASSERT_H__

