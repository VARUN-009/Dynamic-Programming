// MEMOISATION
class Solution
{
private:
    int helper(int idx, vector<int> &prices, int alreadyBuy,
               vector<vector<int>> &dp)
    {
        // base case
        // tu last m aagya tere pass ab shares hi ni bache toh kya khareedega
        // aur bechega toh return 0 agr stock le bhi rakha hai toh bech toh
        // payega ni toh 0
        if (idx >= prices.size())
        {
            return 0;
        }

        // DP
        if (dp[idx][alreadyBuy] != -1)
        {
            return dp[idx][alreadyBuy];
        }
        // recursive case
        // abhi tak ka profit maan ke chlo 0 and agr meine pehle buy kar rakha
        // hai toh ab 2 choice hai ki ab bechdu ya aage bechu. Abhi becha means
        // sell means tere pass se kuch gaya means ki paisa aaya kyuki sell karke toh paisa hi aata hai toh +prices[idx];
        int profit = 0;
        if (alreadyBuy)
        {
            int sell = prices[idx] + helper(idx + 2, prices, 0, dp);
            int notSell = helper(idx + 1, prices, 1, dp);
            profit = max(sell, notSell);
        }

        // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
        // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
        // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]
        else
        {
            int buy = -prices[idx] + helper(idx + 1, prices, 1, dp);
            int notBuy = helper(idx + 1, prices, 0, dp);
            profit = max(buy, notBuy);
        }

        return dp[idx][alreadyBuy] = profit;
    }

public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        return helper(0, prices, 0, dp);
    }
};

// TABULATION
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        // base case ye tha ki last row hai toh sab 0 hai toh already covered in initialisation.
        // m pehle 0 se n jaa rha tha ab n se 0. n wala hogya toh n-1 to 0.  alreadyBuy ki value 0 se 1 ab 1 se 0
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int alreadyBuy = 1; alreadyBuy >= 0; alreadyBuy--)
            {
                int profit = 0;
                if (alreadyBuy)
                {
                    int sell = prices[idx] + dp[idx + 2][0];
                    int notSell = dp[idx + 1][1];
                    profit = max(sell, notSell);
                }

                // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
                // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
                // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]
                else
                {
                    int buy = -prices[idx] + dp[idx + 1][1];
                    int notBuy = dp[idx + 1][0];
                    profit = max(buy, notBuy);
                }

                dp[idx][alreadyBuy] = profit;
            }
        }

        // upr return 0, 0 kar rha tha and yahan bhi same.
        return dp[0][0];
    }
};

// TIME OPTIMISATION
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        // base case ye tha ki last row hai toh sab 0 hai toh already covered in initialisation.
        // m pehle 0 se n jaa rha tha ab n se 0. n wala hogya toh n-1 to 0.  alreadyBuy ki value 0 se 1 ab 1 se 0
        for (int idx = n - 1; idx >= 0; idx--)
        {
            // iske andar alreadyBuy ki value 0 hogi ya 1 so end m dp[idx][0, 1] so bina loop ke kardo

            int sell = prices[idx] + dp[idx + 2][0];
            int notSell = dp[idx + 1][1];
            dp[idx][1] = max(sell, notSell);

            // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
            // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
            // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]

            int buy = -prices[idx] + dp[idx + 1][1];
            int notBuy = dp[idx + 1][0];
            dp[idx][0] = max(buy, notBuy);
        }

        // upr return 0, 0 kar rha tha and yahan bhi same.
        return dp[0][0];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> next2(2, 0), next1(2, 0), curr(2, 0);

        // base case ye tha ki last row hai toh sab 0 hai toh already covered in initialisation.
        // m pehle 0 se n jaa rha tha ab n se 0. n wala hogya toh n-1 to 0.  alreadyBuy ki value 0 se 1 ab 1 se 0
        for (int idx = n - 1; idx >= 0; idx--)
        {
            // iske andar alreadyBuy ki value 0 hogi ya 1 so end m dp[idx][0, 1] so bina loop ke kardo

            int sell = prices[idx] + next2[0];
            int notSell = next1[1];
            curr[1] = max(sell, notSell);

            // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
            // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
            // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]

            int buy = -prices[idx] + next1[1];
            int notBuy = next1[0];
            curr[0] = max(buy, notBuy);

            next2 = next1;
            next1 = curr;
        }

        // upr return 0, 0 kar rha tha and yahan bhi same.
        return next1[0];
    }
};
