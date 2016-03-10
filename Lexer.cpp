#include "Lexer.h"
#include "token.h"


extern list<Token> G_TokenList;  // ȫ�ֵĴʷ���Ԫ�б�

Lexer::Lexer(void)
{
	m_nLinePos			= 0;
	m_strLine				= 0;
}

Lexer::~Lexer(void)
{
}


void Lexer::GetToken(Token* token)							//��ȡһ���ʷ���Ԫ�����������ʷ���Ԫ�б���
{
	int out_pos = 0;

	LexerStatus status = INITIAL_STATUS;					// ��ʼ״̬

	char current_char = 0;											// ��ǰ�ַ�

	token->kind = BAD_TOKEN;

	while (m_strLine[m_nLinePos] != 0)						//ѭ������ÿһ���ַ�
	{
		current_char = m_strLine[m_nLinePos];

		if ((status == IN_INT_PART_STATUS || status == IN_FRAC_PART_STATUS) &&
			!isdigit(current_char) && current_char != '.' ) //�����ǰ״̬�Ǵ��ڲ���������������С�����֣����ҵ�ǰ�ַ����ǰ���������Ҳ����С����
		{
			// ����30.002 + 20 �����ģ�30.002����һ��������ɨ�赽30.002����Ŀհ��ַ�ʱ���ͻ���뵽����
			// ��ʱ30.002����ַ����Ѿ�����token->str����
			
			token->kind = NUMBER_TOKEN;

			sscanf(token->str,"%lf",&token->value);

			G_TokenList.push_back(*token);

			return;
		}

		if (isspace(current_char))									//�˹��հ��ַ�
		{
			if (current_char == '\n' || current_char == '\r') //һ���ַ�������
			{
				token->kind = END_OF_LINE_TOKEN;

				G_TokenList.push_back(*token);

				return;
			}

			++m_nLinePos;												// �����հ��ַ���ֱ������

			continue;
		}

		if (out_pos >= MAX_TOKEN_SIZE -1)					// ����ʷ���Ԫ̫�������
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
			token->kind = ADD_OPERATOR_TOKEN;			//	�ӷ�
			G_TokenList.push_back(*token);
			return;
		case '-':
			token->kind = SUB_OPERATOR_TOKEN;			//����
			G_TokenList.push_back(*token);
			return;
		case '*':
			token->kind = MUL_OPERATOR_TOKEN;			// �˷�
			G_TokenList.push_back(*token);
			return;
		case '/':
			token->kind = DIV_OPERATOR_TOKEN;			//����
			G_TokenList.push_back(*token);
			return;
		case '(':
			token->kind = LEFT_PARENT_TOKEN;				//������
			G_TokenList.push_back(*token);
			return;
		case ')':
			token->kind = RIGHT_PARENT_TOKEN;			//������
			G_TokenList.push_back(*token);
			return;
		case '.':																	// С����
			if (status == IN_INT_PART_STATUS)					// ���ڷ���С�������������
			{
				status = DOT_STATUS;
			}
			else
			{
				error_exit_msg("syntax error!");	
			}
			break;
		default:
			if (isdigit(current_char))									// �жϵ�ǰ�ַ��Ƿ�Ϊ����������
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