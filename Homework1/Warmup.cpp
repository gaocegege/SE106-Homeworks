#include <iostream>
#include <string>
#include "vector.h"
#include "TryTokenScanner.h"
using namespace std;

class Checker {
  int total_weight;
  int pass_weight;
  int total_count;
  int pass_count;

public:
  Checker() {
    pass_weight = 0;
    total_weight = 0;
    pass_count = 0;
    total_count = 0;
  }

  string escapeStr(string str) {
    std::ostringstream ss;
    int i;
    for (i = 0; i != str.length(); i++) {
      switch (str[i]) {
        case '\\': ss << "\\\\"; break;
        case '"' : ss << "\\\""; break;
        case '/' : ss << "\\/";  break;
        case '\b': ss << "\\b";  break;
        case '\f': ss << "\\f";  break;
        case '\n': ss << "\\n";  break;
        case '\r': ss << "\\r";  break;
        case '\t': ss << "\\t";  break;
        default: ss << str[i]; break;
      }
    }
    return ss.str();
  }

  void showErrorMsg(Vector<string>& expected,
    Vector<string>& actual) {
    int i;
    cout << "\tExpected   : {";
    for (i = 0; i != expected.size(); i++) {
      if (i) cout << ", ";
      cout << "\"" << escapeStr(expected[i]) << "\"";
    }
    cout << "}" << endl << "\tYour answer: {";
    for (i = 0; i != actual.size(); i++) {
      cout << "\"" << escapeStr(actual[i]) << "\"";
    }
    cout << "}" << endl;
  };

  bool checkEquals(Vector<string>& expected,
    Vector<string>& actual, int weight = 1) {
    if (expected.size() != actual.size()) {
      fail(weight);	
      showErrorMsg(expected, actual);
      return 0;
    }
    for (int i = 0; i != expected.size(); ++i) {
      if (expected[i] != actual[i]) {
        fail(weight);
        showErrorMsg(expected, actual);
        return 0;
      }
    }
    pass(weight);
    return 1;
  }

  void pass(int weight = 1) {
    total_weight += weight;
    pass_weight += weight;
    ++total_count;
    ++pass_count;
    reportCheck(1);
  }

  void fail(int weight = 1) {
    total_weight += weight; 
    ++total_count;
    reportCheck(0);
  }

  void reportCheck(bool pass) {
    string result = pass ? "Pass" : "Fail";
    cout << "Check " << total_count << ": " << result << endl;
  }

  void reportAllChecks() {
    cout << endl;
    cout << "Check: " << pass_count << "/" << total_count << endl;
    cout << "Score: " << pass_weight << "/" << total_weight << endl;
  }
};

int main() {
  Checker checker;
  // Check Part I
  Vector<string> a1 = TryTokenScanner::allTokens("Hello world!");
  Vector<string> e1;
  e1.push_back("Hello"); e1.push_back(" "); e1.push_back("world"); e1.push_back("!");
  checker.checkEquals(e1, a1);

  // Check Part II
  Vector<string> a2 = TryTokenScanner::noWhitespaces("Hello  !\r\n\tworld\t !");
  Vector<string> e2;
  e2.push_back("Hello"); e2.push_back("!"); e2.push_back("world"); e2.push_back("!");
  checker.checkEquals(e2, a2);

  // Check Part III
  Vector<string> a3 = TryTokenScanner::noComments("Hello/* World */!// SE106");
  Vector<string> e3;
  e3.push_back("Hello"); e3.push_back("!");
  checker.checkEquals(e3, a3);

  checker.reportAllChecks();
  return 0;
}
