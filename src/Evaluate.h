#ifndef __Evaluate_H
#define __Evaluate_H

#include "Token.h"
#include "Stack.h"

int evaluate(char *expression);
int  evaluateExpression(char *expression);
void evaluatePrefixesAndNumber(char *expression,Token *token,Stack *numberStack,Stack *operatorStack);
void evaluatePostfixesPrefixesAndInfixes(char *expression,Token *token,Stack *numberStack,Stack *operatorStack);

#endif // Evaluate_H
