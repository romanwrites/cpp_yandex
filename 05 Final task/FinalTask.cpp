#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class Date {
public:
	Date(int year, int month, int day) {
		if (month < 1 || month > 12) {
			throw Date::BadArgumentException("Month value is invalid: " + to_string(month));
		}

		this->year = year;
		this->month = month;
		this->day = day;
	}

	class BadArgumentException : exception {
	public:
		BadArgumentException(string msg) {message = msg;}
		BadArgumentException() {message = "";}

		virtual const char* what() const throw()
		{
			return message.c_str();
		}

	private:
		string message;
	};

	int GetYear() const {return year;}
	int GetMonth() const {return month;}
	int GetDay() const {return day;}

private:
	int year;
	int month;
	int day;

	Date() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}
};

//bool operator<(const Date& lhs, const Date& rhs);
//
//class Database {
//public:
//	void AddEvent(const Date& date, const string& event);
//	bool DeleteEvent(const Date& date, const string& event);
//	int  DeleteDate(const Date& date);
//
//	/* ??? */ Find(const Date& date) const;
//
//	void Print() const;
//
//private:
//	map<Date, string> m;
//
//};

int main() {
	try {
		Date d = {21, 0, 3};
	} catch (exception &ex) {
		cout << ex.what() <<endl;
	}

}

//int main() {
//  Database db;
//
//  string command;
//  while (getline(cin, command)) {
//	istringstream input(command);
//	if (input) {
//		string cmd;
//		input >> cmd;
//		if (cmd == "Add") {
//			try {
//				string date, event;
//				input >> date >> event;
//			} catch (exception &ex) {
//				cout << ex.what() << endl;
//			}
//		}
//	}
//  }
//
//  return 0;
//}