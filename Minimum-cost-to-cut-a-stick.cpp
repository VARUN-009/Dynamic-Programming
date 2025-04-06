// MEMOISATION
class Solution
{
    int dp[101][101];
    int helper(int left, int right, vector<int> &cuts)
    {
        if (left > right)
        {
            return 0;
        }

        if (dp[left][right] != -1)
        {
            return dp[left][right];
        }

        int ans = INT_MAX;
        for (int i = left; i <= right; i++)
        {
            int cost = (cuts[right + 1] - cuts[left - 1]) +
                       helper(left, i - 1, cuts) + helper(i + 1, right, cuts);
            ans = min(cost, ans);
        }

        return dp[left][right] = ans;
    }

public:
    int minCost(int n, vector<int> &cuts)
    {
        int c = cuts.size();
        sort(cuts.begin(), cuts.end());
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);
        memset(dp, -1, sizeof(dp));
        return helper(1, c, cuts);
    }
};
// cuts.size() = c
// TC - O(c * c) * O(c) (loop inside function) ~ O(c^3) c cube
// SC - O(c * c) + O(c) stack space


// TABULATION
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        sort(cuts.begin(), cuts.end());
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);

        // base case ye hi tha ki agr i mera j se bada hai toh 0 toh meine sabko
        // hi starting m 0 kardiya
        // ind+1 when i = n will you runtime error so make it c+2
        vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

        // recursion mera 1 se n tak chl rha hai dekha jayega toh 1-N but
        // tabulation is opposite means bottoms up so N-1. Memoisation is top
        // down. Similarly j is also from N-1 as right m hai na toh right ki
        // taraf so in tabulation 1-N. j mera N se start ho rha hai and i mera 1
        // se.

        for(int i=c; i>=1; i--) {
            for(int j=1; j<=c; j++) {
                // already sabme 0 laga diya hai that's why continue.
                if(i > j) continue;

                int ans = INT_MAX;
                for(int idx=i; idx<=j; idx++) {
                    int cost = cuts[j+1] - cuts[i-1] + dp[i][idx-1] + dp[idx+1][j];
                    ans = min(ans, cost); 
                }

                dp[i][j] = ans;
            }

        }

        return dp[1][c];
    }
};

/*
TC - O(c^3)
SC - O(c^2)
*/


/*
1. copy the base case
2. write down the changing parameters
3. copy the recurrence (in opposite)

*/


/*
- Recursion se karoge toh exponential time complexity as bohot saari partitions ho sakti hai
- To do memoisation, just check the changing parameter basically here is i and j. i is changing from 1 to cuts.size() and j is also from 1 to cuts.size() - basically 1 toh hoga hi cut na toh iss karke


*/