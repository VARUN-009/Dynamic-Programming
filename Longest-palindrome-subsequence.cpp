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

        return dp[len1][len2] = max(memoisation(str1, str2, len1 - 1, len2), memoisation(str1, str2, len1, len2 - 1));
    }
    int longestPalindromeSubseq(string s)
    {
        // cheeje same hi hai like LCS bss isme meine dusri string ke liye pehli wali string reverse order m leli. Palindrome means ki right to left ho ya left to right same hi hoga toh reverse karne ke baad ab check karo ki ab konsa longest common subsequence hai LCS hai as right wale character ko left wale ke saath dekh rahe ho toh palindrome hi banega.
        string text1 = s;
        string text2 = s;
        reverse(text2.begin(), text2.end());
        int n = text1.length();
        int m = text2.length();
        memset(dp, -1, sizeof(dp));
        return memoisation(text1, text2, n - 1, m - 1);
    }
};
/*
Possible questions keywords include comparison, replaces, edit.
1. Express in indexes i, j
2. Explore possibility on that index
3. Take the best among them


Recursion TC - O(2^n) * O(2*n) har 1 ko baaki ke 2^n se compare karege na SC - O(n+m) stack space as at max dono ki length ke sum ke equal hi hogi bss.alignas

TC - O(n*m)
SC - O(n*m) + O(n+m)

*/

// TABULATION
class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        string text1 = s;
        string text2 = s;
        reverse(text2.begin(), text2.end());

        int n = text1.length();
        int m = text2.length();

        // ab yahan pe m len1<0 bhi dekh rha hu par negative to jaa ni sakta toh to resolve this m ek kaam karta hu sab m 1 1 index badha deta hu toh phir len1<0 ho jayega len1==0. This way I can tabulise it. So when I say index 1, it means index 0 as ek aage badhaya tha par actually m ek kam tha na...
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

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
                if (text1[len1 - 1] == text2[len2 - 1])
                {
                    dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
                }
                else
                {
                    dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
                }
            }
        }

        return dp[n][m];
    }
};

// SPACE OPTMISATION
class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        string text1 = s;
        string text2 = s;
        reverse(text2.begin(), text2.end());
        int n = text1.length();
        int m = text2.length();

        // ab yahan pe m len1<0 bhi dekh rha hu par negative to jaa ni sakta toh to resolve this m ek kaam karta hu sab m 1 1 index badha deta hu toh phir len1<0 ho jayega len1==0. This way I can tabulise it. So when I say index 1, it means index 0 as ek aage badhaya tha par actually m ek kam tha na...
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        // mujhe pehli row means 0th row and 0th col humesha 0 chahiye toh ye toh meine base case m cover kar hi liya hai na toh phirse likhne ki need ni hai

        // 0th row ka toh kam kardiya hai and 0th column ka bhi toh you cna skip them
        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                // baaki sab same rahega bss current index reality m ek km hai toh ek km karke check karo baaki sab same hi hai
                if (text1[len1 - 1] == text2[len2 - 1])
                {
                    curr[len2] = 1 + prev[len2 - 1];
                }
                else
                {
                    curr[len2] = max(prev[len2], curr[len2 - 1]);
                }
            }

            prev = curr;
        }

        return prev[m];
    }
};