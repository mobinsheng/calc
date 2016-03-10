// calc.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

#include "token.h"
#include "Lexer.h"
#include "Parser.h"


using namespace std;


list<Token> G_TokenList;

void DumpTokenList()
{
	list<Token>::iterator it;
	for (it = G_TokenList.begin(); it != G_TokenList.end();++it)
	{
		cout<<(*it).str<<" ";
	}
	cout<<endl;
}

int main(int argc, char* argv[])
{
	char st_line[1024] = {0};
	Token token;
	Lexer lex;
	Parser par;
	FILE* pIn = fopen("cal.txt","r");
	while (fgets(st_line, 1024, pIn) != NULL) 
	{
		lex.Analyze(st_line);

		double v = par.ParseExpression();

		string str = st_line;

		str = str.substr(0,str.find('\n'));

		cout<<str<<"="<<v<<endl;

		G_TokenList.clear();

	}

	wait_for_input();
	return 0;
}

