#ifndef _PARSER_H
#define _PARSER_H

#include "token.h"

/* 
** �﷨������
** ��Ҫ�õ��Ĵʷ���Ԫ�Ѿ������ȫ�ֵĴʷ���Ԫ�б�����
*/
class Parser 
{
public:

	Parser(void);

	~Parser(void);

	bool GetToken(Token* token);					// �Ӵʷ���Ԫ�б���ȡ��һ���ʷ���Ԫ
	
	void UnGetToken(Token* token);				// ��һ���ʷ���Ԫ�Żص��ʷ���Ԫ�б���

	double ParseExpression();							//�������ʽ

	double ParseTerm();									// ����һԪ���ʽ

	double ParsePrimaryExpression();				//�����ս��

};


#endif


