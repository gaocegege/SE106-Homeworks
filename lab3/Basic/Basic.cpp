/*
 * File: basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter
 * from Assignment #5.
 * [TODO: extend and correct the documentation]
 */

#include "../StanfordCPPLib/error.h"
#include "exp.h"
#include "program.h"
#include "parser.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include <cctype>
#include <iostream>
#include <string>
#include "myhead.h"

/* Function prototypes */

bool ProcessLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
	EvalState state;
	Program program;
	while (true) {
		try {
			if (ProcessLine(getLine(), program, state) == false)
				break;
		} catch (ErrorException & ex) {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
	return 0;
}

bool isSe(string str)
{
	if (str == "PRINT" || str == "INPUT" || str == "LET" || str == "REM")
		return true;
	else return false;
}

bool isCon(string str)
{
	if (str == "IF" || str == "GOTO")
		return true;
	else return false;
}

/*
 * Function: ProcessLine
 * Usage: ProcessLine(line, program, state);
 * -----------------------------------------
 * This method processes a single line entered by the user.
 * In this version, the implementation does exactly what the
 * interpreter program does in Chapter 14: read a line,
 * parse it as an expression, and then print the result.
 * In your implementation, you will need to replace this
 * method with one that can respond correctly when the user
 * enters a program line (which begins with a number) or
 * one of the BASIC commands, such as LIST or RUN.
 */

bool ProcessLine(string line, Program & program, EvalState & state) {
	//cout<<"ee";
	TokenScanner scanner;
	scanner.setInput(line);
	string number = "", lineOfNumber = "",token;
	statementT stmt;
	number = scanner.nextToken();
	if (number[0] >= '0' && number[0] <= '9')
	{
		program.addSourceLine(StringToInteger(number), line);
		return true;
	}
	else
	{
		token = number;
		if (isSe(toBig(token)))
		{
			scanner.saveToken(token);
			stmt = new SequentialStatements(scanner);
			stmt->execute(state);
		}
		//cout<<"asdas";//da xiao xie
		if (toBig(token) == "QUIT")
		{
			return false;
		}
		else if (toBig(token) == "LIST")
		{
			int myNumber = program.getFirstLineNumber();
			while (myNumber != -1)
			{
				cout<<program.getSourceLine(myNumber)<<endl;
				myNumber = program.getNextLineNumber(myNumber);
			}
			return true;
		}
		else if (toBig(token) == "HELP")
		{
			cout<<"Name:Gaoce\nID:5120379091\n";
			return true;
		}
		else if (toBig(token) == "RUN")
		{
			int myNumber = program.getFirstLineNumber();
			TokenScanner myscanner;
			while (myNumber != -1)
			{
				myscanner.setInput(program.getSourceLine(myNumber));
				// cout<<myscanner.nextToken();
				// cout<<myscanner.nextToken();
				myscanner.nextToken();
				myscanner.nextToken();
				token = myscanner.nextToken();
				if (isSe(toBig(token)))
				{
					myscanner.saveToken(token);
					stmt = new SequentialStatements(myscanner);
					stmt->execute(state);
					myNumber = program.getNextLineNumber(myNumber);
				}
				else if (toBig(token) == "END")
				{
					myNumber = -1;
				}
				else if (toBig(token) == "GOTO")
				{
					myscanner.nextToken();
					string snumber = myscanner.nextToken();
					myNumber = StringToInteger(snumber);
					if (program.isValid(myNumber) == false)
					{
						myNumber = -1;
						cout<<"LINE NUMBER ERROR\n";
					}
				}
				else if (toBig(token) == "IF")
				{
					string bufflhs = "", buffrhs = "", checkBuff = "";
					char myOperator = '1';
					TokenScanner scannerBuff;
					while (checkBuff != "=" && checkBuff != ">" && checkBuff != "<")
					{
						bufflhs += checkBuff;
						checkBuff = myscanner.nextToken();
					}
					myOperator = checkBuff[0];
					scannerBuff.setInput(bufflhs);\
					scannerBuff.ignoreWhitespace();
					expressionT expBufflhs = ParseExp(scannerBuff);
					checkBuff = myscanner.nextToken();
					while (toBig(checkBuff) != "THEN")
					{
						buffrhs += checkBuff;
						checkBuff = myscanner.nextToken();
					}
					scannerBuff.setInput(buffrhs);
					scannerBuff.ignoreWhitespace();
					expressionT expBuffrhs = ParseExp(scannerBuff);
					myscanner.nextToken();
					string snumber = myscanner.nextToken();
					// cout<<expBufflhs->toString()<<"\t"<<expBuffrhs->toString()<<endl;
					if (myOperator == '=' && expBufflhs->eval(state) == expBuffrhs->eval(state))
					{
						myNumber = StringToInteger(snumber);
						if (program.isValid(myNumber) == false)
						{
							myNumber = -1;
							cout<<"LINE NUMBER ERROR\n";
						}
					}

					else if (myOperator == '<' && expBufflhs->eval(state) < expBuffrhs->eval(state))
					{
						myNumber = StringToInteger(snumber);
						if (program.isValid(myNumber) == false)
						{
							myNumber = -1;
							cout<<"LINE NUMBER ERROR\n";
						}
					}

					else if (myOperator == '>' && expBufflhs->eval(state) > expBuffrhs->eval(state))
					{
						myNumber = StringToInteger(snumber);
						if (program.isValid(myNumber) == false)
						{
							myNumber = -1;
							cout<<"LINE NUMBER ERROR\n";
						}
					}

					else
					{
						myNumber = program.getNextLineNumber(myNumber);
					}
				}
			}
			return true;
		}
		else if (toBig(token) == "CLEAR")
		{
			program.clear();
			state.clear();
			return true;
		}
	}
	return true;
	// scanner.ignoreWhitespace();
	// expressionT exp = ParseExp(scanner);
	// cout << exp->toString() << " evaluates to "
	// 	 << exp->eval(state) << endl;
	// delete exp;
}
