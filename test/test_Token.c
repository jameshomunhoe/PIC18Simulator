#include "unity.h"
#include "Token.h"
#include "Text.h"
#include "StringObject.h"
#include "CharSet.h"
#include "CException.h"
#include "ErrorCode.h"
#include "CustomTypeAssert.h"

void setUp(void) {}
void tearDown(void) {}

void test_getToken_should_get_5(void) {
	Number *number = numberNew(5);
	
	TEST_ASSERT_EQUAL(5,number->value);                                                                                                                                                                                                                                                                                                                                                                                                           
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,number->type);
}

void test_getToken_should_get_100(void) {
	Number *number = numberNew(100);
	
	TEST_ASSERT_EQUAL(100,number->value);                                                                                                                                                                                                                                                                                                                                                                                                           
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,number->type);
}

void test_identifierNew_should_get_return_details(void) {
	int toCompare;
	Text *text = textNew("Yeah");
	Identifier *identifier = identifierNew(text);
	
	toCompare = strcmp("Yeah",identifier->name->string);
	TEST_ASSERT_EQUAL(0,toCompare);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,identifier->type);
}

void test_identifierNew_should_get_return_details_2(void) {
	int toCompare;
	Text *text = textNew("YaoMie");
	Identifier *identifier = identifierNew(text);
	
	toCompare = strcmp("YaoMie",identifier->name->string);
	TEST_ASSERT_EQUAL(0,toCompare);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,identifier->type);
}

void test_operatorNewBySymbol_should_create(){
	int toCompare;
	Operator *operator = operatorNewBySymbol("&&");
	
	toCompare = strcmp(operator->info->symbol,"&&");
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,operator->type);
	TEST_ASSERT_EQUAL(30,operator->info->precedence);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,operator->info->id);
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_operatorNewBySymbol_should_create2(){
	int toCompare;
	Operator *operator = operatorNewBySymbol("~");
	
	toCompare = strcmp(operator->info->symbol,"~");
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,operator->type);
	TEST_ASSERT_EQUAL(150,operator->info->precedence);
	TEST_ASSERT_EQUAL(BITWISE_NOT_OP,operator->info->id);
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_operatorNewBySymbol_should_retun_NULL(){
	int toCompare;
	Operator *operator = operatorNewBySymbol("?");
	
	TEST_ASSERT_EQUAL(NULL,operator);
}

void test_operatorNewByID_should_create(){
	int toCompare;
	Operator *operator = operatorNewByID(BITWISE_NOT_OP);
	
	toCompare = strcmp(operator->info->symbol,"~");
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,operator->type);
	TEST_ASSERT_EQUAL(150,operator->info->precedence);
	TEST_ASSERT_EQUAL(BITWISE_NOT_OP,operator->info->id);
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_operatorNewByID_should_create2(){
	int toCompare;
	Operator *operator = operatorNewByID(LOGICAL_AND_OP);
	
	toCompare = strcmp(operator->info->symbol,"&&");
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,operator->type);
	TEST_ASSERT_EQUAL(30,operator->info->precedence);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,operator->info->id);
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_operatorNewByID_should_retun_NULL(){
	int toCompare;
	Operator *operator = operatorNewByID(123);
	
	TEST_ASSERT_EQUAL(NULL,operator);
}

void test_getToken_sould_return_NumberToken_324(void){
	int test;
	Text *text = textNew("324 123 435 01010");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(324,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String(" 123 435 01010",string);
}

void test_getToken_sould_return_NumberToken_123(void){
	int test;
	Text *text = textNew("123 me nem is cheeliang");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String(" me nem is cheeliang",string);
}

void test_getToken_sould_return_NumberToken_123_without_ending_with_space(void){
	int test;
	Text *text = textNew("123");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String("",string);
}

void test_getToken_sould_return_IdentifierToken_AuCheeLiang(void){
	int test;
	Text *text = textNew("AuCheeLiang + ChiewBingXuan = bff");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("AuCheeLiang",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" + ChiewBingXuan = bff",string);
}

void test_getToken_should_return_IdentifierToken_ChiewBingXuan(void){
	int test;
	Text *text = textNew("ChiewBingXuan 23+ ChiewB32ringXuan = bff");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("ChiewBingXuan",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" 23+ ChiewB32ringXuan = bff",string);
}

void test_getToken_sould_return_IdentifierToken_AuCheeLiang_without_ending_with_space(void){
	int test;
	Text *text = textNew("AuCheeLiang");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("AuCheeLiang",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String("",string);
}
void test_getToken_should_return_OperatorToken_BITWISE_NOT_OP(void){
	int test;
	Text *text = textNew("~ ahahaha hehehe hoho");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("~",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(BITWISE_NOT_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(150,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" ahahaha hehehe hoho",string);
}

void test_getToken_should_return_OperatorToken_BITWISE_AND_OP(void){
	int test;
	Text *text = textNew("   & ahahaha");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("&",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(BITWISE_AND_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(60,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" ahahaha",string);
}

void test_getToken_should_return_OperatorToken_LOGICAL_AND_OP(void){
	int test;
	Text *text = textNew("   && 123sdv  we");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("&&",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(30,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 123sdv  we",string);
}

void test_getToken_should_return_OperatorToken_LOGICAL_OR_OP(void){
	int test;
	Text *text = textNew("   || 123sdv  we");
	String *string = stringNew(text);
	Token *token;
	
	token = getToken(string);
	
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("||",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(LOGICAL_OR_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(20,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 123sdv  we",string);
}

void test_getToken_sould_Throw_an_error_with_mixed_up_number_and_alphabet(void){
	int test,e;
	Text *text = textNew(" 1me nem is cheeliang");
	String *string = stringNew(text);
	Token *token;
	
	Try{
	token = getToken(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NUMBER_NOT_WELL_FORMED,e);
	}
}

void test_getToken_sould_Throw_an_error_with_mixed_up_number_and_operator(void){
	int test,e;
	Text *text = textNew(" 1+1 me nem is cheeliang");
	String *string = stringNew(text);
	Token *token;
	
	Try{
	token = getToken(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NUMBER_NOT_WELL_FORMED,e);
	}
}

void test_getToken_sould_Throw_an_error_with_mixed_up_all_together(void){
	int test,e;
	Text *text = textNew("1T@#%@#%@#232fef me nem is cheeliang");
	String *string = stringNew(text);
	Token *token;
	
	Try{
	token = getToken(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NUMBER_NOT_WELL_FORMED,e);
	}
}

void test_getToken_multiple_times_abc_BITWISE_NOT_OP_123(void){
	Text *text = textNew("  abc ~ 123");
	String *string = stringNew(text);
	Token *token;
	
	//Test for abc
	token = getToken(string);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("abc",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" ~ 123",string);
	
	//Test for +
	token = getToken(string);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("~",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(BITWISE_NOT_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(150,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 123",string);
	
	//Test for 123
	token = getToken(string);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String("",string);
}

void test_getToken_multiple_times_abc_LOGICAL_AND_OP_123(void){
	Text *text = textNew("  abc && 123");
	String *string = stringNew(text);
	Token *token;
	
	//Test for abc
	token = getToken(string);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("abc",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" && 123",string);
	
	//Test for &&
	token = getToken(string);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("&&",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(30,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 123",string);
	
	//Test for 123
	token = getToken(string);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String("",string);
}

void test_getToken_multiple_times_abc_LOGICAL_AND_OP_12a3_should_throw_error(void){
	int e;
	Text *text = textNew("  abc && 12a3");
	String *string = stringNew(text);
	Token *token;
	
	//Test for abc
	token = getToken(string);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("abc",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" && 12a3",string);
	
	//Test for &&
	token = getToken(string);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("&&",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(30,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 12a3",string);
	
	//Test for 123
	Try{
	token = getToken(string);}
	Catch(e){
	TEST_ASSERT_EQUAL(ERR_NUMBER_NOT_WELL_FORMED,e);
	}
	
	// TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	// TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	// TEST_ASSERT_EQUAL_String("",string);
}



void test_tokenDel_should_not_cause_error(){
	Text *text = textNew("  abc && 123");
	String *string = stringNew(text);
	Token *token;
	
	//Test for abc
	token = getToken(string);
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("abc",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String(" && 123",string);
	tokenDel(token);
	
	//Test for &&
	token = getToken(string);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("&&",((Operator *)token)->info->symbol);
	TEST_ASSERT_EQUAL(LOGICAL_AND_OP,((Operator *)token)->info->id);
	TEST_ASSERT_EQUAL(30,((Operator *)token)->info->precedence);
	TEST_ASSERT_EQUAL_String(" 123",string);
	tokenDel(token);
	
	//Test for 123
	token = getToken(string);
	TEST_ASSERT_EQUAL(NUMBER_TOKEN,token->type);
	TEST_ASSERT_EQUAL(123,((Number *)token)->value);
	TEST_ASSERT_EQUAL_String("",string);
	tokenDel(token);

}

void test_getToken_sould_throw_error_mix_Number_Identifier(void){
	int test,e;
	Text *text = textNew("123ABC");
	String *string = stringNew(text);
	Token *token;
	
	Try{
		token = getToken(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NUMBER_NOT_WELL_FORMED,e);
	}
}

void test_getToken_sould_not_throw_error_mix_Identifier_Number(void){
	int test;
	Text *text = textNew("ABC123");
	String *string = stringNew(text);
	Token *token;
	

		token = getToken(string);

	
	TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING("ABC123",((Identifier *)token)->name->string);
	TEST_ASSERT_EQUAL_String("",string);
}


void test_getToken_should_fix_bug_for_close_bracket(void){
	Text *text = textNew(")");
	String *string = stringNew(text);
	Token *token;
	
	//Test for abc
	token = getToken(string);
	TEST_ASSERT_EQUAL(OPERATOR_TOKEN,token->type);
	TEST_ASSERT_EQUAL_STRING(")",((Operator *)token)->info->symbol);
	
}

