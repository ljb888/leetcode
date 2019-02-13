/*
 * Given two strings S and T, determine if they are both one edit distance apart. Hint:

If | n – m | is greater than 1, we know immediately both are not one-edit distance apart.
It might help if you consider these cases separately, m == n and m ≠ n.
Assume that m is always ≤ n, which greatly simplifies the conditional statements.
If m > n, we could just simply swap S and T.
If m == n, it becomes finding if there is exactly one modified operation.
If m ≠ n, you do not have to consider the delete operation.
Just consider the insert operation in T.
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

bool isOneEditApart(const string& s1, const string& s2) {
    if (abs((long)(s1.size()-s2.size())) > 1) return false;

    auto mis1 = mismatch(s1.begin(), s1.end(), s2.begin());
    if (mis1.first == s1.end() || (mis1.second == s2.end())) {
        return s1.size() != s2.size();
    }

    if (s1.size() == s2.size()) {
	auto mis2 = mismatch(mis1.first+1, s1.end(), mis1.second+1);
	return mis2.first == s1.end();
    }

    auto mis2 = mismatch((s1.size() > s2.size()) ? mis1.first+1 : mis1.first,
        s1.end(),
	(s1.size() > s2.size()) ? mis1.second : mis1.second + 1);
    return mis2.first == s1.end();
}

vector<string> one = { "a", "ab", "abc"};
vector<string> two = {"", "ab", "b", "ba", "bc"};

int main() {

    for (const auto& s1: one) {
        for (const auto& s2: two) {
	    cout << s1 << " AND " << s2 << " are one edit apart: " << isOneEditApart(s1, s2) << endl;
	}
    }

    return 0;
}
