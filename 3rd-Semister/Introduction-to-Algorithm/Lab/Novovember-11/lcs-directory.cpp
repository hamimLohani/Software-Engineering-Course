#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <dirent.h>

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

    int max_len = max(n, m);
    cout << "Percentage: " << (double)dp[0][0] / max_len * 100 << "%" << "\n\n";
}


int main() {

    DIR *dir = opendir(".");
    struct dirent *entry;
    string filename = "";
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            cout << "File: " << entry->d_name << endl;
            filename = (string) entry->d_name;
            ifstream file(filename);
            stringstream s;
            s << file.rdbuf();
            string content = s.str();
            file.close();
            lcs_dp("Wise busy past both park when an ye no", content);

        }
    }
    closedir(dir);

    return 0;
}