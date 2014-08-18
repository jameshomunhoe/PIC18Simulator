#include "unity.h"
#include "Evaluate.h"
#include "Stack.h"
#include "Text.h"
#include "StringObject.h"
#include "Types.h"
#include "Token.h"
#include "CharSet.h"
#include "LinkedList.h"
#include "tryEvaluatethenPush.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "createNumberToken.h"
#include "stackForEvaluate.h"
#include "ErrorCode.h"
#include "CException.h"



void setUp(void){}
void tearDown(void){}

/*********************************************************************************************************************************
 Test for function evaluateExpression(char* expression).
 Before that was using function evaluate, but now change to evaluateExpression to test whether
 will pass also.
 Input parameter : 
					1)char *expression
********************************************************************************************************************************/	

 void test_evaluate_should_throw_error_if_the_expression_is_null(){
	
	ErrorCode e;
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
/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|	2	|		|		|				|		|		|		|
	|	1	|		|	+	|				|	3	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/
void test_should_return_3_for_1_plus_2(void){
	
	int check;
	Stack numberStack;
	Stack operatorStack;
	Text *newText;
	
	check=evaluateExpression("1+2");
	TEST_ASSERT_EQUAL(3, check);
	
}	
/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|	4	|		|		|				|		|		|		|
	|	3	|		|	+	|				|		|		|		|
	|	2	|		|	*	|				|	10	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/
void test_evaluate_2_MULTIPLY_3_PLUS_4(void){	
	
	int check;
	
	check=evaluateExpression("2*3+4");
	TEST_ASSERT_EQUAL(10,check);
	
	
}
/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|	42	|		|		|				|		|		|		|
	|	43	|		|	#	|				|		|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/
void test_should_evaluate_43_HASHTAG_42_and_throw_error_invalid_operator(void){

	Stack dataStack;
	Stack operatorStack;
	int check;
	ErrorCode e;
	Try{
		evaluateExpression("43#42");
		 
	 }Catch(e){
		 TEST_ASSERT_EQUAL(ERR_UNKNOWN_INFIX_OPERATOR,e);
	}
}

/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|	)	|				|		|		|		|
	|	25  |		|	(	|				|		|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_should_evaluate_left_parenthesis_25_right_parenthesis(void){
	
	Stack dataStack;
	Stack operatorStack;
	int check;
	Text *newText;
	
	check=evaluateExpression("(25)");
	TEST_ASSERT_EQUAL(25,check);
	
}

/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|	)	|				|		|		|		|
	|	50	|		|	-	|				|		|		|		|
	|	3	|		|	*	|				|		|		|		|
	|	20	|		|	(	|				|	10	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_left_bracket_20_multiply_3_subtract_50_right_bracket(void){
	Stack dataStack;
	Stack operatorStack;
	int check;
	
	
	check=evaluateExpression("(20*3-50)");
	TEST_ASSERT_EQUAL(10,check);
	
}




