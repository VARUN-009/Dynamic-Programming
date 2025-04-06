class Solution
{
private:
    int helper(int i, int j, string &exp, bool isTrue, vector<vector<vector<int>>> &dp)
    {
        // base case
        if (i > j)
        {
            return 0;
        }

        // ab tu ek hi element par khada hai either true or false. But istrue bta rha hai ki vo true mangta hai ya false mangta hai toh jaroori thodi hai ki tu har baar true hi chahiye...aisa bhi ho sakta hai na ki right se saare possible answers do jo false ho. So agr false chahiye toh return 1 if F and true chahiye toh return 1 if T
        if (i == j)
        {
            if (isTrue)
            {
                if (exp[i] == 'T')
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if (exp[i] == 'F')
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        // DP
        if (dp[i][j][isTrue] != -1)
        {
            return dp[i][j][isTrue];
        }

        // recursive case - 1 aage se chlna padega as tabhi toh i,ind-1 and ind se j-1 tak...initially toh i=0, j=n. Now jumping by 2 jumps as T&T&T& aise form m hoga toh mujhe symbols jo hai usme jana hai bss toh uske liye +2 as uske left m expression hogi and then right m dono ko solve karo.
        int ways = 0;
        // 0...i-1  i+1 j so je se pehle tak hi as j+1 j tak ek hoga
        for (int idx = i + 1; idx <= j - 1; idx += 2)
        {
            // No. of ways by which you can get a true from left
            int leftTrue = helper(i, idx - 1, exp, 1, dp);

            // No. of ways by which you can get a false from left
            int leftFalse = helper(i, idx - 1, exp, 0, dp);

            // No. of ways by which you can get a true from right
            int rightTrue = helper(idx + 1, j, exp, 1, dp);

            // No. of ways by which you can get a false from right
            int rightFalse = helper(idx + 1, j, exp, 0, dp);

            if (exp[idx] == '&')
            {
                // same isme bhi agr tu chahta hai ki true btao toh true ka de and agr chahta hai ki false hai toh false ka de ki how many ways you can get a false;
                // T --> T&T   F -- T&F  F&T  F&F
                if (isTrue)
                {
                    ways += (leftTrue * rightTrue);
                }
                else
                {
                    ways += (leftTrue * rightFalse) + (leftFalse * rightTrue) + (leftFalse * rightFalse);
                }
            }
            else if (exp[idx] == '|')
            {
                // same isme bhi agr tu chahta hai ki true btao toh true ka de and agr chahta hai ki false hai toh false ka de ki how many ways you can get a false;
                // T --> T -- T|F  F|T  T|T   F -- F|F
                if (isTrue)
                {
                    ways += (leftTrue * rightFalse) + (leftFalse * rightTrue) + (leftTrue * rightTrue);
                }
                else
                {
                    ways += (leftFalse * rightFalse);
                }
            }

            // XOR wala case. Xor m same hai toh false and different hai toh true;
            // T --- F^T  T^F   F --- T^T   F^F
            else
            {
                if (isTrue)
                {
                    ways += (leftTrue * rightFalse) + (leftFalse * rightTrue);
                }
                else
                {
                    ways += (leftTrue * rightTrue) + (leftFalse * rightFalse);
                }
            }
        }

        return dp[i][j][isTrue] = ways;
    }

public:
    int countWays(string &s)
    {
        // code here
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
        // i kabhi bhi n ke equal ni hoga as i ko at max m n-2 tak hi le jaa sakta hu which is j-1 and j hoga mera n-1 wala index kyuki right m atleast 1 element toh chahiye hi toh iss wajah se n n sixe bhi chlega
        return helper(0, n - 1, s, 1, dp);
    }
};

// TABULATION
class Solution
{
public:
    int countWays(string &s)
    {
        // code here
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));

        // base case
        // 1. i > j so 0 it is already covered in initialisation so no need to do it again.

        // 2. i == j ab agr true hai exp[i] so true wale m 1 else 0 toh true false ptani toh bss s[i] T hai toh 1 wale m 1 else 0 and i==j hai toh alg se j ka loop lene ki need ni hai just i i lelo
        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'T')
            {
                dp[i][i][1] = 1;
                dp[i][i][0] = 0;
            }
            else
            {
                dp[i][i][0] = 1;
                dp[i][i][1] = 0;
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < n; j++)
            {
                for (int isTrue = 0; isTrue <= 1; isTrue++)
                {
                    // already done in the base case so no need to do it again.
                    if (i == j)
                        continue;

                    int ways = 0;
                    // 0...i-1  i+1 j so je se pehle tak hi as j+1 j tak ek hoga
                    for (int idx = i + 1; idx <= j - 1; idx += 2)
                    {
                        // No. of ways by which you can get a true from left
                        int leftTrue = dp[i][idx - 1][1];

                        // No. of ways by which you can get a false from left
                        int leftFalse = dp[i][idx - 1][0];

                        // No. of ways by which you can get a true from right
                        int rightTrue = dp[idx + 1][j][1];

                        // No. of ways by which you can get a false from right
                        int rightFalse = dp[idx + 1][j][0];

                        if (s[idx] == '&')
                        {
                            // same isme bhi agr tu chahta hai ki true btao toh true ka de and agr chahta hai ki false hai toh false ka de ki how many ways you can get a false;
                            // T --> T&T   F -- T&F  F&T  F&F
                            if (isTrue)
                            {
                                ways += (leftTrue * rightTrue);
                            }
                            else
                            {
                                ways += (leftTrue * rightFalse) + (leftFalse * rightTrue) + (leftFalse * rightFalse);
                            }
                        }
                        else if (s[idx] == '|')
                        {
                            // same isme bhi agr tu chahta hai ki true btao toh true ka de and agr chahta hai ki false hai toh false ka de ki how many ways you can get a false;
                            // T --> T -- T|F  F|T  T|T   F -- F|F
                            if (isTrue)
                            {
                                ways += (leftTrue * rightFalse) + (leftFalse * rightTrue) + (leftTrue * rightTrue);
                            }
                            else
                            {
                                ways += (leftFalse * rightFalse);
                            }
                        }

                        // XOR wala case. Xor m same hai toh false and different hai toh true;
                        // T --- F^T  T^F   F --- T^T   F^F
                        else
                        {
                            if (isTrue)
                            {
                                ways += (leftTrue * rightFalse) + (leftFalse * rightTrue);
                            }
                            else
                            {
                                ways += (leftTrue * rightTrue) + (leftFalse * rightFalse);
                            }
                        }
                    }

                    dp[i][j][isTrue] = ways;
                }
            }
        }
        return dp[0][n - 1][1];
    }
};
