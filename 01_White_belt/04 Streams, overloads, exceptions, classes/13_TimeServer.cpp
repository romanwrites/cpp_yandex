#include <iostream>
#include <exception>
#include <string>
#include <exception>
using namespace std;

string AskTimeServer() {
//    return "01:03:33";
//    throw system_error(EDOM, std::generic_category(), "hello world");
	throw invalid_argument("exception");
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
			last_fetched_time = AskTimeServer();
			return last_fetched_time;
        } catch (system_error const &) {
			return last_fetched_time;
		}
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
