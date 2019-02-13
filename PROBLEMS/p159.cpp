/*
 * Longest Substring with At Most Two Distinct Characters
Question

Given a string S, find the length of the longest substring T that contains at most two distinct characters.

For example, Given S = “eceba”, T is "ece" which its length is 3.
*/
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

int maxSubstrWithTwoChars(const string& s)
{
    unordered_set<char> wset;
    size_t start = 0;
    size_t next_start = 0;
    int maxSubstrLen = 0;

    for (size_t i=0; i<s.size(); ++i) {
        if (! wset.count(s[i])) {
            wset.insert(s[i]);
	    switch (wset.size()) {
	    case 1:
	        break;
            case 2:
	        next_start = i;
		break;
            case 3:
	        maxSubstrLen = max(maxSubstrLen, (int)(i-start));
	        wset.clear();
	        wset.insert(s[i]);
	        wset.insert(s[i-1]);
	        start = next_start;
	        next_start = i;
		continue;
	    }
        }
        if (i > 0 && s[i] != s[i-1]) {
            next_start = i;
        }
    }

    return maxSubstrLen;
}

int main() {
    cout << "abcbbbbcccbdddadacb  HAS "  << maxSubstrWithTwoChars("abcbbbbcccbdddadacb")
        << endl;

    return 0;
}
