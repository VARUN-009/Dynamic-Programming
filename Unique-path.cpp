// MEMOISATION
class Solution
{
public:
    // maximum rows and cols toh overall meine sabka hi leliya - from constraints
    int dp[101][101];
    int help(int m, int n)
    {
        // agr m pahoch gya 0 cell m means I have found a way, return 0.
        if (m == 0 and n == 0)
        {
            return 1;
        }

        // grid se bahar chle gya means no way toh return 0
        if (m < 0 || n < 0)
        {
            return 0;
        }

        if (dp[m][n] != -1)
        {
            return dp[m][n];
        }

        // recursive case
        // 2 tareeke hai right and down from 0,0 to n-1,m-1 but m ulta jau n-1,m-1 to 0 toh phir m right up ni left up dekhunga toh ek col km and ek row km.
        return dp[m][n] = help(m - 1, n) + help(m, n - 1);
    }
    int uniquePaths(int m, int n)
    {
        memset(dp, -1, sizeof(dp));
        return help(m - 1, n - 1);
    }
};



// TABULATION
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        // n rows hai and m cols toh 0 se lekar n-1 row tak jaunga end m mera n-1,m-1 m answer milega
        vector<vector<int>> dp(n, vector<int> dp(m, 0));

        // now check base case, tabulation is from base case to required ans - bottom up - mujhe bss ye btana hai ki har cell m m kitne tareeko se aa sakta hu toh starting cell 0,0 m toh m 1 hi tareeke se aa sakta hu means vahi se start kar rha hu toh uska 1 ho jayega na
        dp[0][0] = 1;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                // left and up and check whether they exist or not.
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

        return dp[n - 1][m - 1];
    }
};



// SPACE OPTIMISATION
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        // mujhe bss last row and last col ka hi ans chahiyebss 1 row and 1 col
        // m hu toh bss 0 row and 0 col se hi lena dena hai , 2 row m 1 row like
        // this...
        vector<int> prev(n, 0);
        prev[0] = 1;
        for (int row = 0; row < m; row++)
        {
            vector<int> curr(n, 0);
            for (int col = 0; col < n; col++)
            {
                // left and up and check whether they exist or not.
                // if it's a first cell toh usme 1 hi tareeka hai aane ka toh 1
                if (row == 0 && col == 0)
                    curr[col] = 1;
                else
                {
                    int left = 0;
                    int up = 0;
                    if (row > 0)
                    {
                        up += prev[col];
                    }

                    if (col > 0)
                    {
                        left += curr[col - 1];
                    }

                    curr[col] = left + up;
                }
            }

            prev = curr;
        }

        // at the end last row ke last cell m answer hoga hamara jaane ka.
        return prev[n - 1];
    }
};