#include "unity.h"
#include "Evaluate.h"
#include "Token.h"
#include "Text.h"
#include "StringObject.h"
#include "CharSet.h"
#include "Stack.h"
#include "LinkedList.h"
#include "tryEvaluatethenPush.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "createNumberToken.h"
#include "stackForEvaluate.h"
#include "CustomTypeAssert.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void) {}
void tearDown(void) {}



/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|	10	|		|		|				|	10	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_evaluatePrefixesAndNumber_evaluate_should_push_10_into_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("10");
	String *tokenizer = stringNew(newText);
	
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber("10",token,numberStack,operatorStack);
	token=stackPop(numberStack);
	TEST_ASSERT_NOT_NULL(token);
	TEST_ASSERT_EQUAL(10,((Number*)token)->value);
}

void test_evaluatePrefixesAndNumber_evaluate_should_push_prefix_operator_and_number_into_operator_and_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-12");
	String *tokenizer = stringNew(newText);
	
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber("-12",token,numberStack,operatorStack);
	token=stackPop(operatorStack);
	TEST_ASSERT_NOT_NULL(token);
	TEST_ASSERT_EQUAL_STRING("-",((Operator*)token)->info->symbol);
	TEST_ASSERT_EQUAL(MINUS_OP,((Operator*)token)->info->id);
}

void test_evaluatePrefixesAndNumber_evaluate_should_push_more_than_one_prefix_operator_and_number_into_operator_and_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-+14");
	String *tokenizer = stringNew(newText);
	
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber("-+14",token,numberStack,operatorStack);
	token=stackPop(operatorStack);
	TEST_ASSERT_NOT_NULL(token);
	TEST_ASSERT_EQUAL_STRING("+",((Operator*)token)->info->symbol);
	TEST_ASSERT_EQUAL(PLUS_OP,((Operator*)token)->info->id);
	
}

























































