// MEMOISATION - har baar jaroori ni ki memoisation meri top to down ho like isme hum 0 se n jaa rahe hai top down will be going from n to 0 like in climbing stairs - can also make this go from n to 0.
class Solution
{
private:
    int help(int idx, int n, vector<int> &height, int k, vector<int> &dp)
    {
        // base case
        // last index m aane ke baad mujhe jahan aana tha m aagya toh cost=0 so return 0 as ab jo aa gya m ab thodi koi cost lagegi
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
        int ans = 1e9;
        for (int i = 1; i <= k; i++)
        {
            // check karlena ki k times aage jump laga sakta hu m ya ni if yes lagao and then cost bhi lelo and aage ka recursion ko bolo ki answer laake de
            if (idx + i <= n)
            {
                ans = min(ans, help(idx + i, n, height, k, dp) + abs(height[idx] - height[idx + i]));
            }
        }

        return dp[idx] = ans;
    }

public:
    int minimizeCost(int n, int k, vector<int> &height)
    {
        // n size bhi chlega as indexing n-1 se 0 tak ki hai toh total n and last index will be n-1 so n is sufficient.
        // jaroori ni ki humesha n+1 hi lena hai vo jab lena hai jaise n steps hai toh n+1 will store the nth step ab isme mujhe 4 baar jana hai 0 to 3(4-1) so n bhi lunga tab bhi baat bn jayegi as n-1 m mera answer mil jayega mereko
        vector<int> dp(n + 1, -1);
        return help(0, n - 1, height, k, dp);
    }
};
// TC - O(n*k) recursion at max 0 to n hi jayega baaki sab toh dp m store ho jayega so O(1) for them and har step m k ka loop to traverse so n*k
// SC - O(n) + O(n) recursion

// TABULATION
class Solution
{
public:
    int minimizeCost(int n, int k, vector<int> &height)
    {
        // n size bhi chlega as indexing n-1 se 0 tak ki hai toh total n and last index will be n-1 so n is sufficient.
        vector<int> dp(n);

        // top down means from base case chotte se end tak bade tak
        dp[0] = 0;
        for (int i = 1; i < n; i++)
        {
            int ans = 1e9;
            for (int j = 1; j <= k; j++)
            {
                // same hi hai bss check kar rha hu ki jitni jumps peeche jaa sakta hu and jaa sakta hu toh cost calculate kar rha hu same memo jaisa bhi hai bss ulta hai isme base case se answer tak jaa rahe hai starting to end usme end to starting.
                if (i - j >= 0)
                {
                    ans = min(ans, dp[i - j] + abs(height[i] - height[i - j]));
                }
            }
            dp[i] = ans;
        }

        // as indexing starts from 0 to n-1 therefore n toh array se bahar hi hoga toh last wale index m answer hoga toh n-1.
        return dp[n - 1];
    }
};
// TC - O(n*k)
// SC - O(n)

// NO NEED TO DO THIS - DRY RUN TO UNDERSTAND THIS
// SPACE OPTIMISATION - in this we cannot do O(1) as kaafi saare points hai par mujhe last k points chahiye hai toh m O(n) se O(k) tak laa sakta hu bss.  No need of this as in worst case if k==n then it will be O(n)
class Solution
{
public:
    int minimizeCost(int n, int k, vector<int> &height)
    {
        // O(n) ki jagah O(k) le rha hu ki k size ki window m hi kaam ho jaye
        vector<int> dp(k, 0);

        // top down means from base case chotte se end tak bade tak
        dp[0] = 0;
        for (int i = 1; i < n; i++)
        {
            int ans = 1e9;
            for (int j = 1; j <= k; j++)
            {
                if (i - j >= 0)
                {
                    // mod hi lena padega jiss se ki pta chl jaye ki konse index m hi purana wala k size ke andar hi hona chahiye na iss karke.
                    ans = min(ans, abs(height[i] - height[i - j]) + dp[(i - j) % k]);
                }
            }

            // k ke andar hi rahe toh iss chakkr m meine mod with k liya hai toh humesha k bucket ke andar hi rahega
            dp[i % k] = ans;
        }

        // as indexing starts from 0 to n-1 therefore n toh array se bahar hi hoga toh last wale index m answer hoga toh n-1.
        return dp[(n - 1) % k];
    }
};

/*
[i-k]...[i-2] [i-1] [i]
        [i-k]...[i-2] [i-1] [i]
                [i-k]...[i-2] [i-1] [i]

            aise chlega toh jo second tha vo first bn jayega and jo first tha vo new answer jo nikla hai vo bnjayega toh aage badta rahega toh 1st ko htao and ans ko push kardo baat ek hi hai ji...

TC - O(n)
SC - O(k)

eg k=2 hai toh 0th index m answer then 1st m and then 0m and then 1st aise aise karke answer aayega then ultimately I want the answer for n-1 th index toh mod lo ki abhi konse index m store hoga as even and odd length vary karti hai 0m ho sakta hai ya 1 m.

Given input k = 3 and arr = [10, 30, 40, 50, 20]:

Finall dp array will be:-  [40, 30, 30]
so jaroori ni ki n-1 wale m hi answer ho, waise mujhe answer n-1 wale m hi milta par mod with k lena padega hi haa exact jis index m store hai vahi mile...answer will be 5-1 % 3 -> 4%3 gives 1 so 30
*/