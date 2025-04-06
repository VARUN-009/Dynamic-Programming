class Solution
{
public:
    int dp[100001][101][2];
    int helper(vector<int> &prices, int idx, int k, int wantToBuy)
    {
        // base case
        if (idx >= prices.size() || k == 0)
        {
            return 0;
        }

        if (dp[idx][k][wantToBuy] != -1)
        {
            return dp[idx][k][wantToBuy];
        }

        // recursive case
        int profit = 0;
        // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
        // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
        // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
        // jaye and profit aajaye.
        if (wantToBuy)
        {
            // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
            // nhi buy karna chahta baad m sell karunga pehle
            // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
            // -prices[idx] bechege toh fayda toh prices[idx]
            int abhiKhareeda = -prices[idx] + helper(prices, idx + 1, k, 0);

            // nhi khareeda toh aage badho, aage khareedunga, transaction toh
            // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
            // na jab bech diya, tab jakr 1 transaction hogi tumahri
            int abhiNhiKhareeda = helper(prices, idx + 1, k, wantToBuy);
            profit = max(abhiKhareeda, abhiNhiKhareeda);
        }
        // wantToSell
        else
        {
            // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
            // because ab m khareedna chahta hu
            int abhiSellKiya = prices[idx] + helper(prices, idx + 1, k - 1, 1);

            // abhi sell ni kiya toh aage kar, and k will remain same kyuki
            // transaction ni hui na koi and also wantToBuy will be 0 because
            // abhi becah ni hai na jo khareeda tha
            int abhiSellNhiKiya = helper(prices, idx + 1, k, 0);
            profit = max(abhiSellKiya, abhiSellNhiKiya);
        }

        return dp[idx][k][wantToBuy] = profit;
    }
    int maxProfit(int k, vector<int> &prices)
    {
        memset(dp, -1, sizeof(dp));
        return helper(prices, 0, k, 1);
    }
};

// TABULATION
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();

        // in the form of [idx][k][alreadyBuy]
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));

        // base case tha ki idx == prices.size() || k==0 toh return 0 so meine abhi toh sab m hi 0 laga diya so it is already covered

        for (int idx = n - 1; idx >= 0; idx--)
        {
            // for every k=0, we have already done in the base ki put 0 so what we can do is that start k from 1 else if you start from 0, toh k-1 wale m condition lagani padegi ki k > 0 hai ya ni
            for (int times = 1; times <= k; times++)
            {
                for (int alreadyBuy = 0; alreadyBuy <= 1; alreadyBuy++)
                {
                    int profit = 0;
                    // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                    // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                    // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                    // jaye and profit aajaye.
                    if (alreadyBuy)
                    {
                        // khareed liya toh pehle bechna padega na toh alreadyBuy = 0 ki haa
                        // nhi buy karna chahta baad m sell karunga pehle
                        // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                        // -prices[idx] bechege toh fayda toh prices[idx]
                        int abhiKhareeda = -prices[idx] + dp[idx + 1][times][0];

                        // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                        // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                        // na jab bech diya, tab jakr 1 transaction hogi tumahri
                        int abhiNhiKhareeda = dp[idx + 1][times][alreadyBuy];
                        profit = max(abhiKhareeda, abhiNhiKhareeda);
                    }
                    // wantToSell
                    else
                    {
                        // sell kiya , ek transaction km hui toh k-1, and alreadyBuy = 1
                        // because ab m khareedna chahta hu
                        int abhiSellKiya = prices[idx] + dp[idx + 1][times - 1][1];

                        // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                        // transaction ni hui na koi and also alreadyBuy will be 0 because
                        // abhi becah ni hai na jo khareeda tha
                        int abhiSellNhiKiya = dp[idx + 1][times][0];
                        profit = max(abhiSellKiya, abhiSellNhiKiya);
                    }

                    dp[idx][times][alreadyBuy] = profit;
                }
            }
        }

        return dp[0][k][1];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();

        // in the form of [idx][k][alreadyBuy]
        vector<vector<int>> next(k + 1, vector<int>(2, 0)), curr(k + 1, vector<int>(2, 0));

        // base case tha ki idx == prices.size() || k==0 toh return 0 so meine abhi toh sab m hi 0 laga diya so it is already covered

        for (int idx = n - 1; idx >= 0; idx--)
        {
            // for every k=0, we have already done in the base ki put 0 so what we can do is that start k from 1 else if you start from 0, toh k-1 wale m condition lagani padegi ki k > 0 hai ya ni
            for (int times = 1; times <= k; times++)
            {
                for (int alreadyBuy = 0; alreadyBuy <= 1; alreadyBuy++)
                {
                    int profit = 0;
                    // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                    // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                    // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                    // jaye and profit aajaye.
                    if (alreadyBuy)
                    {
                        // khareed liya toh pehle bechna padega na toh alreadyBuy = 0 ki haa
                        // nhi buy karna chahta baad m sell karunga pehle
                        // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                        // -prices[idx] bechege toh fayda toh prices[idx]
                        int abhiKhareeda = -prices[idx] + next[times][0];

                        // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                        // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                        // na jab bech diya, tab jakr 1 transaction hogi tumahri
                        int abhiNhiKhareeda = next[times][alreadyBuy];
                        profit = max(abhiKhareeda, abhiNhiKhareeda);
                    }
                    // wantToSell
                    else
                    {
                        // sell kiya , ek transaction km hui toh k-1, and alreadyBuy = 1
                        // because ab m khareedna chahta hu
                        int abhiSellKiya = prices[idx] + next[times - 1][1];

                        // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                        // transaction ni hui na koi and also alreadyBuy will be 0 because
                        // abhi becah ni hai na jo khareeda tha
                        int abhiSellNhiKiya = next[times][0];
                        profit = max(abhiSellKiya, abhiSellNhiKiya);
                    }

                    curr[times][alreadyBuy] = profit;
                }

                next = curr;
            }
        }

        return next[k][1];
    }
};
/*
TC - O(n*k*2)
SC - O(k*2)
*/

////////////////////////////////////// USING N*k space ////////////////////////////////////////////
// MEMOISATION
class Solution
{
public:
    int helper(vector<int> &prices, int idx, int k, int times, vector<vector<int>> &dp)
    {
        // base case
        if (idx >= prices.size() || times == 2 * k)
        {
            return 0;
        }

        if (dp[idx][times] != -1)
        {
            return dp[idx][times];
        }

        // recursive case
        int profit = 0;
        // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
        // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
        // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
        // jaye and profit aajaye.
        if (times % 2 == 0)
        {
            // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
            // nhi buy karna chahta baad m sell karunga pehle
            // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
            // -prices[idx] bechege toh fayda toh prices[idx]
            int abhiKhareeda = -prices[idx] + helper(prices, idx + 1, k, times + 1, dp);

            // nhi khareeda toh aage badho, aage khareedunga, transaction toh
            // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
            // na jab bech diya, tab jakr 1 transaction hogi tumahri
            int abhiNhiKhareeda = helper(prices, idx + 1, k, times, dp);
            profit = max(abhiKhareeda, abhiNhiKhareeda);
        }
        // wantToSell
        else
        {
            // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
            // because ab m khareedna chahta hu
            int abhiSellKiya = prices[idx] + helper(prices, idx + 1, k, times + 1, dp);

            // abhi sell ni kiya toh aage kar, and k will remain same kyuki
            // transaction ni hui na koi and also wantToBuy will be 0 because
            // abhi becah ni hai na jo khareeda tha
            int abhiSellNhiKiya = helper(prices, idx + 1, k, times, dp);
            profit = max(abhiSellKiya, abhiSellNhiKiya);
        }

        return dp[idx][times] = profit;
    }
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, -1));
        // possible states are 0, 1, 2, 3 so 4...k size hi but k==k bhi hai toh for this take k+1 size.
        return helper(prices, 0, k, 0, dp);
    }
};
/*
Iske andar k=2 hi tha bss toh meine kya kiya ki 2 transation hai toh aisi hogi B
S B S Buy sell so if index mera even toh buy and odd toh sell. so m 0 se 4 tak
chlunga bss.

*/

// TABULATION
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

        // base case is idx >= prices.size() || k == 4 already covered in initialisation so no need to do it.
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int times = 2 * k - 1; times >= 0; times--)
            {
                int profit = 0;
                // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                // jaye and profit aajaye.
                if (times % 2 == 0)
                {
                    // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
                    // nhi buy karna chahta baad m sell karunga pehle
                    // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                    // -prices[idx] bechege toh fayda toh prices[idx]
                    int abhiKhareeda = -prices[idx] + dp[idx + 1][times + 1];

                    // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                    // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                    // na jab bech diya, tab jakr 1 transaction hogi tumahri
                    int abhiNhiKhareeda = dp[idx + 1][times];
                    profit = max(abhiKhareeda, abhiNhiKhareeda);
                }
                // wantToSell
                else
                {
                    // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
                    // because ab m khareedna chahta hu
                    int abhiSellKiya = prices[idx] + dp[idx + 1][times + 1];

                    // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                    // transaction ni hui na koi and also wantToBuy will be 0 because
                    // abhi becah ni hai na jo khareeda tha
                    int abhiSellNhiKiya = dp[idx + 1][times];
                    profit = max(abhiSellKiya, abhiSellNhiKiya);
                }

                dp[idx][times] = profit;
            }
        }
        return dp[0][0];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        vector<int> next(2*k+1, 0), curr(2*k+1, 0);

        // base case is idx >= prices.size() || k == 4 already covered in initialisation so no need to do it.
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int times = 2*k-1; times >= 0; times--)
            {
                int profit = 0;
                // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                // jaye and profit aajaye.
                if (times % 2 == 0)
                {
                    // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
                    // nhi buy karna chahta baad m sell karunga pehle
                    // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                    // -prices[idx] bechege toh fayda toh prices[idx]
                    int abhiKhareeda = -prices[idx] + next[times + 1];

                    // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                    // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                    // na jab bech diya, tab jakr 1 transaction hogi tumahri
                    int abhiNhiKhareeda = next[times];
                    profit = max(abhiKhareeda, abhiNhiKhareeda);
                }
                // wantToSell
                else
                {
                    // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
                    // because ab m khareedna chahta hu
                    int abhiSellKiya = prices[idx] + next[times + 1];

                    // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                    // transaction ni hui na koi and also wantToBuy will be 0 because
                    // abhi becah ni hai na jo khareeda tha
                    int abhiSellNhiKiya = next[times];
                    profit = max(abhiSellKiya, abhiSellNhiKiya);
                }

                curr[times] = profit;
            }

            next = curr;
        }
        return next[0];
    }
};
