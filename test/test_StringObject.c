#include "unity.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "string.h"
#include "Text.h"

typedef struct FakeText {
	uint32 reference;
	char string[80];
} FakeText;

void setUp(){}
void tearDown(){}

/*
void test_stringDump_should_print_whole_word(void){
	FakeText fakeText = {
		.reference = 10,
		.string = "hello world!"
	};
	String str = {
		.reference = 20,
		.text = (Text *)&fakeText,
		.start = 0,
		.length = 12
		};
	stringDump(&str);
}

void test_stringDump_should_print_from_fifth_word(void){
	FakeText fakeText = {
		.reference = 10,
		.string = "hello world!"
	};
	String str = {
		.reference = 20,
		.text = (Text *)&fakeText,
		.start = 4,
		.length = 12
		};
	stringDump(&str);
}

void test_stringDump_should_print_only_5_character(void){
	FakeText fakeText = {
		.reference = 10,
		.string = "hello world!"
	};
	String str = {
		.reference = 20,
		.text = (Text *)&fakeText,
		.start = 0,
		.length = 6
		};
	stringDump(&str);
}

void test_stringDump_should_not_print_with_0_length(void){
	FakeText fakeText = {
		.reference = 10,
		.string = "hello world!"
	};
	String str = {
		.reference = 20,
		.text = (Text *)&fakeText,
		.start = 0,
		.length = 0
		};
	stringDump(&str);
}

void test_stringDump_should_not_print_with_overload_start(void){
	FakeText fakeText = {
		.reference = 10,
		.string = "hello world!"
	};
	String str = {
		.reference = 20,
		.text = (Text *)&fakeText,
		.start = 12,
		.length =12
		};
	stringDump(&str);
}
*/


void test_stringNew_should_create_string_with_dynamic_text(void){
	int toCompare;
	Text *text = textNew("FhyanSeng");
	String *str = stringNew(text);
	
	toCompare = strcmp(str->text->string,text->string);
	TEST_ASSERT_EQUAL(0,toCompare);
	TEST_ASSERT_EQUAL(1,str->reference);
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(9,str->length);
	TEST_ASSERT_EQUAL(2,str->text->reference);
}

void test_stringNew_should_create_string_with_static_text(void){
	int toCompare;
	Text *text = t"DreFick";
	String *str = stringNew(text);
	toCompare = strcmp(str->text->string,text->string);
	TEST_ASSERT_EQUAL(0,toCompare);
	TEST_ASSERT_EQUAL(1,str->reference);
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(7,str->length);
	TEST_ASSERT_EQUAL_HEX32(0x80000000,str->text->reference);
}

void test_stringAssign_should_increase_reference(void){
	Text *text = textNew("JaNib");
	String *str = stringNew(text);
	String *str1 = stringAssign(str);
	String *str2 = stringAssign(str);
	TEST_ASSERT_EQUAL(3,str->reference);
	TEST_ASSERT_EQUAL(2,str->text->reference);
}

void test_stringDel_should_delete_and_reduce_text_reference(void){
	String *toCompare;
	Text *text = textNew("MosRah");
	String *str = stringNew(text);
	String *str1 = stringAssign(str);
	String *str2 = stringAssign(str);
	toCompare = stringDel(str);
	TEST_ASSERT_EQUAL(2,toCompare->reference);
	TEST_ASSERT_EQUAL(2,str->text->reference);
}

void test_stringDel_should_delete_and_not_reduce_text_reference(void){
	String *toCompare;
	Text *text = t"SelNon";
	String *str = stringNew(text);
	String *str1 = stringAssign(str);
	String *str2 = stringAssign(str);
	toCompare = stringDel(str);
	TEST_ASSERT_EQUAL(2,toCompare->reference);
	TEST_ASSERT_EQUAL_HEX32(0x80000000,str->text->reference);
}

void test_stringSkip_should_skip(void){
	Text *text = textNew("SelNon");
	String *str = stringNew(text);
	stringSkip(str,2);
	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(4,str->length);
}

void test_stringSkip_should_overload_and_stop_at_Null(void){
	Text *text = textNew("SelNonDan");
	String *str = stringNew(text);
	str->start++; //1
	stringSkip(str,100);
	TEST_ASSERT_EQUAL(9,str->start);
	TEST_ASSERT_EQUAL(0,str->length);
}
void test_stringTrimLeft(void){
	Text *text = textNew("SaJon ");
	String *str = stringNew(text);
	stringTrimLeft(str);
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(6,str->length);
}

void test_stringTrimLeft2(void){
	Text *text = textNew("    HohnJon ");
	String *str = stringNew(text);
	str->start+=3;
	str->length-=3;
	stringTrimLeft(str);
	TEST_ASSERT_EQUAL(4,str->start);
	TEST_ASSERT_EQUAL(8,str->length);
}

void test_stringTrimRight(void){
	Text *text = textNew("    LuJian  ");
	String *str = stringNew(text);
	stringTrimRight(str);
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(10,str->length);
}

void test_stringTrimRight2(void){
	Text *text = textNew("   DeeFer\t");
	String *str = stringNew(text);
	stringTrimRight(str);
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(9,str->length);
}

void test_stringTrim_should_trim_both_sides(void){
	Text *text = textNew("  \t \t \t  VeaLer     ");
	String *str = stringNew(text);
	stringTrim(str);
	TEST_ASSERT_EQUAL(9,str->start);
	TEST_ASSERT_EQUAL(6,str->length);
}

void test_stringTrim_should_trim_both_sides2(void){
	Text *text = textNew("  GaLger \t\t    ");
	String *str = stringNew(text);
	stringTrim(str);
	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(6,str->length);
}

void test_stringTrim_should_trim_both_sides3(void){
	Text *text = textNew(" \t\t BeedFack \t\t    ");
	String *str = stringNew(text);
	stringTrim(str);
	TEST_ASSERT_EQUAL(4,str->start);
	TEST_ASSERT_EQUAL(8,str->length);
}

void test_all(void){
	String *toCompare;
	Text *text = textNew(" \t\t ahaha \t\t    ");
	
	String *str = stringNew(text);
	String *str2 = stringAssign(str);
	TEST_ASSERT_EQUAL(2,text->reference);

	toCompare = stringDel(str); //still got 1
	TEST_ASSERT_EQUAL(2,text->reference);
	TEST_ASSERT_EQUAL(1,toCompare->reference);
	
	toCompare = stringDel(str); //no more
	//unable to TEST_ASSERT_EQUAL, bad memory because already removed
	//TEST_ASSERT_EQUAL(0,text->reference);
	
	// stringTrim(str);
	// TEST_ASSERT_EQUAL(4,str->start);
	// TEST_ASSERT_EQUAL(5,str->length);
}

void test_stringRemoveChar_should_remove_w(void){
	char toCompare;
	Text *text = textNew("wahaha");
	String *str = stringNew(text);
	
	toCompare = stringRemoveChar(str);
	TEST_ASSERT_EQUAL('w',toCompare);
	TEST_ASSERT_EQUAL(5,str->length);
	TEST_ASSERT_EQUAL(1,str->start);
}

void test_stringRemoveChar_should_remove_spacing(void){
	char toCompare;
	Text *text = textNew("   iana");
	String *str = stringNew(text);
	
	toCompare = stringRemoveChar(str);
	TEST_ASSERT_EQUAL(' ',toCompare);	
	TEST_ASSERT_EQUAL(6,str->length);
	TEST_ASSERT_EQUAL(1,str->start);
}

void test_stringRemoveChar_should_return_negative_one_after_deletion(void){
	char toCompare;
	Text *text = textNew("a");
	String *str = stringNew(text);
	
	toCompare = stringRemoveChar(str);
	TEST_ASSERT_EQUAL('a',toCompare);
	TEST_ASSERT_EQUAL(0,str->length);
	TEST_ASSERT_EQUAL(0,str->start);
}

void test_stringRemoveChar_should_return_negative_one_with_NULL_input(void){
	char toCompare;
	Text *text = textNew("");
	String *str = stringNew(text);
	
	toCompare = stringRemoveChar(str);
	TEST_ASSERT_EQUAL(-1,toCompare);
	TEST_ASSERT_EQUAL(0,str->length);
	TEST_ASSERT_EQUAL(0,str->start);
}

void test_stringLength_should_get_6(void){
	int toCompareLength;
	Text *text = textNew("abcdefg");
	String *str = stringNew(text);
	
	toCompareLength = stringLength(str);
	TEST_ASSERT_EQUAL(7,toCompareLength);
}

void test_stringLength_should_get_16(void){
	int toCompareLength;
	Text *text = textNew(" \t \t \t 16 length");
	String *str = stringNew(text);
	
	toCompareLength = stringLength(str);
	TEST_ASSERT_EQUAL(16,toCompareLength);
}

void test_stringRemoveWordNotContaining_remove_abcd(void){
	int toCompare;
	Text *text = textNew("abcdefghi");
	String *str = stringNew(text);
	String *test = stringRemoveWordNotContaining(str,"ei");
	
	TEST_ASSERT_EQUAL(4,str->start);
	TEST_ASSERT_EQUAL(5,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(4,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}
void test_stringRemoveWordNotContaining_remove_abcd_static(void){
	int toCompare;
	Text *text = t"abcdefghi";
	String *str = stringNew(text);
	String *test = stringRemoveWordNotContaining(str,"ei");
	
	TEST_ASSERT_EQUAL(4,str->start);
	TEST_ASSERT_EQUAL(5,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(4,test->length);
	TEST_ASSERT_EQUAL(0x80000000,text->reference);
}

void test_stringRemoveWordNotContaining_remove_ww(void){
	int toCompare;
	Text *text = textNew("wwabcdefghi");
	String *str = stringNew(text);
	str->start++;
	str->length--;
	String *test = stringRemoveWordNotContaining(str,"ab");

	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(9,str->length);
	TEST_ASSERT_EQUAL(1,test->start);
	TEST_ASSERT_EQUAL(1,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}

void test_stringRemoveWordNotContaining_remove_ww_static(void){
	int toCompare;
	Text *text = t"wwabcdefghi";
	String *str = stringNew(text);
	str->start++;
	str->length--;
	String *test = stringRemoveWordNotContaining(str,"ab");

	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(9,str->length);
	TEST_ASSERT_EQUAL(1,test->start);
	TEST_ASSERT_EQUAL(1,test->length);
	TEST_ASSERT_EQUAL(0x80000000,text->reference);
}

void test_stringRemoveWordNotContaining_remove_nothing(void){
	int toCompare;
	Text *text = textNew("abcdefghi");
	String *str = stringNew(text);
	String *test = stringRemoveWordNotContaining(str,"ab");
	
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(9,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(0,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}

void test_stringRemoveWordContaining_remove_ab(void){
	int toCompare;
	Text *text = textNew("abcdefghi");
	String *str = stringNew(text);
	String *test = stringRemoveWordContaining(str,"ab");
	
	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(7,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(2,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}

void test_stringRemoveWordContaining_remove_ab_static(void){
	int toCompare;
	Text *text = t"abcdefghi";
	String *str = stringNew(text);
	String *test = stringRemoveWordContaining(str,"ab");
	
	TEST_ASSERT_EQUAL(2,str->start);
	TEST_ASSERT_EQUAL(7,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(2,test->length);
	TEST_ASSERT_EQUAL(0x80000000,text->reference);
}

void test_stringRemoveWordContaining_remove_abc(void){
	int toCompare;
	Text *text = textNew("abcdefghi");
	String *str = stringNew(text);
	String *test = stringRemoveWordContaining(str,"aaaaaaacb");
	
	TEST_ASSERT_EQUAL(3,str->start);
	TEST_ASSERT_EQUAL(6,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(3,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}

void test_stringRemoveWordContaining_remove_abc_static(void){
	int toCompare;
	Text *text = t"abcdefghi";
	String *str = stringNew(text);
	String *test = stringRemoveWordContaining(str,"aaaaaaacb");
	
	TEST_ASSERT_EQUAL(3,str->start);
	TEST_ASSERT_EQUAL(6,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(3,test->length);
	TEST_ASSERT_EQUAL(0x80000000,text->reference);
}

void test_stringRemoveWordContaining_remove_nothing(void){
	int toCompare;
	Text *text = textNew("1234abcdefghi");
	String *str = stringNew(text);
	String *test = stringRemoveWordContaining(str,"ab");
	
	TEST_ASSERT_EQUAL(0,str->start);
	TEST_ASSERT_EQUAL(13,str->length);
	TEST_ASSERT_EQUAL(0,test->start);
	TEST_ASSERT_EQUAL(0,test->length);
	TEST_ASSERT_EQUAL(3,text->reference);
}

void test_stringIsEqual_should_return_equal(void){
	int toCompare;
	Text *text = textNew("abc");
	String *str = stringNew(text);
	Text *text1 = textNew("aabc");
	String *str1 = stringNew(text1);
	str1->start++;
	str1->length--;
	
	toCompare = stringIsEqual(str,str1);
	
	TEST_ASSERT_EQUAL(1,toCompare);
}

void test_stringIsEqual_should_return_equal_static(void){
	int toCompare;
	Text *text = t"abc";
	String *str = stringNew(text);
	Text *text1 = t"aabc";
	String *str1 = stringNew(text1);
	str1->start++;
	str1->length--;
	
	toCompare = stringIsEqual(str,str1);
	
	TEST_ASSERT_EQUAL(1,toCompare);
}

void test_stringIsEqual_should_return_not_equal(void){
	int toCompare;
	Text *text = textNew("aBc");
	String *str = stringNew(text);
	Text *text1 = textNew("aabc");
	String *str1 = stringNew(text1);
	str1->start++;
	str1->length--;
	
	toCompare = stringIsEqual(str,str1);
	
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringIsEqual_should_return_not_equal_static(void){
	int toCompare;
	Text *text = t"aBc";
	String *str = stringNew(text);
	Text *text1 = t"aabc";
	String *str1 = stringNew(text1);
	str1->start++;
	str1->length--;
	
	toCompare = stringIsEqual(str,str1);
	
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringIsEqualCaseInsensitive_should_equal(void){
	int toCompare;
	Text *text = textNew("ChiCkenNuGGer");
	String *str = stringNew(text);
	Text *text1 = textNew("chickennugger");
	String *str1 = stringNew(text1);
	
	toCompare = stringIsEqualCaseInsensitive(str,str1);
	TEST_ASSERT_EQUAL(1,toCompare);
}

void test_stringIsEqualCaseInsensitive_should_equal_with_different_start(void){
	int toCompare;
	Text *text = textNew("ChiCkenNuGGer");
	String *str = stringNew(text);
	Text *text1 = textNew("hahachickennugger");
	String *str1 = stringNew(text1);
	str1->start+=4;
	str1->length-=4;
	
	toCompare = stringIsEqualCaseInsensitive(str,str1);
	TEST_ASSERT_EQUAL(1,toCompare);
}

void test_stringIsEqualCaseInsensitive_should_not_equal(void){
	int toCompare;
	Text *text = textNew("burger");
	String *str = stringNew(text);
	Text *text1 = textNew("king");
	String *str1 = stringNew(text1);
	
	toCompare = stringIsEqualCaseInsensitive(str,str1);
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringIsEqualCaseInsensitive_should_equal_static(){

	Text *name1 = t"pineApPle";
	Text *name2 = t"aPPlE";
	String *string1 = stringNew(name1);
	string1->start = 4;
	string1->length = 5;
	String *string2 = stringNew(name2); 
	
	stringIsEqualCaseInsensitive(string1,string2);
	TEST_ASSERT_EQUAL(1,stringIsEqualCaseInsensitive(string1,string2));
}

void test_extra_to_solve_problem_1(void){
	
	Text *name = t"Bulldog";
	String *string1 = stringNew(name);
	String *string2 = stringRemoveWordNotContaining(string1, "gd");
	
	TEST_ASSERT_EQUAL_String("dog",string1);
	TEST_ASSERT_EQUAL_String("Bull",string2);
}

void test_extra_to_solve_problem_2(){

	Text *name = t"BaskinRobbin";
	String *string1 = stringNew(name);
	string1->start++;
	string1->length--;
	String *string2 = stringRemoveWordNotContaining(string1, "onb");
	
	TEST_ASSERT_EQUAL_String("nRobbin",string1);
	TEST_ASSERT_EQUAL_String("aski",string2);
}

void test_extra_to_solve_problem_3(){

	Text *name1 = textNew("pineApPle");
	Text *name2 = textNew("aPPlE");
	String *string1 = stringNew(name1);
	string1->start = 4;
	string1->length = 5;
	String *string2 = stringNew(name2); 
	
	TEST_ASSERT_EQUAL(1,stringIsEqualCaseInsensitive(string1,string2));
	TEST_ASSERT_EQUAL(1,stringIsEqualCaseInsensitive(string2,string1));
	stringDel(string1);
	stringDel(string2); //unable to test assert, will cause bad memory access
}

void test_stringCharAt_should_return_index(void){

	Text *text = textNew("Poon Jiyeon");
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL(' ',stringCharAt(string,4));
}

void test_stringCharAt_should_return_index_static(void){

	Text *text = t"PoonJiyeon";
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL('J',stringCharAt(string,4));
}

void test_stringCharAt_should_return_negative_1_over_string_length(void){

	Text *text = textNew("TanSooFatt");
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL(-1,stringCharAt(string,15));
}

void test_stringCharAt_should_return_negative_1_over_string_length_static(void){

	Text *text = t"TanSooFatt";
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL(-1,stringCharAt(string,15));
}

void test_stringCharAt_should_return_negative_1_negative_input(void){

	Text *text = textNew("ChiewWingGum");
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL(-1,stringCharAt(string,-1));
}

void test_stringCharAt_should_return_negative_1_negative_input_static(void){

	Text *text = t"ChiewWingGum";
	String *string = stringNew(text);
	
	TEST_ASSERT_EQUAL(-1,stringCharAt(string,-1));
}

void test_stringIsCharAtInSet_should_return_1_contain_in_set(void){

	Text *text = textNew("StoneSir");
	String *string  = stringNew(text);
	
	TEST_ASSERT_EQUAL(1,stringIsCharAtInSet(string,2,"abcdefghijklmno"));
}

void test_stringIsCharAtInSet_should_return_0_error_input(void){

	Text *text = textNew("StoneSir");
	String *string  = stringNew(text);
	string->start++;
	string->length--;
	
	TEST_ASSERT_EQUAL(0,stringIsCharAtInSet(string,-1,"abcdefghijklmno"));
}

void test_stringIsCharAtInSet_should_return_0_not_found_in_set(void){

	Text *text = textNew("StoneSir");
	String *string  = stringNew(text);
	string->start++;
	string->length--;
	
	TEST_ASSERT_EQUAL(0,stringIsCharAtInSet(string,0,"abcdefghijklmno"));
}

void test_stringSubstringInChar_should_crop_out_123(void){
	int toCompare;
	Text *text = textNew("StoneSir123");
	String *string  = stringNew(text);
	char *testing = stringSubstringInChar(string,8,3);
	
	toCompare = strcmp(testing,"123");
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringSubstringInChar_should_crop_out_Stone(void){
	int toCompare;
	Text *text = textNew("StoneSir123");
	String *string  = stringNew(text);
	char *testing = stringSubstringInChar(string,0,5);
	
	toCompare = strcmp(testing,"Stone");
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringSubstringInChar_should_crop_out_1(void){
	int toCompare;
	Text *text = textNew("abc123");
	String *string  = stringNew(text);
	char *testing = stringSubstringInChar(string,3,1);
	
	toCompare = strcmp(testing,"1");
	TEST_ASSERT_EQUAL(0,toCompare);
}

void test_stringSubstringInText_return_Text_1(void){

	Text *text = textNew("abc123");
	String *string  = stringNew(text);
	Text *testing = stringSubstringInText(string,3,1);
	
	TEST_ASSERT_EQUAL(1,testing->reference);
	TEST_ASSERT_EQUAL(0,strcmp(testing->string,"1"));
}

void test_stringSubstringInText_return_Text_abcd(void){

	Text *text = textNew("123abcd123");
	String *string  = stringNew(text);
	Text *testing = stringSubstringInText(string,3,4);
	
	TEST_ASSERT_EQUAL(1,testing->reference);
	TEST_ASSERT_EQUAL(0,strcmp(testing->string,"abcd"));
}

void test_stringToInteger_should_get_1234(void){

	Text *text = textNew("1234");
	String *string = stringNew(text);

	TEST_ASSERT_EQUAL(1234,stringToInteger(string));
}

void test_stringToInteger_should_get_23(void){

	Text *text = textNew("1234");
	String *string = stringNew(text);
	string->start++;
	string->length-=2;

	TEST_ASSERT_EQUAL(23,stringToInteger(string));
}

void test_stringToInteger_should_get_5555(void){

	Text *text = textNew("dsfggggv5555FDG");
	String *string = stringNew(text);
	string->start = 8;
	string->length = 8;

	TEST_ASSERT_EQUAL(5555,stringToInteger(string));
}