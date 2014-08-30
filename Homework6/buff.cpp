#include <iostream>
#include "tokenscanner.h"
#include <string>
#include <vector>
using namespace std;
string readE(TokenScanner & scanner, int prec) ;

string ceceGege = "";
std::vector<string> v;

bool equal(string &a, string &b)
{
	if (a.size() != b.size())
		return false;
	else
	{
		for (int i = 0; i < a.size(); i++)
			if (a[i] != b[i])
				return false;
		return true;
	}
}

int precedence(string token) 
{
	if (token == "=") return 1;
	if (token == "+" || token == "-") return 2;
	if (token == "*" || token == "/") return 3;
	return 0;
}

string readT(TokenScanner & scanner) 
{
	string token = scanner.nextToken();
	TokenType type = scanner.getTokenType(token);
	if (type == NUMBER) 
		return token;
	string exp = readE(scanner, 0);
	scanner.nextToken();
	return exp;
}

string readE(TokenScanner & scanner, int prec) 
{
	string exp = readT(scanner);
	string token, buff = "";
	while (true) 
	{
		token = scanner.nextToken();
		int newPrec = precedence(token);
		if (newPrec <= prec) 
			break;
		string rhs = readE(scanner, newPrec);
		cout<<exp<<rhs<<token<<endl;
		if (ceceGege.size() > 0)
		{
			buff = ceceGege[ceceGege.size() - 1];
			if (precedence(buff) < precedence(token))
				if (v[v.size() - 2] == exp)//error
					exp = exp + " " + token + " " + "(" + rhs + ")";
				else if (v[v.size() - 1] == exp)
					exp = "(" + exp + ")" + " " + token + " " + rhs;
				else 
					exp = exp + " " + token + " " + rhs;
			else
				exp = exp + " " + token + " " + rhs;
		}
		else
			exp = exp + " " + token + " " + rhs;
		ceceGege += token;
		v.push_back(exp);
		v.push_back(rhs);
	}
	scanner.saveToken(token);
	return exp;
}

int main() 
{
	TokenScanner scanner = TokenScanner();
	string input = "";
	cin>>input;
	scanner.setInput(input);
	scanner.ignoreWhitespace();
	string exp = readE(scanner, 0);
	//exp = exp.substr(1,exp.size() - 2);
	cout<<exp;
}