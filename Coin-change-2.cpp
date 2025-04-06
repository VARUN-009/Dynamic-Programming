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
                return 1;
            }
            else
            {
                return 0;
            }
        }

        if (dp[idx][amount] != -1)
        {
            return dp[idx][amount];
        }

        // recursive case
        int take = 0;
        if (coins[idx] <= amount)
        {
            take = memoisation(idx, coins, amount - coins[idx], dp);
        }
        int notTake = memoisation(idx - 1, coins, amount, dp);

        return dp[idx][amount] = take + notTake;
    }
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        return memoisation(n - 1, coins, amount, dp);
    }
};

// TABULATION
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                dp[0][amt] = 1LL;
            }
            else
            {
                dp[0][amt] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 0;
                if (coins[idx] <= amt)
                {
                    take = dp[idx][amt - coins[idx]];
                }
                int notTake = dp[idx - 1][amt];

                dp[idx][amt] = (long long)take + notTake;
            }
        }

        return dp[n - 1][amount];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<long long> prev(amount + 1, 0), curr(amount + 1, 0);

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                prev[amt] = 1LL;
            }
            else
            {
                prev[amt] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 0;
                if (coins[idx] <= amt)
                {
                    take = curr[amt - coins[idx]];
                }
                int notTake = prev[amt];

                curr[amt] = (long long)take + notTake;
            }

            prev = curr;
        }

        return prev[amount];
    }
};


// SUPER SPACE OPTIMISATION
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<long long> prev(amount + 1, 0);

        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
            {
                prev[amt] = 1LL;
            }
            else
            {
                prev[amt] = 0;
            }
        }

        for (int idx = 1; idx < n; idx++)
        {
            // iske andar 0 se amount karna padega kyuki agr ulta kardega toh tu pehle hi purani values use karlega nayi values use karne bina which will give wrong answer.
            for (int amt = 0; amt <= amount; amt++)
            {
                int take = 0;
                if (coins[idx] <= amt)
                {
                    take = prev[amt - coins[idx]];
                }
                int notTake = prev[amt];

                prev[amt] = (long long)take + notTake;
            }
        }

        return prev[amount];
    }
};

/*
Knapsack (Maximize Value) → Pichle valid state ka use karke aage badhna hai → (amount → 0)
Coin Change (Minimize Coins) → Latest best possible answer chahiye → (0 → amount)

like ki knapsack m mujhe maximum chahiye value toh kya pta naya values m le na saku toh mujhe purana data ke hisaab sedekhna hai toh amount se 0 but coin change m mujhe minimum coins chahiy etoh mujhe latest data do ki kya pta km coinsm kaam chl jaye toh iss waajh se 0 se amount
*/