// MEMOISATION
class Solution
{
private:
    int helper(int idx, int weight, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp)
    {
        // base case
        if (idx == 0)
        {
            if (weight >= wt[0])
            {
                return val[0];
            }
            else
            {
                return 0;
            }
        }

        // DP
        if (dp[idx][weight] != -1)
        {
            return dp[idx][weight];
        }

        // recursive case
        int take = 0;
        if (weight >= wt[idx])
        {
            take = val[idx] + helper(idx - 1, weight - wt[idx], val, wt, dp);
        }

        int notTake = helper(idx - 1, weight, val, wt, dp);

        return dp[idx][weight] = max(take, notTake);
    }

public:
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1, -1));
        return helper(n - 1, W, val, wt, dp);
    }
};

/*
Going from n-1 to 0 so base case humesha 0 m hi hoga <0 mt karna.
Think of the base case as a single element always.
Recursion TC - O(2^n) SC - O(n)

TC - O(n*w)
SC - O(n*w) + O(n)

instead of taking -1e9, take 0 as aisa bhi ho sakta ki ye case ho toh answer galat aayega max(-1e9, -1e9) = -1e9
*/

// TABULATION
class Solution
{
public:
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));

        for (int weight = 0; weight <= W; weight++)
        {
            if (weight >= wt[0])
            {
                dp[0][weight] = val[0];
            }
            else
            {
                dp[0][weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = 0; weight <= W; weight++)
            {
                int take = 0;
                if (weight >= wt[idx])
                {
                    take = val[idx] + dp[idx - 1][weight - wt[idx]];
                }

                int notTake = dp[idx - 1][weight];

                dp[idx][weight] = max(take, notTake);
            }
        }

        return dp[n - 1][W];
    }
};
/*
TC - O(n*w)
SC - O(n*w)
*/

// SPACE OPTIMISATION
class Solution
{
public:
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        // code here
        int n = val.size();
        vector<int> prev(W + 1, 0), curr(W + 1, 0);

        for (int weight = 0; weight <= W; weight++)
        {
            if (weight >= wt[0])
            {
                prev[weight] = val[0];
            }
            else
            {
                prev[weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = 0; weight <= W; weight++)
            {
                int take = 0;
                if (weight >= wt[idx])
                {
                    take = val[idx] + prev[weight - wt[idx]];
                }

                int notTake = prev[weight];

                curr[weight] = max(take, notTake);
            }

            prev = curr;
        }

        return prev[W];
    }
};

// SUPER SPACE OPTIMISATION
class Solution
{
public:
    int knapsack(int W, vector<int> &val, vector<int> &wt)
    {
        // code here
        int n = val.size();
        vector<int> prev(W + 1, 0);

        for (int weight = 0; weight <= W; weight++)
        {
            if (weight >= wt[0])
            {
                prev[weight] = val[0];
            }
            else
            {
                prev[weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = W; weight >= 0; weight--)
            {
                int take = 0;
                if (weight >= wt[idx])
                {
                    take = val[idx] + prev[weight - wt[idx]];
                }

                int notTake = prev[weight];

                prev[weight] = max(take, notTake);
            }

        }

        return prev[W];
    }
};

/*
This one also works kyuki mujhe bss previous row ke cols se matlab hai. pichli row ko m ek vector m store kar rha hu and let's say m W weight m hu toh w-wt[idx] mujhe current weight se km m le jayega na kyuki usme se tu kuch minus kar rha hai toh bss ek nayi row ki need hi ni curr ki tu ussi m changes kar sakta hai. 
You have to move from W to >= 0 as ulta kiya toh jo purani values hai vo override ho jayegi but compute karne ke liye you want previous values so W se 0 tak move karo.


*/