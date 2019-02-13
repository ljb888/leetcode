#include "atoi.cpp"
#include <iostream>
#include <vector>

using namespace std;

struct TestCase {
    string input;
    int result;
};

vector<TestCase> tests = {
    { "42", 42},
    {"    42", 42 },
    {"   42 good", 42},
    {"   wild 49", 0},
    {"12345678901", INT_MIN},
    {"-91283472332", -2147483648}
};

int main(int argc, char* argv[]) {

    Solution slt;

    for (auto& t: tests) {
        cout << " Input "  << t.input
	    << " Expected: " << t.result
	    << " Actual: " << slt.myAtoi(t.input)
	    << endl;
    }

    return 0;
}
