// MEMOISATION
class Solution
{
public:
    int dp[201][201];
    int helper(vector<vector<int>> &triangle, int row, int col)
    {
        // base case
        if (row == triangle.size() - 1)
        {
            return triangle[row][col];
        }

        if (dp[row][col] != -1)
        {
            return dp[row][col];
        }

        // recursive case
        int sum = triangle[row][col];
        sum += min(helper(triangle, row + 1, col), helper(triangle, row + 1,
                                                          col + 1));
        return dp[row][col] = sum;
    }
    int minimumTotal(vector<vector<int>> &triangle)
    {
        memset(dp, -1, sizeof(dp));
        return helper(triangle, 0, 0);
    }
};
/*
starting from 0,0 as end se start karege toh bohot saare starting points hoge toh not good. (0,0) m toh bss 1 hi hai point start karne ka

TC - Recursion 
ye rows ke cols hai and har row case m 2 option hai down diagonal so 2 ^ (summation of all these columns as har kisi ke liye 2 options hai na )
1 + 2 + 3 + 4 ... n 

SC - O(n) har row ke liye ho raha hai na th overall n rows


TC - O(n*n) worst case n rows n cols
SC - O(n*n) + O(n)
*/  

// TABULATION
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // last row m toh answer vo hi rahega row hi ek hai toh vo hi ans
        for (int j = 0; j < n; j++)
        {
            dp[n - 1][j] = triangle[n - 1][j];
        }

        // 2nd last row se iterate kar and jo sabse chotta ho usko select kar
        for (int i = n - 2; i >= 0; i--)
        {
            // <i+1 kyuki if row start from 1 then jitna row number utne col hai
            // toh hum technically har cell ka answer store kar rahe hai ki agr
            // ye hai toh kya hoga, ye hai toh kya hoga
            for (int j = 0; j < i + 1; j++)
            {
                dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
            }
        }
        return dp[0][0];
        // end m jo first cell hoga usme number aajayega apneaap kyuki hum
        // neeche se upr jaa rahe hai and row1 m ek hi col hoga toh vahi answer
        // hoga
    }
};
// TC - O(N*N)
// SC - O(n*n) 

// SPACE OPTIMISATION
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        // last row ka store kiya phir further rows ka m previously saved answer
        // se hi nikalunga and on the go usko update karte rahunga
        vector<int> dp = triangle[n - 1]; // last row ke equal

        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j < i + 1; j++)
            {
                // previous row ka ans hoga j, j+1 index m
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }

        // ultimately ans in first index
        return dp[0];
    }
};
/*
TC - O(N*N)
SC - O(n)
*/