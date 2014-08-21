#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Evaluate.h"
#include "Stack.h"
#include "StringObject.h"
#include "Token.h"
#include "tryEvaluatethenPush.h"
#include "operatorEvaluate.h"
#include "calculateToken.h"
#include "createNumberToken.h" 
#include "LinkedList.h"
#include "ErrorCode.h"
#include "CException.h"

/**
	Evaluate all operators on the operator stack, with top of stack 
	operator being evaluated first.
	
	Input :
		stack the operatorStack
**/

void operatorEvaluate(Stack *numberStack , Operator *opeToken){
	
	int answer; 
	Token *answerToken; 
	
	if(opeToken->info->affix ==PREFIX){
		operatorPrefixOrPostfixEvaluate(numberStack ,opeToken);
	}else{
		operatorInfixEvaluate(numberStack ,opeToken);
	}
}

/**
	This function is use to calculate expression which have infix 
	operator
	Input :
		stack the operatorStack
**/
void operatorInfixEvaluate(Stack *numberStack , Operator *opeToken){
	int answer; 
	Number *number1;
	Number *number2;
	Token *answerToken;
	
	number2=stackPop(numberStack); 
	if(number2 == NULL){
		Throw(ERR_EXPECTING_NUMBER);
	}else{
		number1=stackPop(numberStack); 
		if(number1==NULL){
			Throw(ERR_EXPECTING_NUMBER);
		}else{
			answer = calculateInfix(opeToken,number1,number2); 
			answerToken=createNumberToken(answer);
			stackPush(answerToken,numberStack);
		}
	}
	
}

/**
	This function is use to calculate expression which have prefix 
	and postfix operator
	Input :
		stack the operatorStack
**/
void operatorPrefixOrPostfixEvaluate(Stack *numberStack , Operator *opeToken){
	int answer; 
	Token *answerToken;
	Number *number1;
	
	number1=stackPop(numberStack); 
	if(number1 ==NULL){
		Throw(ERR_EXPECTING_NUMBER);
	}else{
		answer = calculatePrefixOrPostfix(opeToken,number1); 
		answerToken=createNumberToken(answer);
		stackPush(answerToken,numberStack);
	}
}	

/**
	Evaluate all operators on the operator stack, with top of stack 
	operator being evaluated first.
	
	Input :
		stack the operatorStack
**/

void evaluateAllOperatorOnStack(Stack *numberStack,Stack *operatorStack){
	
	Operator *opeToken;
	while((opeToken=stackPop(operatorStack))!=NULL)
	{
		operatorEvaluate(numberStack,opeToken);
	}
}

