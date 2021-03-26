#include <iostream>
#include <deque>
using namespace std;

int main() {
  string x;
  int n;

  cin >> x >> n;

  deque<string> expression;
  expression.push_back(x);

  string operation;
  string value;
  for (int i = 0; i < n; ++i) {
    cin >> operation >> value;

    expression.push_front("(");
    expression.push_back(") " + operation + " " + value);
  }

  for (auto const &s : expression) {
    cout << s;
  }
  cout << endl;

  return 0;
}
