/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module, which
 * exports functions to parse expressions from a TokenScanner.
 *
 * Except for this comment, the parser.h file is exactly the same as
 * is appears in Chapter 14.  The only change you need to make in
 * this file is to add the prototype for a function ParseStatement
 * that parses the next statement from a TokenScanner.
 */

#ifndef _parser_h
#define _parser_h

#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"

/*
 * Function: ParseExp
 * Usage: exp = ParseExp(TokenScanner);
 * -------------------------------
 * This function parses an expression by reading tokens from
 * the TokenScanner, which must be provided by the client.
 */

expressionT ParseExp(TokenScanner & scanner);

/*
 * Functions: ReadE, ReadT
 * Usage: exp = ReadE(TokenScanner, prec);
 *        exp = ReadT(TokenScanner);
 * ----------------------------------
 * These functions provide low-level entry points to the parser,
 * which are useful to clients who need to use expression
 * parsing in large applications.  ReadE(TokenScanner, prec) returns
 * the next expression involving operators whose precedence
 * is at least prec; ReadT returns the next individual term.
 */

expressionT ReadE(TokenScanner & scanner, int prec = 0);
expressionT ReadT(TokenScanner & scanner);

/*
 * Function: Precedence
 * Usage: prec = Precedence(token);
 * --------------------------------
 * This function returns the precedence of the specified operator
 * token.  If the token is not an operator, Precedence returns 0.
 */

int Precedence(string token);

#endif
