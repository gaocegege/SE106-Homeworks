#include "TryTokenScanner.h"

#include "tokenscanner.h"

using namespace std;

// Part I
Vector<string> TryTokenScanner::allTokens(string text) {
  Vector<string> tokens;
  // [TODO] put your code here
  TokenScanner scanner(text);
  string temp = scanner.nextToken();
  while (temp != "")
    {
	tokens.push_back(temp);
	temp = scanner.nextToken();
    }
  return tokens;
}

// Part II
Vector<string> TryTokenScanner::noWhitespaces(string text) {
  Vector<string> tokens;
  // [TODO] put your code here
  TokenScanner scanner(text);
  scanner.ignoreWhitespace();
  string temp = scanner.nextToken();
  while (temp != "")
    {
        tokens.push_back(temp);
        temp = scanner.nextToken();
    }
  return tokens;
}

// Part III
Vector<string> TryTokenScanner::noComments(string text) {
  Vector<string> tokens;
  // [TODO] put your code here
  TokenScanner scanner(text);
  scanner.ignoreComments();
  string temp = scanner.nextToken();
  while (temp != "")
    {
        tokens.push_back(temp);
        temp = scanner.nextToken();
    }
  return tokens;
}
