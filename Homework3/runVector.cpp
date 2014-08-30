// [TODO]
// Student ID: 5120379091
// Name: GaoCe
//
#include <iostream>
#include "Vector.h"
using namespace std;

class X {
  int x;
  static int count;
  static bool notify;
public:
  X(): x(-1) { count++; }
  X(int x): x(x) { count++; }
  X(const X& x): x(x.x) { count++; }
  ~X() { count--; if (count == 0 && notify) cout << "All objects destructed." ; }
  static void useNotify() { notify = true; }
  friend ostream& operator<<(ostream& os, const X& x) { return os << x.x; }
};

int X::count = 0;
bool X::notify = false;

int main () {
  std::cout.setf(std::ios::boolalpha);
  {
    X holder;
    {
      Vector<X> v1;
      Vector<X> v2(5);
      Vector<X> v3(v2);

      cout << "Current v1.empty() == " << v1.empty() << endl;
      cout << "Current v2.size() == " << v2.size() << endl;
      cout << "Current v3.size() == " << v3.size() << endl;

      v1 = v3;
      cout << "Current v1.size() == " << v1.size() << endl;
      cout << "Current v1.empty() == " << v1.empty() << endl;

      int n;
      for (n = 5; n < 20; n++) v1.push_back(X(n));
      cout << "Current v1.size() == " << v1.size() << endl;

      v1.resize(10);
      cout << "Current v1.size() == " << v1.size() << endl;
      v1.resize(15);
      cout << "Current v1.size() == " << v1.size() << endl;
      Iterator<X> it = v1.begin();
      it +=10;
      for (it; it < 13; it++) *it = X(100 + it.getIndex());
      cout << "v1 values:";
      for (Iterator<X> it = v1.begin(); it < 15; it++) 
        cout << " " << *it;
      cout << endl;

    }
    X::useNotify();
  }
  cout << endl;
  return 0;
}

