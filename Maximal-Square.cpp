class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        // abhi tak ki maximum sides kitni mili ek square m
        int ans = -1e9;
        vector<vector<int>> dp(n, vector<int>(m));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == '0')
                {
                    continue;
                }
                // Square ke liye left top and diagonal m dekho kitne 1 hai unka
                // minimum lelo as sabse km wala jo hai utni hi sides common
                // hogi toh usme 1 + kardo as abhi tum 1 m ho and single 1 is
                // also a square.
                int top = i > 0 ? dp[i - 1][j] : 0;
                int diagonal = i > 0 && j > 0 ? dp[i - 1][j - 1] : 0;
                int left = j > 0 ? dp[i][j - 1] : 0;

                int mini = min({top, diagonal, left});
                dp[i][j] = 1 + mini;
                ans = max(ans, dp[i][j]);
            }
        }

        if (ans == -1e9)
        {
            return 0;
        }

        return ans == 1 ? 1 : ans * ans;
    }
};