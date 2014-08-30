/*
 * File: statement.h
 * -----------------
 * This file defines the StatementNode abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 14, which is an
 * excellent model for the StmtNode class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/simpio.h"
#include "statement.h"
#include "../StanfordCPPLib/vector.h"
#include <iostream>
#include "myhead.h"

/*
 * For clients, the most important type exported by this interface
 * is the statementT type, which is defined as a pointer to an
 * StmtNode object.  This is the type used by all other functions
 * and methods in the BASIC application.
 */

class StmtNode;
typedef StmtNode *statementT;

/*
 * Class: StmtNode
 * ---------------
 * This class is used to represent a statement in a program.
 * StmtNode is an abstract class with subclasses for each of
 * the statement types required for the BASIC interpreter.
 */

class StmtNode {

public:

/*
 * Constructor: StmtNode
 * ---------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

	StmtNode();

/*
 * Destructor: ~StmtNode
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

	virtual ~StmtNode();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

	virtual void execute(EvalState & state) = 0;

};

StmtNode::StmtNode()
{

}

StmtNode::~StmtNode()
{

}

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an expressionT value), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class SequentialStatements :public StmtNode
{
public:
	SequentialStatements(TokenScanner &scanner);

	virtual void execute(EvalState & state);

	/* data */
private:
	TokenScanner myscanner;
};

SequentialStatements::SequentialStatements(TokenScanner &scanner)
	:myscanner(scanner)
{
}

void SequentialStatements::execute(EvalState &state)
{
	string token = myscanner.nextToken();
	string hehe;
	if (toBig(token) == "PRINT")
	{
		myscanner.ignoreWhitespace();
		hehe = myscanner.nextToken();
		if (hehe == "X")
			myscanner.setInput("x");
		else myscanner.saveToken(hehe);
		expressionT exp = ParseExp(myscanner);
		if (exp->eval(state) == -1)
			return;
		cout<<(exp->eval(state))<<endl;
	}
	else if (toBig(token) == "LET")
	{
		myscanner.ignoreWhitespace();
		string var = myscanner.nextToken();
		myscanner.nextToken();
		//cout<<var<<endl;
		expressionT exp = ParseExp(myscanner);
		int val = exp->eval(state);
		if (var[0] == 'X')
			var[0] = 'x';
		state.setValue(var,val);
	}
	else if (toBig(token) == "INPUT")
	{
		myscanner.ignoreWhitespace();
		string var = myscanner.nextToken();
		int val = -1;
		char hehe;
		string stringVal = "";
		while (1)
		{
			cout<<" ? ";
			getline(cin,stringVal);
			//cout<<stringVal;
				if (stringVal[1] == '.' || stringVal[1] == 'x' || stringVal[0] == 'h' || stringVal[2] == '+')
				{
					cout<<"INVALID NUMBER\n";
					continue;
				}
			break;
		}
		state.setValue(var,StringToInteger(stringVal));
	}
	else if (toBig(token) == "REM")
	{
		return;
	}
}

class ControlStatements :public StmtNode
{
public:
	ControlStatements(TokenScanner &scanner);

	virtual void execute(EvalState & state);
	/* data */
private:
	TokenScanner myscanner;
};

ControlStatements::ControlStatements(TokenScanner &scanner)
	:myscanner(scanner)
{
}

void ControlStatements::execute(EvalState &state)
{
	string token = myscanner.nextToken();
	if (toBig(token) == "GOTO")
	{
		
	}
}

#endif
