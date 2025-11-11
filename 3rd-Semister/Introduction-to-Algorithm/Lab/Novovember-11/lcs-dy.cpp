#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void lcs_dp(const string &a, const string &b) {
    int n = a.size();
    int m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
    
    //  dp[0][0] is the length()

    string lcs = "";
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            lcs += a[i];
            i++;
            j++;
        } else if (dp[i + 1][j] > dp[i][j + 1]) i++;
        else j++;
    }
    cout << "Length: " << dp[0][0] << endl;
    cout <<  "LCS: " << lcs << endl;
}


int main() {
    ifstream file1("input1.txt");
    ifstream file2("input2.txt");
    
    stringstream s1, s2;
    s1 << file1.rdbuf();
    s2 << file2.rdbuf();
    
    string contents1 = s1.str();
    string contents2 = s2.str();
    
    file1.close();
    file2.close();

    lcs_dp(contents1, contents2);
    
    return 0;
}