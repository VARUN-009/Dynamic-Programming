class Solution
{
public:
    int dp[100001][3][2];
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
    int maxProfit(vector<int> &prices)
    {
        memset(dp, -1, sizeof(dp));
        return helper(prices, 0, 2, 1);
    }
};
/*
Tum khareed bhi sakte ho ek din m and nhi bhi khareed sakte toh at a day, you
have choice ki tum khareedo ya ni, toh recursion toh tumhe poore question ka
answer dedega ki bhai poora as a whole ka answer kya hoga.
1. agr ni khareeda toh bss aage badho and recursion ko bolo ki aage ka answer
bta
2. agr khareed liya toh same day toh bech ni sakte na, toh check karo ki kis din
bechu.
3. -Prices[idx] because m le rha hu khareed rha hu toh uski cost lagegi na toh
-. other way to understand this is that ki isko khareedne ke baad jab aage
bechoge toh toh jab dono ki cost + hogi toh ultimately you will get the profit.


Recursion TC - O(exponential) + O(n) n shares

*/

// TABULATION
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // in the form of [idx][k][alreadyBuy]
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(3, vector<int>(2, 0)));

        // base case tha ki idx == prices.size() || k==0 toh return 0 so meine abhi toh sab m hi 0 laga diya so it is already covered

        for (int idx = n - 1; idx >= 0; idx--)
        {
            // for every k=0, we have already done in the base ki put 0 so what we can do is that start k from 1 else if you start from 0, toh k-1 wale m condition lagani padegi ki k > 0 hai ya ni
            for (int k = 1; k < 3; k++)
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
                        int abhiKhareeda = -prices[idx] + dp[idx + 1][k][0];

                        // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                        // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                        // na jab bech diya, tab jakr 1 transaction hogi tumahri
                        int abhiNhiKhareeda = dp[idx + 1][k][alreadyBuy];
                        profit = max(abhiKhareeda, abhiNhiKhareeda);
                    }
                    // wantToSell
                    else
                    {
                        // sell kiya , ek transaction km hui toh k-1, and alreadyBuy = 1
                        // because ab m khareedna chahta hu
                        int abhiSellKiya = prices[idx] + dp[idx + 1][k - 1][1];

                        // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                        // transaction ni hui na koi and also alreadyBuy will be 0 because
                        // abhi becah ni hai na jo khareeda tha
                        int abhiSellNhiKiya = dp[idx + 1][k][0];
                        profit = max(abhiSellKiya, abhiSellNhiKiya);
                    }

                    dp[idx][k][alreadyBuy] = profit;
                }
            }
        }

        return dp[0][2][1];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // in the form of [idx][k][alreadyBuy]
        vector<vector<int>> next(3, vector<int>(2, 0)), curr(3, vector<int>(2, 0));

        // base case tha ki idx == prices.size() || k==0 toh return 0 so meine abhi toh sab m hi 0 laga diya so it is already covered

        for (int idx = n - 1; idx >= 0; idx--)
        {
            // for every k=0, we have already done in the base ki put 0 so what we can do is that start k from 1 else if you start from 0, toh k-1 wale m condition lagani padegi ki k > 0 hai ya ni
            for (int k = 1; k < 3; k++)
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
                        int abhiKhareeda = -prices[idx] + next[k][0];

                        // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                        // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                        // na jab bech diya, tab jakr 1 transaction hogi tumahri
                        int abhiNhiKhareeda = next[k][alreadyBuy];
                        profit = max(abhiKhareeda, abhiNhiKhareeda);
                    }
                    // wantToSell
                    else
                    {
                        // sell kiya , ek transaction km hui toh k-1, and alreadyBuy = 1
                        // because ab m khareedna chahta hu
                        int abhiSellKiya = prices[idx] + next[k - 1][1];

                        // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                        // transaction ni hui na koi and also alreadyBuy will be 0 because
                        // abhi becah ni hai na jo khareeda tha
                        int abhiSellNhiKiya = next[k][0];
                        profit = max(abhiSellKiya, abhiSellNhiKiya);
                    }

                    curr[k][alreadyBuy] = profit;
                }

                next = curr;
            }
        }

        return next[2][1];
    }
};
/*
TC - O(n*2*3)
SC - O(6)
*/

////////////////////////////////////// USING N*4 space ////////////////////////////////////////////
// MEMOISATION
class Solution
{
public:
    int dp[100001][5];
    int helper(vector<int> &prices, int idx, int k)
    {
        // base case
        if (idx >= prices.size() || k == 4)
        {
            return 0;
        }

        if (dp[idx][k] != -1)
        {
            return dp[idx][k];
        }

        // recursive case
        int profit = 0;
        // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
        // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
        // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
        // jaye and profit aajaye.
        if (k % 2 == 0)
        {
            // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
            // nhi buy karna chahta baad m sell karunga pehle
            // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
            // -prices[idx] bechege toh fayda toh prices[idx]
            int abhiKhareeda = -prices[idx] + helper(prices, idx + 1, k + 1);

            // nhi khareeda toh aage badho, aage khareedunga, transaction toh
            // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
            // na jab bech diya, tab jakr 1 transaction hogi tumahri
            int abhiNhiKhareeda = helper(prices, idx + 1, k);
            profit = max(abhiKhareeda, abhiNhiKhareeda);
        }
        // wantToSell
        else
        {
            // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
            // because ab m khareedna chahta hu
            int abhiSellKiya = prices[idx] + helper(prices, idx + 1, k + 1);

            // abhi sell ni kiya toh aage kar, and k will remain same kyuki
            // transaction ni hui na koi and also wantToBuy will be 0 because
            // abhi becah ni hai na jo khareeda tha
            int abhiSellNhiKiya = helper(prices, idx + 1, k);
            profit = max(abhiSellKiya, abhiSellNhiKiya);
        }

        return dp[idx][k] = profit;
    }
    int maxProfit(vector<int> &prices)
    {
        // possible states are 0, 1, 2, 3 so 4 size liya toh 3 tak hi but k==4 bhi hai toh for this take 5 size.
        memset(dp, -1, sizeof(dp));
        return helper(prices, 0, 0);
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
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // base case is idx >= prices.size() || k == 4 already covered in initialisation so no need to do it.
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int k = 3; k >= 0; k--)
            {
                int profit = 0;
                // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                // jaye and profit aajaye.
                if (k % 2 == 0)
                {
                    // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
                    // nhi buy karna chahta baad m sell karunga pehle
                    // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                    // -prices[idx] bechege toh fayda toh prices[idx]
                    int abhiKhareeda = -prices[idx] + dp[idx + 1][k + 1];

                    // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                    // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                    // na jab bech diya, tab jakr 1 transaction hogi tumahri
                    int abhiNhiKhareeda = dp[idx + 1][k];
                    profit = max(abhiKhareeda, abhiNhiKhareeda);
                }
                // wantToSell
                else
                {
                    // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
                    // because ab m khareedna chahta hu
                    int abhiSellKiya = prices[idx] + dp[idx + 1][k + 1];

                    // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                    // transaction ni hui na koi and also wantToBuy will be 0 because
                    // abhi becah ni hai na jo khareeda tha
                    int abhiSellNhiKiya = dp[idx + 1][k];
                    profit = max(abhiSellKiya, abhiSellNhiKiya);
                }

                dp[idx][k] = profit;
            }
        }
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
        vector<int> next(5, 0), curr(5, 0);

        // base case is idx >= prices.size() || k == 4 already covered in initialisation so no need to do it.
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int k = 3; k >= 0; k--)
            {
                int profit = 0;
                // mein khareedna chahta hu, toh ya toh m abhi khareedu ya m baad wale
                // din m khareedta hu, abhi khareeda toh -proces[idx] liya jiss se ki
                // aage jab bechu toh jo uski value add karunga na, vo isme se minus ho
                // jaye and profit aajaye.
                if (k % 2 == 0)
                {
                    // khareed liya toh pehle bechna padega na toh wantToBuy = 0 ki haa
                    // nhi buy karna chahta baad m sell karunga pehle
                    // aise bhi keh sakte hai ki khareeda h toh ghata hua hai, toh
                    // -prices[idx] bechege toh fayda toh prices[idx]
                    int abhiKhareeda = -prices[idx] + next[k + 1];

                    // nhi khareeda toh aage badho, aage khareedunga, transaction toh
                    // kisi m nhi ki hai toh k will remain same na, transaction tab hogi
                    // na jab bech diya, tab jakr 1 transaction hogi tumahri
                    int abhiNhiKhareeda = next[k];
                    profit = max(abhiKhareeda, abhiNhiKhareeda);
                }
                // wantToSell
                else
                {
                    // sell kiya , ek transaction km hui toh k-1, and wantToBuy = 1
                    // because ab m khareedna chahta hu
                    int abhiSellKiya = prices[idx] + next[k + 1];

                    // abhi sell ni kiya toh aage kar, and k will remain same kyuki
                    // transaction ni hui na koi and also wantToBuy will be 0 because
                    // abhi becah ni hai na jo khareeda tha
                    int abhiSellNhiKiya = next[k];
                    profit = max(abhiSellKiya, abhiSellNhiKiya);
                }

                curr[k] = profit;
            }

            next = curr;
        }
        return next[0];
    }
};


