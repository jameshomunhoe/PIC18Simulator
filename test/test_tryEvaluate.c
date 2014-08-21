#include "unity.h"
#include "tryEvaluatethenPush.h"
#include "Stack.h"
#include "LinkedList.h"
#include "operatorEvaluate.h"
#include "createNumberToken.h" 
#include "calculateToken.h"
#include "Token.h"
#include "StringObject.h"
#include "Text.h"
#include "CharSet.h"
#include "CustomTypeAssert.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_tryEvaluateOperatorOnStackThenPush_will_push_infix_operator_into_stack_when_stack_is_empty(void){
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Operator *opeToken;
	Operator plus = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(ADD_OP)};
	tryEvaluateOperatorOnStackThenPush(&plus,numberStack,operatorStack);
	opeToken=stackPop(operatorStack);
	TEST_ASSERT_NOT_NULL(operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(ADD_OP,(Token*)&plus);
}

void test_tryEvaluateOperatorOnStackThenPush_will_push_high_precedence_infix_operator_into_stack(void){
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Operator *opeToken;
	Operator plus = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(ADD_OP)};
	Operator multiply = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(MUL_OP)};
	
	stackPush(&plus,operatorStack);
	tryEvaluateOperatorOnStackThenPush(&multiply,numberStack,operatorStack);
	opeToken=stackPop(operatorStack);
	TEST_ASSERT_NOT_NULL(operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(MUL_OP,(Token*)&multiply);
	opeToken=stackPop(operatorStack);
	TEST_ASSERT_NOT_NULL(operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(ADD_OP,(Token*)&plus);
}

void test_tryEvaluateOperatorOnStackThenPush_will_not_push_lower_precedence_infix_operator_into_stack(void){
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	CEXCEPTION_T e;
	Operator *opeToken;
	Operator plus = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(ADD_OP)};
	Operator multiply = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(MUL_OP)};
	
	stackPush(&multiply,operatorStack);
	Try{
		tryEvaluateOperatorOnStackThenPush(&plus,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Should throw ERR EXPECTING_NUMBER.");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXPECTING_NUMBER,e);//Throw expecting number because the multiply will pop out and call operatorInfix function
	}
}

void test_tryConvertToPrefix_if_operator_is_not_prefix(void){
	Operator add = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(ADD_OP)};
	tryConvertToPrefix(&add);
	TEST_ASSERT_EQUAL_OPERATOR(PLUS_OP,(Token*)&add);
}

void test_tryConvertToPrefix_if_operator_is_not_prefix_2(void){
	Operator subtract = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(SUB_OP)};
	tryConvertToPrefix(&subtract);
	TEST_ASSERT_EQUAL_OPERATOR(MINUS_OP,(Token*)&subtract);
}

void test_tryConvertToPrefix_will_throw_error_if_operator_cannot_convert_to_prefix(void){
	CEXCEPTION_T e;
	
	Operator multiply = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(MUL_OP)};
	
	Try{
		tryConvertToPrefix(&multiply);
		TEST_FAIL_MESSAGE("Should throw ERR CANNOT CONVERT TO PREFIX");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CANNOT_CONVERT_TO_PREFIX,e);
	}
}

void test_tryEvaluateAndExecutePostfix_will_throw_error_for_closing_bracket_when_operator_stack_does_not_have_open_bracket(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Operator closeBracket = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	
	Try{
		tryEvaluateAndExecutePostfix(&closeBracket,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Expect opening bracket");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXPECTING_OPENING_BRACKET,e);
	}
}

void test_tryEvaluateAndExecutePostfix_will_push_closing_bracket_when_operator_stack_contain_open_bracket(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Operator openBracket = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Operator closeBracket = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	
	stackPush(&openBracket,operatorStack);
	stackPush(&number2,numberStack);
	tryEvaluateAndExecutePostfix(&closeBracket,numberStack,operatorStack);
	TEST_ASSERT_NOT_NULL(operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(OPENING_BRACKET_OP,(Token*)&openBracket);
	TEST_ASSERT_NOT_NULL(operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(CLOSING_BRACKET_OP,(Token*)&closeBracket);
	TEST_ASSERT_NOT_NULL(numberStack);
	TEST_ASSERT_EQUAL_NUMBER(2,(Token*)&number2);
}



