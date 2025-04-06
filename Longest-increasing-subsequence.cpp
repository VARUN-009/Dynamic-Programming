// MEMOISATION 2D
class Solution
{
public:
    vector<int> dp;
    int helper(vector<int> &nums, int idx, int prev, vector<vector<int>> &dp)
    {
        // base case
        if (idx == nums.size())
        {
            return 0;
        }

        if (dp[idx][prev + 1] != -1)
        {
            return dp[idx][prev + 1];
        }

        // recursive case
        int include = 0;
        if (prev == -1 || nums[idx] > nums[prev])
        {
            include = 1 + helper(nums, idx + 1, idx, dp);
        }
        int exclude = helper(nums, idx + 1, prev, dp);
        return dp[idx][prev + 1] = max(include, exclude);
    }
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return helper(nums, 0, -1, dp);
    }
};

// MEMOISATION 1D
class Solution
{
public:
    vector<int> dp;
    int helper(vector<int> &nums, int idx, int prev)
    {
        // base case
        if (idx == nums.size())
        {
            return 0;
        }

        if (dp[prev + 1] != -1)
        {
            return dp[prev + 1];
        }

        // recursive case
        int include = 0;
        if (prev == -1 || nums[idx] > nums[prev])
        {
            include = 1 + helper(nums, idx + 1, idx);
        }
        int exclude = helper(nums, idx + 1, prev);
        return dp[prev + 1] = max(include, exclude);
    }
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        dp.assign(n + 1, -1);
        return helper(nums, 0, -1);
    }
};

/*

Brute force - O(2^n)
We have taken prev+1 because prev is initially at -1 and index can never be
-1 so it will create a problem. Basically we have choice, either we can take
this element or not so if you are at index 2 and haven't taken an element yet
so dp[2][-1] which will cause error if prev = -1, it only means that you
haven't taken any element yet so put dp[i][prev+1] i.e. index 0 of dp to
value dp indicates number of elements you have scanned.

Since we only take those things for dp vector which are constantly changing
in every function call, here i and prev will be changing so we take a 2d
array of i and prev But notice that prev will point to index, basically we
will check the value at prev index so prev will iterate the whole array,
dp[i] tells number of elements you have scanned, at last prev will be at last
index and total numbber of elements will be prev+1, so at dp[prev+1] we put
ans, means on scanning all the elements of the array, what's the answer we
got.
*/

// TABULATION 2D
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // base case ki agr idx==n toh return 0 so last row m hai toh m usko 0 kar rha hu sabko it is already covered in the initialisation part so no need to do it.
        // In prev we have to do the coordinate shift toh jabjab prev ka kuch bhi use karoge toh second parameter ten it will be prev + 1...+1 add karna hi hai huemsha
        // last row ka ho gya toh last-1 se kaam karo. memo idx 0-n, prev -1 - n-1  here ulta so idx n to 0 and prev n-1 se -1
        for (int idx = n - 1; idx >= 0; idx--)
        {
            // 0 se n jaa rahe the toh prev humesha idx se pehle hi tha toh ab n-1 se 0 jaa rahe hai toh prev humesha idx se pehle hi hoga na baad m toh ni sakta as it is prev to idx - 1 ki humesha pehle hi rahe.
            for (int prev = idx - 1; prev >= -1; prev--)
            {
                int include = 0;
                if (prev == -1 || nums[idx] > nums[prev])
                {
                    include = 1 + dp[idx + 1][idx + 1];
                }
                int exclude = dp[idx + 1][prev + 1];
                dp[idx][prev + 1] = max(include, exclude);
            }
        }

        return dp[0][-1 + 1];
        // ultimately it is dp[0][0]
    }
};
/*
Recursion TC - O(2^n) take or not take for every element.
Memo - TC - O(n*n)
SC - O(n*n) + O(n) recursion

isko 2d vector leke aaram se kar sakte hai bss prev+1 karna hai har jagah for coordinate shift.
*/

// TABULATION - O(n^2) & 1D
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> next(n + 1, 0), curr(n + 1, 0);

        // base case ki agr idx==n toh return 0 so last row m hai toh m usko 0 kar rha hu sabko it is already covered in the initialisation part so no need to do it.
        // In prev we have to do the coordinate shift toh jabjab prev ka kuch bhi use karoge toh second parameter ten it will be prev + 1...+1 add karna hi hai huemsha
        // last row ka ho gya toh last-1 se kaam karo. memo idx 0-n, prev -1 - n-1  here ulta so idx n to 0 and prev n-1 se -1
        for (int idx = n - 1; idx >= 0; idx--)
        {
            // 0 se n jaa rahe the toh prev humesha idx se pehle hi tha toh ab n-1 se 0 jaa rahe hai toh prev humesha idx se pehle hi hoga na baad m toh ni sakta as it is prev to idx - 1 ki humesha pehle hi rahe.
            for (int prev = idx - 1; prev >= -1; prev--)
            {
                int include = 0;
                if (prev == -1 || nums[idx] > nums[prev])
                {
                    include = 1 + next[idx + 1];
                }
                int exclude = next[prev + 1];
                curr[prev + 1] = max(include, exclude);
            }

            next = curr;
        }

        return next[-1 + 1];
        // ultimately it is next[0]
    }
};

// TABULATION - O(n^2) && 1D
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        vector<int> dp(n, 1);

        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (nums[idx] > nums[prev])
                {
                    dp[idx] = max(dp[idx], 1 + dp[prev]);
                }
            }
        }

        // jo sabse bada hoga vahi answer ho jayega mera toh return it
        return *max_element(dp.begin(), dp.end());
    }
};

// Print Longest Increasing Subsequence
// TC - O(n^2) + O(LIS)
class Solution
{
public:
    vector<int> longestIncreasingSubsequence(int n, vector<int> &arr)
    {
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        vector<int> dp(n, 1);
        vector<int> path(n);
        for (int i = 0; i < n; i++)
        {
            path[i] = i;
        }

        int maxi = 0;
        int index = 0;
        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (arr[idx] > arr[prev])
                {
                    if (dp[idx] < 1 + dp[prev])
                    {
                        // agr mera bada hai toh thik hai m store kar leta hu and ye path vector m store karlunga ki kahan se aaya hu m basically uska index.
                        dp[idx] = 1 + dp[prev];
                        path[idx] = prev;
                    }
                }
            }

            // maximum compute karte raho ki abhi tak ka max LIS kya hai and uska index.
            if (dp[idx] > maxi)
            {
                maxi = dp[idx];
                index = idx;
            }
        }

        vector<int> result;

        // jo sabse bada hoga vahi answer ho jayega mera toh return it
        while (index != path[index])
        {
            result.push_back(arr[index]);
            index = path[index];
        }

        // end m jo first wala rehta hai vo bhi toh lena hai na so take it too jaroori ni ki 0 hi index hoga ab path m jis index m ho uski value index ke equal hai toh kya pta 2nd index m aaye hai and usme value 2 hi hai toh take it.
        result.push_back(arr[index]);

        // ulta jaa rahe hai toh reverse karna padega
        reverse(result.begin(), result.end());

        return result;
    }
};

// LIS using Binary Search TC - O(n*logn) SC - O(n)
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> vec;

        // pehla element toh pehle se hi daaldo
        vec.push_back(nums[0]);
        int len = 1;
        for (int i = 1; i < n; i++)
        {
            // agr mera bada hai toh thik hai lelo phir isko part of LIS
            if (nums[i] > vec.back())
            {
                vec.push_back(nums[i]);
                len++;
            }

            // agr bada ni hai toh jo element hai usko ab mujhe apne vec wale m put karna hai sahi jagah and since vec is in sorted toh lower bound lagao vo first element >= dedega thus uss se replace kardo.
            else
            {
                // it returns an iterator so - vec.begin() to get actual index.
                int idx = lower_bound(vec.begin(), vec.end(), nums[i]) - vec.begin();
                vec[idx] = nums[i];
            }
        }

        return len;
    }
};