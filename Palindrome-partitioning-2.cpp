// MEMOISATION
class Solution
{
public:
    bool checkPalindrome(string &s, int start, int end)
    {
        while (start < end)
        {
            if (s[start] != s[end])
            {
                return false;
            }
            start++;
            end--;
        }

        return true;
    }

    int helper(string &s, int idx, int n, vector<int> &dp)
    {
        // base case
        if (idx == n)
        {
            return 0;
        }

        // DP
        if (dp[idx] != -1)
        {
            return dp[idx];
        }

        // recursive case
        int ans = 1e9;
        for (int i = idx; i < n; i++)
        {
            if (checkPalindrome(s, idx, i))
            {
                int curr = 1 + helper(s, i + 1, n, dp);
                ans = min(curr, ans);
            }
        }

        return dp[idx] = ans;
    }

    int minCut(string s)
    {
        int n = s.size();
        vector<int> dp(n + 1, -1);
        return helper(s, 0, n, dp) - 1;
    }
};
/*
Just like palindrome partitioning 1, meine li ki haa paldinrome hai and doing front partition lene ke baad 1 + aage se recursion answer dega and minimum leta rahunga bsss. Now last character jab akela bachega toh then vo khud leke then 1 + fun() kardega and fun() will return 0 as idx=n so ye extra partiton count ho gayi toh ignore this at the end jab answer return karo main function se return ans - 1

Recursion TC - exponential checking all possible partitions.


*/

// TABULATION
class Solution
{
public:
    bool checkPalindrome(string &s, int start, int end)
    {
        while (start < end)
        {
            if (s[start] != s[end])
            {
                return false;
            }
            start++;
            end--;
        }

        return true;
    }

    int minCut(string s)
    {
        int n = s.size();

        // base case jo tha ki agr m idx=n m hu toh bhai phir that gives me 0.
        vector<int> dp(n + 1, 0);

        // base case meine upr hi cover karliya hai toh ab ek step km ho gya
        // kyuki ek toh meine base case uor hi cover karliya na toh iska dhyan
        // rakhna hota hai ki base case ke baad usko htake likho recursive case
        for (int idx = n - 1; idx >= 0; idx--)
        {
            int ans = 1e9;
            for (int i = idx; i < n; i++)
            {
                if (checkPalindrome(s, idx, i))
                {
                    int curr = 1 + dp[i + 1];
                    ans = min(curr, ans);
                }
            }

            dp[idx] = ans;
        }

        // jo jo change ho rahe hai parameters unko likho in form of loop but in
        // reverse order and jo at the last main function se return kar rahe ho
        // usko dp ki form m likho and recursive case same hi rahega
        return dp[0] - 1;
    }
};

/*
TC - O(n) * O(n) loop
SC - O(n) * O(n)


1. Write down the base case
2. Changing parameters in reverse order in the form of a loop
3. Copy the recurrence relation.
*/