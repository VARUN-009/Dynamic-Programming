// MEMOISATION
class Solution
{
    // directly taking from constraints as max value is 200,200
    int dp[201][201];
    int helper(int row, int col, vector<vector<int>> &grid, int n, int m)
    {
        // base case
        if (row >= n || col >= m)
        {
            return 1e9;
        }

        if (row == n - 1 && col == m - 1)
        {
            return grid[row][col];
        }

        // DP
        if (dp[row][col] != -1)
        {
            return dp[row][col];
        }

        // recursive case
        int down = grid[row][col] + helper(row + 1, col, grid, n, m);
        int right = grid[row][col] + helper(row, col + 1, grid, n, m);

        return dp[row][col] = min(down, right);
    }

public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        memset(dp, 0, sizeof(dp));
        return helper(0, 0, grid, n, m);
    }
};
/*
TC - O(n*m) as cells are n*m
SC - o(n*m) for storing in dp array + recursion space O(m-1) + O(n-1)
In the worst-case scenario, the recursion stack will go as deep as the
longest path from the top-left corner to the bottom-right corner of the grid.
The longest path involves moving n−1 steps down and m−1 steps right.
*/



// TABULATION
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0 && j == 0)
                    dp[i][j] = grid[i][j];
                else
                {
                    int left = grid[i][j];

                    // requiring the previous col in the same row.
                    if (j > 0)
                        left += dp[i][j - 1];
                    else
                        left += 1e9;

                    int up = grid[i][j];

                    // requiring the previous row in the same col.
                    if (i > 0)
                        up += dp[i - 1][j];
                    else
                        up += 1e9;

                    dp[i][j] = min(left, up);
                }
            }
        }

        return dp[n - 1][m - 1];
    }
};
// TC - O(n*m) as cells are n*m so visiting total.
// SC - O(n*m) dp vector (No recursion space here).



// SPACE OPTIMISATION
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        // basically I can save current row and previous row in vectors - curr
        // and prev and take directly from there - same row ka pehle col will be
        // like curr[j-1] and previous row ka same col will be like prev[i-1]

        vector<int> prev(n, 0);

        for (int i = 0; i < n; i++)
        {
            vector<int> curr(m, 0);

            for (int j = 0; j < m; j++)
            {
                if (i == 0 && j == 0)
                    // same row ka jth col means curr[j]
                    curr[j] = grid[i][j];
                else
                {
                    int left = grid[i][j];

                    // requiring the j-1 col in the same row - basically current
                    // row's j-1 dedo.
                    if (j > 0)
                        left += curr[j - 1];
                    else
                        left += 1e9;

                    int up = grid[i][j];

                    // requiring the j col in the previous row basically
                    // previous row's j dedo.
                    // previous row but current col basically jisme previous row
                    // ka kaam ho rha hai basically col same hai par pehle wali
                    // row i-1 wali toh iske liye ek vector leliya
                    if (i > 0)
                        up += prev[j];
                    else
                        up += 1e9;

                    // current row ka jth col so curr[j];
                    curr[j] = min(left, up);
                }
            }

            prev = curr;
        }

        // ek km wali row ka as i mera n m jakr rukega par mujhe uss se upr wali chahiye row toh n-1.
        return prev[m - 1];
    }
};
/*
DP on Grids points
1. Express the recurrence in terms of (i,j)
2. Explore all paths
3. Take the minimum/maximum path.

*/