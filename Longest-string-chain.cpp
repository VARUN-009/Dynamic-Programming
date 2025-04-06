// Memoisation, tabulation, space optimisation everything will be written same as that of LIS bss dp[idx] > dp[prev] ki jagah bss compare(s1, s2) aayega bss baaki sab ek dum same.
// SPACE OPTIMISATION 1D
class Solution
{
private:
    bool compare(string &s1, string &s2)
    {
        if (s1.size() != s2.size() + 1)
        {
            return false;
        }

        // m chahta hu ki dono m iterate karu and agr ek same ni hua toh bss koi ni s1 m aage jao s1 badi length hai at the end agr dono hi mere last m aagaye toh sahi hai else false;
        int first = 0;
        int second = 0;

        // agr ek baar bhi aisa hua ki alg hai toh vo toh second wala aage badhega ni toh bss return false 
        while (first < s1.size())
        {
            if (s1[first] == s2[second])
            {
                first++;
                second++;
            }
            else
            {
                first++;
            }
        }

        return (first == s1.size() && second == s2.size());
    }

public:
    int longestStrChain(vector<string> &nums)
    {
        int n = nums.size();
        // initally sab mere 1 hi hoge as single element toh le hi sakta hu na m
        vector<int> dp(n, 1);

        // need to sort as sequence chahiye ek toh koi sa bhi ho sakta hai toh kya pta 4th index m first ho then 0th index m second and so on...so sort karlo on the basis of length. isme subsequence ni chahiye ki sequence same ho isme sequence chahiye bss like a subset as subset m sequence aage peeche ho sakta hai
        auto cmp = [](const string &a, const string &b)
        {
            return a.length() < b.length();
        };

        sort(nums.begin(), nums.end(), cmp);
        int ans = -1e9;
        for (int idx = 0; idx < n; idx++)
        {
            for (int prev = 0; prev < idx; prev++)
            {
                // ye jab hoga na jab mera previous jo jo hai vo mera chotta hai mera current idx se
                if (compare(nums[idx], nums[prev]))
                {
                    dp[idx] = max(dp[idx], 1 + dp[prev]);
                }
            }

            ans = max(ans, dp[idx]);
        }

        // jo sabse bada hoga vahi answer ho jayega mera toh return it
        return ans;
    }
};
/*
TC - O(n*n) * O(length) compare
SC - O(n)

*/