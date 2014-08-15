#include "unity.h"
#include "Interpret.h"
#include "FileRegister.h"
#include "Execute.h"
#include "CException.h"
#include "ExecutionTable.h"
#include "String.h"
#include "StringObject.h"
#include "Token.h"
#include "Text.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CustomTypeAssert.h"
#include "FA.h"
#include "FBA.h"
#include "FDA.h"
#include "FsFd.h"
#include "K.h"
#include "N.h"
#include "NS.h"
#include "S.h"
#include "ExtractValue.h"
#include "Extract1BitsAccessBanked.h"
#include "Extract3BitsValue.h"
#include "Extract1BitsDestination.h"
#include "MaskTable.h"
#include "mock_Evaluate.h"
#include "Extract1BitsValue.h"

void setUp(void){}
void tearDown(void){}


void test_extractValue_should_return_correct_value_in_integer(void){
	Text *text = textNew("12+34,f,BANKED");
	String *string = stringNew(text);

	char *stringMock = "12+34";
	int test;

	evaluate_ExpectAndReturn(stringMock,46);
	test = extractValue(string);

	TEST_ASSERT_EQUAL(46,test);
}

void test_extractValue_should_throw_error_with_empty_argument(void){
	Text *text = textNew("      ; ");
	String *string = stringNew(text);

	int test,e;

	Try{
		test = extractValue(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

void test_extractValue_should_throw_error_with_empty_argument_semicolon(void){
	Text *text = textNew(";123 ");
	String *string = stringNew(text);

	int test,e;

	Try{
		test = extractValue(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

void test_extractValue_should_get_thrown_in_evaluate(void){
	Text *text = textNew("    12+34abc   ,yaomie");
	String *string = stringNew(text);

	char *stringMock = "12+34abc";
	int test,e;

	evaluate_ExpectAndThrow(stringMock,ERR_ILLEGAL_ARGUMENT);

	Try{
		test = extractValue(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_ILLEGAL_ARGUMENT,e);
	}
}

void test_extractValue_should_supports_FsFd_instruction(void){
	Text *text = textNew(" 123  , 321");
	String *string = stringNew(text);

	char *stringMock;
	int test;

	stringMock = "123";
	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "321";
	evaluate_ExpectAndReturn(stringMock,321);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(321,test);
}

void test_extractDestination_should_return_correct_value_in_integer(void){
	Text *text = textNew("12+34,F,BANKED");
	String *string = stringNew(text);

	char *stringMock = "12+34";
	int test;

	evaluate_ExpectAndReturn(stringMock,46);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(46,test);

	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);
}

void test_extractDestination_should_throw_error_with_empty_argument(void){
	Text *text = textNew("      ; ");
	String *string = stringNew(text);

	int test,e;

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT,e);
	}
}

void test_extractDestination_should_throw_error_with_empty_argument_semicolon(void){
	Text *text = textNew(";F ");
	String *string = stringNew(text);

	int test,e;

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

void test_extractDestination_should_get_value_from_evaluate(void){
	Text *text = textNew("123,  1    ,BANKED");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "1";
	evaluate_ExpectAndReturn(stringMock,1);
	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

}

void test_extractDestination_should_get_value_from_F(void){
	Text *text = textNew("123,  F   ,BANKED");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

}

void test_extractDestination_should_throw_with_invalid_argument(void){
	Text *text = textNew("123,  FA   ,BANKED");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "FA";
	evaluate_ExpectAndThrow(stringMock,ERR_ILLEGAL_ARGUMENT);

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_ILLEGAL_ARGUMENT,e);
	}

}

void test_extractACCESSBANKED_should_return_correct_value_in_integer(void){
	Text *text = textNew("12+34,F,3");
	String *string = stringNew(text);

	char *stringMock = "12+34";
	int test;

	evaluate_ExpectAndReturn(stringMock,46);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(46,test);

	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

	stringMock = "3";
	evaluate_ExpectAndReturn(stringMock,3);
	test = extractACCESSBANKED(string);
	TEST_ASSERT_EQUAL(3,test);
}

void test_extractACCESSBANKED_should_throw_error_with_empty_argument(void){
	Text *text = textNew(" 123, F,     ; ");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "F";
	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

	Try{
		test = extractACCESSBANKED(string);
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT,e);
	}
}

void test_extractACCESSBANKED_should_throw_error_with_empty_argument_semicolon(void){
	Text *text = textNew("123,  F   ;");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "F";
	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

	Try{
		test = extractACCESSBANKED(string);
	}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

void test_extractAccessBaked_should_get_value_from_ACCESS(void){
	Text *text = textNew("1+2,  F   ,ACCESS");
	String *string = stringNew(text);

	char *stringMock = "1+2";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,3);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(3,test);

	stringMock = "F";
	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

	stringMock = "ACCESS";
	test = extractACCESSBANKED(string);
	TEST_ASSERT_EQUAL(0,test);

}

void test_extractACCESSBANKED_should_get_value_from_evaluate(void){
	Text *text = textNew("   123   , 1    ,1+2");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	stringMock = "1";
	evaluate_ExpectAndReturn(stringMock,1);
	test = extractDestination(string);
	TEST_ASSERT_EQUAL(1,test);

	stringMock = "1+2";
	evaluate_ExpectAndReturn(stringMock,3);
	test = extractACCESSBANKED(string);
	TEST_ASSERT_EQUAL(3,test);

}

  void test_extractValue_should_able_to_throw_NO_ARGUMENT_for_both(void){
	Text *text = textNew("123   ");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}

	Try{
		test = extractACCESSBANKED(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

 void test_extractValue_should_able_to_throw_EMPTY_ARGUMENT(void){
	Text *text = textNew("123,   , ");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT,e);
	}

	Try{
		test = extractACCESSBANKED(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT,e);
	}
}

 void test_extractValue_should_able_to_throw_NO_ARGUMENT(void){
	Text *text = textNew("123,    ");
	String *string = stringNew(text);

	char *stringMock = "123";
	int test,e;

	evaluate_ExpectAndReturn(stringMock,123);
	test = extractValue(string);
	TEST_ASSERT_EQUAL(123,test);

	Try{
		test = extractDestination(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EMPTY_ARGUMENT,e);
	}

	Try{
		test = extractACCESSBANKED(string);}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_NO_ARGUMENT,e);
	}
}

void test_getInstruction_should_get_opCode_RLNCF(){

	instructionTable test;

	test = getInstruction("RLNCF");
	TEST_ASSERT_EQUAL_HEX16(0x4400,test.opCode);
	TEST_ASSERT_EQUAL(FDA_TYPE,test.type);
}

void test_getInstruction_should_get_opCode_RETLW(){

	instructionTable test;

	test = getInstruction("RETLW");
	TEST_ASSERT_EQUAL_HEX16(0x0C00,test.opCode);
	TEST_ASSERT_EQUAL(K_TYPE,test.type);
}

void test_interpret_should_able_to_run_FDA_ADDWF(){
	Text *text = textNew(" ADDWF  0x180, F");
	String *string = stringNew(text);

	char *stringMock = "0x180";
	evaluate_ExpectAndReturn(stringMock,0x180);

	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0x2780,test);

}

void test_interpret_should_able_to_run_FA_CLRF(){
	Text *text = textNew(" CLRF  0x210");
	String *string = stringNew(text);

	char *stringMock = "0x210";
	evaluate_ExpectAndReturn(stringMock,0x210);
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0x6b10,test);

}

void test_interpret_should_able_to_run_FBA_BCF(){
	Text *text = textNew(" BCF  0x10, 5, ACCESS ");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	stringMock = "5";
	evaluate_ExpectAndReturn(stringMock,0x5);
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0x9a10,test);

}

void test_interpret_should_able_to_run_FsFd_MOVFF(){
	Text *text = textNew(" MOVFF  0x10, 0x11 ");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	stringMock = "0x11";
	evaluate_ExpectAndReturn(stringMock,0x11);
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0xf011c010,test);

}

void test_interpret_should_able_to_run_K_ADDLW(){
	Text *text = textNew(" ADDLW  0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0x0f10,test);

}

void test_interpret_should_able_to_run_NS_CALL(){
	Text *text = textNew(" CALL  0x12345, 1");
	String *string = stringNew(text);

	char *stringMock = "0x12345";
	evaluate_ExpectAndReturn(stringMock,0x12345);
	
	stringMock = "1";
	evaluate_ExpectAndReturn(stringMock,1);
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0xf123ed45,test);

}

void test_interpret_should_able_to_run_N8_BC(){
	Text *text = textNew(" BC 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0xe210,test);

}

void test_interpret_should_able_to_run_N11_BRA(){
	Text *text = textNew(" BRA 0x7ff");
	String *string = stringNew(text);

	char *stringMock = "0x7ff";
	evaluate_ExpectAndReturn(stringMock,0x7ff);
	
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0xd7ff,test);

}

void test_interpret_should_able_to_run_N12_GOTO(){
	Text *text = textNew(" GOTO 0x12345");
	String *string = stringNew(text);

	char *stringMock = "0x12345";
	evaluate_ExpectAndReturn(stringMock,0x12345);
	
	int test = interpret(string);

	TEST_ASSERT_EQUAL_HEX32(0xf123ef45,test);

}

void test_runProgram_should_able_to_run_MOVWF(){
	Text *text = textNew(" MOVWF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x5;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x5,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_ADDWF(){
	Text *text = textNew(" ADDWF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x5;
	fileRegisters[0x10] = 0x10;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x15,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_ADDWFC(){
	Text *text = textNew(" ADDWFC 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[STATUS] = 0x01;
	fileRegisters[WREG] = 0x5;
	fileRegisters[0x10] = 0x10;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x16,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_ANDWF(){
	Text *text = textNew(" ANDWF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x11;
	fileRegisters[0x10] = 0x12;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_CLRF(){
	Text *text = textNew(" CLRF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	
	fileRegisters[0x10] = 0x12;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_COMF(){
	Text *text = textNew(" COMF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	
	fileRegisters[0x10] = 0x12;
	
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0xED,fileRegisters[0x10]);
}

void test_runProgram_should_able_to_run_CPFSEQ(){
	Text *text = textNew(" CPFSEQ 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x12;
	fileRegisters[0x10] = 0x12;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x12,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x04,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_CPFSGT(){
	Text *text = textNew(" CPFSGT 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x13;
	fileRegisters[0x10] = 0x12;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x12,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x04,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_CPFSLT(){
	Text *text = textNew(" CPFSLT 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x12;
	fileRegisters[0x10] = 0x13;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x13,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x04,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_DECF(){
	Text *text = textNew(" DECF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x13;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x12,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_DECFSZ(){
	Text *text = textNew(" DECFSZ 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x01;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_DCFSNZ(){
	Text *text = textNew(" DCFSNZ 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x0F,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x04,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_INCF(){
	Text *text = textNew(" INCF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x11,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_INCFSZ(){
	Text *text = textNew(" INCFSZ 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0xff;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x00,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_INFSNZ(){
	Text *text = textNew(" INFSNZ 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x11,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_IORWF(){
	Text *text = textNew(" IORWF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	

	fileRegisters[0x10] = 0x10;
	fileRegisters[WREG] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[0x10]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_MOVF(){
	Text *text = textNew(" MOVF 0x10");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	
	fileRegisters[WREG] = 0x11;
	fileRegisters[0x10] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[WREG]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}

void test_runProgram_should_able_to_run_MOVFF(){
	Text *text = textNew(" MOVFF 0x10,0x12");
	String *string = stringNew(text);

	char *stringMock = "0x10";
	evaluate_ExpectAndReturn(stringMock,0x10);
	char *stringMock1 = "0x12";
	evaluate_ExpectAndReturn(stringMock1,0x12);
	
	fileRegisters[0x12] = 0x11;
	fileRegisters[0x10] = 0x10;
	fileRegisters[PCLATU] = 0x00;
	fileRegisters[PCLATH] = 0x00;
	fileRegisters[PCL] = 0x00;
	runProgram(string);
	
	TEST_ASSERT_EQUAL_HEX16(0x10,fileRegisters[0x12]);
	TEST_ASSERT_EQUAL(0x02,fileRegisters[PCL]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATU]);
	TEST_ASSERT_EQUAL(0x00,fileRegisters[PCLATH]);
}







