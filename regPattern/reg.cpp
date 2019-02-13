#include <vector>
#include <utility>
#include <iostream>
#include <string>

#define DEBUG 1

using namespace std;

struct State {
    enum Type {
        NORMAL,
        CHAR_STAR,
        ANY_STAR,
        END_STATE
    };
    
    int id;
    string p;
    int match_any_id;
    Type type = NORMAL;
    
    State(const string& p, int id, int match_any_id=-1) :
        id(id), p(p), match_any_id(match_any_id) {
            if (p.empty()) type = END_STATE;
            else if (p.size() == 1) type = NORMAL;
            else if (p[0] == '.') type = ANY_STAR;
            else type = CHAR_STAR;
        }
    
    pair<int, bool> operator()(char c) const {
        switch (type) {
            case NORMAL:
                return ((p[0] == c) || p[0] == '.') ? make_pair(id+1, true)
                    : make_pair(match_any_id, false);
            case CHAR_STAR:
                return (p[0] == c) ? make_pair(id, true)
                    : make_pair(match_any_id, false);
            case ANY_STAR:
                if ((p.size() == 3) && (p[2] == c)) {
                    return make_pair(id+1, false);
                } else {
                    return make_pair(id, true);
                }
            case END_STATE:
                return make_pair(match_any_id, false);
        }
    }
    
    int end() {
        switch (type) {
            case NORMAL:
                return -1;
            case END_STATE:
            case CHAR_STAR:
            case ANY_STAR:
                return id+1;
        }
    }
};

vector<string> getPatternTokens(const string& p) {
    vector<string> result;
    assert(!p.empty());
    size_t i{0};
    
    while (i < (p.length() - 1)) {
        if (p[i+1] == '*') {
            if (p[i] != '.') {
                auto n = p.substr(i, 2);
                if (result.empty() || (result.back() != n)) {
                    result.push_back(n);
                }
            } else {
                auto n = p.substr(i, (i + 2 < p.size()) && p[i+2] != '.' ? 3 : 2);
                if (result.empty() || (result.back()[0] != n[0])) {
                    result.push_back(n);
                } else {
		    result.pop_back();
		    result.push_back(n);
		}
            }
            i+=2;
        } else if (result.empty() || (result.back()[0] != p[i] && p[i] != '.')) {
            result.push_back(p.substr(i, 1));
            ++i;
        } else {
            auto last = result.back();
            result.push_back(p.substr(i, 1));
            if (last.size() == 2) {
                swap(last, result.back());
            }
            ++i;
        }
    }

    if (i < p.size()) {
        string newp = p.substr(i, 1);
	auto lastOne = result.back();
	result.push_back(newp);
	if (lastOne[0] == newp[0]) {
	    swap(result.back(), lastOne);
	}
    }

#if DEBUG
    copy(result.begin(), result.end(), ostream_iterator<string>(cout, "  "));
    cout << endl;
#endif 
    
    return result;
}

struct StateStore {
    vector<State> states;
    
    StateStore(const string& p) {
        auto plets = getPatternTokens(p);
        int match_any_id = -1;
        int id = 0;
        transform(plets.begin(), plets.end(), back_inserter(states),
                 [&](const string& pp){
                     State newState(pp, id, match_any_id);
                     if (newState.type == State::ANY_STAR) match_any_id = id;
                     ++id;
                     return newState;
                 });
        states.emplace_back("", id, match_any_id);

	#if DEBUG
	for_each(states.begin(), states.end(), [](const State& s) {
	    cout << "id: " << s.id << " pattern " << s.p << " type: " << s.type
	    << " fallback state: " << s.match_any_id << endl;
	    });
	#endif 
    }
    
    bool match(const string& s) {
        int state = 0;
            
        for (auto& c: s) {
            auto matched = states[state](c);
#if DEBUG
	    cout <<  "state: " << state << " matched " << matched.first << "  " << matched.second << " c " << c << endl;
#endif
            state = matched.first;
            while (! matched.second) {
                if (state == -1) return false;
                matched = states[state](c);
		#if DEBUG
	    cout <<  "state: " << state << " matched " << matched.first << "  " << matched.second << " c " << c << endl;
		#endif
                state = matched.first;
            }
        }

	cout << "Final state " << state << endl;
        
        while ((state != -1) && (state != states.size())) {
	    state = states[state].end();
	    //cout << state << endl;
	}
        
        return state == states.size();
    }
    
};


class Solution {
public:
    bool isMatch(string s, string p) {
        StateStore stateStore(p);
        
        return stateStore.match(s);
    }
};

struct TestCase {
    string s;
    string p;
    bool expected;
};

vector<TestCase> testCases {
/*
    { "aa", "aa", true},
    { "aaaa", "a*", true},
    { "aaaa", "a*a", true},
    { "aa", "a*a", true},
    { "aa", ".*", true},
    { "aa", "a.*", true},
    { "aa", "a**", false},
    */
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
