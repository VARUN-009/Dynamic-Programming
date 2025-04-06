
int helper(int n, vector<vector<int>> &points, int days, int prev, vector<vector<int>> &dp)
{
    // base case
    // 0 to n-1 days hi hai bsss uske aage toh kuch ni hai toh take 0
    if (days >= n)
    {
        return 0;
    }

    // DP
    if (dp[days][prev] != -1)
    {
        return dp[days][prev];
    }

    // recursive case
    // agr koi aisa task hai jo m pehle previously kar chuka hu vo toh ni lena hai ji baaki jo 2 bache task hai unme se jo maximum hai vo lunga m. Basically 0 liya toh 1 2 m se jo max hai vo lunga, 1 liya toh 0 2 m se max last day m aisa hi ho rha hai ki agr 0 liya toh baaki 2 ka max etc.
    int ans = 0;
    for (int task = 0; task < 3; task++)
    {
        if (task == prev)
            continue;
        int curr = points[days][task] + helper(n, points, days + 1, task, dp);
        ans = max(ans, curr);
    }

    // at the end m 0 to n jaa rha hu toh 0 wali row m prev=3 m mera answer hoga [0][3] m ki teeno m se jo max hoga vo lo tabulation m har row ke 3 index m abhi tak ka max answer store hota rahega and last row ke 3 index m final answer.
    return dp[days][prev] = ans;
}
int ninjaTraining(int n, vector<vector<int>> &points)
{
    // Write your code here.
    //
    vector<vector<int>> dp(n, vector<int>(4, -1));
    return helper(n, points, 0, 3, dp);
}
// TC - O(n*4) * O(3) - previous can by anything from 0 1 2 3 so 4 elements - as for every call, running a loop 3 times
// SC - O(n*4) + O(n) - as max you will only go for n levels so recursion stack space O(n)

// TABULATION
int ninjaTraining(int n, vector<vector<int>> &points)
{
    // Write your code here.
    // n days hai toh - to n-1 hi jaunga and m task 0 le sakta hu 1, 2 and initially koi bhi task ni toh memoisation m meine 3 bheja tha toh 3 means ki teeno m se koi ni liya toh ab kya maximum hai. and yes, task 0 liya toh 1 2 ka max, 1 liya hai toh 0 2 ka max and so on. 3 liya means ki koi bhi task ni toh teeno m jo max value hai abhi tak vo.
    vector<vector<int>> dp(n, vector<int>(4, 0));
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

    // mujhe ye toh pta ni ki previously konsa task liya hai meine konsa ni toh m sabke liye hi calculate karunga - just like memoisation sab cases m jaunga toh pehle 0 ko prev bnaunga then 1 ko then 2 and then 3 and so on for each level.
    for (int days = 1; days < n; days++)
    {
        // saare possible previous - 0, 1, 2, 3 leke check karege ki kisme kya kya ans aarha hai - har day ke liye tu different prev leek bhej rha hai ki agr ye liya toh kya hoga, ye liya toh kya hoga like this...
        for (int prev = 0; prev < 4; prev++)
        {
            int ans = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task == prev)
                    continue;
                // same as memoisation, current day task ke point add karke then meine bola
                int curr = points[days][task] + dp[days - 1][task];
                ans = max(ans, curr);
            }

            dp[days][prev] = ans;
        }
    }

    // end m answer mera last day ke 3 index m hoga as 3 means ki koi bhi ni liya sabka maximum toh last day answer aajayega sabka and usme se sabka max lene ke liye [n-1][3] index.
    return dp[n - 1][3];
}
/*
TC - O(n*4*3)
SC - O(n*4)
*/

// SPACE OPTIMISATION
int ninjaTraining(int n, vector<vector<int>> &points)
{
    // mujhe bss 1 upr wali row chahiye [days-1] toh phir ek prev vector lelo and ek curr and baad m iteration khatam hone ke baad prev ko curr ke equal bna do for next row.
    vector<int> dp(4, 0);
    dp[0] = max(points[0][1], points[0][2]);
    dp[1] = max(points[0][0], points[0][2]);
    dp[2] = max(points[0][0], points[0][1]);
    dp[3] = max(points[0][0], max(points[0][1], points[0][2]));

    // mujhe ye toh pta ni ki previously konsa task liya hai meine konsa ni toh m sabke liye hi calculate karunga - just like memoisation sab cases m jaunga toh pehle 0 ko prev bnaunga then 1 ko then 2 and then 3 and so on for each level.
    for (int days = 1; days < n; days++)
    {
        // saare possible previous - 0, 1, 2, 3 leke check karege ki kisme kya kya ans aarha hai - har day ke liye tu different prev leek bhej rha hai ki agr ye liya toh kya hoga, ye liya toh kya hoga like this...
        vector<int> curr(4, 0);
        for (int prev = 0; prev < 4; prev++)
        {
            int ans = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task == prev)
                    continue;
                // same as tabulation, bss upr wale ke liye upr wale vector se ans leliya 
                int value = points[days][task] + dp[task];
                ans = max(ans, value);
            }

            curr[prev] = ans;
        }

        // agli row ke liye ab curr ko dp bna do 
        dp = curr;
    }

    // end m answer mera last day ke 3 index m hoga as 3 means ki koi bhi ni liya sabka maximum toh last day answer aajayega sabka and usme se sabka max lene ke liye dp[3] index.
    return dp[3];
}

/*
TC - O(n*4*3)
SC - O(4) ~ O(1)
*/

