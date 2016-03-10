#include "Parser.h"
#include "token.h"

extern list<Token> G_TokenList;

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

bool Parser::GetToken(Token* token)  // 获取一个词法单元
{
	if (G_TokenList.size() > 0)
	{
		*token = *(G_TokenList.begin());

		G_TokenList.pop_front();

		return true;
	}
	
	error_exit_msg("Need More Token!");

	return false;
}


void Parser::UnGetToken(Token* token)	// 将一个词法单元放回词法单元列表中
{
	G_TokenList.push_front(*token);
}

double Parser::ParseExpression()				// 对表达式进行语法分析，形如（xxx） + （cccc） 或 （ccc） - （xxx）的表达式
{
	double v1,v2;
	Token token;

	v1 = ParseTerm();									// 分析出第一个一元表达式的值

	for(;;)
	{
		GetToken(&token);

		if (token.kind != ADD_OPERATOR_TOKEN && token.kind != SUB_OPERATOR_TOKEN) //紧接着v1的词法单元如果不是+或-
		{
			UnGetToken(&token);

			break;
		}

		v2 = ParseTerm(); // 分析出第二个医院表达式的值

		if (token.kind == ADD_OPERATOR_TOKEN)
		{
			v1 += v2;
		}
		else if (token.kind == SUB_OPERATOR_TOKEN)
		{
			v1 -= v2;
		}
		else
		{
			UnGetToken(&token);
		}
	}
	return v1;
}

double Parser::ParseTerm()			// 对一元表达式进行语法分析，如：10.6、(10 + 6), 10 * 9等等表达式
{
	double v1,v2;
	Token token;

	v1 = ParsePrimaryExpression();	// 分析出第一个终结符的值

	while(1)
	{
		GetToken(&token);

		if (token.kind != MUL_OPERATOR_TOKEN && token.kind != DIV_OPERATOR_TOKEN) // 如果紧接着第一个终结符的词法单元不是*或/
		{
			UnGetToken(&token);
			break;
		}

		v2 = ParsePrimaryExpression(); //分析出第二个终结符的值

		if (token.kind == MUL_OPERATOR_TOKEN)
		{
			v1 *= v2;
		}
		else if (token.kind == DIV_OPERATOR_TOKEN)
		{
			v1 /= v2;
		}
	}

	return v1;
}

double Parser::ParsePrimaryExpression() // 对终结符进行语法分析
{
	Token token;

	double value = 0;

	int minus_flag = 0;

	GetToken(&token);
	
	if (token.kind == SUB_OPERATOR_TOKEN) //某一个值是否为负值
	{
		minus_flag = 1;
	}
	else
	{
		UnGetToken(&token);
	}

	GetToken(&token);

	if (token.kind == NUMBER_TOKEN)
	{
		value = token.value;
	}
	else if(token.kind == LEFT_PARENT_TOKEN)		// 如果是带括号的
	{
		value = ParseExpression();								// 计算括号里的表达式的值

		GetToken(&token);

		if(token.kind != RIGHT_PARENT_TOKEN)
		{
			error_exit_msg("missing ')' error!");
		}
	}
	else
	{
		UnGetToken(&token);
	}

	if (minus_flag)
	{
		value = -value;
	}

	return value;
}