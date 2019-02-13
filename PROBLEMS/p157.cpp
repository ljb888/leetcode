/*
157 LeetCode : Read N Characters Given Read4 – Easy

Problem:
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case.
*/

int readFile(char* buf, int n) {
    int nread = n / 4;
    int left = n % 4;

    for (int i=0; i<nread; ++i) {
        auto chars = read4(buf+i*4);
	if (chars < 4) return i * 4  + chars;
    }
    if (left) {
        char temp_buf[4];
	auto chars = read4(temp_buf);
	strncpy(buf+(nread * 4), temp_buf, min(left, chars));
	return min(left, chars) + 4 * nread;
    }

    return 4 * nread;
}
