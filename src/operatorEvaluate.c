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
		operatorPrefixEvaluate(numberStack ,opeToken);
	}else{
		operatorInfixEvaluate(numberStack ,opeToken);
	}
}

void operatorInfixEvaluate(Stack *numberStack , Operator *opeToken){
	int answer; 
	Number *number1;
	Number *number2;
	Token *answerToken;
	
	number2=stackPop(numberStack); 
	number1=stackPop(numberStack); 
	answer = calculate(opeToken,number1,number2); 
	answerToken=createNumberToken(answer);
	stackPush(answerToken,numberStack);
	
}

void operatorPrefixEvaluate(Stack *numberStack , Operator *opeToken){
	int answer; 
	Token *answerToken;
	
	Number *number1=stackPop(numberStack); 
	if(number1 ==NULL){
		Throw(ERR_EXPECTING_NUMBER);
	}else{
		answer = prefixCalculate(opeToken,number1); 
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

void evaluatePrefixOperatorOnStack(Stack *numberStack,Stack *operatorStack){
	
	Operator *opeToken;
	
	while((opeToken=stackPop(operatorStack))==NULL)
	{
		operatorPrefixEvaluate(numberStack,opeToken);
	}
}
