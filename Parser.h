#ifndef _PARSER_H
#define _PARSER_H

#include "token.h"

/* 
** 语法分析器
** 需要用到的词法单元已经存放在全局的词法单元列表当中了
*/
class Parser 
{
public:

	Parser(void);

	~Parser(void);

	bool GetToken(Token* token);					// 从词法单元列表中取出一个词法单元
	
	void UnGetToken(Token* token);				// 将一个词法单元放回到词法单元列表中

	double ParseExpression();							//解析表达式

	double ParseTerm();									// 解析一元表达式

	double ParsePrimaryExpression();				//解析终结符

};


#endif


