// MEMOISATION
class Solution
{
private:
    bool helper(int idx, int sum, vector<int> &arr, vector<vector<int>> &dp)
    {
        // base case
        if (sum == 0)
        {
            return true;
        }

        // agr vo bahar hi chle gya koi ni mila usko toh then return false kyuki ab toh ni hi mil sakta
        if (idx == arr.size())
        {
            return false;
        }

        // DP
        if (dp[idx][sum] != -1)
        {
            return dp[idx][sum];
        }

        // recursive case
        // chotta hai toh le bhi sakta hu and ni hai toh obvio ni le sakta toh ek kaam karo take and not take lelo recursion se and agr koi bhi true hai toh return true else return false; aisa ni karna knapsack ki tarah ki try both take and not take. le sakta hai toh lo and then usko na lo toh bhi answer nikalo then dono m se true.
        bool take = false;
        if (arr[idx] <= sum)
        {
            take = helper(idx + 1, sum - arr[idx], arr, dp);
        }
        bool notTake = helper(idx + 1, sum, arr, dp);
        return dp[idx][sum] = take || notTake;
    }

public:
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        // code here
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(sum + 1, -1));
        return helper(0, sum, arr, dp);
    }
};
/*
Recursion TC - O(2^n) -- n elements hai and har element ke liye either you can take it or not take it - 2 options.
SC - O(n) stack space

TC - O(n*sum)
SC - O(n*sum) + O(n)

*/

// TABULATION
class Solution
{
public:
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        // code here
        int n = arr.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

        // base case tha ki agr mera sum 0 hai toh uska answer hai true. Toh 2d vector hai idx vs sum ka toh har row m sum = 0 m true karde na.
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = true;
        }

        // agr mera idx n ke equal hai toh sab false hai - ye toh humne initialisation m hi cover kardiya na by default sab false hi hai so no need to write it explicitly.

        // jitni number of changing parameters hoge utne hi number of loops hoge
        // target 1 se start hoga as 0 ka toh answer humne mark kar hi diya hai base case m
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int target = 1; target <= sum; target++)
            {
                bool take = false;
                if (arr[idx] <= target)
                {
                    take = dp[idx + 1][target - arr[idx]];
                }

                bool notTake = dp[idx + 1][target];
                dp[idx][target] = take || notTake;
            }
        }

        return dp[0][sum];
    }
};
/*
We can also do it like ki last index m hai toh agr vo mera sum ke equal hai element toh hi return true else return false - aise m then idx == n wala case ni lagega.
TC - O(n*sum)
SC - O(n*sum)

*/

// SPACE OPTIMISATION
class Solution
{
public:
    bool isSubsetSum(vector<int> &arr, int sum)
    {
        // code here
        int n = arr.size();
        // mujhe 2 chahiye rows prev and curr - now curr ko har baar bnane se badiya hai ki 1 hi baar bnau and then usme hi changes kardu bss baar baar overhead km hoga as har iteration m values update hi hogi curr ki.
        vector<bool> prev(sum + 1, false), curr(sum + 1, false);

        // har row ka 0th index mera true tha pehle toh koi bhi row ho uska 0th index mera true hoga hi basically sum=0 m true tha na vo base case ke liye.
        prev[0] = curr[0] = true;

        // agr mera idx n ke equal hai toh sab false hai - ye toh humne initialisation m hi cover kardiya na by default sab false hi hai so no need to write it explicitly.

        // jitni number of changing parameters hoge utne hi number of loops hoge
        // target 1 se start hoga as 0 ka toh answer humne mark kar hi diya hai base case m
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int target = 1; target <= sum; target++)
            {
                bool take = false;
                if (arr[idx] <= target)
                {
                    // row + 1 wali row is represented as prev
                    take = prev[target - arr[idx]];
                }

                bool notTake = prev[target];
                curr[target] = take || notTake;
            }

            // ab aage ke liye this will be my previous
            prev = curr;
        }

        // at the end answer will be in the previous row's sum index
        return prev[sum];
    }
};
/*
We can also do it like ki last index m hai toh agr vo mera sum ke equal hai element toh hi return true else return false - aise m then idx == n wala case ni lagega.
TC - O(n*sum)
SC - O(sum)

*/