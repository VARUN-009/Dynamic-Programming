// MEMOISATION
class Solution
{
public:
    bool helper(string &str, string &pattern, int i, int j, vector<vector<int>> &dp)
    {
        // base case
        // dono ke end m pahoch gya toh means dono match = true
        if (i < 0 && j < 0)
        {
            return true;
        }

        // s bachi hai abhi match karne ke liye and pattern ke end m ho gya = false
        if (i >= 0 && j < 0)
        {
            return false;
        }

        // s ke end m pahoch gya but p wali rehti hai toh m chahunga ki p ke aage jitne characters bach rahe hai vo * ho.
        if (i < 0 && j >= 0)
        {
            for (int idx = 0; idx <= j; idx++)
            {
                if (pattern[idx] != '*')
                {
                    return false;
                }
            }

            return true;
        }

        // DP
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // recursive case
        if (str[i] == pattern[j] || pattern[j] == '?')
        {
            return dp[i][j] = helper(str, pattern, i - 1, j - 1, dp);
        }

        if (pattern[j] == '*')
        {
            // * means m empty bhi le sakta hu, 1 bhi, 2 bhi and so on... so agr m ek le rha hu toh star as it is rahega and nhi le rha hu toh pattern wali m ek kadam km kardo peeche aajao and s m same hi rahega as kuch compare ni kara na -- dono m se jo true hoga vahi answer hoga.
            //     * taking nothing        * taking one character
            return dp[i][j] = helper(str, pattern, i, j - 1, dp) || helper(str, pattern, i - 1, j, dp);
        }

        return dp[i][j] = false;
    }
    bool isMatch(string s, string p)
    {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return helper(s, p, n - 1, m - 1, dp);
    }
};
/*
strings ke pattern matching types question m usually end se hi iterate kare karo better raheta hai and simple to understand.
TC - O(n*m)
SC - O(n*m) + O(n+m)

*/

// TABULATION
class Solution
{
public:
    bool isMatch(string str, string pattern)
    {
        int n = str.size();
        int m = pattern.size();
        // taking 1 based so ek ek badhana padega as I am going from 1 to n,m - initally false lelo sab
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // see the base cases - Can I ever go < 0 ? No, but usko karne ke liye what I can do is that make it 1-based indexing and then ek ek index badha ke kardo sab means ki <0 ko ==0.
        dp[0][0] = 1;

        // i >= 0 && j < 0
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = 0;
        }

        // i < 0 && j >= 0
        // for every i==0 and j ki value more than 0 agr ek bhi aisa hua ki * nhi hai toh [0][j] = false
        for (int j = 1; j <= m; j++)
        {
            int flag = 1;
            // jaise hi mujhe ek aisa mil gya ki * ni hai toh pehle toh hum return hi kar rahe the par ab hum false kardege break karke nhi hua aisa toh simple true hi.
            for (int idx = 1; idx <= j; idx++)
            {
                // 1-based hai toh pehle ka check karna hai kyuki ek step aage hai toh idx-1
                if (pattern[idx - 1] != '*')
                {
                    flag = 0;
                    break;
                }
            }
            dp[0][j] = flag;
        }

        // 1-based indexing hai toh check karne ke liye compare karne ke liye 1 peeche ka dekhna padega na i-1 aise...as hum 1 step aage hai. DP same hi rahega kyuki 1 step aage hi karna hai 0 wala kar chuke hai base case handle. wahan pe <0 is ==0 here, wahan pe >=0 is > 0 here.
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                // recursive case
                if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '?')
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }

                else if (pattern[j - 1] == '*')
                {
                    // * means m empty bhi le sakta hu, 1 bhi, 2 bhi and so on... so agr m ek le rha hu toh star as it is rahega and nhi le rha hu toh pattern wali m ek kadam km kardo peeche aajao and s m same hi rahega as kuch compare ni kara na -- dono m se jo true hoga vahi answer hoga.
                    //     * taking nothing        * taking one character
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }

        // 1-based indexing so ek aage ka
        return dp[n][m];
    }
};

/*

RULE FOR CONVERTING TO TABULATION IN DP ON STRINGS
For converting to tabulation in strings, take 1-based indexing as you can never go less than 0 so usko compensate karne ke liye base case ko toh 1-based indexing and sab index 1 1 se badha do toh baat ek hi ho jayegi 0-n-1 and 1-n distance same hi hai ji.

TC - O(n*m)
SC - O(n*m)
*/

// SPACE OPTIMISATION
class Solution
{
public:
    bool isMatch(string str, string pattern)
    {
        int n = str.size();
        int m = pattern.size();

        // prev means i-1 row and curr means i row. size is m+1 as iss row m meri j buckets hai na till m+1 so m+1
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        // i-1th row ka 0th index = true;
        prev[0] = 1;

        // i >= 0 && j < 0
        for (int i = 1; i <= m; i++)
        {
            // dp[i][0] = 0;
            prev[i] = 0;
        }

        //
        for (int i = 1; i <= n; i++)
        {
            // curr is the current row and that's 0th column has to be assigned everytime.
            int flag = 1;
            // jaise hi mujhe ek aisa mil gya ki * ni hai toh pehle toh hum return hi kar rahe the par ab hum false kardege break karke nhi hua aisa toh simple true hi.
            for (int idx = 1; idx <= m; idx++)
            {
                // 1-based hai toh pehle ka check karna hai kyuki ek step aage hai toh idx-1
                if (pattern[idx - 1] != '*')
                {
                    flag = 0;
                    break;
                }
            }

            // ab har row ka 1st column tu assign kar raha hai toh isko row ke loop ke andar likhde and ye curr ho jayega -- poora ye loop inside row loop
            curr[0] = flag;

            for (int j = 1; j <= m; j++)
            {
                // recursive case
                if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '?')
                {
                    curr[j] = prev[j - 1];
                }

                else if (pattern[j - 1] == '*')
                {
                    // * means m empty bhi le sakta hu, 1 bhi, 2 bhi and so on... so agr m ek le rha hu toh star as it is rahega and nhi le rha hu toh pattern wali m ek kadam km kardo peeche aajao and s m same hi rahega as kuch compare ni kara na -- dono m se jo true hoga vahi answer hoga.
                    //     * taking nothing        * taking one character
                    curr[j] = curr[j - 1] || prev[j];
                }
                else
                {
                    curr[j] = 0;
                }
            }
        }

        // 1-based indexing so ek aage ka
        return prev[m];
    }
};

// GETTING SOME ERROR IN ABOVE CODE__ RECTIFY IT