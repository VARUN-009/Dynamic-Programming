// MEMOISATION - TC - O(n*m*k) SC - O(n*m*k) + O(n) recursion
class Solution
{
private:
    int dp[101][101][201];
    bool helper(int i, int j, int k, int n, int m, int N, string s1, string s2, string s3)
    {
        // base case
        // m chahta hu ki teeno ek hi baari m complete ho as interleaving means ki dono strings poori poori lag gayi bnane m s3 ko
        if (i == n && j == m && k == N)
        {
            return true;
        }

        // agr sirf ek se hi bn gayi toh means dusri poori use ni hui, s3=abc and s1=abc and s2="" so in this s2 will not use which we do not want.
        if (k == N)
        {
            return false;
        }

        if (dp[i][j][k] != -1)
        {
            return dp[i][j][k];
        }

        // recursive case
        // agr s1 ka same hai toh take s1, s2 ka same hai toh take s2 and both so take both. Dono m se kisi se bhi answer aaye bss true.
        // in this we can also do this without checking i and j as last m null character hi hoga jo kabhi equal ni hoga so iske bina bhi ho jayega
        bool take_s1 = i < n && s1[i] == s3[k] && helper(i + 1, j, k + 1, n, m, N, s1, s2, s3);
        bool take_s2 = j < m && s2[j] == s3[k] && helper(i, j + 1, k + 1, n, m, N, s1, s2, s3);

        return dp[i][j][k] = take_s1 || take_s2;
    }

public:
    bool isInterleave(string s1, string s2, string s3)
    {
        memset(dp, -1, sizeof(dp));
        int n = s1.size();
        int m = s2.size();
        int N = s3.size();

        return helper(0, 0, 0, n, m, N, s1, s2, s3);
    }
};

// MEMOISATION 2D
// MEMOISATION - TC - O(n*m*k) SC - O(n*m) + O(n) recursion
class Solution
{
private:
    int dp[101][101];
    bool helper(int i, int j, int n, int m, int N, string s1, string s2, string s3)
    {
        // base case
        // m chahta hu ki teeno ek hi baari m complete ho as interleaving means ki dono strings poori poori lag gayi bnane m s3 ko
        if (i == n && j == m && i + j == N)
        {
            return true;
        }

        // agr sirf ek se hi bn gayi toh means dusri poori use ni hui, s3=abc and s1=abc and s2="" so in this s2 will not use which we do not want.
        if (i + j == N)
        {
            return false;
        }

        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // recursive case
        // agr s1 ka same hai toh take s1, s2 ka same hai toh take s2 and both so take both. Dono m se kisi se bhi answer aaye bss true.
        // in this we can also do this without checking i and j as last m null character hi hoga jo kabhi equal ni hoga so iske bina bhi ho jayega
        // Now agr mere s3 m 3 characters ho gaye this means ki s1 & s2 dono ke characters milake 3 hi hue hoge total jyada ni ho sakte. basically 3rd index m hu toh i + j mera 3 ke equal hoga na jyada na kam 4 element liye hai means ki 4 process kar chuka hu.
        bool take_s1 = i < n && s1[i] == s3[i + j] && helper(i + 1, j, n, m, N, s1, s2, s3);
        bool take_s2 = j < m && s2[j] == s3[i + j] && helper(i, j + 1, n, m, N, s1, s2, s3);

        return dp[i][j] = take_s1 || take_s2;
    }

public:
    bool isInterleave(string s1, string s2, string s3)
    {
        memset(dp, -1, sizeof(dp));
        int n = s1.size();
        int m = s2.size();
        int N = s3.size();

        return helper(0, 0, n, m, N, s1, s2, s3);
    }
};

// TABULATION TC - O(n*m) SC - O(n*m) 2D DP
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size();
        int m = s2.size();
        int N = s3.size();
        // for interleaving, sum of s1 + s2 should be equal to s3 because we want ki dono ki saari ki saari strings use ho.
        if (n + m != N)
        {
            return false;
        }
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // 2 base case hai - 1. i==n j==m and i+j ==N which is only possible in dp[n][m] so make it true. 2. base case is of making false which is already covered in initialisation so no need to do it again.
        dp[n][m] = true;

        for (int i = n; i >= 0; i--)
        {
            for (int j = m; j >= 0; j--)
            {
                if (i == n && j == m)
                    continue;

                bool take_s1 = i < n && s1[i] == s3[i + j] && dp[i + 1][j];
                bool take_s2 = j < m && s2[j] == s3[i + j] && dp[i][j + 1];

                dp[i][j] = take_s1 || take_s2;
            }
        }

        return dp[0][0];
    }
};

// TABULATION TC - O(n*m) SC - O(m) 1D DP
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size();
        int m = s2.size();
        int N = s3.size();
        // for interleaving, sum of s1 + s2 should be equal to s3 because we want ki dono ki saari ki saari strings use ho.
        if (n + m != N)
        {
            return false;
        }

        vector<bool> next(m + 1, false), curr(m + 1, false);

        next[m] = curr[m] = true;

        for (int i = n; i >= 0; i--)
        {
            for (int j = m; j >= 0; j--)
            {
                if (i == n && j == m)
                    continue;

                // no need to check i < n && j < m as last m null character hoga jo kabhi bhi equal ni hoga so don't worry you can skip it.
                bool take_s1 = i < n && s1[i] == s3[i + j] && next[j];
                bool take_s2 = j < m && s2[j] == s3[i + j] && curr[j + 1];

                curr[j] = take_s1 || take_s2;
            }

            next = curr;
        }

        return next[0];
    }
};