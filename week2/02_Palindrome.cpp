bool	IsPalindrom(std::string const &str) {
	uint32_t half = str.length() / 2;
	for (uint32_t i = 0, j = str.length() - 1; i < half; i++, j--) {
		if (str[i] != str[j]) {
			return false;
		}
	}
	
	return true;
}
