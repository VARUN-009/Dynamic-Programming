class Solution
{
private:
    int helper(int idx, int length, vector<int> &price, vector<vector<int>> &dp)
    {
        // base case
        if (idx == 0)
        {
            // idx = 0 so 0 + 1 = 1 so can also check if length >= 1
            if (length >= idx + 1)
            {
                // ye bhi chlega as idx=0 hai and 0 + 1 = 1 toh 1 se divide means same toh direct multiply kardo.
                return length * price[0];
                // return (length / (idx + 1)) * price[0];
            }
            else
            {
                return 0;
            }
        }

        // DP
        if (dp[idx][length] != -1)
        {
            return dp[idx][length];
        }

        // recursive case
        int take = 0;
        if (length >= idx + 1)
        {
            // recursion m kabhi bhi karo toh phir bracket laga ke karo as vo out of bounds jaa sakta hai dikkat de sakta hai
            take = price[idx] + helper(idx, length - (idx + 1), price, dp);
        }

        int notTake = helper(idx - 1, length, price, dp);

        return dp[idx][length] = max(take, notTake);
    }

public:
    int cutRod(vector<int> &price)
    {
        // code here
        int n = price.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return helper(n - 1, n, price, dp);
    }
};

/*
length - idx + 1
Incorrect subproblem size: Instead of reducing length properly, it sometimes increases it due to the +1, leading to out-of-bounds recursion.

Recursion going into invalid states: The recursion might try to access dp[idx][invalid_length], which can go out of bounds, causing a segmentation fault.

Recursion TC - O(>>>2^n) & SC - O(n length) at max

TC - O(n*n)
SC - O(n*n)


*/

// TABULATION
class Solution
{
public:
    int cutRod(vector<int> &price)
    {
        // code here
        int n = price.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        for (int length = 0; length <= n; length++)
        {
            // length >= idx + 1 but idx here is 0 so 1
            if (length >= 1)
            {
                dp[0][length] = length * price[0];
            }
            else
            {
                dp[0][length] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int length = 0; length <= n; length++)
            {
                int take = 0;
                if (length >= idx + 1)
                {
                    // recursion m kabhi bhi karo toh phir bracket laga ke karo as vo out of bounds jaa sakta hai dikkat de sakta hai
                    take = price[idx] + dp[idx][length - (idx + 1)];
                }

                int notTake = dp[idx - 1][length];

                dp[idx][length] = max(take, notTake);
            }
        }

        return dp[n - 1][n];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int cutRod(vector<int> &price)
    {
        // code here
        int n = price.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int length = 0; length <= n; length++)
        {
            // length >= idx + 1 but idx here is 0 so 1
            if (length >= 1)
            {
                prev[length] = length * price[0];
            }
            else
            {
                prev[length] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int length = 0; length <= n; length++)
            {
                int take = 0;
                if (length >= idx + 1)
                {
                    // recursion m kabhi bhi karo toh phir bracket laga ke karo as vo out of bounds jaa sakta hai dikkat de sakta hai
                    take = price[idx] + curr[length - (idx + 1)];
                }

                int notTake = prev[length];

                curr[length] = max(take, notTake);
            }

            prev = curr;
        }

        return prev[n];
    }
};

// SUPER SAPCE OPTIMISATION
class Solution
{
public:
    int cutRod(vector<int> &price)
    {
        // code here
        int n = price.size();
        vector<int> prev(n + 1, 0);

        for (int length = 0; length <= n; length++)
        {
            // length >= idx + 1 but idx here is 0 so 1
            if (length >= 1)
            {
                prev[length] = length * price[0];
            }
            else
            {
                prev[length] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            // 0 se n tak as mujhe maximum chahiye toh jo sabse latest data hai vo chahiye mujhe toh iss karke agr minimum hi chahiye hota toh phir ulta karte n to 0.
            for (int length = 0; length <= n; length++)
            {
                int take = 0;
                if (length >= idx + 1)
                {
                    // recursion m kabhi bhi karo toh phir bracket laga ke karo as vo out of bounds jaa sakta hai dikkat de sakta hai
                    take = price[idx] + prev[length - (idx + 1)];
                }

                int notTake = prev[length];

                prev[length] = max(take, notTake);
            }

        }

        return prev[n];
    }
};