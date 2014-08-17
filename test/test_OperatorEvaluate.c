#include "unity.h"
#include "Evaluate.h"
#include "Token.h"
#include "LinkedList.h"
#include "Stack.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "stackForEvaluate.h"
#include "Text.h"
#include "createNumberToken.h"
#include "StringObject.h"
#include "mock_tryEvaluatethenPush.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

/***********************************************************************	
 Test on function operatorEvaluate
 Input parameter : 
					1)Stack *numberStack
					2)Operator *opeToken

 Using following mock function : 
								1)stringCreate()
								2)getToken()
								3)stackPop()  
								4)stackPush()
								5)createNumberToken()
								
 ***********************************************************************/	
 
 void test_operatorEvaluate_should_throw_error_when_encounter_invalid_operator(void){
	
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Token *tempToken;
	Number *tempAns;
	ErrorCode exception;
	
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"1#2"};
	Number number1 = {.type= NUMBER_TOKEN, .value=1};
	Operator hashTag = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(HASH_OP)};
	Number number2 = {.type= NUMBER_TOKEN, .value=2};
	
	Try{
		 operatorInfixEvaluate(numberStack,&hashTag);
		TEST_FAIL_MESSAGE("Invalid Operator should throw Error Not Operator");
	}
	Catch(exception){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR,exception);
	}
}	

void test_operatorEvaluate_100_MINUS_37(void)
{
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	Token *tempToken;
	Number *tempAns;
	int check;
	//Initialize tokenizer,token and stack
	String tokenizer = {.text = t"100-37"};
	Number number100 = {.type= NUMBER_TOKEN, .value=100};
	Operator minus = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(SUB_OP)};
	Number number37 = {.type= NUMBER_TOKEN, .value=37};
	Number number63;
	
	stackPush(&number100,numberStack);
	stackPush(&minus,operatorStack);
	stackPush(&number37,numberStack);
	
	
	operatorInfixEvaluate(numberStack,&minus);
}

void test_operatorEvaluate_opening_bracket_3_should_throw_error(void){
	Token *tempToken;
	Number *tempAns;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	int check;
	//Initialize tokenizer,token and stack
	
	Operator openBracket = {.type= OPERATOR_TOKEN, .info=operatorFindInfoByID(OPENING_BRACKET_OP)};
	Number number3 = {.type= NUMBER_TOKEN, .value=3};
	
	stackPush(&openBracket,operatorStack);
	stackPush(&number3,numberStack);
	stackPush(NULL,operatorStack);
	
	operatorEvaluate(numberStack,&openBracket);
}





















