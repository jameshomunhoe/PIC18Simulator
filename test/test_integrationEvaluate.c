#include "unity.h"
#include "Evaluate.h"
#include "Stack.h"
#include "LinkedList.h"
#include "StringObject.h"
#include "tryEvaluatethenPush.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "createNumberToken.h"
#include "stackForEvaluate.h"
#include "Text.h"
#include "Types.h"
#include "Token.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CException.h"


void setUp(void){}
void tearDown(void){}

/*********************************************************************************************************************************
 Test on function evaluate(char *expression)
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

After doing the mocking tests at test_Evaluate.c , I running the integration test for function evaluate(char *expression)
by copying the mock test from test_Evaluate.
However, this is evaluate(char *expression) is a prototype function so this function could not evaluate
expression example like (((((25))))) and -+---++++20. 
I will improve this function and named it as evaluateExpression(char *expression). 
The TDD for evaluateExpression(char *expression) will be on file test_integrateEvaluate.c 
********************************************************************************************************************************/	

void test_evaluate_should_throw_error_if_the_expression_is_null(){
	
	ErrorCode e;
	int check;
	
	Try
	{
		check=evaluate(NULL);
		TEST_FAIL_MESSAGE("Should throw Error no expression ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT ,e);
	}
}

/****************************************************************************
	|		|		|		|				|		|		|		|
	|	6	|		|		|				|		|		|		|
	|	5	|		|	*	|				|		|		|		|
	|	4	|		|	+	|				|		|		|		|
	|	3	|		|	*	|				|		|		|		|
	|	2	|		|	+	|				|	44	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_evaluate_2_PLUS_3_MULTIPLY_4_PLUS_5_MULTIPLY_6(void){
	int check;
	check=evaluate("2+3*4+5*6");
	TEST_ASSERT_EQUAL(44,check);
	printf("Answer : %d ",check);
}



void test_should_evaluate_43_HASHTAG_42_and_throw_error_invalid_operator(void){

	int check;
	ErrorCode e;
	Try{
		evaluate("43#42");
	}Catch(e){
		 TEST_ASSERT_EQUAL(ERR_UNKNOWN_INFIX_OPERATOR,e);
		 
	}
}


/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|	)	|				|		|		|		|
	|	50	|		|	-	|				|		|		|		|
	|	3	|		|	*	|				|		|		|		|
	|	20  |		|	(	|				|	10	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_left_bracket_2_plus_3_right_bracket(void){
	int check;
	check=evaluate("(20*3-50)");
	TEST_ASSERT_EQUAL(10,check);
	printf("Answer : %d ",check);
}

/****************************************************************************
	|		|		|		|				|		|		|		|
	|		|		|		|				|		|		|		|
	|		|		|	)	|				|		|		|		|
	|	5	|		|	5	|				|		|		|		|
	|		|		|	(	|				|		|		|		|
	|	10  |		|	+	|				|	15	|		|		|
	numberstack		operatorStack			numberstack		operatorStack
			BEFORE									  AFTER
****************************************************************************/

void test_logic_not_13_SHOULD_RETURN_0(void){
	int check;
	check=evaluate("10+(5)");
	TEST_ASSERT_EQUAL(15,check);
	printf("Answer : %d ",check);

}
