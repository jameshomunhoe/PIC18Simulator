#ifndef __OPERATOREVALUATE_H__
#define __OPERATOREVALUATE_H__

#include "Stack.h"
#include "Token.h"

//Function declaration
void operatorEvaluate(Stack *numberStack , Operator *opeToken);
void evaluateAllOperatorOnStack(Stack *numberStack,Stack *operatorStack);
void operatorPrefixOrPostfixEvaluate(Stack *numberStack , Operator *opeToken1);
void operatorInfixEvaluate(Stack *numberStack , Operator *opeToken);

#endif //__OPERATOREVALUATE_H__