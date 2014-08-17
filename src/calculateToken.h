#ifndef __CALCULATETOKEN_H__
#define __CALCULATETOKEN_H__

#include "Token.h"

//Function declaration

int calculate(Operator *opeToken, Number *first , Number *second);
int prefixCalculate(Operator *opeToken1, Number *first );


#endif //__CALCULATETOKEN_H__