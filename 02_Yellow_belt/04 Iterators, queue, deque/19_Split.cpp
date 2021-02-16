#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> v;
    if (s.empty()) {
        return v;
    }

    auto it = s.begin();
    auto next = find(it, s.end(), ' ');
    v.emplace_back(it, next);
    if (next == s.end()) {
        return v;
    }
    do {
        next++;
        it = next;
        next = find(it, s.end(), ' ');
        v.emplace_back(it, next);
    }
    while (next != s.end());
    return v;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
