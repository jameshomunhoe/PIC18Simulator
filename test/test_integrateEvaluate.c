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
void test_evaluatePrefixesAndNumber_should_push_10_into_number_stack(void){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	CEXCEPTION_T e;
	
	Text *newText=textNew("10");
	String *tokenizer = stringNew(newText);
	token=getToken(tokenizer);
	evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
}

void test_evaluatePrefixesAndNumber_should_push_prefix_operator_and_number_into_operator_and_number_stack(void){
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
	
	newText=textNew("(10(");
	tokenizer = stringNew(newText);
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

void test_evaluatePostfixesAndInfix_push_closing_bracket_into_operator_stack(void){
	CEXCEPTION_T e;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Text *newText;
	String *tokenizer;
	Operator openBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number10 = {.type= NUMBER_TOKEN, .value=10};
	Operator closingBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	
	newText=textNew("(10)");
	tokenizer = stringNew(newText);
	
	stackPush(&openBracket,operatorStack);
	stackPush(&number10,numberStack);
	Try
	{
		evaluatePostfixesAndInfix(tokenizer,(Token*)&closingBracket,numberStack,operatorStack);
		TEST_FAIL_MESSAGE("Should throw Error no expression ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NOT_EXPECTING_PREFIX_OPERATOR,e);
	}
	
}

void test_evaluatePostfixesAndInfix_push_closing_bracket_divide_into_operator_stack(void){
	CEXCEPTION_T e;
	Text *newText;
	String *tokenizer;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	
	Operator openBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number10 = {.type= NUMBER_TOKEN, .value=10};
	Operator closingBracket =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(CLOSING_BRACKET_OP)};
	Operator divide =  {.type= OPERATOR_TOKEN,.info=operatorFindInfoByID(DIV_OP)};
	
	newText=textNew("(10)/");
	tokenizer = stringNew(newText);
	
	stackPush(&openBracket,operatorStack);
	stackPush(&number10,numberStack);
	
	evaluatePostfixesAndInfix(tokenizer,(Token*)&divide,numberStack,operatorStack);
	TEST_ASSERT_EQUAL_OPERATOR(DIV_OP,stackPop(operatorStack));
}


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

void test_evaluate_should_throw_error_if_the_expression_is_null(void){
	
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

void test_evaluateExpression_5_should_push_into_number_stack(void){
	int check;
	check=evaluateExpression("5");
	TEST_ASSERT_EQUAL(5,check);
}

void test_evaluateExpression_negative_2_should_return_answer_negative_2(void){
	
	CEXCEPTION_T e;
	int check;
	check=evaluateExpression("-2");
	TEST_ASSERT_EQUAL(-2,check);	
}

void test_should_evaluate_negative_negative_60(void){
	int check;
	
	check=evaluateExpression("--60");
	TEST_ASSERT_EQUAL(- -60,check);
	
}

void test_should_evaluate_1_plus_2(void){
	ErrorCode e;
	int check;
	
	check=evaluateExpression("1+2");
	TEST_ASSERT_EQUAL(1+2,check);
}

void test_should_evaluate_10_minus_2_plus_7(void){
	ErrorCode e;
	int check;
	
	check=evaluateExpression("10-2+7");
	TEST_ASSERT_EQUAL(10-2+7,check);
}

void test_should_evaluate_negative_10_plus_2_multiply_20(void){
	
	int check;
	check=evaluateExpression("--10+2*20");
	TEST_ASSERT_EQUAL(- -10+2*20,check);
}

void test_should_evaluate_negative_10_multiply_negative_2(void){
	
	int check;
	check=evaluateExpression("-10*-2");
	TEST_ASSERT_EQUAL(-10*-2,check);
}

void test_should_evaluate_open_bracket_99_closing_bracket(void){
	
	CEXCEPTION_T e;
	int check;
	
	check=evaluateExpression("(99)");
	TEST_ASSERT_EQUAL((99),check);
}

void test_should_evaluate_open_open_bracket_100_closing_closing_bracket(void){
	
	CEXCEPTION_T e;
	int check;
	
	check=evaluateExpression("((100))");
	TEST_ASSERT_EQUAL(((100)),check);
}

void test_should_evaluate_expression_involve_prefix_postfix(void){
	
	CEXCEPTION_T e;
	int check;
	
	check=evaluateExpression("(12+13)*14");
	TEST_ASSERT_EQUAL((12+13)*14,check);
}

void test_should_evaluate_expression_involve_prefix_postfix_2(void){
	
	CEXCEPTION_T e;
	int check;
	
	check=evaluateExpression("((8&9))");
	TEST_ASSERT_EQUAL(((8&9)),check);
}

void test_should_evaluate_expression_involve_prefix_postfix_3(void){
	
	CEXCEPTION_T e;
	int check;
	
	check=evaluateExpression("((8&9))+(((17||20)))/(((60%19)))");
	TEST_ASSERT_EQUAL(((8&9))+(((17||20)))/(((60%19))),check);
}

void test_should_throw_error_for_negative_8_plus_multiply_7(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("-8+*7");
		TEST_FAIL_MESSAGE("Should throw Error no expression ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_CANNOT_CONVERT_TO_PREFIX ,e);
	}
}

void test_should_throw_error_for_open_bracket_18(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("(18");
		TEST_FAIL_MESSAGE("Should throw Error expecting closing bracket ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EXPECTING_CLOSING_BRACKET,e);
	}
	
}

void test_should_throw_error_for_18_closing_bracket(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("16)");
		TEST_FAIL_MESSAGE("Should throw Error expecting OPEN bracket ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EXPECTING_OPENING_BRACKET,e);
	}
	
}

void test_should_throw_error_for_open_and_closing_bracket_without_number(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("( )");
		TEST_FAIL_MESSAGE("Should throw Error no argument ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
	
}

void test_should_throw_error_for_17_open_bracket_18_plus_19(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("17(18+19)");
		TEST_FAIL_MESSAGE("Should throw expect infix operator ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NOT_EXPECTING_PREFIX_OPERATOR,e);
	}
}

void test_should_throw_error_for_open_bracket_20_closing_bracket_3(void){
	
	CEXCEPTION_T e;
	int check;
	Try
	{
		check=evaluateExpression("(20)3");
		TEST_FAIL_MESSAGE("Should throw not expect number ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NOT_EXPECTING_NUMBER,e);
	}
}



