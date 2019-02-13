#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

class Solution {
    #define MIN_INT numeric_limits<int>::min()
    #define MAX_INT numeric_limits<int>::max()
public:
    int divide(int dividend, int divisor) {
        assert(divisor);
        
        if (divisor == MIN_INT) return (dividend == MIN_INT) ? 1 : 0;
        if (divisor == -1) return (dividend == MIN_INT) ? MAX_INT : 0 - dividend;
        if (divisor == 1) return dividend;
        
        int sign = (divisor < 0 && (dividend > 0)) || ((divisor > 0) && (dividend < 0)) ? -1 : 1;
        int ndivisor = (divisor < 0) ? (0 - divisor) : divisor;
        int ndividend = (dividend < 0) ? ((dividend == INT_MIN) ? (0 - (dividend + ndivisor)) : (0 - dividend)) : dividend;
        
        int result = dividUsingBinarySearch(ndividend, ndivisor);
        
        if (dividend == INT_MIN) ++result;
        
        return (sign < 0) ? (0 - result) : result;
    }
    
    int dividUsingBinarySearch(unsigned int dividend, unsigned int divisor) {
        vector<pair<unsigned int, int>> divisors{make_pair(divisor, 1)};
        int result = 0;
          
        while (divisors.back().first <= dividend && (divisors.back().first < (1 << 30))) {
            auto& ndivisor = divisors.back();
            result += ndivisor.second;
            dividend -= ndivisor.first;
            divisors.push_back(make_pair(ndivisor.first+ndivisor.first, ndivisor.second + ndivisor.second));
            //cout << ndivisor.first << "  " << ndivisor.second << "  " << dividend <<"   " << result << endl;
        }        

        while (divisors.back().first <= dividend) {
            auto& ndivisor = divisors.back();
            result += ndivisor.second;
            dividend -= ndivisor.first;
            
            //cout << ndivisor.first << "  " << ndivisor.second << "  " << dividend <<"  " << result<< endl;
        }
        
        while(true) {
            auto fI = upper_bound(divisors.begin(), divisors.end(), dividend,
                                  [](const unsigned int& d, const auto& v){
                    return v.first > d;});
            
            //cout << fI->first << "  " << fI->second << "   " << dividend << endl;
            
            if (fI == divisors.begin()) break;
            --fI;
            dividend -= fI->first;
            result += fI->second;
            
        }
        
        return result;
    }
};
