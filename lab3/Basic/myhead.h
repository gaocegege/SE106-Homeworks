#ifndef _myhead_H_
#define _myhead_H_

#include <sstream>
static string IntegerToString(int integer)
{
	ostringstream stringstream;
	stringstream<<integer;
	return stringstream.str();
}

static int StringToInteger(string str)
{
	stringstream stream;
	int answer;
	stream<<str;
	stream>>answer;
	return answer;
}

static string toBig(string str)
{
	for (int i = 0; i < str.size(); i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] += 'A' - 'a';
	return str;
}

#endif