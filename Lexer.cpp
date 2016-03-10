#include "Lexer.h"
#include "token.h"


extern list<Token> G_TokenList;  // 全局的词法单元列表

Lexer::Lexer(void)
{
	m_nLinePos			= 0;
	m_strLine				= 0;
}

Lexer::~Lexer(void)
{
}


void Lexer::GetToken(Token* token)							//获取一个词法单元，并将其放入词法单元列表中
{
	int out_pos = 0;

	LexerStatus status = INITIAL_STATUS;					// 初始状态

	char current_char = 0;											// 当前字符

	token->kind = BAD_TOKEN;

	while (m_strLine[m_nLinePos] != 0)						//循环处理每一个字符
	{
		current_char = m_strLine[m_nLinePos];

		if ((status == IN_INT_PART_STATUS || status == IN_FRAC_PART_STATUS) &&
			!isdigit(current_char) && current_char != '.' ) //如果当前状态是处于操作数的整数或者小数部分，并且当前字符不是阿拉伯数字也不是小数点
		{
			// 形如30.002 + 20 这样的，30.002就是一个数，当扫描到30.002后面的空白字符时，就会进入到这里
			// 此时30.002这个字符串已经放在token->str中了
			
			token->kind = NUMBER_TOKEN;

			sscanf(token->str,"%lf",&token->value);

			G_TokenList.push_back(*token);

			return;
		}

		if (isspace(current_char))									//滤过空白字符
		{
			if (current_char == '\n' || current_char == '\r') //一行字符串结束
			{
				token->kind = END_OF_LINE_TOKEN;

				G_TokenList.push_back(*token);

				return;
			}

			++m_nLinePos;												// 其他空白字符串直接跳过

			continue;
		}

		if (out_pos >= MAX_TOKEN_SIZE -1)					// 处理词法单元太长的情况
		{
			error_exit_msg("token too long!");
		}

		token->str[out_pos] = m_strLine[m_nLinePos];

		++m_nLinePos;

		++out_pos;

		token->str[out_pos] = 0;

		switch(current_char)
		{
		case '+':
			token->kind = ADD_OPERATOR_TOKEN;			//	加法
			G_TokenList.push_back(*token);
			return;
		case '-':
			token->kind = SUB_OPERATOR_TOKEN;			//减法
			G_TokenList.push_back(*token);
			return;
		case '*':
			token->kind = MUL_OPERATOR_TOKEN;			// 乘法
			G_TokenList.push_back(*token);
			return;
		case '/':
			token->kind = DIV_OPERATOR_TOKEN;			//除法
			G_TokenList.push_back(*token);
			return;
		case '(':
			token->kind = LEFT_PARENT_TOKEN;				//左括号
			G_TokenList.push_back(*token);
			return;
		case ')':
			token->kind = RIGHT_PARENT_TOKEN;			//右括号
			G_TokenList.push_back(*token);
			return;
		case '.':																	// 小数点
			if (status == IN_INT_PART_STATUS)					// 正在分析小数点的整数部分
			{
				status = DOT_STATUS;
			}
			else
			{
				error_exit_msg("syntax error!");	
			}
			break;
		default:
			if (isdigit(current_char))									// 判断当前字符是否为阿拉伯数字
			{
				if (status == INITIAL_STATUS)
				{
					status = IN_INT_PART_STATUS;
				} 
				else if (status == DOT_STATUS)
				{
					status = IN_FRAC_PART_STATUS;
				}
			}
		}
	}
}


void Lexer::Analyze(char* line)
{
	m_strLine				=	line;

	m_nLinePos			= 0;

	Token token;

	for (;;)
	{
		GetToken(&token);

		if (token.kind == END_OF_LINE_TOKEN) 
		{
			break;
		}
	}
}