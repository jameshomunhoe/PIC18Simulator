#ifndef __TRYEVALUATETHENPUSH_H__
#define __TRYEVALUATETHENPUSH_H__

#include "Evaluate.h"
#include "Stack.h"
#include "Token.h"

//Function declaration
void tryEvaluateOperatorOnStackThenPush(Operator *newToken,Stack *numberStack,Stack *operatorStack);
void tryEvaluatePrefixOperatorOnStackThenPush(Operator *newToken,Stack *numberStack,Stack *operatorStack);
void tryConvertToPrefix(Operator *opeToken);
void tryEvaluateAndExecutePostfix(Operator *newToken,Stack *numberStack,Stack *operatorStack);
void checkPrefixOperator(Operator *newToken,Stack *numberStack,Stack *operatorStack);

#endif //__TRYEVALUATETHENPUSH_H__