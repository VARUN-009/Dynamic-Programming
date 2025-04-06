// Not necessary to write memo, tabu always. Agr tumhe pta hai space optimised wala toh direct vahi likho. This is way more intuitive than memo tabu and space optimisation
class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        vector<int> dp(n, 1);
        vector<int> count(n, 1);
        int maxi = -1e9;
        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se and prev dp m 1 add karke tu length bada sakta hai toh means ye ussi ka part hai toh koi naya count ni hoga bss uski length bdd gayi and length badd gayi toh jo prev element hai wahan tak ka count same hi hoga as length badi hai count vahi hai kyuki ussi m tunne add kardiya
                if (nums[idx] > nums[prev] && dp[prev] + 1 > dp[idx])
                {
                    dp[idx] = 1 + dp[prev];
                    // inherit
                    count[idx] = count[prev];
                }

                // ab tunne dekha ki prev + 1 karne ke baad bhi same hi length aarahi means pakka m isko isme toh ni le sakta means till idx pakka alg alg tarah ki length hai means pakka more than 1 way hai mere pass. dusre subsequence ki wajha se length pehle hi bdd chuki hai ab toh bss rasta mil gya tujhe. Jahan se aarha hai bss wahan ke total count add karde bss idx ke andar.
                else if (nums[idx] > nums[prev] && dp[prev] + 1 == dp[idx])
                {
                    // increase the count
                    count[idx] += count[prev];
                }
            }

            maxi = max(maxi, dp[idx]);
        }

        // vo vo jo Longest hai unko lo and then unka count add kardo bss
        int ans = 0;
        for(int i=0; i<n; i++) {
            if(dp[i] == maxi) {
                ans += count[i];
            }
        }

        return ans;
    }
};