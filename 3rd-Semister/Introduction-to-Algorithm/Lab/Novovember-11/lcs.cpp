// Bottom-up DP: Longest Common Subsequence (LCS)
// Time: O(n*m), Space: O(n*m)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int lcs_dp(const string &a, const string &b) {
    int n = a.size();
    int m = b.size();
    int dp[n + 1][m + 1];
    
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
    
    return dp[0][0];
}

int main() {
    string s1 = "hello";
    string s2 = "ll";
    cout << lcs_dp(s1, s2) << endl;
    return 0;
}


