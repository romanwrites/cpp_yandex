#include <iostream>
#include <map>
#include <vector>

using namespace std;

template<typename T> T Sqr(T x);
template <typename T> vector<T> operator *(vector<T> const &lhs, vector<T> const &rhs);
template <typename First, typename Second> pair<First, Second> operator *(pair<First, Second> const &p1, pair<First, Second> const &p2);
template <typename Key, typename Value> map<Key, Value> operator *(map<Key, Value> const &lhs, map<Key, Value> const &rhs);

template <typename T>
vector<T> operator *(vector<T> const &lhs, vector<T> const &rhs) {
    vector<T> res(lhs.size());

    for (int i = 0; i < lhs.size(); i++) {
        res[i] = lhs[i] * rhs[i];
    }
    return res;
}

template <typename First, typename Second>
pair<First, Second> operator *(pair<First, Second> const &p1, pair<First, Second> const &p2) {
    First f = p1.first * p2.first;
    Second s = p1.second * p2.second;
    return make_pair(f, s);
}

template <typename Key, typename Value>
map<Key, Value> operator *(map<Key, Value> const &lhs, map<Key, Value> const &rhs) {
    map<Key, Value> res;
    for (auto const &i : lhs) {
        res[i.first] = i.second * i.second;
    }
    return res;
}

template <typename T>
T Sqr(T x) {
    return x * x;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}
