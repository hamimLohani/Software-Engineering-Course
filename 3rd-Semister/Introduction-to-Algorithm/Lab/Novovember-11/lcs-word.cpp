#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int lcs(const vector<string>& w1, const vector<string>& w2) {
    int n = w1.size();
    int m = w2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (w1[i - 1] == w2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

vector<string> splitWords(const string& text) {
    stringstream ss(text);
    vector<string> words;
    string word;
    while (ss >> word)
        words.push_back(word);
    return words;
}

int main() {
    ifstream fin1("input1.txt");
    ifstream fin2("input2.txt");

    if (!fin1.is_open() || !fin2.is_open()) {
        cout << "Error opening files." << endl;
        return 1;
    }

    string s1((istreambuf_iterator<char>(fin1)), istreambuf_iterator<char>());
    string s2((istreambuf_iterator<char>(fin2)), istreambuf_iterator<char>());

    fin1.close();
    fin2.close();

    vector<string> w1 = splitWords(s1);
    vector<string> w2 = splitWords(s2);

    int result = lcs(w1, w2);
    cout << "Number of common words in LCS: " << result << endl;

    return 0;
}