// TABULATION - O(nlogn) + O(n^2) + O(n)
class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> path(n);
        for (int i = 0; i < n; i++)
        {
            path[i] = i;
        }

        // DP store kar rha hai ki till this index abhi tak ka sabse bada divisible subset ki length kya hai...it is exactly same hai LIS
        // a mera b se divide ho rha hai and b mera c se divide ho rha hai toh ultimately a mera c se bhi divide hoga so sort kardiya ki ek order m rahe
        sort(nums.begin(), nums.end());
        int maxi = 0;
        int index = 0;
        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (nums[idx] % nums[prev] == 0)
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
            result.push_back(nums[index]);
            index = path[index];
        }

        // end m jo first wala rehta hai vo bhi toh lena hai na so take it too jaroori ni ki 0 hi index hoga ab path m jis index m ho uski value index ke equal hai toh kya pta 2nd index m aaye hai and usme value 2 hi hai toh take it.
        result.push_back(nums[index]);

        // ulta jaa rahe hai toh reverse karna padega
        reverse(result.begin(), result.end());

        return result;
    }
};