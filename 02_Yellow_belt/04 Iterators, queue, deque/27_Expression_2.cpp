#include <iostream>
#include <deque>
using namespace std;

bool greaterPriority(string const &o) {
  return o == "*" || o == "/" || o.empty();
}

int main() {
  string x;
  int n;

  cin >> x >> n;

  deque<string> expression;
  expression.push_back(x);

  string operation;
  string value;
  string prevOperation;

  for (int i = 0; i < n; ++i) {
    cin >> operation >> value;

    if (!greaterPriority(prevOperation) && (greaterPriority(operation))) {
      expression.push_front("(");
      expression.push_back(")");
    }
    expression.push_back(" " + operation + " " + value);
    prevOperation = operation;
  }

  for (auto const &s : expression) {
    cout << s;
  }
  cout << endl;

  return 0;
}
