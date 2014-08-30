#ifndef _TRY_TOKENSCANNER_H_
#define _TRY_TOKENSCANNER_H_

#include <string>
#include "vector.h"
using namespace std;

class TryTokenScanner {
public:
  static Vector<string> allTokens(string text);
  static Vector<string> noWhitespaces(string text);
  static Vector<string> noComments(string text);
};

#endif /* _TRY_TOKENSCANNER_H_ */
