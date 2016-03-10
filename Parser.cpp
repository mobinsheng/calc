#include "Parser.h"
#include "token.h"

extern list<Token> G_TokenList;

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

bool Parser::GetToken(Token* token)  // ��ȡһ���ʷ���Ԫ
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


void Parser::UnGetToken(Token* token)	// ��һ���ʷ���Ԫ�Żشʷ���Ԫ�б���
{
	G_TokenList.push_front(*token);
}

double Parser::ParseExpression()				// �Ա��ʽ�����﷨���������磨xxx�� + ��cccc�� �� ��ccc�� - ��xxx���ı��ʽ
{
	double v1,v2;
	Token token;

	v1 = ParseTerm();									// ��������һ��һԪ���ʽ��ֵ

	for(;;)
	{
		GetToken(&token);

		if (token.kind != ADD_OPERATOR_TOKEN && token.kind != SUB_OPERATOR_TOKEN) //������v1�Ĵʷ���Ԫ�������+��-
		{
			UnGetToken(&token);

			break;
		}

		v2 = ParseTerm(); // �������ڶ���ҽԺ���ʽ��ֵ

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

double Parser::ParseTerm()			// ��һԪ���ʽ�����﷨�������磺10.6��(10 + 6), 10 * 9�ȵȱ��ʽ
{
	double v1,v2;
	Token token;

	v1 = ParsePrimaryExpression();	// ��������һ���ս����ֵ

	while(1)
	{
		GetToken(&token);

		if (token.kind != MUL_OPERATOR_TOKEN && token.kind != DIV_OPERATOR_TOKEN) // ��������ŵ�һ���ս���Ĵʷ���Ԫ����*��/
		{
			UnGetToken(&token);
			break;
		}

		v2 = ParsePrimaryExpression(); //�������ڶ����ս����ֵ

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

double Parser::ParsePrimaryExpression() // ���ս�������﷨����
{
	Token token;

	double value = 0;

	int minus_flag = 0;

	GetToken(&token);
	
	if (token.kind == SUB_OPERATOR_TOKEN) //ĳһ��ֵ�Ƿ�Ϊ��ֵ
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
	else if(token.kind == LEFT_PARENT_TOKEN)		// ����Ǵ����ŵ�
	{
		value = ParseExpression();								// ����������ı��ʽ��ֵ

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