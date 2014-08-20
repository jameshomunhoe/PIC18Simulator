#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Token.h"
#include "Text.h"
#include "CharSet.h"
#include "StringObject.h"
#include "Evaluate.h"
#include "CustomTypeAssert.h"
#include "Stack.h"
#include "LinkedList.h"
#include "tryEvaluatethenPush.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "createNumberToken.h"
#include "stackForEvaluate.h"
#include "ErrorCode.h"
#include "CException.h"



/*******************************************************************************************
 *	This function is to evaluate prefixes and number.
 *	This function will stop and return after number is detected.
 *  Get a operator token,check whether it can be convert to prefix. If yes, convert to prefix 
 *	input  : expression,token,numberStack,operatorStack
 *	output : none
 *	return : function
 *	Throw : ERR_EXPECTING_NUMBER
********************************************************************************************/

void evaluatePrefixesAndNumber(String *tokenizer,Token *token,Stack *numberStack,Stack *operatorStack){
	
	if(token==NULL){
		Throw(ERR_EXPECTING_NUMBER);
	}
	while(1){
		if(isNumber(token)){
			stackPush(token,numberStack);
			break;
		}else if(isOperator(token)){
			if(((Operator*)token)->info->affix!=PREFIX)
				if(((Operator*)token)->info->affix == POSTFIX){
					Throw(ERR_NO_ARGUMENT);
				}else{
					tryConvertToPrefix((Operator*)token);
				}
			stackPush(token,operatorStack);
		}
		token=getToken(tokenizer);
		if(token==NULL)
			Throw(ERR_EXPECTING_NUMBER);
	}
}

/*******************************************************************************************
 *	This function is to evaluate postfix and infix operator.
 *	input  : expression,token,numberStack,operatorStack
 *	output : none
 *	return : function
 *	After detect one infix operator, the loop will stop and come out.
********************************************************************************************/

void evaluatePostfixesAndInfix(String *tokenizer,Token *token,Stack *numberStack,Stack *operatorStack){
	
	if(token==NULL){
		return;
	}
	while(1){
		if(isOperator(token)){
			if(((Operator*)token)->info->affix==INFIX){
				tryEvaluateOperatorOnStackThenPush((Operator*)token,numberStack,operatorStack);
				break;
			}else if(((Operator*)token)->info->affix==POSTFIX){
				tryEvaluatePrefixOperatorOnStackThenPush((Operator*)token,numberStack,operatorStack);
			}else{
				Throw(ERR_NOT_EXPECTING_PREFIX_OPERATOR);
			}
		}
		token=getToken(tokenizer);
		if(token==NULL){
			return;
		}else if(isNumber(token)){
			Throw(ERR_NOT_EXPECTING_NUMBER);
		}
	}
}

/*******************************************************************************************
 *	This function is to evaluate the expression which contains numbers and operators and
 *	return the results in number form.
 *	This function is the improved function from the evaluate(char *expression)
 *	Thus, this function can evaluate expression like -2,*2,(((2))), +-+-2... *
 *	input  : expression
 *	output : none
 *	return : ((Number*)token)->value
 *
********************************************************************************************/

int evaluation(char *expression){
	Text *newText;
	String *tokenizer;
	Token *token;
	//Create 2 stack to take in number token and operator token
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();
	//Check the expression whether is NULL. If yes throw error no argument.
	if(expression ==NULL){
		Throw(ERR_NO_ARGUMENT);
	}
	//If the expression is not NULL, start create token from the expression.Keep get Token until is NULL.Use token dump to check whether all the
	//expression are tokenize anot.
	newText=textNew(expression);
	tokenizer = stringNew(newText);
	
	while((token=getToken(tokenizer))!=NULL){
	
		evaluatePrefixesAndNumber(tokenizer,token,numberStack,operatorStack);
		token=getToken(tokenizer);
		if(token!=NULL)
			evaluatePostfixesAndInfix(tokenizer,token,numberStack,operatorStack);
	}
	evaluateAllOperatorOnStack(numberStack,operatorStack);
	Number *result=(Number*)stackPop(numberStack);
	destroyStack(numberStack);
	if(operatorStack !=NULL){
		destroyStack(operatorStack);
	}
	return result->value;
	
}
























































































/*******************************************************************************************
 *	This function is to evaluate postfix, prefix and infix operator.
 *	This function will stop and go out the loop once no operator is detected.
 *	input  : expression,token,numberStack,operatorStack
 *	output : none
 *	return : function
 *	Throw  : 
********************************************************************************************/

void evaluatePostfixesPrefixesAndInfixes(char *expression,Token *token,Stack *numberStack,Stack *operatorStack){
	
	if(token!=NULL){
		if(isOperator(token)){
			if(((Operator*)token)->info->affix == INFIX ){
				tryEvaluateOperatorOnStackThenPush((Operator*)token,numberStack,operatorStack);
			}else if(((Operator*)token)->info->affix == PREFIX || ((Operator*)token)->info->affix == POSTFIX){
				tryEvaluatePrefixOperatorOnStackThenPush((Operator*)token,numberStack,operatorStack);
			}else{
				Throw(ERR_EXPECTING_OPERATOR);
			}
		}else if(isNumber(token)){
				stackPush(token,numberStack);
		}else{
			Throw(ERR_EXPECTING_NUMBER_OR_PREFIX);
		}
	}
}


int evaluateExpression(char *expression){
	Token *token;
	Stack *numberStack=createStack();
	Stack *operatorStack=createStack();

	if(expression ==NULL){
		Throw(ERR_NO_ARGUMENT);
	}
	Text *newText=textNew(expression);
	String *tokenizer = stringNew(newText);
	
	
	token=getToken(tokenizer);
	if(token->type == IDENTIFIER_TOKEN){
		Throw(ERR_NOT_ACCEPT_IDENTIFIER);
	}else{
	while(token!=NULL){
		if(isOperator(token)){
			if(((Operator*)token)->info->affix!=PREFIX)
			tryConvertToPrefix((Operator*)token);
		stackPush(token,operatorStack);
		}else if(isNumber(token)){
			stackPush(token,numberStack);
			break;
		}else
			Throw(ERR_INVALID_IDENTIFIER);
		
		token=getToken(tokenizer);
		if(token==NULL)
			break;
	}
	}
	while((token=getToken(tokenizer))!=NULL ){
		evaluatePostfixesPrefixesAndInfixes(expression,token,numberStack,operatorStack);
		
	}
	evaluateAllOperatorOnStack(numberStack,operatorStack);
	Number *result=(Number*)stackPop(numberStack);
	destroyStack(numberStack);
	if(operatorStack !=NULL){
		destroyStack(operatorStack);
	}
	return result->value;
	
}


