class Solution
{
public:
    int dp[50000];
    int nextIndex(vector<vector<int>> &vec, int low, int currentEnd)
    {
        int high = vec.size() - 1;
        int ans = vec.size();
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (vec[mid][0] >= currentEnd)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
    int helper(vector<vector<int>> &vec, int i)
    {
        // base case
        if (i >= vec.size())
        {
            return 0;
        }

        if (dp[i] != -1)
        {
            return dp[i];
        }

        int next = nextIndex(vec, i + 1, vec[i][1]);

        int include = vec[i][2] + helper(vec, next);
        int exclude = helper(vec, i + 1);

        return dp[i] = max(include, exclude);
    }

    int jobScheduling(vector<int> &startTime, vector<int> &endTime,
                      vector<int> &profit)
    {
        int n = startTime.size();
        vector<vector<int>> vec(n, vector<int>(3, 0));
        for (int i = 0; i < n; i++)
        {
            vec[i][0] = startTime[i];
            vec[i][1] = endTime[i];
            vec[i][2] = profit[i];
        }
        memset(dp, -1, sizeof(dp));
        sort(vec.begin(), vec.end());
        return helper(vec, 0);
    }
};
// the only thing that is changing is length so take this to make dp array, if
// two things are changing then we will take 2d array with those 2 things
// sorting so that all the start time are in sorted order, first element is
// starttime so it will sort on the basis of first element. then we will se only
// on the basis of start time