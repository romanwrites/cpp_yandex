//#include <iostream>
//#include <vector>
//using namespace std;

void		Reverse(vector<int>& v) {
	int		tmp;

	for (int i = 0; i < v.size() / 2; i++) {
		tmp = v[i];
		v[i] = v[v.size() - i - 1];
		v[v.size() - i - 1] = tmp;
	}
}

vector<int>	Reversed(const vector<int>& v) {
	vector<int> copy = v;

	Reverse(copy);
	return copy;
}

//int main() {
//	vector<int> k = {0, 1, 2};
//	vector<int> get = Reversed(k);
//
//	cout << "Original vector: ";
//	for (auto i : k) {
//		cout << i << " ";
//	}
//
//	cout << endl << "Reversed vector: ";
//	for (auto i : get) {
//		cout << i << " ";
//	}
//	cout << endl;
//}
