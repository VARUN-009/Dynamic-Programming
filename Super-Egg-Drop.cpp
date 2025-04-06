// MEMOISATION - TC - O(k*n*n) SC - O(k*n) + O(n) recursion stack Gives TLE as O(k*n^2) complexity
class Solution
{
private:
    int helper(int k, int n, vector<vector<int>> &dp)
    {
        // base case
        // agr 0 floor hai toh 0 ans as ussme toh tu khada hi hai and 1st floor hai toh 1 hi step se pta chl jayega ki yahan se tootega ya ni.
        if (n == 0 || n == 1)
        {
            return n;
        }

        // ek hi egg bacha hai and maanle ki 10 floors hai toh worst case m har floor m jana padd sakta hai toh return n
        if (k == 1)
        {
            return n;
        }

        // DP
        if (dp[k][n] != -1)
        {
            return dp[k][n];
        }

        // recursive case
        // abhi toh ptani toh 1e9 and m saare cases m se minimum hi lunga.
        int ans = 1e9;
        for (int floor = 1; floor < n; floor++)
        {
            // agr mera egg break ho gya means ki ye floor jyada hi high hai toh iss se neeche jakr dekho and egg break hua means ki ek egg km ho jayega - neeche jakr dekhna means ki  se floor-1 tak as floor m toh break hi ho gya
            int egg_break = helper(k - 1, floor - 1, dp);

            // agr egg break ni hua means kya pta aur upr se fek sakta hu toh aur upr jao, egg break toh ni hua toh sab same hi rahega and floors will be n - floor.
            int egg_not_break = helper(k, n - floor, dp);

            /*  Agar tum k floor se egg drop kar rahe ho aur do possibilities hain:
                Egg break ho jaye → Tumhe niche ke floors (k-1 floors) check karne padenge, aur maan lo ki 3 moves lag rahe hain (find(k-1, k-1) = 3).
                Egg na toote → Tumhe upar ke floors (n-k floors) check karne padenge, aur maan lo ki 10 moves lag rahe hain (find(k, n-k) = 10).
                Ab hume worst-case scenario consider karna hai, toh hum max(3,10) = 10 lenge, kyunki minimum moves wala case toh waise hi cover ho jayega.

                +1 as abhi toh ek move lag hi gya na tumhe toh +1 for this. M basically har floor pe iterate kar rha hu and dekh rha hu ki iss floor m kitna laga and overall saare floors m se jo minimum hai vo le rha hu
            */
            int curr = max(egg_break, egg_not_break) + 1;
            ans = min(ans, curr);
        }

        return dp[k][n] = ans;
    }

public:
    int superEggDrop(int k, int n)
    {

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, -1));
        return helper(k, n, dp);
    }
};

// TABULATION - TC - O(k*n^2) SC - O(n*k) -- gives TLE as worst case m O(10^10) and we want 10^8
class Solution
{
public:
    int superEggDrop(int k, int n)
    {

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

        // covered the base case in it n == 0 || n == 1 return n so n=0 hai toh 0 and n=1 hai toh 1
        for (int i = 0; i <= k; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 1;
        }

        // k == 1 return n so n means floors so jo floor hai vo hi return kardo so i
        for (int i = 0; i <= n; i++)
        {
            dp[1][i] = i;
        }

        // k ki value humesha 1 >= hi hogi 0 ni hogi as 0 eggs hai toh tu bta hi ni sakta as kuch hai hi ni nanga nahyega kya nichodega kya
        for (int i = 2; i <= k; i++)
        {
            if (i == 1)
                continue;

            // 2 se as n==0 & n==1 ka cover karliya base case m
            for (int j = 2; j <= n; j++)
            {
                int ans = 1e9;
                // floors m m j se iterate kar rha hu toh till j
                for (int floor = 1; floor <= j; floor++)
                {
                    // agr mera egg break ho gya means ki ye floor jyada hi high hai toh iss se neeche jakr dekho and egg break hua means ki ek egg km ho jayega - neeche jakr dekhna means ki  se floor-1 tak as floor m toh break hi ho gya
                    // egg m mein i se and floor m j se iterate so vo lo...
                    int egg_break = dp[i - 1][floor - 1];

                    // agr egg break ni hua means kya pta aur upr se fek sakta hu toh aur upr jao, egg break toh ni hua toh sab same hi rahega and floors will be n - floor.
                    // egg m mein i se and floor m j se iterate so vo lo...
                    int egg_not_break = dp[i][j - floor];

                    /*  Agar tum k floor se egg drop kar rahe ho aur do possibilities hain:
                        Egg break ho jaye → Tumhe niche ke floors (k-1 floors) check karne padenge, aur maan lo ki 3 moves lag rahe hain (find(k-1, k-1) = 3).
                        Egg na toote → Tumhe upar ke floors (n-k floors) check karne padenge, aur maan lo ki 10 moves lag rahe hain (find(k, n-k) = 10).
                        Ab hume worst-case scenario consider karna hai, toh hum max(3,10) = 10 lenge, kyunki minimum moves wala case toh waise hi cover ho jayega.

                        +1 as abhi toh ek move lag hi gya na tumhe toh +1 for this. M basically har floor pe iterate kar rha hu and dekh rha hu ki iss floor m kitna laga and overall saare floors m se jo minimum hai vo le rha hu
                    */
                    int curr = max(egg_break, egg_not_break) + 1;
                    ans = min(ans, curr);
                }

                dp[i][j] = ans;
            }
        }

        return dp[k][n];
    }
};

// TABULATION WITH BINARY SEARCH - Instead of linear search, we will do binary search here. TC - O(k*nlogn) SC - O(n*k)
class Solution
{
public:
    int superEggDrop(int k, int n)
    {

        vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

        // covered the base case in it n == 0 || n == 1 return n so n=0 hai toh 0 and n=1 hai toh 1
        for (int i = 0; i <= k; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 1;
        }

        // k == 1 return n so n means floors so jo floor hai vo hi return kardo so i
        for (int i = 0; i <= n; i++)
        {
            dp[1][i] = i;
        }

        // k ki value humesha 1 >= hi hogi 0 ni hogi as 0 eggs hai toh tu bta hi ni sakta as kuch hai hi ni nanga nahyega kya nichodega kya
        for (int i = 2; i <= k; i++)
        {
            if (i == 1)
                continue;

            // 2 se as n==0 & n==1 ka cover karliya base case m
            for (int j = 2; j <= n; j++)
            {
                // floors m m j se iterate kar rha hu toh till j
                int low = 1;
                int high = j;
                int ans = 1e9;

                while (low <= high)
                {
                    int mid = (low + high) / 2;
                    int egg_break = dp[i - 1][mid - 1];
                    int egg_not_break = dp[i][j - mid];
                    int worst_case = 1 + max(egg_break, egg_not_break);
                    ans = min(ans, worst_case);
                    
                    // agr egg break ho gya toh neeche search kar, ab pta kaisa chlega ki break ho gya means value jyada aarahi hai egg break ki toh iss wajah se. and egg break ni hua means tu aur upr jaa sakta hai toh aur upr jaa.
                    if (egg_break > egg_not_break)
                    {
                        high = mid - 1;
                    }
                    else
                    {
                        low = mid + 1;
                    }
                }

                dp[i][j] = ans;
            }
        }

        return dp[k][n];
    }
};
