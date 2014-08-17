#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Evaluate.h"
#include "Text.h"
#include "StringObject.h"
#include "Types.h"
#include "Token.h"

/*
	This function will generate a Token from a number.
	
	input :
	number				Carry the number that going to store in a Token.
	
	output:
	none
	
	return:
	(Token*)newToken	The token that generated.
*/

Token *createNumberToken(int number)
{
	Number *newToken = malloc (sizeof(Number));
	newToken->type = NUMBER_TOKEN;
	newToken->value=number;
	
	return (Token*)newToken;
}

