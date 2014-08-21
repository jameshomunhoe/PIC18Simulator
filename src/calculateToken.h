#ifndef __CALCULATETOKEN_H__
#define __CALCULATETOKEN_H__

#include "Token.h"

//Function declaration

int calculateInfix(Operator *opeToken, Number *first, Number *second);
int calculatePrefixOrPostfix(Operator *opeToken, Number *first);


#endif //__CALCULATETOKEN_H__