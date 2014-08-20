#ifndef __Evaluate_H
#define __Evaluate_H

#include "Token.h"
#include "Stack.h"


int  evaluateExpression(char *expression);
void evaluatePrefixesAndNumber(String *tokenizer,Token *token,Stack *numberStack,Stack *operatorStack);
void evaluatePostfixesAndInfix(String *tokenizer,Token *token,Stack *numberStack,Stack *operatorStack);
#endif // Evaluate_H
