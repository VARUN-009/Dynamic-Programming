// MEMOISATION
class Solution
{
private:
    int helper(int idx, int weight, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp)
    {
        // base case
        if (idx == 0)
        {
            // mujhe bs maximum profit chahiye amount end m 0 ho ya na ho matlab ni. toh agr at the end 0 index m weight <= hai capacity se toh and infinite suppy hai item ki toh jitni baari le sakte ho lo and har baari uski value bhi milegi toh value multiply
            if (weight >= wt[0])
            {
                return (weight / wt[0]) * val[0];
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
            take = val[idx] + helper(idx, weight - wt[idx], val, wt, dp);
        }

        int notTake = helper(idx - 1, weight, val, wt, dp);

        return dp[idx][weight] = max(take, notTake);
    }

public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity)
    {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
        return helper(n - 1, capacity, val, wt, dp);
    }
};

// TABULATION
class Solution
{
public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity)
    {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        for (int weight = 0; weight <= capacity; weight++)
        {
            if (weight >= wt[0])
            {
                dp[0][weight] = (weight / wt[0]) * val[0];
            }
            else
            {
                dp[0][weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = 0; weight <= capacity; weight++)
            {
                int take = 0;
                if (weight >= wt[idx])
                {
                    take = val[idx] + dp[idx][weight - wt[idx]];
                }

                int notTake = dp[idx - 1][weight];

                dp[idx][weight] = max(take, notTake);
            }
        }

        return dp[n - 1][capacity];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity)
    {
        // code here
        int n = val.size();
        vector<int> prev(capacity + 1, 0), curr(capacity + 1, 0);

        for (int weight = 0; weight <= capacity; weight++)
        {
            if (weight >= wt[0])
            {
                prev[weight] = (weight / wt[0]) * val[0];
            }
            else
            {
                prev[weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = 0; weight <= capacity; weight++)
            {
                int take = 0;
                if (weight >= wt[idx])
                {
                    take = val[idx] + curr[weight - wt[idx]];
                }

                int notTake = prev[weight];

                curr[weight] = max(take, notTake);
            }

            prev = curr;
        }

        return prev[capacity];
    }
};

// SUPER SPACE OPTIMISATION
class Solution
{
public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity)
    {
        // code here
        int n = val.size();
        vector<int> prev(capacity + 1, 0);

        for (int weight = 0; weight <= capacity; weight++)
        {
            if (weight >= wt[0])
            {
                prev[weight] = (weight / wt[0]) * val[0];
            }
            else
            {
                prev[weight] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int weight = 0; weight <= capacity; weight++)
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

        return prev[capacity];
    }
};
