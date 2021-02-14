#include <iostream>
#include <map>
#include <stdexcept>
using namespace std;

template <typename Key, typename Value>
Value &GetRefStrict(map<Key, Value> &m, Key const &key) {
    if (m.find(key) == m.end()) {
        throw runtime_error("error");
    }
    Value &r = m[key];
    return r;
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}
