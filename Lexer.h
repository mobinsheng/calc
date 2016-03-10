#ifndef _LEXER_H_
#define _LEXER_H_

#include <list>
using namespace std;

struct Token;

enum LexerStatus
{
	INITIAL_STATUS,						// 初始化状态
	IN_INT_PART_STATUS,				// 处于浮点数的整数部分
	DOT_STATUS,							// 处于浮点数的小数点部分
	IN_FRAC_PART_STATUS			// 处于浮点数的整数部分
};


/* 
**词法分析器
** 词法分析器是以字符串行为单位进行处理的
*/
class Lexer
{
public:
	Lexer(void);

	~Lexer(void);

	void	Analyze(char* line);											// 分析每一个表达式行

private:

	void GetToken(Token* token);									// 获取一个词法单元

	char*							m_strLine;								// 表达式串

	unsigned int					m_nLinePos;							// 字符串下标
};


#endif


