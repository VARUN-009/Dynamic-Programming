// MEMOISATION
class Solution
{
public:
    int memoisation(int idx, vector<int> &coins, int amount, vector<vector<int>> &dp)
    {
        // base case
        if (idx == 0)
        {
            // last coin m hai tu agr tu amoount ko 0 kar sakta hai toh sahi hai warna bhul jao ji toh if amount is divisible by the coin then take required coins else return 0.
            if (amount % coins[0] == 0)
            {
                return amount / coins[0];
            }
            else
            {
                return 1e9;
            }
        }

        if (dp[idx][amount] != -1)
        {
            return dp[idx][amount];
        }

        // recursive case
        int take = 1e9;
        if (coins[idx] <= amount)
        {
            take = 1 + memoisation(idx, coins, amount - coins[idx], dp);
        }
        int notTake = memoisation(idx - 1, coins, amount, dp);

        return dp[idx][amount] = min(take, notTake);
    }
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        int ans = memoisation(n - 1, coins, amount, dp);
        return (ans == 1e9) ? -1 : ans;
    }
};
/*
Recursion TC - >>> O(2^n) as lene ke baad bhi you can again take it SC - >>> O(n) at max SC - O(target) ki ek ek karke target ko km kar rahe ho 
TC - O(n*amount) + O(n)
SC - O(n*amount);
Whenever there is infinite supply of something or multiple use then take m idx-1 ni karega same hi jagah rahega.

In memoisation tum humesha saari states m ni visit karte par tabulation m saari states m visit karte ho toh aisa bhi ho sakta hai ki kabhi kabhi tabulation TLE dede.
*/

// TABULATION
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                dp[0][amt] = amt / coins[0];
            }
            else
            {
                dp[0][amt] = 1e9;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 1e9;
                if (coins[idx] <= amt)
                {
                    take = 1 + dp[idx][amt - coins[idx]];
                }
                int notTake = dp[idx - 1][amt];

                dp[idx][amt] = min(take, notTake);
            }
        }

        return dp[n - 1][amount] == 1e9 ? -1 : dp[n - 1][amount];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<int> prev(amount + 1, 0), curr(amount+1, 0);

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                prev[amt] = amt / coins[0];
            }
            else
            {
                prev[amt] = 1e9;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 1e9;
                if (coins[idx] <= amt)
                {
                    take = 1 + curr[amt - coins[idx]];
                }
                int notTake = prev[amt];

                curr[amt] = min(take, notTake);
            }

            prev = curr;
        }

        return prev[amount] == 1e9 ? -1 : prev[amount];
    }
};


// SUPER SPACE OPTIMISATION
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<int> prev(amount + 1, 0);

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                prev[amt] = amt / coins[0];
            }
            else
            {
                prev[amt] = 1e9;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            // iske andar 0 se amount karna padega kyuki agr ulta kardega toh tu pehle hi purani values use karlega nayi values use karne bina which will give wrong answer.
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 1e9;
                if (coins[idx] <= amt)
                {
                    take = 1 + prev[amt - coins[idx]];
                }
                int notTake = prev[amt];

                prev[amt] = min(take, notTake);
            }
        }

        return prev[amount] == 1e9 ? -1 : prev[amount];
    }
};