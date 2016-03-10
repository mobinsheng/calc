#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;


enum TokenKind
{
	BAD_TOKEN,
	NUMBER_TOKEN,
	ADD_OPERATOR_TOKEN,
	SUB_OPERATOR_TOKEN,
	MUL_OPERATOR_TOKEN,
	DIV_OPERATOR_TOKEN,
	LEFT_PARENT_TOKEN,
	RIGHT_PARENT_TOKEN,
	END_OF_LINE_TOKEN
};

#define MAX_TOKEN_SIZE (256)


struct Token
{
	TokenKind			kind;
	double					value;
	char						str[MAX_TOKEN_SIZE];
};
#define wait_for_input()\
{\
	int xxx;\
	cin>>xxx;\
}

#define error_exit_msg(msg) \
{\
	cout<<msg<<endl;\
	wait_for_input();\
	exit(-1);\
}

extern list<Token> G_TokenList;

#endif