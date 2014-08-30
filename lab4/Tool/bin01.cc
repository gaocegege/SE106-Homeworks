#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
  istream* is;
  char c;
  if (argc == 2) is = new ifstream(argv[1]);
  else is = &cin;
  for (size_t n = 0; is->get(c); n++) {
    if (!(n & 7)) {
      if (n) cout << endl;
      cout.fill(' '); cout.width(12); cout << n;
      cout << " : ";
    }
    for (int i = 0; i < 8; i++) cout << "01"[!!(c & (128 >> i))];
  }
  cout << endl;
  if (argc == 2) delete is;
  return 0;
}
