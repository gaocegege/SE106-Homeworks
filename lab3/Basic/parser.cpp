/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 *
 * Except for this comment, the parser.cpp file is exactly the same
 * as is appears in Chapter 14.  The only changes you need to make
 * in this file are (1) to remove the code from the parser that
 * recognizes the = operator because BASIC does not allow embedded
 * assignments and (2) to implement the function ParseStatement
 * that reads tokens from the Tokenscanner to create a statementT.
 */

#include "exp.h"
#include <iostream>
#include "map.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "parser.h"
#include "myhead.h"

/*
 * Implementation notes: ParseExp
 * ------------------------------
 * This function reads an expression and then checks for extra tokens.
 */

expressionT ParseExp(TokenScanner & scanner) {
	expressionT exp = ReadE(scanner);
	// if (scanner.hasMoreTokens()) {
	// 	cout<<"ParseExp found extra token: " + scanner.nextToken());
	// }
	return exp;
}

/*
 * Implementation notes: ReadE
 * Usage: exp = ReadE(Tokenscanner, prec);
 * ----------------------------------
 * This function reads the next expression from the Tokenscanner by
 * matching the input to the following ambiguous grammar:
 *
 *       E  ->  T
 *       E  ->  E op E
 *
 * This version of the method uses precedence to resolve the
 * ambiguity.  This level of the recursive descent parser
 * reads operators and subexpressions until the precedence of
 * a new operator is greater than the prevailing one.  When a
 * higher-precedence operator is found, ReadE calls itself
 * recursively to read in that subexpression as a unit.
 */

expressionT ReadE(TokenScanner & scanner, int prec) {
	expressionT exp = ReadT(scanner);
	string token;
	EvalState hehe;
	while (true) {
		token = scanner.nextToken();
		int newPrec = Precedence(token);
		if (newPrec <= prec) break;
		expressionT rhs = ReadE(scanner, newPrec);
		// if (rhs->eval(hehe) == 0)
		// {
		// 	cout<<"DIVIDE BY ZERO\n";
		// }
		exp = new CompoundNode(token[0], exp, rhs);
	}
	scanner.saveToken(token);
	return exp;
}

/*
 * Function: ReadT
 * Usage: exp = ReadT(Tokenscanner);
 * ----------------------------
 * This function reads a single term from the Tokenscanner by matching
 * the input to one of the following grammatical rules:
 *
 *       T  ->  integer
 *       T  ->  identifier
 *       T  ->  ( E )
 */

expressionT ReadT(TokenScanner & scanner) {
	expressionT exp;
	string token = scanner.nextToken();
	if (isdigit(token[0])) {
		exp = new ConstantNode(StringToInteger(token));
	} else if (isalpha(token[0])) {
		exp = new IdentifierNode(token);
	} else if (token == "(") {
		exp = ReadE(scanner);
		if (scanner.nextToken() != ")") {
			cout<<"Unbalanced parentheses in expression";
		}
	} else {
		cout<<"Illegal term in expression";
	}
	return exp;
}

/*
 * Function: IsOperator
 * Usage: if (IsOperator(token)) . . .
 * -----------------------------------
 * This function returns true if the token is a legal operator.
 */

bool IsOperator(string token) {
	return (Precedence(token) != 0);
}

/*
 * Function: Precedence
 * Usage: prec = Precedence(token);
 * --------------------------------
 * This function returns the precedence of the specified operator
 * token.  If the token is not an operator, Precedence returns 0.
 */

int Precedence(string token) {
	if (token.length() > 1) return 0;
	switch (token[0]) {
	  case '=': return 1;
	  case '+': case '-': return 2;
	  case '*': case '/': return 3;
	  default:  return 0;
	}
}
