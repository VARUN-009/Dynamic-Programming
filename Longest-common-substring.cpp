// MEMPOISATION approach in which m saari possible substrings m iterate kar rha hu. TC - O(n*m*n*m) as memoisation takes n*m and for every pair it takes n*m and SC - O(n*m)
class Solution
{
public:
    int dp[1001][1001];
    int memoisation(string &str1, string &str2, int len1, int len2)
    {
        // base case
        // agr aisa hua ki ek string ya dono hi string khatam ho gayi toh phir toh m check ni kar sakta na toh then phir return 0
        if (len1 < 0 || len2 < 0)
        {
            return 0;
        }

        if (dp[len1][len2] != -1)
        {
            return dp[len1][len2];
        }

        // recursive case
        // agr match kar gayi toh uska answer dedo and agr match ni kari toh uska answer dedo. yahan pe aisa nhi hai ki le sakta hu and nhi le sakta like knapsack. Not like take or notTake so agr match kari direct return and nhi toh bhi direct return .
        if (str1[len1] == str2[len2])
        {
            return dp[len1][len2] = 1 + memoisation(str1, str2, len1 - 1, len2 - 1);
        }

        // agr ni hai same toh isme mujhe continous hi chahiye bss subsequence m toh ek ek leave bhi kar sakte hai par isme continous hi chahiye bss. toh agr same ni hai toh phir vo 0 and aage se dekho ab...
        else
        {
            return dp[len1][len2] = 0;
        }
    }
    int longestCommonSubstr(string &s1, string &s2)
    {
        // your code here
        int n = s1.length();
        int m = s2.length();
        memset(dp, -1, sizeof(dp));
        int maxLen = -1e9;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                maxLen = max(maxLen, memoisation(s1, s2, i, j));
            }
        }
        return maxLen;
    }
};
/*
memoisation(s1, s2, n - 1, m - 1, dp); only computes the value for (n-1, m-1)
This only ensures the longest common substring that ends at (n-1, m-1), but the longest common substring could end at any (i, j).
The recursion fills in the dp table only for indices that contribute to (n-1, m-1), meaning some values might remain -1.
The dp table might not be fully computed
When you later iterate over the dp table to get maxLen, it might still have uninitialized -1 values, leading to incorrect results.

So that's why recursion memoisation se karna hai toh har possible pairs of strings m har possible pair of indexes m iterate karna padega (i,j).
*/

// TABULATION Just checking from the table
class Solution
{
public:
    int longestCommonSubstr(string &s1, string &s2)
    {
        // your code here
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLen = -1e9;
        // agr meri row ya col 0 hai toh vo 0 hai
        for (int col = 0; col <= m; col++)
        {
            dp[0][col] = 0;
        }

        for (int row = 0; row <= n; row++)
        {
            dp[row][0] = 0;
        }

        // 0th row ka toh kam kardiya hai and 0th column ka bhi toh you cna skip them
        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                // baaki sab same rahega bss current index reality m ek km hai toh ek km karke check karo baaki sab same hi hai
                if (s1[len1 - 1] == s2[len2 - 1])
                {
                    dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
                }

                // agr ni hai same toh isme mujhe continous hi chahiye bss subsequence m toh ek ek leave bhi kar sakte hai par isme continous hi chahiye bss. toh agr same ni hai toh phir vo 0 and aage se dekho ab...jab tak same hai sahi hai jaise hi same ni abhi tak ka answer karo maxLen m save and then aage badho at the end maxLen m Longest common substring store ho jayegi
                else
                {
                    dp[len1][len2] = 0;
                }

                maxLen = max(maxLen, dp[len1][len2]);
            }
        }

        return maxLen;
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int longestCommonSubstr(string &s1, string &s2)
    {
        // your code here
        int n = s1.length();
        int m = s2.length();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        int maxLen = -1e9;
        // agr meri row ya col 0 hai toh vo 0 hai
        for (int col = 0; col <= m; col++)
        {
            prev[col] = 0;
        }

        for (int row = 0; row <= n; row++)
        {
            prev[0] = 0;
        }

        // 0th row ka toh kam kardiya hai and 0th column ka bhi toh you cna skip them
        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                // baaki sab same rahega bss current index reality m ek km hai toh ek km karke check karo baaki sab same hi hai
                if (s1[len1 - 1] == s2[len2 - 1])
                {
                    curr[len2] = 1 + prev[len2 - 1];
                }

                // agr ni hai same toh isme mujhe continous hi chahiye bss subsequence m toh ek ek leave bhi kar sakte hai par isme continous hi chahiye bss. toh agr same ni hai toh phir vo 0 and aage se dekho ab...jab tak same hai sahi hai jaise hi same ni abhi tak ka answer karo maxLen m save and then aage badho at the end maxLen m Longest common substring store ho jayegi
                else
                {
                    curr[len2] = 0;
                }

                maxLen = max(maxLen, curr[len2]);
            }

            prev = curr;
        }

        return maxLen;
    }
};
