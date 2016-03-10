#ifndef _LEXER_H_
#define _LEXER_H_

#include <list>
using namespace std;

struct Token;

enum LexerStatus
{
	INITIAL_STATUS,						// ��ʼ��״̬
	IN_INT_PART_STATUS,				// ���ڸ���������������
	DOT_STATUS,							// ���ڸ�������С���㲿��
	IN_FRAC_PART_STATUS			// ���ڸ���������������
};


/* 
**�ʷ�������
** �ʷ������������ַ�����Ϊ��λ���д����
*/
class Lexer
{
public:
	Lexer(void);

	~Lexer(void);

	void	Analyze(char* line);											// ����ÿһ�����ʽ��

private:

	void GetToken(Token* token);									// ��ȡһ���ʷ���Ԫ

	char*							m_strLine;								// ���ʽ��

	unsigned int					m_nLinePos;							// �ַ����±�
};


#endif


