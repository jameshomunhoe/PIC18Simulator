#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "unity.h"
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
