class Solution
{
private:
    int help(int idx, vector<int> &nums, int n, vector<int> &dp)
    {
        // base case
        // last element m aagya, iss se aage toh jaa ni sakta means ki ye lena hi padega as mujhe mera sum maximise karna hai toh
        if (idx == n - 1)
        {
            return nums[idx];
        }
        // agr mera bahar gya toh phir toh kuch ni milega means ki 0 milega
        if (idx >= n)
        {
            return 0;
        }

        // DP
        if (dp[idx] != -1)
        {
            return dp[idx];
        }

        // recursive case
        // call marne se pehle condition check bhi kar sakte hai ki 2 ki jump maar sakta hu ya ni agr yahin check karliya toh ek base case km ho jayega par agr ni check kiya toh upr ek base case add ho jayeaga ki agr bahar gaya toh return 0
        int taken = nums[idx] + help(idx + 2, nums, n, dp);
        int notTaken = help(idx + 1, nums, n, dp);

        return dp[idx] = max(taken, notTaken);
    }

public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();

        // jaroori ni ki har baari n+1 hi lena hai, yahan dekho n bhi touch ni hoga mera, 0 se n-1 hi jayega at max so good to take n
        vector<int> dp(n, -1);
        return help(0, nums, n, dp);
    }
};
/*
Recursion se karege toh O(2^n) aayegi TC
TC - O(n)
SC - O(n) + O(n);
In this, we can also go from n-1 to 0, baat ek hi hai like in climbing stairs go from 0 to n or n to 0.

*/

// TABULATION
class Solution
{

public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        // jaroori ni ki har baari n+1 hi lena hai, yahan dekho n bhi touch ni hoga mera, 0 se n-1 hi jayega at max so good to take n
        // top down means base case se aage jana chotte se n tak ka safar karna
        vector<int> dp(n);
        dp[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            // m bhai left to right chl rha hu means from 0 to n-1. n-1 m mujhe mera answer mil jayega. ab agr m 2 ki jump laga sakta hu toh current value + 2 wali jump wali lelunga nhi laga sakta toh abhi tak jo hai ek kam wala vahi lelunga like ki 2 size hai toh 0 liya toh 1 nhi le sakta, 1 liya toh 0 ni toh 1st bucket m max store hoga ki 0 lu ya 1.
            int taken = nums[i];
            if (i - 2 >= 0)
            {
                taken += dp[i - 2];
            }
            int noTaken = dp[i - 1];
            dp[i] = max(taken, noTaken);
        }

        return dp[n - 1];
    }
};
/*
1st and 2nd element hai toh ya toh 1st hi lo and ya toh 2nd hi lo toh dono ka max dekhna padega vo mera 2nd m store hoga, 1st m toh 1st hi rahega bss...
TC - O(n)
SC - O(n);
*/

// SPACE OPTIMISATION
class Solution
{

public:
    int rob(vector<int> &nums)
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
};
/*
dp[i-1] dp[i-1] dp[i]
        dp[i-1] dp[i-1] dp[i]
                dp[i-1] dp[i-1] dp[i]
bss last ke 2 hi chahiye bss so starting m 0th index ko toh lelo nums[0] basically dp[0] prev1 ko and uss se pehle prev2 hai usko lelo 0 as index 1 se -2 ki jump ni kar sakte aap, then uske baad ek ek karke aage badha do like fibonacci.
TC - O(n)
SC - O(1)

*/
