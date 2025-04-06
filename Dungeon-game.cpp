class Solution
{
public:
    int dp[201][201];
    int helper(vector<vector<int>> &dungeon, int i, int j, int n, int m)
    {
        // base case
        // agr tu grid se bahar chle gaya toh kuch aisa answer de jo minimum nhi
        // ho sakta hai toh humne iNT_MAX return kardiya hai
        if (i < 0 || i >= dungeon.size() || j < 0 || j >= dungeon[0].size())
        {
            return INT_MAX;
        }

        // dekh agr ab tu last cell m hai bottm right cell m toh dekh agr vo
        // cell 0 ya positive hai toh tujhe aur energy toh chahiye hi ni toh 0
        // karde, kyuki positive hai na toh chahie hi ni extra power, but agr
        // negative hai toh jitni negative hai + 1, kyuki agr utni hi dedi toh
        // wahan jakr tu marjaeyega na, last m aakr mr gaya, toh you need 1
        // extra power
        if (i == n && j == m)
        {
            return dungeon[i][j] >= 0 ? 1 : 1 - dungeon[i][j];
        }

        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }
        int ans = INT_MAX;
        // 0,0 se aage se recursion ko ans dene ko bol minimum
        ans = min({ans, helper(dungeon, i, j + 1, n, m),
                   helper(dungeon, i + 1, j, n, m)});

        // agr 0,0 hi 0 hai toh aage ka jo minimumhai tujhe utna hi chahiye
        // kyuki 0 means tujhe koi extra power ni chahiye
        if (dungeon[i][j] == 0)
        {
            return dp[i][j] = ans;

            // negative hai toh isko bhi include karna padega 1 - -ve = 1 + -ve
        }
        else if (dungeon[i][j] < 0)
        {
            return dp[i][j] = ans - dungeon[i][j];

            // aage ka ans 50 hai tu 0,0 m 10 hai toh you need 50-10 but maanlo
            // starting m 100 hai and toh 50-100 toh ans will be -50 but this is
            // not the answer toh 1 dedo kyuki neeche wala toh 1 extra chahiye
            // na, same leliya toh lastm aakr mr jaoge, toh yaa toh 1 ya minus
            // karke
        }
        else
        {
            return dp[i][j] = max(1, ans - dungeon[i][j]);
        }

        /*
        int res = ans - dungeon[i][j];
        if(res <= 0 ? res : 1);
        return dp[i][j] = res;
        // return dp[i][j] = dungeon[i][j] <=0 ?  ans - dungeon[i][j] : max(1, ans-dungeon[i][j])
        */
    }
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int n = dungeon.size() - 1;
        int m = dungeon[0].size() - 1;
        memset(dp, -1, sizeof(dp));
        return helper(dungeon, 0, 0, n, m);
    }
};
/*



*/