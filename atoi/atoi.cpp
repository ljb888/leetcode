#include <iostream>
#include <string>

using namespace std;

static const string bound = to_string(0x7fffffff);

class Solution {
public:
    int myAtoi(string str) {
        auto start = str.find_first_not_of(" ");
	if (start == string::npos) return 0;

	int sign = (str.at(start) == '-') ? -1 : 1;

	if (str.at(start)  == '+' || str.at(start) == '-') ++start;
	if (! isdigit(str.at(start))) return 0;

	auto end = str.find_first_not_of("0123456789", start);
	auto digits = (end == string::npos) ? str.substr(start) : str.substr(start, end);

	if (bound.length() < digits.length() ||
	   (bound.length() == digits.length() && bound < digits)) {
	    return INT_MIN;
	}

	return sign * stoi(digits);
    }
};
