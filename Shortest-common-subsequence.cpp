class Solution
{
private:
    string findLCS(int n, int m, string &s1, string &s2)
    {

        // ab yahan pe m len1<0 bhi dekh rha hu par negative to jaa ni sakta toh to resolve this m ek kaam karta hu sab m 1 1 index badha deta hu toh phir len1<0 ho jayega len1==0. This way I can tabulise it. So when I say index 1, it means index 0 as ek aage badhaya tha par actually m ek kam tha na...
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // agr meri row ya col 0 hai toh vo 0 hai
        for (int col = 0; col <= m; col++)
        {
            dp[0][col] = 0;
        }

        for (int row = 0; row <= n; row++)
        {
            dp[row][0] = 0;
        }

        // 0th row ka toh kam kardiya hai and 0th column ka bhi toh you cna skip them
        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                // baaki sab same rahega bss current index reality m ek km hai toh ek km karke check karo baaki sab same hi hai
                if (s1[len1 - 1] == s2[len2 - 1])
                {
                    dp[len1][len2] = 1 + dp[len1 - 1][len2 - 1];
                }
                else
                {
                    dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
                }
            }
        }

        // LCS is the part which is commmon in both of the string so usko toh bss 1 hi baar lena hai par vo hai dono m toh bss lena ek hi baar. So m last cell se iterate karunga agr same hai characters toh 1 hi lunga and diagonally ek peeche chle jaunga jahan se aaya tha and agr same ni hai toh bss ek hi lunga maximum jo bhi hoga an upr yan left m se jo max hai wahan chle jaunga.

        string ans = "";
        int len1 = n, len2 = m;
        while (len1 > 0 && len2 > 0)
        {
            // len1-1 len2-1 as ek extra liya tha for handling case when len1<0 so ek peeche dekho agr same hai vo toh answer ka part bnao and uss index m vo char daalo basically iske andar hum backtrack kar rahe hai till anyone becomes 0 neeche se upr len->0 so on the go answer calculate karne hai and waise hi chlna hai jaise recursion m chle hai bss ulta.
            if (s1[len1 - 1] == s2[len2 - 1])
            {
                ans += s1[len1 - 1];
                len1--;
                len2--;
                // tum len1-1, len2-1 se aaye the toh neeche se upr jana hai toh ek ek kam karke diagonal move karna padega.
            }
            // else dono m se jo maximum hai wahan jao and aisa bhi ho sakta hai dono same ho toh that is the case for multiple LCS so usko abhi ni dekhna.
            else if (dp[len1 - 1][len2] > dp[len1][len2 - 1])
            {
                ans += s1[len1 - 1];
                len1--;
            }
            else
            {
                ans += s2[len2 - 1];
                len2--;
            }
        }

        while (len1 > 0)
        {
            ans += s1[len1 - 1];
            len1--;
        }

        while (len2 > 0)
        {
            ans += s2[len2 - 1];
            len2--;
        }

        // our final SCS - reverse karna padega as hum last se first ki taraf jaa rahe hai toh answer mera ulta aayega
        reverse(ans.begin(), ans.end());
        return ans;
    }

public:
    string shortestCommonSupersequence(string str1, string str2)
    {
        int n = str1.length();
        int m = str2.length();

        // this will only be done via tabulation as memoisation m sab jagah ni ja payega vo sab states m toh kuch values khali reh sakti hai. Tabulation m har possible pair of indices m jayega toh poori table bhr jayegi and then we can computer our answer.
        return findLCS(n, m, str1, str2);
    }
};