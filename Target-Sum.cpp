// MEMOISATION
class Solution
{
private:
    int helper(int idx, vector<int> &nums, int target, vector<vector<int>> &dp)
    {
        // base case
        // 0 ke liye ye case use karna padega kyuki agr pehle wale use kiye toh target 0 it will directly return 1 but hume har possibility check karni hai toh jab m end m pahoch gya and abhi bhi mera target 0 hai toh return 1.
        if (idx == nums.size())
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
        int notTake = helper(idx + 1, nums, target, dp);
        if (nums[idx] <= target)
        {
            take = helper(idx + 1, nums, target - nums[idx], dp);
        }

        return dp[idx][target] = take + notTake;
    }

public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int required = (totalSum - target) / 2;

        if (totalSum - target < 0 || (totalSum - target) % 2 == 1)
        {
            return 0;
        }

        vector<vector<int>> dp(n + 1, vector<int>(required + 1, -1));
        return helper(0, nums, required, dp);
    }
};
/*
Can also be done ki isko lena hai ya isko subtract karna hai par usme target hamara negative m jaa sakta hai toh usme dikakt ho jayegi
*/

// TABULATION
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int required = (totalSum - target) / 2;
        // ab isme 2 cheeje hai totalSum - target mera even hona chahiye jabhi toh mera 2 se divide hoga and also totalSum - target mera negative ni hona chahiye negative toh ni laa paunga and odd hua toh usko 2 se divide karke decimal m toh la ni sakta
        if ((totalSum - target) % 2 == 1 || totalSum - target < 0)
        {
            return 0;
        }
        vector<vector<int>> dp(n + 1, vector<int>(required + 1, 0));

        // base case tha ki agr idx==n then agr target=0 hai toh 1 else 0. toh else wala jo case hai vo initialisation m hi cover karliya hai as sabko hi 0 kardiya hai bss ab idx==n and target=0 ko 1 kardo bss else everything is same.
        dp[n][0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int sum = 0; sum <= required; sum++)
            {
                int take = 0;
                int notTake = dp[idx + 1][sum];
                if (nums[idx] <= sum)
                {
                    take = dp[idx + 1][sum - nums[idx]];
                }

                dp[idx][sum] = take + notTake;
            }
        }

        return dp[0][required];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int required = (totalSum - target) / 2;
        // ab isme 2 cheeje hai totalSum - target mera even hona chahiye jabhi toh mera 2 se divide hoga and also totalSum - target mera negative ni hona chahiye negative toh ni laa paunga and odd hua toh usko 2 se divide karke decimal m toh la ni sakta
        if ((totalSum - target) % 2 == 1 || totalSum - target < 0)
        {
            return 0;
        }
        vector<int> prev(required + 1, 0), curr(required + 1, 0);

        // base case tha ki agr idx==n then agr target=0 hai toh 1 else 0. toh else wala jo case hai vo initialisation m hi cover karliya hai as sabko hi 0 kardiya hai bss ab idx==n and target=0 ko 1 kardo bss else everything is same.
        prev[0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int sum = 0; sum <= required; sum++)
            {
                int take = 0;
                int notTake = prev[sum];
                if (nums[idx] <= sum)
                {
                    take = prev[sum - nums[idx]];
                }

                curr[sum] = take + notTake;
            }

            prev = curr;
        }

        return prev[required];
    }
};
