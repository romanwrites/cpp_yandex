#include <iostream>

using namespace std;

class Animal {
 public:
  Animal(string const &name) : Name(name) {}

  const string Name;
};

class Dog : public Animal {
 public:
  Dog(string const &name) : Animal(name) {}

  void Bark() {
    cout << Name << " barks: woof!" << endl;
  }
};
