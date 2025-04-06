// Top-down Recursive with memo
class Solution
{
public:
    int minFallingPathSumHelper(vector<vector<int>> &matrix, int r, int c, vector<vector<int>> &dp)
    {
        if (r == 0 and c < matrix[0].size() and c >= 0)
        {
            return matrix[r][c];
        }
        if (c >= matrix[0].size() or c < 0)
        {
            return INT_MAX;
        }

        if (dp[r][c] != INT_MAX)
        {
            return dp[r][c];
        }

        return dp[r][c] = matrix[r][c] + min(min(minFallingPathSumHelper(matrix, r - 1, c + 1, dp), minFallingPathSumHelper(matrix, r - 1, c, dp)), minFallingPathSumHelper(matrix, r - 1, c - 1, dp));
    }
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int rows = matrix.size(), cols = matrix[0].size();
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, INT_MAX));
        int ans = INT_MAX;
        for (int c = 0; c < cols; c++)
        {
            ans = min(ans, minFallingPathSumHelper(matrix, rows - 1, c, dp));
        }
        return ans;
    }
};
/*
mujhe bss pehli row ke saare elements m iterate karna h toh bss pehli row ke elements m iterate kar neeche se and then har ek element ke liye function call karde and jo sabse min ho calculate karte reh and then usko return karde.
agr tu helper function m loop lagata toh dikkat ho jati na, tujhe neeche wali row ke sirf 3 elements lene hai par loop h tph vo saare lega

We usually write the recurrence in the opposite fashion. We go from n-1,m-1 to 0,0 and then tabulation m iska ulta. 

Instead of returning INT_MAX, INT_MIN return 1e9 or -1e9 do prevent overflow.
Recursion TC - O(3^n) as 3 rows hai and har row m aap 3 cheeje le sakte hai. Ye dekhna padta hai ki kitni kitni states/levels m jaa rahe ho and usme kya kar rahe ho...alignas
SC - O(n) n rows traverse kar rahe hai na

TC - O(n*m) - ye sirf ye hi ni hai recursion calls hoti hai toh usme bhi time lagta hai toh it might and might not give you TLE.
SC - O(n*m) + O(n)
*/

// TABULATION
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
        {
            dp[0][i] = matrix[0][i];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // for every element, we can arrive at that element from 3 directions, choose the minimum of three
                dp[i][j] = matrix[i][j] + min({dp[i - 1][j],
                                               dp[i - 1][max(0, j - 1)],
                                               dp[i - 1][min(n - 1, j + 1)]});
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
/*
mujhe bss pehli row ke saare elements m iterate karna h toh bss pehli row ke elements m iterate kar neeche se and then har ek element ke liye function call karde and jo sabse min ho calculate karte reh and then usko return karde.
agr tu helper function m loop lagata toh dikkat ho jati na, tujhe neeche wali row ke sirf 3 elements lene hai par loop h tph vo saare lega

dekh ek vector lele 2d same size ka n X n.
kinda hum bottom to top ka sum calculate kar rahe hai minimum, dekh pehli row m tu aa ni sakta kahin se vahi se start kar rahi h toh same rahegi, ab neeche wali row ke elements dekhle ki wahan pe kahan kahanse aa sakta hai, jahan se aa sakta h unka minimum lele do for last row,
ab last row m jo elements hoge vo minimum answers hoge and usme se jo minimum hoga vo return karde.
har element ko lekr jo jo sum banege vo last row m hai

tu ulta bhi kar sakta hai baat ek hi hai

TC - O(n*m)
SC - O(n*m)
*/

// SPACE OPTIMISATION
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        vector<int> prev(n, 0);
        for (int i = 0; i < n; i++)
        {
            prev[i] = matrix[0][i];
        }

        for (int i = 1; i < n; i++)
        {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++)
            {
                // for every element, we can arrive at that element from 3 directions, choose the minimum of three
                curr[j] = matrix[i][j] + min({prev[j],
                                               prev[max(0, j - 1)],
                                               prev[min(n - 1, j + 1)]});
            }

            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }
};
/*
TC - O(n*m)
SC - O(m)
*/
