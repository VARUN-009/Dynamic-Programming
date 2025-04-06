class Solution
{
public:
    int LongestBitonicSequence(int n, vector<int> &nums)
    {
        // Bitonic means longest bitonic, LIS, LDS  - all of them can be possible answers.
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        vector<int> dp1(n, 1);
        vector<int> dp2(n, 1);

        // To find the LIS basically left to right increasing
        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (nums[idx] > nums[prev])
                {
                    dp1[idx] = max(dp1[idx], 1 + dp1[prev]);
                }
            }
        }

        // No reverse as reverse karege toh indices hi change ho gayi na last element ka index n-1 tha par reverse ke baad 0 ho gya...not good.

        // Now going from right to left so reverse hi karliya humne ab yahan se LIS nikalo.
        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int prev = n - 1; prev > idx; prev--)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (nums[idx] > nums[prev])
                {
                    dp2[idx] = max(dp2[idx], 1 + dp2[prev]);
                }
            }
        }

        int maxBitonic = 0;
        // Combine LIS and LDS for each index i, but ensure both arms are present.
        for (int i = 0; i < n; i++)
        {
            if (dp1[i] > 1 && dp2[i] > 1) // valid bitonic must have both increasing and decreasing parts.
            {
                maxBitonic = max(maxBitonic, dp1[i] + dp2[i] - 1);
            }
        }

        return maxBitonic;
    }
};