int 	Factorial(int n) {
	if (n < 2) {
		return 1;
	}
	int res = n--;
	for (; n > 1; n--) {
		res *= n;
	}
	return res;
}
