/*164. Maximum Gap
Hard

399

112

Favorite

Share
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

Example 1:

Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.
Example 2:

Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
Note:

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
Try to solve it in linear time/space.
*/

// use average gap to bucket
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2) return 0;

        auto min_max = minmax_element(nums.begin(), nums.end());
        auto gap = max<int>(1, (*min_max.second - *min_max.first)/(nums.size()-1));
        auto bucket_size = 1 + (*min_max.second - *min_max.first) / gap;
        vector<int> bucket_min(bucket_size, numeric_limits<int>::max());
        vector<int> bucket_max(bucket_size, numeric_limits<int>::min());

        for (auto& n: nums) {
            auto k = (n - *min_max.first) / gap;
            if (n > bucket_max[k]) bucket_max[k] = n;
            if (n < bucket_min[k]) bucket_min[k] = n;
        }

        int maxGap = 0;
        size_t idx = 0, next=1;
        while (next < bucket_size) {
            while (next <bucket_size && (bucket_min[next] == numeric_limits<int>::max()) &&
               (bucket_max[next] == numeric_limits<int>::min())) {
                ++next;
            }

            if (next == bucket_size) break;
            if (maxGap < (bucket_min[next] - bucket_max[idx]))
                maxGap = bucket_min[next] - bucket_max[idx];
            idx = next;
            ++next;
        }

        return maxGap;
    }
};
