#include <stdio.h>
#include <malloc.h>
#include "String.h"
#include "Text.h"

/**
* The show the details of the text
*
* Input:
*	text	is the text that will be dump
* 
*/
void textDump(Text *text){
	if(text==NULL){
		printf("(NULL)");
		return;
	}
	printf("text[0x%x];%s\n", text->reference, text->string);
}

/**
* To create a new text object
*
* Input:
*	charStr	the string of character that will be created in the text object
*
* Return the text that have created 
*/
Text *textNew(char *charStr){
	// Character string copy from charStr to text->string
	Text *text = (Text *)malloc(strlen(charStr) + 4 + 1);
	strcpy(text->string,charStr);
	text->reference = 1;
	return text;
}

/**
* Assign the text to from another text
*
* Input:
*	text	the text that will be assign to
*
* Return the assigned text
*/
Text *textAssign(Text *text){
	if(text->reference < 0x80000000)
		text->reference++;
	return text;
}

/**
* To deleted the text reference
*
* Input:
*	text	the text that will be removed
*
* Return the text that left 
*/
Text *textDel(Text *text){
	//check if text reference not equals to 0x80000000
	//reduce text reference by one
	//do normal delete
	//else do nth
	int i;
	
	if(text->reference < 0x80000000 && text->reference > 0){
		text->reference--;
		if(text->reference == 0){
			for( i = 0; i < strlen(text->string); i++){
				text->string[i] = 0;
			}
			free(text);
			return NULL;
		}		
	}
	return text;
}