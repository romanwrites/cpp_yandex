#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr auto STUDENT = "Student";
constexpr auto TEACHER = "Teacher";
constexpr auto POLICEMAN = "Policeman";

// Use coplien form
class Person {
 protected:
  string name;
  string status;

 public:
  Person(string const &name, string const &status = "Developer") : name(name), status(status) {}

  virtual void Walk(string const &destination) const {
    cout << status << ": " << name << " walks to: " << destination << endl;
  }

  virtual ~Person() = default;

  Person &operator=(Person const &p) {
    if (this == &p) {
      return *this;
    }
    this->status = p.status;
    this->name = p.name;
    return *this;
  }

  // Getters
  const string &getName() const {
    return name;
  }
  const string &getStatus() const {
    return status;
  }

 private:
  Person() {}
  Person(Person const &p) {
    this->operator=(p);
  }

};

class Student : public Person {
 private:
  string favourite_song;

 public:
  Student(string const &name, string const &favouriteSong) : Person(name, STUDENT), favourite_song(favouriteSong) {}

  void Learn() const {
    cout << status << ": " << name << " learns" << endl;
  }

  void Walk(const string &destination) const override {
    Person::Walk(destination);
    SingSong();
  }

  void SingSong() const {
    cout << status << ": " << name << " sings a song: " << favourite_song << endl;
  }

};

class Teacher : public Person {
 private:
  string subject;

 public:
  Teacher(string const &name, string const &subject) : Person(name, TEACHER), subject(subject) {}

  void Teach() const {
    cout << status << ": " << name << " teaches: " << subject << endl;
  }

};

class Policeman : public Person {
 public:
  Policeman(string const &name) : Person(name, POLICEMAN) {}

 public:
  void Check(Person const &p) const {
    cout << status << ": " << name << " checks " << p.getStatus() << ". " << p.getStatus() << "'s name is: "
         << p.getName() << endl;
  }
};

void VisitPlaces(Person const &t, vector<string> const &places) {
  for (auto const &p : places) {
    t.Walk(p);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
  return 0;
}

/* LEGACY CODE
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Student {
public:

    Student(string name, string favouriteSong) {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};


class Teacher {
public:

    Teacher(string name, string subject) {
        Name = name;
        Subject = subject;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination) {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};


class Policeman {
public:
    Policeman(string name) {
        Name = name;
    }

    void Check(Teacher t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination) {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};


void VisitPlaces(Teacher t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
*/
