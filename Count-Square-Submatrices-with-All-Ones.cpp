class Solution
{
public:
    int countSquares(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));
        int ans = 0;

        // making 1st poori row and 1st poora column as 0.
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = matrix[i][0];
            ans += dp[i][0];
        }

        // from 1 as upr row ka karte samay 0th column ka kardiya hoga ji
        for (int i = 1; i < m; i++)
        {
            dp[0][i] = matrix[0][i];
            ans += dp[0][i];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                // agr 1 hai toh upr left and upper-left diagonal ka minimum lo and usme + 1 for 1 itself.
                if (matrix[i][j])
                {
                    dp[i][j] +=
                        min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    ans += dp[i][j];
                }
            }
        }

        return ans;
    }
};

/*
Iske andar mujhe agr 1 hai toh uske upr left and upper-left diagonal m dekhna
padega ki kahan tak 1 hai, jo sabse minimum hoga vahi answer hoga kyuki square
ke liye minimum dekhna padega jo common ho. Mera har cell store karega ki abhi
tak kitne square bn rahe hai uss particular (i,j) m.


In case of rectangle or square questions, tabulation is more good as it is more
intuitive. Just take a separate array and store the data in this.

TC - O(n*n) possible states dekho
SC - O(n*n)
*/