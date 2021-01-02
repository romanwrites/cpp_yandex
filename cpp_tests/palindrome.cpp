#include <iostream>
using namespace std;

class Solution {
public:
	bool isPalindrome(string s) {
		string str;

		for (int i = 0; i < s.length(); i++) {
			if (isalpha(s[i]) || isdigit(s[i])) {
				str.push_back(tolower(s[i]));
			}
		}
		uint32_t half = str.length() / 2;
		for (uint32_t i = 0, j = str.length() - 1; i < half; i++, j--) {
			if (str[i] != str[j]) {
				return false;
			}
		}
		return true;
	}
};

int main() {
	Solution s;
	cout << s.isPalindrome("A man, a plan, a canal: Panama") << endl;
}