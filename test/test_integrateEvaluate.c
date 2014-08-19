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

/******************************************************************************************
	Tests for evaluatePrefixesAndNumber(char *expression,token,numberStack,operatorStack)
*******************************************************************************************/
void xtest_evaluatePrefixesAndNumber_should_push_10_into_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	CEXCEPTION_T e;
	
	Text *newText=textNew("10");
	String *tokenizer = stringNew(newText);
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
}

void xtest_evaluatePrefixesAndNumber_should_push_prefix_operator_and_number_into_operator_and_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-12");
	String *tokenizer = stringNew(newText);
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_NULL(stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(12,stackPop(numberStack));
}


void test_evaluatePrefixesAndNumber_should_push_more_than_one_prefix_operator_and_number_into_stack_with_loop(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-+14");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix push more than one prefix operator with loop\n");
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(PLUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(14,stackPop(numberStack));
	TEST_ASSERT_NOT_NULL(token);
	
}

void test_evaluatePrefixesAndNumber_should_push_more_than_two_prefix_operator_and_number_into_stack_wit_loop(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-+-16");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix push more than two prefix operator with loop\n");
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(PLUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(16,stackPop(numberStack));
}

void test_evaluatePrefixesAndNumber_should_push_prefix_operator_without_convert_and_number_into_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("!18");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix push prefix operator without convert with loop\n");
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(LOGICAL_NOT_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(18,stackPop(numberStack));
}

void test_evaluatePrefixesAndNumber_should_throw_error_cannot_convert_prefix(void){
	CEXCEPTION_T e;
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("*18");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix throw error cannot convert to prefix\n");
	token=getToken(tokenizer);
	Try{
		evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Cannot convert to prefix");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CANNOT_CONVERT_TO_PREFIX,e);
	}
}

void test_evaluatePrefixesAndNumber_should_throw_error_cannot_convert_prefix_after_a_prefix_operator(void){
	CEXCEPTION_T e;
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-*18");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix throw error cannot convert to prefix after a prefix operator\n");
	token=getToken(tokenizer);
	Try{
		evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Cannot convert to prefix");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CANNOT_CONVERT_TO_PREFIX,e);
	}
}

void test_evaluatePrefixesAndNumber_should_throw_error_expect_a_number_after_prefix_operator(void){
	CEXCEPTION_T e;
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("-");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix throw error throw error expect a number after prefix operator\n");
	token=getToken(tokenizer);
	Try{
		evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Cannot expecting number");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXPECTING_NUMBER,e);
	}
}

void test_evaluatePrefixesAndNumber_should_stop_the_loop_after_encounter_a_number(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Text *newText=textNew("-+-20+");
	String *tokenizer = stringNew(newText);
	//printf("Test evaluatePrefix should stop the loop after encounter number\n");
	
	Token *token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_NOT_NULL(token);
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(PLUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(20,stackPop(numberStack));
}

void test_evaluatePrefixesAndNumber_evaluate_opening_bracket_7(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("(7");
	String *tokenizer = stringNew(newText);
	
	//(
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(OPENING_BRACKET_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(7,stackPop(numberStack));
}

void test_evaluatePrefixesAndNumber_evaluate_opening_opening_opening_bracket_10(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Text *newText=textNew("(((10");
	String *tokenizer = stringNew(newText);
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(OPENING_BRACKET_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(OPENING_BRACKET_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_OPERATOR(OPENING_BRACKET_OP,stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(10,stackPop(numberStack));
}

/*****************************************************************************************
	Tests for evaluatePostfixesAndInfix(char *expression,(token,numberStack,operatorStack)
*******************************************************************************************/

void test_evaluatePostfixesAndInfix_throw_error_expecting_open_bracket(void){
	CEXCEPTION_T e;
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Text *newText;
	String *tokenizer;
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	Operator closingBracket =  {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	
	newText=textNew("2)");
	tokenizer = stringNew(newText);
	
	stackPush(&number2,numberStack);
	Try{
		evaluatePostfixesAndInfix(tokenizer,(Token*)&closingBracket,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Expecting a open bracket ");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXPECTING_OPENING_BRACKET,e);
	}
}

void test_evaluatePostfixesAndInfix_should_evaluate_2_plus_and_push_plus_to_operator_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Text *newText;
	String *tokenizer;
	//2+
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	Operator plus =  {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(ADD_OP)};
	
	newText=textNew("2)");
	tokenizer = stringNew(newText);
	
	stackPush(&number2,numberStack);
	evaluatePostfixesAndInfix(tokenizer,(Token*)&plus,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(ADD_OP,stackPop(operatorStack));
	TEST_ASSERT_NULL(stackPop(operatorStack));
	TEST_ASSERT_EQUAL_NUMBER(2,stackPop(numberStack));
	TEST_ASSERT_NULL(stackPop(numberStack));
}	

void test_evaluatePostfixesAndInfix_should_throw_error_invalid_operator_for_open_bracket_2_open_bracket(void){
	CEXCEPTION_T e;
	Token *token;
	Stack *numberStack;
	Stack *operatorStack;
	Text *newText;
	String *tokenizer;
	
	Operator openBracket =  {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number10 = {.type= NUMBER_TOKEN, .value=10};
	numberStack=createStack();
	operatorStack=createStack();
	stackPush(&openBracket,operatorStack);
	stackPush(&number10,numberStack);
	stackPush(&openBracket,operatorStack);
	
	Try
	{
		evaluatePostfixesAndInfix(tokenizer,(Token*)&openBracket,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Not expecting prefix to come in ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NOT_EXPECTING_PREFIX_OPERATOR,e);
	}
}
/*
void xtest_evaluatePostfixesAndInfix_push_closing_bracket_into_operator_stack(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Operator openBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number10 = {.type= NUMBER_TOKEN, .value=10};
	Operator closingBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	
	stackPush(&openBracket,operatorStack);
	stackPush(&number10,numberStack);
	
	evaluatePostfixesAndInfix("10)",(Token*)&closingBracket,numberStack,operatorStack);
}

void xtest_evaluatePostfixesAndInfix_push_closing_bracket_divide_into_operator_stack(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Operator openBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number10 = {.type= NUMBER_TOKEN, .value=10};
	Operator closingBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	Operator divide =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(DIV_OP)};
	stackPush(&openBracket,operatorStack);
	stackPush(&number10,numberStack);
	
	evaluatePostfixesAndInfix("10)/",(Token*)&closingBracket,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(DIV_OP,stackPop(operatorStack));
}
*/

/*********************************************************************************************************************************
 Test on function evaluateExpression(char *expression)
 Input parameter : 
					1)char *expression

 Using following real function : 
								1)getToken()
								2)stackPop()  
								3)stackPush()
								4)createNumberToken()
								5)operatorEvaluate(Stack *numberStack , Operator *opeToken);
								6)evaluateAllOperatorOnStack(Stack *numberStack,Stack *operatorStack);
								7)tryEvaluateOperatorOnStackThenPush(Operator *newToken,Stack *numberStack,Stack *operatorStack);
								8)calculate(Operator *opeToken, Number *first , Number *second);
								9)textNew(char *expression)
								10)stringNew(Text *text)

This test files will doing all the tests request by Dr. Poh using the latest evaluate function which is 
evaluateExpression(char *expression)

********************************************************************************************************************************/
void xtest_evaluate_should_throw_error_if_the_expression_is_null(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression(NULL);
		TEST_FAIL_MESSAGE("Should throw Error no expression ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT ,e);
	}
}










