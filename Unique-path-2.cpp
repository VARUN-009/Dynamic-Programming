// MEMOISATION
class Solution
{
public:
    int dp[101][101];
    int help(vector<vector<int>> &vec, int n, int m)
    {
        // base case
        if (n < 0 || m < 0 || vec[n][m] == 1)
        {
            return 0;
        }

        if (n == 0 and m == 0)
        {
            return 1;
        }

        if (dp[n][m] != -1)
        {
            return dp[n][m];
        }

        // recursive case
        return dp[n][m] = help(vec, n - 1, m) + help(vec, n, m - 1);
    }

    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        memset(dp, -1, sizeof(dp));
        return help(obstacleGrid, n - 1, m - 1);
    }
};

// TABULATION
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // dp[0][0] = 1;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                // base case hi hai ye starting m ho toh 1
                if (row == 0 && col == 0 && obstacleGrid[row][col] != 1)
                {
                    dp[row][col] = 1;
                    continue;
                }

                // agr obstacle hai toh uske aage jaan ni sakte na usko use kar sakte toh 0
                if (obstacleGrid[row][col] == 1)
                {
                    dp[row][col] = 0;
                }
                else
                {
                    // left and up and check whether they exist or not. If yes, then add it to dp. hum ek hi condition m ni kar sakte ki n < 0 || m < 0 || vec[n][m] == 1 kyuki agr manlo top se ni left se rasta hai toh vo sabko hi 0 kardega which is not good.
                    int left = 0;
                    int top = 0;
                    if (row > 0)
                    {
                        top += dp[row - 1][col];
                    }

                    if (col > 0)
                    {
                        left += dp[row][col - 1];
                    }

                    dp[row][col] = left + top;
                }
            }
        }

        // answer will be on the last cell
        return dp[n - 1][m - 1];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();

        // previous row ke liye ye vector and curr row ke liye har row m jab iterate karunga toh on the go bnaunga. Curr row ka change jo bhi hai usme karunga and previous row ka kaam jo bhi hai prev m karunga
        vector<int> prev(m, 0);

        for (int row = 0; row < n; row++)
        {
            vector<int> curr(m, 0);
            for (int col = 0; col < m; col++)
            {
                // base case hi hai ye starting m ho toh 1
                if (row == 0 && col == 0 && obstacleGrid[row][col] != 1)
                {
                    curr[col] = 1;
                    continue;
                }

                // agr obstacle hai toh uske aage jaan ni sakte na usko use kar sakte toh 0
                if (obstacleGrid[row][col] == 1)
                {
                    curr[col] = 0;
                }
                else
                {
                    // left and up and check whether they exist or not. If yes, then add it to dp. hum ek hi condition m ni kar sakte ki n < 0 || m < 0 || vec[n][m] == 1 kyuki agr manlo top se ni left se rasta hai toh vo sabko hi 0 kardega which is not good.
                    int left = 0;
                    int top = 0;
                    if (row > 0)
                    {
                        top += prev[col];
                    }

                    if (col > 0)
                    {
                        left += curr[col - 1];
                    }

                    curr[col] = left + top;
                }
            }
            
            // ab aage ke liye ye curr previous bn jayegi na kyuki you are traversing rows.
            prev = curr;
        }

        // answer will be on the last cell
        return prev[m - 1];
    }
};