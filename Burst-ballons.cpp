// MEMOISATION
class Solution
{
private:
    int helper(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
    {
        // base case
        // elements hi ni hai toh phir 0 coins
        if (i > j)
        {
            return 0;
        }

        // DP
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // recursive case
        int coins = -1e9;
        // till j because m last element bhi toh le sakta hu na and first element bhi le sakta hu bss as a starting element.
        for (int idx = i; idx <= j; idx++)
        {
            // not like MCM, m single element se start karunga and will go from bottom to top.
            int value = nums[i - 1] * nums[idx] * nums[j + 1];
            int left = helper(i, idx - 1, nums, dp);
            int right = helper(idx + 1, j, nums, dp);
            value += (left + right);
            coins = max(coins, value);
        }

        return dp[i][j] = coins;
    }

public:
    int maxCoins(vector<int> &nums)
    {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));
        return helper(1, n - 2, nums, dp);
    }
};
/*
1. isme m upr se neeche nhi neeche se upr jaa rha hu means sab elements m se ek element ni start hi kar rha hu single element se kyuki at the end 1 hi element bachega na. Bottom to top jaa rha hu. M ulta ni jaa sakta kyuki phir jo meri subproblems hai vo independent ni hogi ek dusre m dependent hogi. And mujhe ye bhi ni pta na m left m konsa element lu and right m konsa as koi bhi le sakta hu so that's why start with single element then left and right m jo bhi sum aaye plus.

** To know ki konsa size ka lena hai DP array just see ki jo jo parameters change ho rahe hai vo konsi konsi values m jaa sakte hai and max konsi value touch karege - here j plus hoke ek dum last m bhi jaa sakta hai and and i minus hoke ek dum starting toh initially 4 elements so 0,1,2,3 then add 1 1 so i starts from 1 to 4+1=5 to n=6 jab hi 0 to 5 ka banega index.

TC (Recursion) = Exponential
TC - O(n*n) * O(n) ~ O(n^3) -- changing states dekho and vo total kitne time change ho sakti hai toh total states i and j and both till n can change -- basically dekho ki konsi konsi states m program ja sakta hai toh dp size so n*n and O(n) for a loop inside function. n tak ni chlega ek dum par around n estimate.

SC - O(n*n) + O(n) auxillary stack space
*/

// TABULATION
class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();

        // base case is already covered in this as humne sabko hi 0 bna diya - generic hai ye base case simple toh direct initialisation ke time bhi kar sakte hai
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // call meri 1 se start ho rahi thi toh tu ulta start kar as you have to go from bottom to top. 1 to last element in original array
        // Similarly j mera n-2 se start ho rha tha so ulta karo 1 to n-2 
        // hume 1 element touch ni karna hume uss se pehle tak ka hi dekhna hai toh uske acc loop ki conditions.
        for (int i = n - 2; i >= 1; i--)
        {
            for (int j = 1; j <= n - 2; j++)
            {
                // out of bound hai toh nhi karna kuch
                if (i > j)
                    continue;
                // recursive case
                int coins = -1e9;
                // till j because m last element bhi toh le sakta hu na and first element bhi le sakta hu bss as a starting element.
                for (int idx = i; idx <= j; idx++)
                {
                    // not like MCM, m single element se start karunga and will go from bottom to top.
                    int value = nums[i - 1] * nums[idx] * nums[j + 1];
                    int left = dp[i][idx - 1];
                    int right = dp[idx + 1][j];
                    value += (left + right);
                    coins = max(coins, value);
                }

                dp[i][j] = coins;
            }
        }

        return dp[1][n - 2];
    }
};
/*
TC - O(n^3)
SC - O(n*n)

*/