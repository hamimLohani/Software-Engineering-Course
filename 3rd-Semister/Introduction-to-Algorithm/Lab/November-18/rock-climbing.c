#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ROW 4
#define COL 5
#define MAX_REACH_R 1
#define MAX_REACH_C 1

int is_valid(int r, int c) {
    return (r >= 0) && (r < ROW) && (c >= 0) && (c < COL);
}

void dp_min_climbing_cost(int grid[ROW][COL]) {
    int dp[ROW][COL];
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < ROW; i++) {
        dp[i][0] = grid[i][0];
    }

    for (int j = 1; j < COL; j++) {
        for (int i = 0; i < ROW; i++) {
            
            for (int i_prev = 0; i_prev < ROW; i_prev++) {
                
                if (abs(i - i_prev) <= MAX_REACH_R) {
                    
                    if (dp[i_prev][j - 1] != INT_MAX) { // Check if the preceding hold is reachable
                        int cost_via_prev = dp[i_prev][j - 1] + grid[i][j];
                        
                        if (cost_via_prev < dp[i][j]) {
                            dp[i][j] = cost_via_prev;
                        }
                    }
                }
            }
        }
    }

    int min_total_cost = INT_MAX;
    int end_col = COL - 1;
    for (int i = 0; i < ROW; i++) {
        if (dp[i][end_col] < min_total_cost) {
            min_total_cost = dp[i][end_col];
        }
    }

    printf("\n\n DP Table (Min Cost to Reach Hold):\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (dp[i][j] == INT_MAX) {
                 printf(" INF ");
            } else {
                 printf("%4d ", dp[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n🎉 Minimum Total Climbing Difficulty (Cost) to the End: **%d**\n", min_total_cost);
}

int main() {
    int climbing_wall[ROW][COL] = {
        { 1,             4,      2,      7,      1  },
        { 3,             1,      5,      2,      6  }, 
        { 2,             6,      1,      4,      1  },
        { 5,             3,      8,      1,      5  } 
    };

    printf("Climbing Wall Grid (Hold Difficulty/Cost):\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%2d ", climbing_wall[i][j]);
        }
        printf("\n");
    }

    printf("\nDP Search Parameters: Max vertical reach change is %d row(s).", MAX_REACH_R);
    dp_min_climbing_cost(climbing_wall);

    return 0;
}