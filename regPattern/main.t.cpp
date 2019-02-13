#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include "regDP.cpp"

#define DEBUG 1

using namespace std;

struct TestCase {
    string s;
    string p;
    bool expected;
};

vector<TestCase> testCases {
    { "aa", "aa", true},
    { "aaaa", "a*", true},
    { "aaaa", "a*a", true},
    { "aa", "a*a", true},
    { "aa", ".*", true},
    { "aa", "a.*", true},
    { "aa", "a**", false},
    { "aaaaabbbb", "a.*.*b*..", true},
};

int main (int argc, char* argv[]) {
    Solution slt;

    for (auto& tc: testCases) {
        auto isMatch = slt.isMatch(tc.s, tc.p);
	if (isMatch != tc.expected) {
	    cout << "ERROR: " << tc.s << "  " << tc.p <<  " expected: " << tc.expected
	       << " got: " << isMatch << endl;
	} else {
	    cout << "Matched: " << tc.s << "  " << tc.p <<  " expected: " << tc.expected
	       << " got: " << isMatch << endl;
	}
    }

    return 0;
}
