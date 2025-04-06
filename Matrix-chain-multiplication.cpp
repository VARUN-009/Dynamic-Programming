// MEMOISATION
class Solution
{
private:
    int helper(vector<int> &arr, int i, int j, vector<vector<int>> &dp)
    {
        // base case - ki agr meri single hi matrix bch rahi hai toh m phir multiply ni kar paunga kisi aur se toh operations total = 0;
        if (i == j)
        {
            return 0;
        }

        // DP
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // recursive case
        // m left se ek ek karke badha rha hu then ek ek karke aage jaa rha hu i,k then k+1,j toh at last mujhe ek element toh chahiye hi jiss se m k+1 m jaa saku, nhi bacha means poori matrix hi leli which is not required.
        int ans = 1e9;
        for (int k = i; k < j; k++)
        {
            int left = helper(arr, i, k, dp);
            int right = helper(arr, k + 1, j, dp);
            int operations = (arr[i - 1] * arr[k] * arr[j]) + left + right;
            ans = min(operations, ans);
        }

        return dp[i][j] = ans;
    }

public:
    int matrixMultiplication(vector<int> &arr)
    {
        // 1 se because [1 2] hai toh 1*2 ka size hai matrix ka toh left lena padega na and curr tab jake size niklega
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return helper(arr, 1, n - 1, dp);
        // i and j ki values last meri 0 se n-1 tak hi jayegi toh sirf n hi lunga to bhi kaam bn jayega
    }
};

// BOTTOM UP MEANS NEECHE SE UPR -- TABULATION  --  SMALLER PROBLEM (base case) TO BIGGER PROBLEM
// TOP DOWN MEANS UPR SE NEECHE -- MEMOISATION  --  BIGGER PROBLEM TO SMALLER PROBLEM (base case)

// TABULATION
class Solution
{
public:
    int matrixMultiplication(vector<int> &arr)
    {
        // 1 se because [1 2] hai toh 1*2 ka size hai matrix ka toh left lena padega na and curr tab jake size niklega
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // RULE - 1  -- copy the base case jo bhi likha hai usko copy karo
        // i mera 1 se start ho rha hai and also jab jab single matrix hogi toh answer is 0.
        for (int i = 1; i < n; i++)
        {
            dp[i][i] = 0;
        }

        // Mark the changing states and copy the recurrence. Ab dekho upr return kar rahe hai 1, n-1 toh neeche mera answer issi m hoga toh i ko start karo n-1 se 0 and

        // now i     j   aise hoga humesha and j start ho rha tha 0 se n-1 toh i ar 2 3 4 hai toh j ko 0 se thodi na start karege kyuki j humesha right hand side hai i ke toh j will start from i + 1 at least.

        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                int ans = 1e9;
                for (int k = i; k < j; k++)
                {
                    int left = dp[i][k];
                    int right = dp[k + 1][j];
                    int operations = (arr[i - 1] * arr[k] * arr[j]) + left + right;
                    ans = min(operations, ans);
                }

                dp[i][j] = ans;
            }
        }

        // jo upr return kar rahe the vahi kar rahe hai bss 
        return dp[1][n - 1];
    }
};

/*
jaroori ni ki humesha ulta hi ho tabulation memoisation ka like in this same hi hai same base case and same recursive case and dp array size same hi hoga bss halka sa dimaag lagana padega recursive case m and loop kahan se start karna hai.

tum neeche se upr jao and upr se neeche jao baat ek hi hai like climbing stairs so same base case se bhi start kar sakte ho tabulation m 

jaroori ni ki tabulation m ulta hi chlna hai ki waha`n jo base case hai yahan usko last bnayega ni...same hi kar sakte hai at the end answer chahiye.
*/