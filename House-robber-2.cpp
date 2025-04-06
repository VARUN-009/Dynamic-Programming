// MEMOISATION
class Solution
{
public:
    // used this as constraint for number of houses max is 100 so +1 for safety.
    int dp[101];
    int helper(int idx, vector<int> &nums)
    {
        // base case
        if (idx >= nums.size())
        {
            return 0;
        }

        if (dp[idx] != -1)
        {
            return dp[idx];
        }

        return dp[idx] = max(nums[idx] + helper(idx + 2, nums),
                             helper(idx + 1, nums));
    }
    int rob(vector<int> &nums)
    {
        // first and last same hi hai toh ye hi lelo na, 2 adjacent ni le sakte,
        // par agr ek hi hai toh usko lelo first leliya toh last ni le sakte
        // kyuki first and last are adjacent and last leliya toh first ni le
        // sakte, toh dono hi tareeke hi lelo and dekho kisme maximum aarha hai
        if (nums.size() == 1)
            return nums[0];
        memset(dp, -1, sizeof(dp));
        int ans = helper(1, nums);
        nums.pop_back();
        memset(dp, -1, sizeof(dp));
        ans = max(ans, helper(0, nums));
        return ans;
    }
};

// TABULATION - case mere 2 hi hai ki ek baar lena hai first wale ko and ek baar ni lena hai bss same as that of house robber 1.
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        // kai kai baar aise chotte chotte hi edge cases hote hai as mujhe ek baari na first lena and ek baari na last lena toh nanga nhayega kya nichodega kya agr sirf 1 hi element hai toh aise karege toh temp1 and temp2 dono khali vector hoge.
        if (n == 1)
            return nums[0];

        vector<int> temp1, temp2;
        for (int i = 0; i < n; i++)
        {
            // temp1 m first element ni hoga and temp2 m last element ni hoga.
            if (i != 0)
                temp1.push_back(nums[i]);

            if (i != n - 1)
                temp2.push_back(nums[i]);
        }

        int ans = 0;
        // jaroori ni ki har baari n+1 hi lena hai, yahan dekho n bhi touch ni hoga mera, 0 se n-1 hi jayega at max so good to take n
        // top down means base case se aage jana chotte se n tak ka safar karna
        vector<int> dp(n);
        dp[0] = temp1[0];
        for (int i = 1; i < n - 1; i++)
        {
            // m bhai left to right chl rha hu means from 0 to n-1. n-1 m mujhe mera answer mil jayega. ab agr m 2 ki jump laga sakta hu toh current value + 2 wali jump wali lelunga nhi laga sakta toh abhi tak jo hai ek kam wala vahi lelunga like ki 2 size hai toh 0 liya toh 1 nhi le sakta, 1 liya toh 0 ni toh 1st bucket m max store hoga ki 0 lu ya 1.
            int taken = temp1[i];
            if (i - 2 >= 0)
            {
                taken += dp[i - 2];
            }
            int noTaken = dp[i - 1];
            dp[i] = max(taken, noTaken);
        }

        // why n-2 as dekho ab usme n nhi n-1 elements hai kyuki 1 1 hum le hi ni rahe hai and n m agr ans n-1 m tha toh n-1 size m toh n-2 m hoga na 4 element hai 0 1 2 3 toh 3rd index m mujhe mera answer mil jayega.
        ans = max(ans, dp[n - 2]);

        dp.resize(n, -1);

        // jaroori ni ki har baari n+1 hi lena hai, yahan dekho n bhi touch ni hoga mera, 0 se n-1 hi jayega at max so good to take n
        // top down means base case se aage jana chotte se n tak ka safar karna
        vector<int> dp(n);
        dp[0] = temp2[0];
        for (int i = 1; i < n - 1; i++)
        {
            // m bhai left to right chl rha hu means from 0 to n-1. n-1 m mujhe mera answer mil jayega. ab agr m 2 ki jump laga sakta hu toh current value + 2 wali jump wali lelunga nhi laga sakta toh abhi tak jo hai ek kam wala vahi lelunga like ki 2 size hai toh 0 liya toh 1 nhi le sakta, 1 liya toh 0 ni toh 1st bucket m max store hoga ki 0 lu ya 1.
            int taken = temp2[i];
            if (i - 2 >= 0)
            {
                taken += dp[i - 2];
            }
            int noTaken = dp[i - 1];
            dp[i] = max(taken, noTaken);
        }

        ans = max(ans, dp[n - 2]);
        return ans;
    }
};

// SPACE OPTIMISATION
class Solution
{
private:
    int helper(vector<int> &nums)
    {
        int n = nums.size();

        // 1st index m ya toh 0th index lelu ya m i-2 toh ni kar sakta toh current prev2 then inko aage badhao ab 2nd index aayega toh prev2 can be taken so it will be equal to prev1 and prev1 will be current answer as of now. ki yaa toh bhai m just pehle wala le sakta hu ya m 2 jump maarke calculate kar sakta hu at the end answer will be in prev1
        // loop mera n m khatam hoga means i=n and n-1 m prev1 hoga and n-2 m prev2 toh answer mera prev1 m hoga na
        int prev1 = nums[0];
        int prev2 = 0;
        for (int i = 1; i < n; i++)
        {
            int take = nums[i];
            if (i - 2 >= 0)
            {
                // dp[i-2]
                take += prev2;
            }

            // matlab jo pehle tha vahi le rha hu abhi kuch add ni kar rha dp[i-1]
            int notTake = 0 + prev1;
            int curr = max(take, notTake);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        // kai kai baar aise chotte chotte hi edge cases hote hai as mujhe ek baari na first lena and ek baari na last lena toh nanga nhayega kya nichodega kya agr sirf 1 hi element hai toh aise karege toh temp1 and temp2 dono khali vector hoge.
        if (n == 1)
            return nums[0];

        vector<int> temp1, temp2;
        for (int i = 0; i < n; i++)
        {
            // temp1 m first element ni hoga and temp2 m last element ni hoga.
            if (i != 0)
                temp1.push_back(nums[i]);

            if (i != n - 1)
                temp2.push_back(nums[i]);
        }

        int ans = 0;
        ans = max(ans, helper(temp1));
        ans = max(ans, helper(temp2));
        return ans;
    }
};
