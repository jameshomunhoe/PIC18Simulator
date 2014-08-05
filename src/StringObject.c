#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "CustomTypeAssert.h"
#include "StringObject.h"
#include "malloc.h"
#include "CharSet.h"

/**
* This function takes in String and display information about the String.
*
* Input:
*	str				is the String object
* 
*/
void stringDump(String *string){
	uint32 index = 0, len = 0;
	char *fullString = "(NULL)";
	char *actualString = "(NULL)";


	if(string == NULL){
		printf("NULL\n");
		return;
	}
	if(string->text != NULL){
		int actualLength;
		fullString = string->text->string;
		index = string->start;
		
		if(index <= strlen(fullString)){
			actualString = &fullString[index];
			actualLength = strlen(actualString);
			len = string->length;
			if(len > actualLength)
				len = actualLength;
		} else{
			actualString = "";
		}
	}
	
	printf("[%d] f_str[:%d]:%s, start:%d, len:%d, str:%.*s\n", \
			string->reference, string->text->reference, fullString, index, \
			string->length, len, actualString);
	return;

}

/**
* Create a new String object by using a Text sturcture
*
* Input:
*	text	the text object
* 
* Return the new String object
*/
String *stringNew(Text *text){

	String *newString = malloc(sizeof(String));
	
	newString->text = textAssign(text);
	newString->reference = 1;
	newString->start = 0;
	newString->length = strlen(text->string);
	
	return newString;
}

/**
* Assign another string into a existing string.
*
* Input:
*	string	the string to assign.
* 
* Return the input string
*/
String *stringAssign(String *string){

	string->reference++;
	return string;
}

/**
* Remove the reference(unassign) a string to from another
*
* Input:
*	string	the string to delete
* 
* Return the input string
*/
String *stringDel(String *string){

	string->reference--;
	if(string->reference == 0){
		free(string);
		textDel(string->text);
		return NULL;
	}
	return string;

}

/**
* Skip certain amount of value of the string's character
*
* Input:
*	string			the string for skip purpose
*	numChar2Skip	the amount of character wanted to skip
* 
*/
void stringSkip(String *string, int numChar2Skip){

	int startPoint = string->start + numChar2Skip;
	
	if(startPoint < strlen(string->text->string)){
		string->start = startPoint;
		string->length = strlen(string->text->string) - string->start;
	}
	else{
		string->start = strlen(string->text->string);
		string->length = strlen(string->text->string) - string->start;
	}
}

/**
* Trim/remove empty spacing or tab on the left of the string
*
* Input:
*	string	the string that wanted to trim
* 
*/
void stringTrimLeft(String *string){
	
	int i = string->start;
	int l = strlen(string->text->string);
	
	if(string->text->string[i] != 0){
		for(;i<=l;i++){
			if(isSpace(string->text->string[i])){
				string->start++;
				string->length--;
			}
			else
				break;
		}
	}
}

/**
* Trim/remove empty spacing or tab on the right of the string
*
* Input:
*	string	the string that wanted to trim
* 
*/
void stringTrimRight(String *string){

	int end = string->start + string->length - 1;
	
	for(;;end--){
		if(string->length == 0)
			break;
			
		else if(isSpace(string->text->string[end]))
				string->length--;
		
		else
			break;
	}
}

/**
* Trim/remove empty spacing or tab on both left and right of the string
*
* Input:
*	string	the string that wanted to trim
* 
*/
void stringTrim(String *string){
	stringTrimLeft(string);
	stringTrimRight(string);
}

/**
* Remove the initial character where start pointer pointing at
*
* Input:
*	string	the string to removeChar
* 
* Return the character if successfully deleted
* Return -1 otherwise
*/
// return -l if empty remove by moving index number
int stringRemoveChar(String *str){
	
	if(stringLength(str) != 0){
		char forReturn = str->text->string[str->start];
		if(stringLength(str) > 1)
			str->start++;
			str->length--;
		return forReturn;
	}
	else
		return -1;
	
}

/**
* Get the string length
*
* Input:
*	string	the string length that wanted
* 
* Return the length of the string
*/
// length of string
int stringLength(String *str){
	return str->length;
}

/**
* Remove the word from the string which not contain in the delimites(s) from the left
* Once detected character contain in delimites, stop
*
* Input:
*	string		the string to remove the word
*	delimites	the set that character that should not remove
* 
* Return the string that have removed from the original string
*/
String *stringRemoveWordNotContaining(String *str,char delimites[]){
	int i,j,count,delimitesLength,strLength;
	String *strReturn = stringNew(str->text);
	
	delimitesLength = strlen(delimites);
	strLength = strlen(str->text->string);
	strReturn->start = str->start;
	strReturn->length = 0;
	
	for(j=str->start;j<strLength;j++){
		for(i=0,count=0;i<delimitesLength;i++){
			if(str->text->string[j] == delimites[i]){
				break;
			}
			else{
				count++;
			}
		}
		if(count>=delimitesLength){
			str->start++;
			str->length--;
			strReturn->length++;
		}
		else
			break;
	}
	return strReturn;
}

/**
* Remove the word from the string which contain in the containSet from the left
* Once detected character not contain in containSet, stop 
*
* Input:
*	string		the string to remove the word
*	containSet	the set that character that should remove
* 
* Return the string that have removed from the original string
*/
String *stringRemoveWordContaining(String *str, char containSet[]){
	int i,j,count,containLength,strLength;
	String *strReturn = stringNew(str->text);
	containLength = strlen(containSet);
	strLength = strlen(str->text->string);
	strReturn->start = str->start;
	strReturn->length = 0;
	
	for(j=str->start;j<strLength;j++){
		for(i=0,count=0;i<containLength;i++){
			if(str->text->string[j] == containSet[i]){
				str->start++;
				str->length--;
				strReturn->length++;
				break;
			}
			else{
				count++;
			}
		}
		if(count>=containLength)
			break;
	}
	return strReturn;
}

/**
* Compare two string whether are equals, with case sensitive
*
* Input:
*	str1	the first string to compare with second
*	str2	the second string to compare with first
* 
* Return 1 if it is the same
* Return 0 otherwise
*/
int stringIsEqual(String *str1, String *str2){
	int i;
	int actualLength;
	int actualLength2;
	char *actualString;
	char *actualString2;
	
	actualString = &str1->text->string[str1->start];
	actualString2 = &str2->text->string[str2->start];
	
	actualLength = strlen(actualString);
	actualLength2 = strlen(actualString2);
	
	if(actualLength == actualLength2){
		for(i=0;i<actualLength;i++){
			if(actualString[i] != actualString2[i])
				return 0;
		}
		return 1;
	}
	else
		return 0;
}

/**
* Compare two string whether are equals, without case sensitive
*
* Input:
*	str1	the first string to compare with second
*	str2	the second string to compare with first
* 
* Return 1 if it is the same
* Return 0 otherwise
*/
int stringIsEqualCaseInsensitive(String *str1, String *str2){
	int i;
	int actualLength;
	int actualLength2;
	char *actualString;
	char *actualString2;
	
	actualString = &str1->text->string[str1->start];
	actualString2 = &str2->text->string[str2->start];
	
	actualLength = strlen(actualString);
	actualLength2 = strlen(actualString2);
	
	if(actualLength == actualLength2){
		for(i=0;i<actualLength;i++){
			if(tolower(actualString[i]) != tolower(actualString2[i]))
				return 0;
		}
		return 1;
	}
	else
		return 0;

}

/**
* Return the character at the specified relative index of the String
*
* Input:
* 	str				is the String object
*	relativeIndex	is the relative index into the String.
*					This value must be positive.
*
* Return the character at the relative index if exists.
* Otherwise return -1. If relativeIndex < 0, -1 is returned as well.
*/
int stringCharAt(String *str, int relativeIndex){
	if(relativeIndex >= 0 && relativeIndex < str->length)
		return str->text->string[str->start+relativeIndex];
	else
		return -1;

}

/**
* Determine if the character specified by the relative index in the
* String is in the given set of characters.
*
* Input:
*	str				is the String object
*	relativeIndex	is the relative index into the String
*					This value must be positive
*	set				is the set of characters delimited by NULL
* 
* Return 1 if the character that chosen is in the set list.
* Return 0 otherwise
*/
int stringIsCharAtInSet(String *str, int relativeIndex, char set[]){
	
	int i, setLength = strlen(set);

	if(relativeIndex >= 0 && relativeIndex < str->length){
		for(i=0;i < setLength; i++){
			if(str->text->string[str->start+relativeIndex] == set[i])
				return 1;
		}
	}
	return 0;
}

/**
* Convert the string into integer
*
* Input:
*	str		is the string that use as reference for converting
* 
* Return the value in integer
*/
int stringToInteger(String *str){

	char *string = stringSubstringInChar(str,0,str->length);
	int forReturn = atoi(string);

	free(string);
	
	return forReturn;
}

/**
* To take out a portion of character(s) in the string
*
* Input:
*	str				is the String object
*	relativePosition	is the relative index to start the cropping
*					This value must be positive
*
*	length			the amount of character will be cropped out
* 
* Return the array of character that selected
*/
char *stringSubstringInChar(String *str, int relativePosition, int length){
	
	int size;
	if(str->start+relativePosition+length > strlen(str->text->string))
		size = str->length - str->start + relativePosition+1;
	else
		size = length+1;
		
	char *character = malloc(sizeof(char)*size);
		
	int i,j,h;
	
	for(j=0,i=str->start+relativePosition; i < str->start+relativePosition+length ; j++,i++){
		character[j] = str->text->string[i];
		h = j;
	}
	character[h+1] = 0;
	return character;
}

/**
* To take out a portion of character(s) in the string into a Text
*
* Input:
*	str					is the String object
*	relativePosition	is the relative index to start the cropping
*						This value must be positive
*
*	length				the amount of character will be cropped out
* 
* Return the Text that selected
*/
Text *stringSubstringInText(String *str, int relativePosition, int length){
	
	char *charStr = stringSubstringInChar(str,relativePosition,length);
	Text *text = textNew(charStr);
	free(charStr);
	return text;
}

/*
String *stringRemoveWordNotContaining(String *str,char delimites[]){
	int i,j = 0,k = 0,length;
	Text *text;
	String *strReturn;
	length = strlen(delimites);
	char forReturn[length];
	
	for( i = str->start; i < str->length && j < length;i++){
		for(;j<length;i++){
			if(str->text->string[i] != delimites[j]){
				forReturn[k] = str->text->string[i];
				k++;
				str->start++;
				str->length--;
			}
			else{
				j++;
			}
		}
	}
	
	text = textNew(forReturn);
	strReturn = stringNew(text);
	return  strReturn;
}
*/
