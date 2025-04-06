// MEMOISATION
class Solution
{
public:
    int helper(int i, int j, int n, int m, string &s, string &t, vector<vector<int>> &dp)
    {
        // base case - agr mera j poori t ko cover kar chuka hai means ki mujhe string mil chuki hai toh return 1 ki haa bhai 1 baari answer mil chuka hai. Aisa hua ki m s wali string poori traverse kar chuka hu par abhi tak answrr ni mila toh return 0 kyuki aage aur hai hi ni ab. Order of base cased matter agr ulta likh dete like - dono i and j last m hai and dono match kar gaye toh then base case pehle i wala likha toh 0 return 0 ho jayega.
        if (j == m)
            return 1;
        if (i == n)
            return 0;

        // DP
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // recursive case
        // m starting se chl rha hu and agr match kar rha hai toh dono ke count add kar ki agr isko liya then and agr isko ni liya then dono ke add kar total chahiye hume. Agr nhi kar rha match toh bhai aage badh and jo answer mile vo dede.
        if (s[i] == t[j])
        {
            // take it and don't take it
            return dp[i][j] = helper(i + 1, j + 1, n, m, s, t, dp) + helper(i + 1, j, n, m, s, t, dp);
        }
        else
        {
            return dp[i][j] = helper(i + 1, j, n, m, s, t, dp);
        }
    }
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return helper(0, 0, s.size(), t.size(), s, t, dp);
    }
};
/*
Count ways / total -- in cases m base case m usually return 0 / 1. Recursion m fun() + fun() -- ye syntax hota hai.
Whenever you have two strings - take 2 parameters i and j for both strings.
1. Express everything in terms of i and j.
2. Explore all possibilities.
3. Return summation of all possibilities.
4. Base case



recursion TC = exponential as 2^n subsequences for s and 2^m subsequences for t so total is 2^n * 2^m ~ exponential
recursion SC - O(n+m) as dono strings ke character lene padege na

TC = O(n*m)
SC = O(n*m) + O(n+m)
*/

// TABULATION
class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        int MOD = 1e9 + 7;

        // base case ek issi m cover ho gya ki sabko 0 lelo toh i==n wala cover ho gya.
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // j==m m bhi ye hi karna hai toh isko loop se kardo
        for (int i = 0; i <= n; i++)
        {
            dp[i][m] = 1;
        }

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {

                if (s[i] == t[j])
                {
                    // take it + don't take it
                    dp[i][j] = (dp[i + 1][j + 1] + dp[i + 1][j]) % MOD;
                }
                else
                {
                    // no match
                    dp[i][j] = (dp[i + 1][j]) % MOD;
                }
            }
        }

        return dp[0][0];
    }
};
/*
1. Write down the base case
2. Write down the changing parameters in opposite direction in the form of loops.
3. Copy paste the recurrence

JAB OVERFLOW HO LONG LONG LENE KE BAAD BHI THEN YOU CAN TAKE DOUBLE. AND END M JIS TAREEKE SE RETURN KARNA HAI TYPECAST KARKE RETURN KARDO.   OR    YOU CAN TAKE MOD

*/

// SPACE OPTIMISATION
class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        // row agr nth hai toh all 0 but mth index all rows ka is 1. So both covered in this as per done in tabulation.
        vector<double> prev(m + 1, 0);
        prev[m] = 1;

        vector<double> curr(m + 1, 0);
        curr[m] = 1;

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {

                if (s[i] == t[j])
                {
                    // take it
                    curr[j] = (prev[j + 1] + prev[j]);
                }
                else
                {
                    curr[j] = (prev[j]);
                }
            }

            prev = curr;
        }

        return (int)prev[0];
    }
};
/*
isme bss upr wala array chahiye tha [i+1] so meine uske liye ek naya array leliya and for current store uske liye bhi. size vahi jaisa liya hai pehle m+1 and [m] = 1 as agr mera j bahar gya toh I've got an answer so 1 and i==n ke liye 0 tha toh for that too we have taken all values as 0. Both cases covered.

TC - O(n*n)
SC - O(m+1)
*/

// HAVE DO IT VIA A SINGLE ARRAY ONLY. UNDERSTAND HOW THIS CODE WORKS.
// SPACE OPTIMISATION
class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        // row agr nth hai toh all 0 but mth index all rows ka is 1. So both
        // covered in this as per done in tabulation.
        vector<double> prev(m + 1, 0);
        prev[m] = 1;

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {

                if (s[i] == t[j])
                {
                    // take it
                    prev[j] = (prev[j + 1] + prev[j]);
                }
                // else {
                //     prev[j] = (prev[j]);
                // }
            }

            // prev = curr;
        }

        return (int)prev[0];
    }
};