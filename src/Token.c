#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "Token.h"
#include "Text.h"
#include "CharSet.h"
#include "ErrorCode.h"
#include "CustomTypeAssert.h"

#define MAIN_OPERATOR_TABLE_SIZE	(sizeof(mainOperatorTable)/sizeof(OperatorInfo))
#define	ALTERNATIVE_OPERATOR_TABLE_SIZE	(sizeof(alternativeOperatorTable)/sizeof(OperatorInfo))

OperatorInfo mainOperatorTable[] = {
  {.symbol="~", .id=BITWISE_NOT_OP, .precedence=150, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="!", .id=LOGICAL_NOT_OP, .precedence=150, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="*", .id=MUL_OP, .precedence=100, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="/", .id=DIV_OP, .precedence=100, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="%", .id=MOD_OP, .precedence=100, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="+", .id=ADD_OP, .precedence=80, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="-", .id=SUB_OP, .precedence=80, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="&", .id=BITWISE_AND_OP, .precedence=60, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="^", .id=BITWISE_XOR_OP, .precedence=50, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="|", .id=BITWISE_OR_OP, .precedence=40, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="&&", .id=LOGICAL_AND_OP, .precedence=30, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  {.symbol="||", .id=LOGICAL_OR_OP, .precedence=20, .affix=INFIX, .assoc=LEFT_TO_RIGHT},
  // All other symbols MUST have higher precedence than those below:
  {.symbol="(", .id=OPENING_BRACKET_OP, .precedence=10, .affix=PREFIX, .assoc=RIGHT_TO_LEFT},
  {.symbol=")", .id=CLOSING_BRACKET_OP, .precedence=9,  .affix=POSTFIX, .assoc=LEFT_TO_RIGHT}
};

OperatorInfo alternativeOperatorTable[] = {
  {.symbol="+", .id=PLUS_OP, .precedence=150, .affix=PREFIX, .assoc=RIGHT_TO_LEFT},
  {.symbol="-", .id=MINUS_OP, .precedence=150, .affix=PREFIX, .assoc=RIGHT_TO_LEFT}
};

/**
 * Create an Number token by the value input
 *
 * Input:
 *   value  is the value to initialized with
 *
 * Return the Number object
 */
Number *numberNew(int value) {
	Number *number = malloc(sizeof(Number));
	number->value = value;
	number->type = NUMBER_TOKEN;
	return number;
}

/**
 * Create an Operator token identified by symbol.
 *
 * Input:
 *   symbol is symbol in string of characters, i.e., "*"
 *          and "&&".
 *
 * Return the Operator object
 */
Operator *operatorNewBySymbol(char *symbol) {
	int i;
	Operator *operator = malloc(sizeof(Operator));
	operator->type = OPERATOR_TOKEN;
	for(i=0;i < MAIN_OPERATOR_TABLE_SIZE; i++){
		if(strcmp(mainOperatorTable[i].symbol,symbol) == 0){
			operator->info = &mainOperatorTable[i];
			return operator;
		}
	}
	return NULL;
}

/**
 * Create an Operator token identified by the ID.
 *
 * Input:
 *   symbol is symbol in string of characters, i.e., MUL_OP
 *          and CLOSING_BRACKET_OP.
 *
 * Return the Operator object
 */
Operator *operatorNewByID(OperatorID id) {
	int i;
	Operator *operator = malloc(sizeof(Operator));
	operator->type = OPERATOR_TOKEN;

	for(i=0;i < MAIN_OPERATOR_TABLE_SIZE; i++){
		if(mainOperatorTable[i].id == id){
			operator->info = &mainOperatorTable[i];

			return operator;
		}
	}
	return NULL;
}

/**
 * Create an Identifier token initialized with the name
 * given.
 *
 * Input:
 *   name is the name of the identifier.
 *
 * Return the Identifier object
 */
Identifier *identifierNew(Text *name) {
  Identifier *identifier = malloc(sizeof(Identifier));
  identifier->name = name;
  identifier->type = IDENTIFIER_TOKEN;
  identifier->number = NULL;
  return identifier;
}

/**
 * Return the one token from the String. The String is updated.
 * If the string is empty, NULL is return.
 *
 * Input:
 *   str  is the String object
 *
 * Possible returned token:
 *    Number, Operator, and Identifier tokens
 */
Token *getToken(String *str) {
	//1 trim left
	//2 check first character
	//	a	-if a number then extract the number string
	//		-convert into integer
	//		-create number token
	//	b	-if alphabetSet then extract the identifier
	//		-create identifier token
	//	c	-if operator set then extract operator symbol
	//		-create operator token

	char charReturn[3];
	Token *tokenReturn = NULL;
	String *strReturn = NULL;
	Number *number = NULL;
	Identifier *identifier = NULL;
	Operator *operator = NULL;

	stringTrimLeft(str);
	if(stringLength(str) == 0)
		return NULL;


	//Number
	if(stringIsCharAtInSet(str,0,numberSet)){
		strReturn = stringRemoveWordContaining(str,numberSet);
		if(stringIsCharAtInSet(str,0,alphabetSet)){
			Throw(ERR_NUMBER_NOT_WELL_FORMED);
		}
		else{
			number = numberNew(stringToInteger(strReturn));
			tokenReturn = (Token *)number;
			stringDel(strReturn);
		}
	}

	//Identifier
	else if(stringIsCharAtInSet(str,0,alphabetSet)){
		strReturn = stringRemoveWordContaining(str,alphaNumericSet);
		identifier = identifierNew(stringSubstringInText(strReturn,0,strReturn->length));
		tokenReturn = (Token *)identifier;
		stringDel(strReturn);
	}

	//Operator
	else if(stringIsCharAtInSet(str,0,operatorSet)){
		charReturn[0] = (char )stringRemoveChar(str);
		charReturn[1] = 0;

		if(stringCharAt(str,0) == charReturn[0] && stringLength(str) != 0){
			if(charReturn[0] == '&'){
				charReturn[0] = '&';
				charReturn[1] = '&';
				charReturn[2] = 0;
				str->start++;
				str->length--;
			}
			else if(charReturn[0] == '|'){
				charReturn[0] = '|';
				charReturn[1] = '|';
				charReturn[2] = 0;
				str->start++;
				str->length--;
			}
		}

		operator = operatorNewBySymbol(charReturn);
		tokenReturn = (Token *)operator;

	}
	else
		Throw(ERR_ILLEGAL_ARGUMENT);


	return tokenReturn;
}

/**
 * Remove a token
 *
 * Input:
 *   token	the token to delete
 *
 */
void tokenDel(Token *token){

	if(token->type == NUMBER_TOKEN){
		free(token);
	}

	else if(token->type == OPERATOR_TOKEN){
		if(((Operator *)token)->info != NULL)
		free(token);
	}

	else if(token->type == IDENTIFIER_TOKEN){
		if(((Identifier *)token)->name != NULL)
			textDel(((Identifier *)token)->name);
		if(((Identifier *)token)->number != NULL)
			tokenDel((Token *)(((Identifier *)token)->number));
		free(token);
	}
}

void tokenDump(Token *token){

	if(token==NULL)
	{
		printf("NULL token\n");
		return;
	}

	if(token->type == NUMBER_TOKEN){
		printf("Number Token=%d\n",((Number*)token)->value);
	}else if(token->type == OPERATOR_TOKEN){
		printf("Operator Token=%s, precedence=%d, affix=%d\n",
					((Operator*)token)->info->symbol,
					((Operator*)token)->info->precedence,
					((Operator*)token)->info->affix);
	}else if(token->type == IDENTIFIER_TOKEN){
		printf("Identifier Token=%s\n",((Identifier*)token)->name->string);
	}else{
		printf("Unknown Token\n");
	}
}