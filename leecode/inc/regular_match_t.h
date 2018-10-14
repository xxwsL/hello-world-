#ifndef _regular_match_t_h_
#define _regular_match_t_h_
#include <iostream>
#include <vector>

using namespace std;

       bool match(char a, char b) {     //判断字符相等
        return a == b || b == '.';
    }
 
    char getChar(string s, int n) {    //获取字符串的第n个字符
        if (s.length() > n) {
            return s[n];
        }
        return 0;    //超过索引就返回0
    }
    bool isMatch(string s, string p) {

        int slen = s.length();
        int plen = p.length();
 
        if (slen == 0 && plen == 0) return true;
 
        char c0 = getChar(s, 0);
        char p0 = getChar(p, 0);
        char p1 = getChar(p, 1);
        if (match(c0, p0) || p1 == '*') {
            if (p1 != '*') {
                if (slen == 0) return false;
                return isMatch(s.substr(1), p.substr(1));    //递归判断下一个字符
            }
            // if p1 is *, * means 0 ~ n
            int i = 0;
            bool ret = isMatch(s.substr(0), p.substr(2)); // try 0
            if (ret) return ret;
            while (i < slen && match(getChar(s, i), p0)) {
                ret = isMatch(s.substr(i+1), p.substr(2)); // try for every available position
                if (ret) return ret;
                i++;
            }
        }
 
        return false;
    }

    bool isMatch_temp0(string s, string p) {
        //get s and p size
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (j > 1 && p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                } else {
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[m][n];
    }
#endif