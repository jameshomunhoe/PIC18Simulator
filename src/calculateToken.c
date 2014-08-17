#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Token.h"
#include "calculateToken.h"
#include "ErrorCode.h"
#include "CException.h"

int calculate(Operator *opeToken, Number *first, Number *second){
	Stack *numberStack;
	int answer;
	
	if(opeToken->info==NULL)
	{
		Throw(ERR_INVALID_OPERATOR);
	}

	switch(opeToken->info->id)
	{	
		case MUL_OP:
			answer=first->value*second->value;
		break;
		
		case DIV_OP:
			answer=first->value/second->value;
		break;
		
		case MOD_OP:
			answer=first->value%second->value;
		break;
		
		case ADD_OP:
			answer=first->value+second->value;
			
		break;	
		
		case SUB_OP:
			answer = first->value-second->value;
			
		break;
		
		case BITWISE_AND_OP:
			answer=first->value&second->value;
		break;
		
		case BITWISE_XOR_OP:
			answer=first->value^second->value;
		break;
		
		case BITWISE_OR_OP:
			answer=first->value|second->value;
		break;
		
		case LOGICAL_AND_OP:
			answer=first->value&&second->value;
		break;
		
		case LOGICAL_OR_OP:
			answer=first->value||second->value;
		break;
		

		default:
		{
			Throw(ERR_UNKNOWN_INFIX_OPERATOR);
		}
	}
	
	
	return answer;
	
}

int prefixCalculate(Operator *opeToken, Number *first){
	int answer;
	if(opeToken->info==NULL)
	{
		Throw(ERR_INVALID_OPERATOR);
	}
	
	switch(opeToken->info->id)
	{	
		case BITWISE_NOT_OP:
			answer=~first->value;
		break;
		
		case LOGICAL_NOT_OP:
			answer=!first->value;
		break;
		
		case OPENING_BRACKET_OP:
			answer=first->value;
		break;
		
		case PLUS_OP:
			answer=+first->value;
		break;
		
		case MINUS_OP:
			answer=-first->value;
		break;
		
		default:
		{
			Throw(ERR_UNKNOWN_PREFIX_OPERATOR);
		}
	}
	
	return answer;
}