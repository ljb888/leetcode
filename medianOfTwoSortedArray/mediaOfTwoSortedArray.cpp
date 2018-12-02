#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < nums2.size()) {
            return findMedian(nums1, nums2);
        } else {
            return findMedian(nums2, nums1);
        }
    }
    
    double findMedian(const vector<int>& n1, const vector<int>& n2) {
        assert(n1.size() <= n2.size());
        size_t l{0}, r{n1.size()-1};
        size_t mid = (n1.size() + n2.size() -1) / 2;
        size_t mid2 = (n1.size() + n2.size()) / 2;
        
        if (n1.empty()) {
            return (n2[mid] + n2[mid2]) / 2.0;
        }
        
        while (l < r) {
            auto m = (l + r) / 2;
            if (n1[m] <= n2[mid-m]) {
                l = m + 1;
            } else {
                r = (m > 0) ? (m - 1) : 0;
            }
        }
        
        cout << l << "  " << r << "  " << mid << endl;
        int result;
        if (n1[l] < n2[mid-l]) {
            result = (mid > l) ? max(n1[l], n2[mid-l-1]) : n1[l];
            result += (mid == mid2) ? result : min(n2[mid-l], (l+1 < n1.size()) ? n1[l+1] : n2[mid-l]);
        } else {
            result = (l > 0) ? max(n1[l-1], n2[mid-l]) : n2[mid-l];
            result += (mid == mid2) ? result : min(n1[l], (1+mid-l < n2.size()) ? n2[mid-l+1] : n1[l]);
        }
        
        return result/2.0;
    }
};
