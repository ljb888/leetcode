#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        results.clear();
	return isMatch(s, 0, p, 0);
    }

    bool isMatch(const string& s, size_t ss, const string& p, size_t ps) {
	// ps >= p.size
	if (ps >= p.size()) return ss >= s.size();

        if (results.count(ss) && results.at(ss).count(ps)) {
	    return results[ss][ps];
	}

	// ps + 1 == p.size(), the last one
	if (ps + 1 == p.size()) {
	    if (ss + 1 != s.size()) {
	        results[ss][ps] = false;
		return false;
	    } else {
	        auto result = isMatch(s[ss], p[ps]);
	    	results[ss][ps] = result;
		return result;
	    }
	}

	// at least two elements for p
	if (p[ps+1] != '*') {
	    if (ss + 1 >= s.size() || (! isMatch(s[ss], p[ps]))) {
	        results[ss][ps] = false;
		return false;
	    }
	    auto result = isMatch(s, ss+1, p, ps+1);
	    results[ss][ps] = result;
	    return result;
	} else {
	    auto r1 = isMatch(s, ss, p, ps+2);
	    if (r1) {
	        results[ss][ps] = true;
		return true;
	    }
	    auto r2 = (ss < s.size()) && isMatch(s[ss], p[ps]) && isMatch(s, ss+1, p, ps);
	    results[ss][ps] = r2;
	    return r2;
	}
    }

    bool isMatch(char c, char p) {
        return (c == p) || (p == '.');
    }

    unordered_map<size_t, unordered_map<size_t, bool>> results;
};
