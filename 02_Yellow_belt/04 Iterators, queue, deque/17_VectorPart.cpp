#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto it = numbers.begin();
    while (it != numbers.end() && *it >= 0) {
        it++;
        if (*it < 0) {
            while (it != numbers.begin()) {
                it--;
                cout << *it << " ";
            }
            return ;
        }
    }
    while (it != numbers.begin()) {
        it--;
        cout << *it << " ";
    }
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}
