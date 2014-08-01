#include "unity.h"
#include "Token.h"
#include "Text.h"
#include "StringObject.h"
#include "ErrorCode.h"
#include "CustomTypeAssert.h"
#include "CharSet.h"
#include "CException.h"


void setUp(void) {}

void tearDown(void) {}



void test_getToken_should_get_5(void) {

 Number *number = numberNew(5);



 UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((number->value)), (((void *)0)), (_U_UINT)16, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((number->type)), (((void *)0)), (_U_UINT)17, UNITY_DISPLAY_STYLE_INT);

}



void test_getToken_should_get_100(void) {

 Number *number = numberNew(100);



 UnityAssertEqualNumber((_U_SINT)((100)), (_U_SINT)((number->value)), (((void *)0)), (_U_UINT)23, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((number->type)), (((void *)0)), (_U_UINT)24, UNITY_DISPLAY_STYLE_INT);

}



void test_identifierNew_should_get_return_details(void) {

 int toCompare;

 Text *text = textNew("Yeah");

 Identifier *identifier = identifierNew(text);



 toCompare = strcmp("Yeah",identifier->name->string);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)33, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((identifier->type)), (((void *)0)), (_U_UINT)34, UNITY_DISPLAY_STYLE_INT);

}



void test_identifierNew_should_get_return_details_2(void) {

 int toCompare;

 Text *text = textNew("YaoMie");

 Identifier *identifier = identifierNew(text);



 toCompare = strcmp("YaoMie",identifier->name->string);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)43, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((identifier->type)), (((void *)0)), (_U_UINT)44, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewBySymbol_should_create(){

 int toCompare;

 Operator *operator = operatorNewBySymbol("&&");



 toCompare = strcmp(operator->info->symbol,"&&");

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((operator->type)), (((void *)0)), (_U_UINT)52, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((operator->info->precedence)), (((void *)0)), (_U_UINT)53, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((operator->info->id)), (((void *)0)), (_U_UINT)54, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)55, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewBySymbol_should_create2(){

 int toCompare;

 Operator *operator = operatorNewBySymbol("~");



 toCompare = strcmp(operator->info->symbol,"~");

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((operator->type)), (((void *)0)), (_U_UINT)63, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((operator->info->precedence)), (((void *)0)), (_U_UINT)64, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_NOT_OP)), (_U_SINT)((operator->info->id)), (((void *)0)), (_U_UINT)65, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)66, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewBySymbol_should_retun_NULL(){

 int toCompare;

 Operator *operator = operatorNewBySymbol("?");



 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((operator)), (((void *)0)), (_U_UINT)73, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewByID_should_create(){

 int toCompare;

 Operator *operator = operatorNewByID(BITWISE_NOT_OP);



 toCompare = strcmp(operator->info->symbol,"~");

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((operator->type)), (((void *)0)), (_U_UINT)81, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((operator->info->precedence)), (((void *)0)), (_U_UINT)82, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_NOT_OP)), (_U_SINT)((operator->info->id)), (((void *)0)), (_U_UINT)83, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)84, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewByID_should_create2(){

 int toCompare;

 Operator *operator = operatorNewByID(LOGICAL_AND_OP);



 toCompare = strcmp(operator->info->symbol,"&&");

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((operator->type)), (((void *)0)), (_U_UINT)92, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((operator->info->precedence)), (((void *)0)), (_U_UINT)93, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((operator->info->id)), (((void *)0)), (_U_UINT)94, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((toCompare)), (((void *)0)), (_U_UINT)95, UNITY_DISPLAY_STYLE_INT);

}



void test_operatorNewByID_should_retun_NULL(){

 int toCompare;

 Operator *operator = operatorNewByID(123);



 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((operator)), (((void *)0)), (_U_UINT)102, UNITY_DISPLAY_STYLE_INT);

}



void test_getToken_sould_return_NumberToken_324(void){

 int test;

 Text *text = textNew("324 123 435 01010");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)113, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((324)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)114, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123 435 01010"), (string), 115, ((void *)0));

}



void test_getToken_sould_return_NumberToken_123(void){

 int test;

 Text *text = textNew("123 me nem is cheeliang");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)126, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((123)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)127, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" me nem is cheeliang"), (string), 128, ((void *)0));

}



void test_getToken_sould_return_NumberToken_123_without_ending_with_space(void){

 int test;

 Text *text = textNew("123");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)138, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((123)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)139, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((""), (string), 140, ((void *)0));

}



void test_getToken_sould_return_IdentifierToken_AuCheeLiang(void){

 int test;

 Text *text = textNew("AuCheeLiang + ChiewBingXuan = bff");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)151, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("AuCheeLiang"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)152);

 assertStringEqual((" + ChiewBingXuan = bff"), (string), 153, ((void *)0));

}



void test_getToken_should_return_IdentifierToken_ChiewBingXuan(void){

 int test;

 Text *text = textNew("ChiewBingXuan 23+ ChiewB32ringXuan = bff");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)164, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("ChiewBingXuan"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)165);

 assertStringEqual((" 23+ ChiewB32ringXuan = bff"), (string), 166, ((void *)0));

}



void test_getToken_sould_return_IdentifierToken_AuCheeLiang_without_ending_with_space(void){

 int test;

 Text *text = textNew("AuCheeLiang");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)177, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("AuCheeLiang"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)178);

 assertStringEqual((""), (string), 179, ((void *)0));

}

void test_getToken_should_return_OperatorToken_BITWISE_NOT_OP(void){

 int test;

 Text *text = textNew("~ ahahaha hehehe hoho");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)189, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("~"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)190);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_NOT_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)191, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)192, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" ahahaha hehehe hoho"), (string), 193, ((void *)0));

}



void test_getToken_should_return_OperatorToken_BITWISE_AND_OP(void){

 int test;

 Text *text = textNew("   & ahahaha");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)204, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("&"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)205);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_AND_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)206, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((60)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)207, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" ahahaha"), (string), 208, ((void *)0));

}



void test_getToken_should_return_OperatorToken_LOGICAL_AND_OP(void){

 int test;

 Text *text = textNew("   && 123sdv  we");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)219, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("&&"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)220);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)221, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)222, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123sdv  we"), (string), 223, ((void *)0));

}



void test_getToken_should_return_OperatorToken_LOGICAL_OR_OP(void){

 int test;

 Text *text = textNew("   || 123sdv  we");

 String *string = stringNew(text);

 Token *token;



 token = getToken(string);



 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)234, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("||"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)235);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_OR_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)236, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((20)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)237, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123sdv  we"), (string), 238, ((void *)0));

}



void test_getToken_sould_Throw_an_error_with_mixed_up_number_and_alphabet(void){

 int test,e;

 Text *text = textNew(" 1me nem is cheeliang");

 String *string = stringNew(text);

 Token *token;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame){

 token = getToken(string);}

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { e = CExceptionFrames[MY_ID].Exception; e=e; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

  UnityAssertEqualNumber((_U_SINT)((ERR_NUMBER_NOT_WELL_FORMED)), (_U_SINT)((e)), (((void *)0)), (_U_UINT)250, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_getToken_sould_Throw_an_error_with_mixed_up_number_and_operator(void){

 int test,e;

 Text *text = textNew(" 1+1 me nem is cheeliang");

 String *string = stringNew(text);

 Token *token;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame){

 token = getToken(string);}

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { e = CExceptionFrames[MY_ID].Exception; e=e; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

  UnityAssertEqualNumber((_U_SINT)((ERR_NUMBER_NOT_WELL_FORMED)), (_U_SINT)((e)), (((void *)0)), (_U_UINT)263, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_getToken_sould_Throw_an_error_with_mixed_up_all_together(void){

 int test,e;

 Text *text = textNew("1T@#%@#%@#232fef me nem is cheeliang");

 String *string = stringNew(text);

 Token *token;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame){

 token = getToken(string);}

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { e = CExceptionFrames[MY_ID].Exception; e=e; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

  UnityAssertEqualNumber((_U_SINT)((ERR_NUMBER_NOT_WELL_FORMED)), (_U_SINT)((e)), (((void *)0)), (_U_UINT)276, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_getToken_multiple_times_abc_BITWISE_NOT_OP_123(void){

 Text *text = textNew("  abc ~ 123");

 String *string = stringNew(text);

 Token *token;





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)287, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("abc"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)288);

 assertStringEqual((" ~ 123"), (string), 289, ((void *)0));





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)293, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("~"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)294);

 UnityAssertEqualNumber((_U_SINT)((BITWISE_NOT_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)295, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((150)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)296, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123"), (string), 297, ((void *)0));





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)301, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((123)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)302, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((""), (string), 303, ((void *)0));

}



void test_getToken_multiple_times_abc_LOGICAL_AND_OP_123(void){

 Text *text = textNew("  abc && 123");

 String *string = stringNew(text);

 Token *token;





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)313, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("abc"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)314);

 assertStringEqual((" && 123"), (string), 315, ((void *)0));





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)319, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("&&"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)320);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)321, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)322, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123"), (string), 323, ((void *)0));





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)327, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((123)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)328, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((""), (string), 329, ((void *)0));

}



void test_getToken_multiple_times_abc_LOGICAL_AND_OP_12a3_should_throw_error(void){

 int e;

 Text *text = textNew("  abc && 12a3");

 String *string = stringNew(text);

 Token *token;





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)340, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("abc"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)341);

 assertStringEqual((" && 12a3"), (string), 342, ((void *)0));





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)346, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("&&"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)347);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)348, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)349, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 12a3"), (string), 350, ((void *)0));





 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame){

 token = getToken(string);}

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { e = CExceptionFrames[MY_ID].Exception; e=e; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

 UnityAssertEqualNumber((_U_SINT)((ERR_NUMBER_NOT_WELL_FORMED)), (_U_SINT)((e)), (((void *)0)), (_U_UINT)356, UNITY_DISPLAY_STYLE_INT);

 }









}







void test_tokenDel_should_not_cause_error(){

 Text *text = textNew("  abc && 123");

 String *string = stringNew(text);

 Token *token;





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)373, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("abc"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)374);

 assertStringEqual((" && 123"), (string), 375, ((void *)0));

 tokenDel(token);





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((OPERATOR_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)380, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("&&"), (const char*)(((Operator *)token)->info->symbol), (((void *)0)), (_U_UINT)381);

 UnityAssertEqualNumber((_U_SINT)((LOGICAL_AND_OP)), (_U_SINT)((((Operator *)token)->info->id)), (((void *)0)), (_U_UINT)382, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((30)), (_U_SINT)((((Operator *)token)->info->precedence)), (((void *)0)), (_U_UINT)383, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((" 123"), (string), 384, ((void *)0));

 tokenDel(token);





 token = getToken(string);

 UnityAssertEqualNumber((_U_SINT)((NUMBER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)389, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((123)), (_U_SINT)((((Number *)token)->value)), (((void *)0)), (_U_UINT)390, UNITY_DISPLAY_STYLE_INT);

 assertStringEqual((""), (string), 391, ((void *)0));

 tokenDel(token);



}



void test_getToken_sould_throw_error_mix_Number_Identifier(void){

 int test,e;

 Text *text = textNew("123ABC");

 String *string = stringNew(text);

 Token *token;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame){

  token = getToken(string);}

 else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { e = CExceptionFrames[MY_ID].Exception; e=e; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A)){

  UnityAssertEqualNumber((_U_SINT)((ERR_NUMBER_NOT_WELL_FORMED)), (_U_SINT)((e)), (((void *)0)), (_U_UINT)405, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_getToken_sould_not_throw_error_mix_Identifier_Number(void){

 int test;

 Text *text = textNew("ABC123");

 String *string = stringNew(text);

 Token *token;





  token = getToken(string);





 UnityAssertEqualNumber((_U_SINT)((IDENTIFIER_TOKEN)), (_U_SINT)((token->type)), (((void *)0)), (_U_UINT)419, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualString((const char*)("ABC123"), (const char*)(((Identifier *)token)->name->string), (((void *)0)), (_U_UINT)420);

 assertStringEqual((""), (string), 421, ((void *)0));

}
