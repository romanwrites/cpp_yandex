bool	IsPalindrom(std::string const &str) {
	uint32_t half = str.length() / 2;
	for (uint32_t i = 0, j = str.length() - 1; i < half; i++, j--) {
		if (str[i] != str[j]) {
			return false;
		}
	}

	return true;
}

vector<string>	PalindromFilter(vector<string> words, int minLength) {
	vector<string>	res;
	for (auto str : words) {
		if (str.length() >= minLength && IsPalindrom(str)) {
			res.push_back(str);
		}
	}
	return res;
}
