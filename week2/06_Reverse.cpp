//#include <iostream>
//#include <vector>
//using namespace std;
//
void Reverse(vector<int>& v) {
	int	tmp;
	for (int i = 0; i < v.size() / 2; i++) {
		tmp = v[i];
		v[i] = v[v.size() - i - 1];
		v[v.size() - i - 1] = tmp;
	}
}
//
//int main() {
//	vector<int> k = {0, 1, 2};
//	Reverse(k);
//	for (auto i : k) {
//		cout << i << " ";
//	}
//}