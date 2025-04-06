class Solution
{
public:
    int dp[201][201];
    int helper(vector<vector<int>> &grid, int i, int j, int row)
    {
        // base case
        if (i < 0 || i >= row || j < 0 || j >= row)
        {
            return INT_MAX;
        }

        if (i == row - 1)
            return grid[i][j];

        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        int ans = INT_MAX;
        for (int k = 0; k < row; k++)
        {
            if (k == j)
                continue;
            int sum = grid[i][j] + helper(grid, i + 1, k, row);
            ans = min(sum, ans);
        }
        return dp[i][j] = ans;
    }
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        memset(dp, -1, sizeof(dp));
        int n = grid.size();
        int ans = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            ans = min(ans, helper(grid, 0, i, n));
        }
        return ans;
    }
};
/*
ab isme 3 call ni marni isme poora loop hi chlana padega kyuki mujhe bss same column wala element ni lena baaki sab lene hai toh multiple possibilities thats why loop

mujhe bss pehli row ke saare elements m iterate karna h toh bss pehli row ke elements m iterate kar neeche se and then har ek element ke liye function call karde and jo sabse min ho calculate karte reh and then usko return karde.
agr tu helper function m loop lagata toh dikkat ho jati na, tujhe neeche wali row ke sirf 3 elements lene hai par loop h tph vo saare lega
*/

// TABULATION
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // upr m 0 se n-1 jaa rha tha and yahan m n-1 se 0. ab usme base case tha ki agr 0th row m hai toh vahi value hai toh isme kardo ki last row m hai toh vahi value hai
        for (int i = 0; i < m; i++)
        {
            dp[n - 1][i] = grid[n - 1][i];
        }

        // last row base case ka kaam toh ho gya toh ab uss se ek km se start karo.
        for (int row = n - 2; row >= 0; row--)
        {
            for (int col = m - 1; col >= 0; col--)
            {
                int ans = INT_MAX;
                for (int k = 0; k < m; k++)
                {
                    if (k == col)
                        continue;
                    int sum = grid[row][col] + dp[row + 1][k];
                    ans = min(sum, ans);
                }
                dp[row][col] = ans;
            }
        }

        // at the end 0th row m jo sabse chotta hoga vahi answer hoga.
        return *min_element(dp[0].begin(), dp[0].end());
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        // previous row ka kaam iss row se hoga
        vector<int> prev(m, 0);

        // upr m 0 se n-1 jaa rha tha and yahan m n-1 se 0. ab usme base case tha ki agr 0th row m hai toh vahi value hai toh isme kardo ki last row m hai toh vahi value hai
        for (int i = 0; i < m; i++)
        {
            prev[i] = grid[n - 1][i];
        }

        // last row base case ka kaam toh ho gya toh ab uss se ek km se start karo.
        for (int row = n - 2; row >= 0; row--)
        {
            // current row ke liye
            vector<int> curr(m, 0);
            for (int col = m - 1; col >= 0; col--)
            {
                int ans = INT_MAX;
                for (int k = 0; k < m; k++)
                {
                    if (k == col)
                        continue;
                    int sum = grid[row][col] + prev[k];
                    ans = min(sum, ans);
                }
                curr[col] = ans;
            }

            prev = curr;
        }

        // at the end 0th row which is prev m jo sabse chotta hoga vahi answer hoga.
        return *min_element(prev.begin(), prev.end());
    }
};