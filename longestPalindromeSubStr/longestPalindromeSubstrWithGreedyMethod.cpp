#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class GreedyLongestPalindrome {
public:
    string longestPalindrome(string s) {
        unordered_map<char, vector<size_t>> char_pos;
        for (size_t i{0}; i < s.length(); ++i) {
            char_pos[s[i]].emplace_back(i);
        }
        
        string result = s.substr(0, 1);
        for (size_t i{0}; i < s.size(); ++i) {
            if (i + result.size() >= s.size()) break;
            auto& lastPos = char_pos.at(s[i]);
            for (auto bIt = lastPos.rbegin(); bIt != lastPos.rend(); ++bIt) {
                if (i + result.size() > *bIt) break;
                if (isPalindrome(s, i, *bIt)) {
                    result = s.substr(i, *bIt + 1 - i);
                    break;
                }
            }
        }
        
        return result;
    }
    
    bool isPalindrome(const string& s, size_t i, size_t lastPos) {
        for (; i<lastPos; ++i,--lastPos) {
            if (s[i] != s[lastPos]) {
                return false;
            }
        }
        
        return true;
    }
};
