class Solution
{
private:
    int helper(int idx, vector<int> &prices, int alreadyBuy, int fee,
               vector<vector<int>> &dp)
    {
        // base case
        // tu last m aagya tere pass ab shares hi ni bache toh kya khareedega
        // aur bechega toh return 0 agr stock le bhi rakha hai toh bech toh
        // payega ni toh 0
        if (idx == prices.size())
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
            int sell = prices[idx] + helper(idx + 1, prices, 0, fee, dp) - fee;
            int notSell = helper(idx + 1, prices, 1, fee, dp);
            profit = max(sell, notSell);
        }

        // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
        // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
        // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]
        else
        {
            int buy = -prices[idx] + helper(idx + 1, prices, 1, fee, dp);
            int notBuy = helper(idx + 1, prices, 0, fee, dp);
            profit = max(buy, notBuy);
        }

        return dp[idx][alreadyBuy] = profit;
    }

public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        return helper(0, prices, 0, fee, dp);
    }
};
/*
1. Express everything in terms of idx, buy
2. Explore possibilities on that day
3. Take the max of all profits made
4. Base case

Recursion - O(2^n) O(n)
TC - O(n*2) + O(n)
SC - O(n*2)
*/

// TABULATION
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int alreadyBuy = 1; alreadyBuy >= 0; alreadyBuy--)
            {
                int profit = 0;
                if (alreadyBuy)
                {
                    int sell = prices[idx] + dp[idx + 1][0] - fee;
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

        return dp[0][0];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        vector<int> next(2, 0), curr(2, 0);

        // base case ye tha ki last row hai toh sab 0 hai toh already covered in initialisation.
        // m pehle 0 se n jaa rha tha ab n se 0. n wala hogya toh n-1 to 0.  alreadyBuy ki value 0 se 1 ab 1 se 0
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int alreadyBuy = 1; alreadyBuy >= 0; alreadyBuy--)
            {
                int profit = 0;
                if (alreadyBuy)
                {
                    int sell = prices[idx] + next[0] - fee;
                    int notSell = next[1];
                    profit = max(sell, notSell);
                }

                // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
                // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
                // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]
                else
                {
                    int buy = -prices[idx] + next[1];
                    int notBuy = next[0];
                    profit = max(buy, notBuy);
                }

                curr[alreadyBuy] = profit;
            }

            next = curr;
        }

        // upr return 0, 0 kar rha tha and yahan bhi same.
        return next[0];
    }
};
/*
can also be done via 4 variables - alreadyBuy next[0], alreadyBuy next[1], notBuy next[0], notBuy next[1]

*/

// SPACE OPTIMISATION USING VARIABLES
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int nextBuy, nextNotBuy, currBuy, currNotBuy;

        // last row ka pta hona chahiye tha toh ye last ke variables hai inko 0 kardo
        nextBuy = nextNotBuy = 0;

        // base case ye tha ki last row hai toh sab 0 hai toh already covered in initialisation.
        for (int idx = n - 1; idx >= 0; idx--)
        {

            // dono jo jo conditions toh unko direct likh diya ek currBuy ki thi ki buy kar rakha hai and ek currNotBuy ki thi ki buy ni kar rakha hai
            int sell = prices[idx] + nextNotBuy - fee;
            int notSell = nextBuy;
            currBuy = max(sell, notSell);

            // agr pehle buy ni kara means 2 options hai ki abhi buy karlo and abhi
            // bhi buy na karo aage buy karna ab. Abhi buy kiya means tunne leliya
            // toh lena means khareedna and khareedne ke lagte hai paise toh tumne paise diye means -prices[idx]

            int buy = -prices[idx] + nextBuy;
            int notBuy = nextNotBuy;
            currNotBuy = max(buy, notBuy);

            // ab switch karna tha toh
            nextBuy = currBuy;
            nextNotBuy = currNotBuy;
        }

        // upr return 0, 0 kar rha tha and yahan bhi same.
        return nextNotBuy;
    }
};