class Solution
{
public:
    int dp[501];
    int helper(vector<int> &arr, int k, int start)
    {
        // base case
        if (start >= arr.size())
        {
            return 0;
        }

        if (dp[start] != -1)
        {
            return dp[start];
        }

        // recursive case
        int currMax = INT_MIN;
        int ans = INT_MIN;
        for (int j = start; j < min(start + k, (int)arr.size()); j++)
        {
            currMax = max(currMax, arr[j]);
            ans = max(ans, currMax * (j - start + 1) + helper(arr, k, j + 1));
        }
        return dp[start] = ans;
    }
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        memset(dp, -1, sizeof(dp));
        return helper(arr, k, 0);
    }
};
/*
Tere pass array hai unme se tujhe subarray lene hai max k size ka, toh ek kaam
kar na, pehle 1 size ka le, phir 2 size ka...till k size ka. ab ek subarray
tunne leliya, uski tunne max val nikal li and then size of that array, toh jo
bhi ka ans hai aur jo ab tunne sum liya + aage recursion jo dega uska max lele,
ek baar 1 size ka subaaray se milega, phir 2 phir 3 multiple options hai na tere
pass, toh loop aayega and out of all possibilities, you'll get the max answer

TC - O(n*k) SC - O(n)
*/

// TABULATION
class Solution
{
public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        vector<int> dp(n + 1, 0);

        // base case start >= arr.size() already covered in dp initialisation so no need to do it again.
        // changing parameters jo hai unko reverse order m likhna hai baaki recursive case will be as it is.
        for (int start = n - 1; start >= 0; start--)
        {
            int currMax = INT_MIN;
            int ans = INT_MIN;
            for (int j = start; j < min(start + k, (int)arr.size()); j++)
            {
                currMax = max(currMax, arr[j]);
                ans = max(ans, currMax * (j - start + 1) + dp[j+1]);
            }
            dp[start] = ans;
        }

        return dp[0];
    }
};