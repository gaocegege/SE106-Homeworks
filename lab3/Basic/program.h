/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.  You should not need to make any changes to this
 * file unless you extend the interpreter.
 */

#ifndef _program_h
#define _program_h

#include "statement.h"
#include "map.h"
#include <list>
#include <string>

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    statementT.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

	Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

	~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

	void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */

	void addSourceLine(int lineNumber, string line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

	void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the text for the program line with the specified
 * line number.  If no such program line exists, this method
 * returns the empty string.
 */

	string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the
 * statement at the specified line number.  If no such
 * line number exists, this method raises an error.  If
 * a previous parsed representation exists, the memory
 * for that statementT is reclaimed.
 */

	void setParsedStatement(int lineNumber, statementT stmt);

/*
 * Method: getParsedStatement
 * Usage: statementT stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */

	statementT getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

	int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

	int getNextLineNumber(int lineNumber);

	bool isValid(int lineNumber);

private:
	std::list<string> sourceLine;
	std::list<int> lineNumber;
	int current;
};

Program::Program() {
	//?
}

Program::~Program() {
	//?
}

void Program::clear() {
	sourceLine.clear();
	lineNumber.clear();
	current = 0;
}

void Program::addSourceLine(int lineNumber, string line) {
	int index = 0;
	if (this->lineNumber.empty())
	{
		this->lineNumber.push_back( lineNumber);
		this->sourceLine.push_back( line);
		return;
	}
	for (list<int>::iterator it = this->lineNumber.begin(); it != this->lineNumber.end(); it++)
	{
		if (lineNumber < *it)
		{
			if (line.size() == 2 || line.size() == 5)
				return;
			this->lineNumber.insert(it, lineNumber);
			list<string>::iterator lineIt = this->sourceLine.begin();//maybe wrong
			for (int i = 0; i < index; i++)
				lineIt++;
			this->sourceLine.insert(lineIt, line);
			return;
		}
		else if (lineNumber == *it)
		{
			if (line.size() == 2 || line.size() == 5)
			{
				this->lineNumber.erase(it);
				list<string>::iterator lineIt = this->sourceLine.begin();//maybe wrong
				for (int i = 0; i < index; i++)
					lineIt++;
				this->sourceLine.erase(lineIt);
				return;
			}
			list<string>::iterator lineIt = this->sourceLine.begin();//maybe wrong
			for (int i = 0; i < index; i++)
				lineIt++;
			this->sourceLine.insert(lineIt, line);
			this->sourceLine.erase(lineIt);
			return;
		}
		index++;
	}
	if (line.size() == 2 || line.size() == 5)
		return;
	this->lineNumber.push_back(lineNumber);
	this->sourceLine.push_back(line);

}

void Program::removeSourceLine(int lineNumber) {
	int index = 0;
	for (list<int>::iterator it = this->lineNumber.begin(); it != this->lineNumber.end(); it++)
	{
		if (*it == lineNumber)
		{
			this->lineNumber.erase(it);
			list<string>::iterator lineIt = this->sourceLine.begin();//maybe wrong
			for (int i = 0; i < index; i++)
				lineIt++;
			this->sourceLine.erase(lineIt);
			return;
		}
		index++;
	}
}

string Program::getSourceLine(int lineNumber) {
	int index = 0;
	for (list<int>::iterator it = this->lineNumber.begin(); it != this->lineNumber.end(); it++)
	{
		if (*it == lineNumber)
		{
			list<string>::iterator lineIt = this->sourceLine.begin();//maybe wrong
			for (int i = 0; i < index; i++)
				lineIt++;
			return *(lineIt);
		}
		index++;
	}
}

void Program::setParsedStatement(int lineNumber, statementT stmt) {
	// Replace this stub with your own code
}

statementT Program::getParsedStatement(int lineNumber) {
	return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
	if (this->lineNumber.empty())
		return -1;
	return *(this->lineNumber.begin());
}

int Program::getNextLineNumber(int lineNumber) {
	for (list<int>::iterator it = this->lineNumber.begin(); it != this->lineNumber.end(); it++)
	{
		if (*it == lineNumber)
		{
			it++;
			if (it == this->lineNumber.end())
				return -1;
			return *(it);
		}
	}
	return -1;
}

bool Program::isValid(int lineNumber)
{
	for (list<int>::iterator it = this->lineNumber.begin(); it != this->lineNumber.end(); it++)
	{
		if (*it == lineNumber)
		{
			return true;
		}
	}
	return false;
}

#endif
