#ifndef __TRYEVALUATETHANPUSH_H__
#define __TRYEVALUATETHANPUSH_H__

#include "Evaluate.h"
#include "Stack.h"
#include "Token.h"

//Function declaration
void tryEvaluateOperatorOnStackThenPush(Operator *newToken,Stack *numberStack,Stack *operatorStack);
void tryEvaluatePrefixOperatorOnStackThenPush(Operator *newToken,Stack *numberStack,Stack *operatorStack);
void tryConvertToPrefix(Operator *opeToken);
void tryEvaluateAndExecutePostfix(Operator *newToken,Stack *numberStack,Stack *operatorStack);

#endif //__TRYEVALUATETHANPUSH_H__