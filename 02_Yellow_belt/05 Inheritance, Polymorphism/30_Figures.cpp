#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Figure {
 public:
  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;

  virtual ~Figure() = default;
};

class Triangle : public Figure {

 private:
  const string NAME = "TRIANGLE";
  double a;
  double b;
  double c;

 public:
  Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

  virtual string Name() const {
    return NAME;
  }

  virtual double Perimeter() const {
    return a + b + c;
  }

  virtual double Area() const {
    double s = Perimeter() / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
  }

};

class Rect : public Figure {
 private:
  const string NAME = "RECT";
  double a;
  double b;

 public:
  Rect(double a, double b) : a(a), b(b) {}

  virtual string Name() const {
    return NAME;
  }

  virtual double Perimeter() const {
    return (a + b) * 2;
  }

  virtual double Area() const {
    return a * b;
  }

};

class Circle : public Figure {
 private:
  const float PI = 3.14;
  const string NAME = "CIRCLE";
  double r;

 public:
  Circle(double r) : r(r) {}

  virtual string Name() const {
    return NAME;
  }

  virtual double Perimeter() const {
    return 2 * PI * r;
  }

  virtual double Area() const {
    return PI * (r * r);
  }

};

shared_ptr<Figure> CreateFigure(istringstream &is) {
  string name;
  is >> name;

  if (name == "TRIANGLE") {
    double a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  }

  if (name == "RECT") {
      double a, b;
      is >> a >> b;
      return make_shared<Rect>(a, b);
  }

  if (name == "CIRCLE") {
    double r;
    is >> r;
    return make_shared<Circle>(r);
  }

  return {};
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line);) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto &current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }

  return 0;
}
