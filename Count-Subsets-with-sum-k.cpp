// MEMOISATION
class Solution
{
private:
    int helper(int idx, vector<int> &arr, int target, vector<vector<int>> &dp)
    {
        // base case
        // 0 ke liye ye case use karna padega kyuki agr pehle wale use kiye toh target 0 it will directly return 1 but hume har possibility check karni hai toh jab m end m pahoch gya and abhi bhi mera target 0 hai toh return 1.
        if (idx == arr.size())
        {
            return (target == 0) ? 1 : 0;
        }

        // DP
        if (dp[idx][target] != -1)
        {
            return dp[idx][target];
        }

        // recursive case
        // ab isme le sakta hu toh usme dono ko add ni karna ki ni lena and lena as nhi lena wala kara and vo m neeche bhi kar rha hu toh repeated ho jayega toh wrong answer dega. le sakta hu toh leta hu and ni le sakta toh ni letahu and then dono ka sum. 
        int take = 0;
        int notTake = helper(idx + 1, arr, target, dp);
        if (arr[idx] <= target)
        {
            take = helper(idx + 1, arr, target - arr[idx], dp);
        }

        return dp[idx][target] = take + notTake;
    }

public:
    int perfectSum(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
        return helper(0, arr, target, dp);
    }
};

/*
Count all the ways
Whenever there is a problem related to count, then you return 1 when you have found one basically when the condition is me and not met you return 0 then all the function calls will be added and thus you will get the answer.

0 10 0 target=0 for this ans is 4 {}, 0, 0, 0,0
empty bhi hoga na as m agr kuch na lu tab bhi target toh achieve ho hi rha hai.

recursion TC - O(2^n) SC - O(n) 

It can also be done jaise pehle kar tha same bss jo ans aayega usko pow(2,no_of_zeroes) * ans(previously jo aarha tha)
*/

// TABULATION
class Solution
{
public:
    int perfectSum(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        // base case tha ki agr idx==n then agr target=0 hai toh 1 else 0. toh else wala jo case hai vo initialisation m hi cover karliya hai as sabko hi 0 kardiya hai bss ab idx==n and target=0 ko 1 kardo bss else everything is same.
        dp[n][0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int sum = 0; sum <= target; sum++)
            {
                int take = 0;
                int notTake = dp[idx + 1][sum];
                if (arr[idx] <= sum)
                {
                    take = dp[idx + 1][sum - arr[idx]];
                }

                dp[idx][sum] = take + notTake;
            }
        }

        return dp[0][target];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int perfectSum(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<int> prev(target + 1, 0), curr(target + 1, 0);

        // har baari karne ki need ni hai bss ek baari kardo as last row m hi karna tha baaki sab same hai 
        prev[0] = curr[0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int sum = 0; sum <= target; sum++)
            {
                int take = 0;
                int notTake = prev[sum];
                if (arr[idx] <= sum)
                {
                    take = prev[sum - arr[idx]];
                }

                curr[sum] = take + notTake;
            }

            prev = curr;
        }

        return prev[target];
    }
};