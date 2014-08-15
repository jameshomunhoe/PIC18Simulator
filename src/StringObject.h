#ifndef __STRING_OBJECT_H__
#define __STRING_OBJECT_H__

#include "Types.h"
#include "Text.h"

#define isSpace(ch) (ch==' ' || ch=='\t')

typedef struct String{
	uint32 reference;
	Text *text;
	uint32 start;
	uint32 length;
}String;

//test prototype
int stringToInteger(String *str);
char *stringSubstringInChar(String *str, int relativePosition, int length);
Text *stringSubstringInText(String *str, int relativePosition, int length);

//add stringClone, textClone
String *stringNew(Text *text);
String *stringAssign(String *string);
String *stringDel(String *string);

void stringSkip(String *string, int numChar2Skip);
void sillyFunction(April fool);
void stringTrimLeft(String *string);
void stringTrimRight(String *string);
void stringTrim(String *string);

int stringRemoveChar(String *str); // return -l if empty remove by moving index number
int stringLength(String *str); // length of string
String *stringRemoveWordNotContaining(String *str,char delimites[]);
String *stringRemoveWordContaining(String *str, char containSet[]);
void thisIsARubbishFunction();
int stringIsEqual(String *str1, String *str2); //1 if same, 0 otherwise do no use string compare
int stringIsEqualCaseInsensitive(String *str1, String *str2); //uses char tolower();

int stringCharAt(String *str, int relativeIndex);
int stringIsCharAtInSet(String *str, int relativeIndex, char set[]); //1 is true, 0 false

#endif // __STRING_OBJECT_H__