// MEMOISATION - har baar jaroori ni ki memoisation meri top to down ho like isme hum 0 se n jaa rahe hai top down will be going from n to 0 like in climbing stairs - can also make this go from n to 0.
class Solution
{
private:
    int help(int idx, int n, vector<int> &height, vector<int> &dp)
    {
        // base case
        // agr m pahoch gya nth step m then ab toh m wahan pe khada hu ab thodi cost lagegi koi m aagya yahan pe jahan pe jana hai and wahin pe hi khade ho toh no cost.
        if (idx == n)
        {
            return 0;
        }

        // DP
        if (dp[idx] != -1)
        {
            return dp[idx];
        }

        // recursive case
        // one hai toh thik hai lelo and agr 2 ki jump maar sakta hai toh 2 lelo but agr ni toh 2 ko kuch aisa set kardo ki min lene m one ka hi aaye so INT_MAX, agr ni kiya toh jis case m two ki jump vo ni le payega uss case m two is undeclared ki error aayegi.
        int one = help(idx + 1, n, height, dp) + abs(height[idx] - height[idx + 1]);
        int two = INT_MAX;
        if (idx <= n - 2)
        {
            two = help(idx + 2, n, height, dp) + abs(height[idx] - height[idx + 2]);
        }

        return dp[idx] = min(one, two);
    }

public:
    int minCost(vector<int> &height)
    {
        int n = height.size() - 1;
        // n size bhi chlega as indexing n-1 se 0 tak ki hai toh total n and last index will be n-1 so n is sufficient.
        vector<int> dp(n + 1, -1);
        return help(0, n, height, dp);
    }
};
// TC - O(n) recursion at max 0 to n hi jayega baaki sab toh dp m store ho jayega so O(1) for them.
// SC - O(n) + O(n) recursion

// TABULATION
class Solution
{

public:
    int minCost(vector<int> &height)
    {
        // mujhe 0th index se n-1th index tak jana hai toh size basically n -1 ho gya na as index starts from 0 to 4 elements hai toh 0 to 3
        int n = height.size() - 1;
        vector<int> dp(n + 1);
        // going from base case to required answer
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            int one = dp[i - 1] + abs(height[i] - height[i - 1]);
            int two = INT_MAX;
            if (i >= 2)
            {
                two = dp[i - 2] + abs(height[i] - height[i - 2]);
            }

            dp[i] = min(one, two);
        }

        // bss nth m mera answer hoga as initially n is total ele - 1 for taking care of indexes 4 elements hai total toh n=4 but taken n = 4-1 = 3 so answer will be in taken n that is 3 so dp[n];
        return dp[n];
    }
};
// TC - O(n)
// SC - O(n)

// SPACE OPTIMISATION
class Solution
{

public:
    int minCost(vector<int> &height)
    {
        // mujhe 0th index se n-1th index tak jana hai toh size basically n -1 ho gya na as index starts from 0 to 4 elements hai toh 0 to 3
        // ya toh isko -1 mt karo but phir loop will rum til < n baat ek hi hai - ye bss aise isliye kiya hai ki pattern same rahe. 
        int n = height.size() - 1;
        int first = 0;
        int second = 0;
        for (int i = 1; i <= n; i++)
        {
            int one = first + abs(height[i] - height[i - 1]);
            int two = INT_MAX;
            if (i >= 2)
            {
                two = second + abs(height[i] - height[i - 2]);
            }

            second = first;
            first = min(one, two);
        }

        return first;
    }
};

/*
[i-2] [i-1] [i]
      [i-2] [i-1] [i]
            [i-2] [i-1] [i]

            aise chlega toh jo second tha vo first bn jayega and jo first tha vo new answer jo nikla hai vo bnjayega

TC - O(n)
SC - O(1)
*/