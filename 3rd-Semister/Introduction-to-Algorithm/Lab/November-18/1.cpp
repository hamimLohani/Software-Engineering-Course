#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

void printPathRecursive(int i, int j, const vector<vector<int>> &A, const vector<vector<int>> &C)
{
    if (i == 0)
        return;

    int current_cost_without_curr = A[i][j] - C[i - 1][j - 1];

    if (j - 1 >= 1 && A[i - 1][j - 1] == current_cost_without_curr)
    {
        printPathRecursive(i - 1, j - 1, A, C);
    }
    else if (A[i - 1][j] == current_cost_without_curr)
    {
        printPathRecursive(i - 1, j, A, C);
    }
    else if (j + 1 <= (int)A[0].size() - 1 && A[i - 1][j + 1] == current_cost_without_curr)
    {
        printPathRecursive(i - 1, j + 1, A, C);
    }

    cout << "(" << i << ", " << j << ") ";
}

int rockClimbing(const vector<vector<int>> &C)
{
    if (C.empty() || C[0].empty())
        return 0;

    int n = C.size();
    int m = C[0].size();

    vector<vector<int>> A(n + 1, vector<int>(m + 2, INF));

    for (int j = 1; j <= m; j++)
        A[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int curr = C[i - 1][j - 1];
            int mn = min({A[i - 1][j - 1], A[i - 1][j], A[i - 1][j + 1]});
            if (mn != INF)
                A[i][j] = curr + mn;
        }
    }

    int min_cost = INF, best_j = -1;
    for (int j = 1; j <= m; j++)
    {
        if (A[n][j] < min_cost)
        {
            min_cost = A[n][j];
            best_j = j;
        }
    }

    if (min_cost == INF)
    {
        cout << "No valid path found\n";
        return INF;
    }

    cout << "Minimum danger rating: " << min_cost << endl;
    cout << "Path (Top to Bottom): ";

    printPathRecursive(n, best_j, A, C);

    cout << endl;
    return min_cost;
}

int main()
{
    vector<vector<int>> C = {
        {3, 2, 5, 4, 8},
        {5, 7, 5, 6, 1},
        {4, 4, 6, 2, 3},
        {2, 8, 9, 5, 8}};

    rockClimbing(C);
    return 0;
}