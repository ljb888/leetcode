/*
 * Missing Ranges Total Accepted: 510 Total Submissions: 2300
Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].


---------------------
作者：xudli
来源：CSDN
原文：https://blog.csdn.net/xudli/article/details/42290511
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> missingRanges(const vector<int>& nums, int lower, int upper) {
    vector<string> result;

    for (const auto& n: nums) {
        if (n > lower) {
	    stringstream ss;
	    ss << lower;
	    if (n-1 != lower) ss << "->" << min(n-1, upper);
	    result.push_back(ss.str());
	    lower = n + 1;
	}

	if (n >= upper) break;
    }

    return result;
}
