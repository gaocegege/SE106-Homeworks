//Name:Gaoce
//ID:5120379091

/*	Version 1.0	*/

/*	
 *	The program has some problems, 
 *	because I don't how to get the 
 *	position of the token, it always
 *	return -1 because it has more 
 *	than one saveTokens().
 */

// #include <iostream>
// #include "tokenscanner.h"
// #include <string>
// #include <vector>
// using namespace std;
// string readE(TokenScanner & scanner, int prec) ;

// string ceceGege = "";
// std::vector<string> v;

// bool equal(string &a, string &b)
// {
// 	if (a.size() != b.size())
// 		return false;
// 	else
// 	{
// 		for (int i = 0; i < a.size(); i++)
// 			if (a[i] != b[i])
// 				return false;
// 		return true;
// 	}
// }

// int precedence(string token) 
// {
// 	if (token == "=") return 1;
// 	if (token == "+" || token == "-") return 2;
// 	if (token == "*" || token == "/") return 3;
// 	return 0;
// }

// string readT(TokenScanner & scanner) 
// {
// 	string token = scanner.nextToken();
// 	TokenType type = scanner.getTokenType(token);
// 	if (type == NUMBER) 
// 		return token;
// 	string exp = readE(scanner, 0);
// 	scanner.nextToken();
// 	return exp;
// }

// string readE(TokenScanner & scanner, int prec) 
// {
// 	string exp = readT(scanner);
// 	string token, buff = "";
// 	while (true) 
// 	{
// 		token = scanner.nextToken();
// 		int newPrec = precedence(token);
// 		if (newPrec <= prec) 
// 			break;
// 		string rhs = readE(scanner, newPrec);
// 		cout<<exp<<rhs<<token<<endl;
// 		if (ceceGege.size() > 0)
// 		{
// 			buff = ceceGege[ceceGege.size() - 1];
// 			if (precedence(buff) < precedence(token))
// 				if (v[v.size() - 2] == exp)//error
// 					exp = exp + " " + token + " " + "(" + rhs + ")";
// 				else if (v[v.size() - 1] == exp)
// 					exp = "(" + exp + ")" + " " + token + " " + rhs;
// 				else 
// 					exp = exp + " " + token + " " + rhs;
// 			else
// 				exp = exp + " " + token + " " + rhs;
// 		}
// 		else
// 			exp = exp + " " + token + " " + rhs;
// 		ceceGege += token;
// 		v.push_back(exp);
// 		v.push_back(rhs);
// 	}
// 	scanner.saveToken(token);
// 	return exp;
// }

// int main() 
// {
// 	TokenScanner scanner = TokenScanner();
// 	string input = "";
// 	cin>>input;
// 	scanner.setInput(input);
// 	scanner.ignoreWhitespace();
// 	string exp = readE(scanner, 0);
// 	//exp = exp.substr(1,exp.size() - 2);
// 	cout<<exp;
// }

/*	version 2.0 */

/*因为最近一直在写ICS的作业，C写习惯了，忘了是用C++写程序设计的作业，
所以代码看起来非常C，不要在意这些细节了*/

#include <iostream>
#include <malloc.h>
#include <string>
#define maxsize 100

using namespace std;
typedef struct 
{
	char data[maxsize];
	int top;
}Stack;

Stack *InitStack()
{
	Stack *S;
	S=(Stack *)malloc(sizeof(Stack));
	S->top=-1;
	return S;
}
int EmptyStack(Stack *S)
{
	if(S->top<=-1)
		return 1;
	else
		return 0;
}
int FullStack(Stack *S)
{
	if(S->top>=maxsize)
		return 1;
	else
		return 0;
}
Stack *Pop(Stack *S)
{
	if(!EmptyStack(S))
	{
		S->top--;
	}
	return S;
}
Stack *Push(Stack *S,char Data)
{
	if(!FullStack(S))
	{
		S->top++;
		S->data[S->top]=Data;
	}
	return S;
}
void PrintStack(Stack *S)
{
	if(EmptyStack(S))
	{
		printf("此栈为空，无法输出!");
	}
	else
	{
		while(S->top>-1)
		{
			S=Pop(S);
			printf("%c",S->data[S->top+1]);
		}
	}
}
int main()
{
	Stack *S1,*S2;
	char c;
	string s;
	int i=-1,j,k,m,n;
	S1=InitStack();
	S2=InitStack();
	printf("请输入一个四则运算表达式:\n");
	cin>>s;
	i = s.size() - 1;
	for(j=0;j<=i;j++)
	{
		if(s[j]=='(')//考虑左括号
		{
			if(s[j+2]==')')//若括号里只有一个字符，删除括号
			{
				j++;
				S1=Push(S1,s[j]);
				j++;
			}
			else if(s[j+3]==')')
			{
				if(s[j+1]=='-')//若与左括号相邻的是负号
				{
				for(k=0;k<4;k++)
				{
					S1=Push(S1,s[j]);
					j++;
				}
				}
				else
				{
					for(k=0;k<2;k++)
					{
						j++;
						S1=Push(S1,s[j]);
					}
					j++;
				}
			}
			else if(j-1==-1)//若第一个字符是左括号
			{
				S1=Push(S1,s[j]);
			}
			else if(j-1>=0)//若第一个字符不是左括号
			{
	           if(s[j-1]=='/')
			   {
				  S1=Push(S1,s[j]);
			   }
			   else if((s[j-1]=='*'||s[j-1]=='-')&&(s[j+2]=='+'||s[j+2]=='-')||s[j+1]=='-')
			   { 
				   for(;s[j]!=')';j++)
				   {
					   S1=Push(S1,s[j]);
				   }
				   S1=Push(S1,s[j]);
			   }
			   else
			   {
				  for(;s[j]!=')';j++)
				  {
					  S1=Push(S1,s[j]);
				  }
				  j--;
			   }
			}
		}
		else if(s[j]==')')//考虑右括号
		{
			if(j==i)
			{
				S1=Push(S1,s[j]);
			}
			else if((s[j-2]=='+'||s[j-2]=='-')&&(s[j+1]=='*'||s[j+1]=='/'))
			{
				S1=Push(S1,s[j]);
			}
			else
			{
				m=S1->top;
				for(k=0;S1->data[m]!='(';k++)
				{
					S2=Push(S2,S1->data[m]);
					m--;
				}
				for(n=0;n<k+1;n++)
				{
					S1=Pop(S1);
				}
				for(n=0;n<k;n++)
				{
					S1=Push(S1,S2->data[S2->top]);
					S2->top--;
				}
			}
		}
		else//考虑除左右括号以外的字符
		{
			S1=Push(S1,s[j]);
		}
	}
	while(!EmptyStack(S1))
	{
		S2=Push(S2,S1->data[S1->top]);
		S1=Pop(S1);
	}
	printf("整理括号后，四则运算表达式为:\n");
	PrintStack(S2);//遍历栈
	printf("\n");
}