#include "unity.h"
#include <malloc.h>
#include "Token.h"
#include "Text.h"
#include "LinkedList.h"
#include "calculateToken.h"
#include "createNumberToken.h"
#include "mock_StringObject.h"
#include "mock_operatorEvaluate.h"
#include "mock_initializeToken.h"
#include "mock_tryEvaluatethenPush.h"
#include "stackForEvaluate.h"
#include "Stack.h"
#include "ErrorCode.h"
#include "CharSet.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}


void test_should_calculate_2_PLUS_3(void)
{
	int check;
	Operator plus={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(ADD_OP)};
	Number two={.type=NUMBER_TOKEN,.value=2};
	Number three={.type=NUMBER_TOKEN,.value=3};
	
	check=calculate(&plus,&two,&three);
	
	TEST_ASSERT_EQUAL(5,check);
	
}

void test_should_calculate_10_MINUS_3(void)
{
	int check;
	Operator subtract={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(SUB_OP)};
	Number ten={.type=NUMBER_TOKEN,.value=10};
	Number three={.type=NUMBER_TOKEN,.value=3};
	
	check=calculate(&subtract,&ten,&three);
	
	TEST_ASSERT_EQUAL(7,check);
	
}

void test_should_calculate_10_MULTIPLY_10(void)
{
	int check;
	Operator multiply={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(MUL_OP)};
	Number ten={.type=NUMBER_TOKEN,.value=10};
	Number ten1={.type=NUMBER_TOKEN,.value=10};
	
	check=calculate(&multiply,&ten,&ten1);
	
	TEST_ASSERT_EQUAL(100,check);
	
}

void test_should_calculate_1000_DIVIDE_10(void)
{
	int check;
	Operator divide={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(DIV_OP)};
	Number thousand={.type=NUMBER_TOKEN,.value=1000};
	Number ten={.type=NUMBER_TOKEN,.value=20};
	
	check=calculate(&divide,&thousand,&ten);
	
	TEST_ASSERT_EQUAL(50,check);
	
}

void test_should_calculate_56_BITWISE_AND_30(void)
{
	int check;
	Operator bitwiseAnd ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(BITWISE_AND_OP)};
	Number fiftySix ={.type=NUMBER_TOKEN,.value=56};
	Number thirty ={.type=NUMBER_TOKEN,.value=30};
	
	check=calculate(&bitwiseAnd,&fiftySix,&thirty);
	
	TEST_ASSERT_EQUAL(24,check);
	
}

void test_should_calculate_56_LOGICAL_AND_30(void)
{
	int check;
	Operator logicalAnd ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(LOGICAL_AND_OP)};
	Number fiftySix ={.type=NUMBER_TOKEN,.value=56};
	Number thirty ={.type=NUMBER_TOKEN,.value=30};
	
	check=calculate(&logicalAnd,&fiftySix,&thirty);
	
	TEST_ASSERT_EQUAL(1,check);
	
}

void test_should_calculate_90_BITWISE_OR_20(void)
{
	int check;
	Operator bitwiseOR ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(BITWISE_OR_OP)};
	Number ninety ={.type=NUMBER_TOKEN,.value=90};
	Number twenty ={.type=NUMBER_TOKEN,.value=20};
	
	check=calculate(&bitwiseOR,&ninety,&twenty);
	
	TEST_ASSERT_EQUAL(94,check);
	
}

void test_should_calculate_90_LOGICAL_OR_20(void)
{
	int check;
	Operator logicalOR ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(LOGICAL_OR_OP)};
	Number ninety ={.type=NUMBER_TOKEN,.value=90};
	Number twenty ={.type=NUMBER_TOKEN,.value=20};
	
	check=calculate(&logicalOR,&ninety,&twenty);
	
	TEST_ASSERT_EQUAL(1,check);
	
}

void test_should_calculate_99_BITWISE_XOR_66(void)
{
	int check;
	Operator bitwiseXOR ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(BITWISE_XOR_OP)};
	Number ninetyNine ={.type=NUMBER_TOKEN,.value=99};
	Number sistySix ={.type=NUMBER_TOKEN,.value=66};
	
	check=calculate(&bitwiseXOR,&ninetyNine,&sistySix);
	
	TEST_ASSERT_EQUAL(33,check);
	
}

void test_should_calculate_55_MODULUS_3(void)
{
	int check;
	Operator modulus ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(MOD_OP)};
	Number fiftyFive ={.type=NUMBER_TOKEN,.value=55};
	Number three ={.type=NUMBER_TOKEN,.value=3};
	
	check=calculate(&modulus,&fiftyFive,&three);
	
	TEST_ASSERT_EQUAL(1,check);
	
}

void test_should_calculate_68_MODULUS_7(void)
{
	int check;
	Operator modulus ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(MOD_OP)};
	Number sixtyEight ={.type=NUMBER_TOKEN,.value=68};
	Number seven ={.type=NUMBER_TOKEN,.value=7};
	
	check=calculate(&modulus,&sixtyEight,&seven);
	
	TEST_ASSERT_EQUAL(5,check);
	
}

void test_should_prefixCalculate_bitwise_not_op(void){
	int check;
	Operator bitwiseNOT ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(BITWISE_NOT_OP)};
	Number ten ={.type=NUMBER_TOKEN,.value=10};
	
	check=prefixCalculate(&bitwiseNOT,&ten);
	
	TEST_ASSERT_EQUAL(-11,check);
	
}

void test_should_prefixCalculate_logical_not_op(void){
	int check;
	Operator bitwiseNOT ={.type=OPERATOR_TOKEN,.info=operatorFindInfoByID(LOGICAL_NOT_OP)};
	Number ten ={.type=NUMBER_TOKEN,.value=10};
	
	check=prefixCalculate(&bitwiseNOT,&ten);
	
	TEST_ASSERT_EQUAL(0,check);
	
}

void test_Calculate_should_throw_error_if_accept_invalid_operator_token(void){
	CEXCEPTION_T e;
	int check;
	Operator hashTAG ={.type=OPERATOR_TOKEN, .info=operatorFindInfoByID(HASH_OP)};
	Number ten ={.type=NUMBER_TOKEN,.value=10};
	Number seven ={.type=NUMBER_TOKEN,.value=7};
	
	Try{
		check=calculate(&hashTAG,&ten,&seven);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR,e);
	}
	
}

void test_prefixCalculate_should_throw_error_if_accept_invalid_operator_token(void){
	CEXCEPTION_T e;
	int check;
	Operator hashTAG ={.type=OPERATOR_TOKEN, .info=operatorFindAlternateInfoByID(HASH_OP)};
	Number ten ={.type=NUMBER_TOKEN,.value=10};
	
	
	Try{
		check=prefixCalculate(&hashTAG,&ten);
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_OPERATOR,e);
	}
	
}


