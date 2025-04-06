// MEMOISATION
class Solution
{
public:
    int dp[71][71][71];
    int helper(vector<vector<int>> &grid, int row, int c1, int c2)
    {
        // base case
        // agr bahar gaya grid se toh ek aisi value return karo jo max answer ni
        // degi, so we return -1e8 not INT_MIN as INT_MIN upon addition with a
        // negative number can go out of range.
        if (c1 < 0 || c1 >= grid[0].size() || c2 < 0 || c2 >= grid[0].size())
        {
            return -1e8;
        }

        // Agr last row m ho toh check karo ki dono same cell ko toh point ni
        // kar rahe, if yes then 1 baar count karo and agr dono alg alg ko point
        // kar rahe hai toh dono ki values add karo
        if (row == grid.size() - 1)
        {
            if (c1 == c2)
            {
                return grid[row][c1];
            }
            else
            {
                return grid[row][c1] + grid[row][c2];
            }
        }

        if (dp[row][c1][c2] != -1)
        {
            return dp[row][c1][c2];
        }

        // abhi jis point m ho uska ans add karo and recursion ko bolo ki bhai
        // mujhe aage ka answer lakr de jo sabse maximum ho, bss uss maximum ans
        // ko apne result m add kardo and usko return kardo
        int result = 0;

        // Case when columns are same, row will always be increasing so every
        // time, each robot will go to a new row and also row will be same for
        // both as both will reach the end row at the same time
        if (c1 == c2)
        {
            result += grid[row][c1];
        }
        else
        {
            result += grid[row][c1] + grid[row][c2];
        }

        int maxx = 0;

        // -1 0 1 bss ye hi add karoge har baar, total possibilties = 9 as for
        // every possibilty, we have 3 possibility
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                maxx = max(maxx, helper(grid, row + 1, c1 + j, c2 + k));
            }
        }

        result += maxx;

        return dp[row][c1][c2] = result;
    }
    int cherryPickup(vector<vector<int>> &grid)
    {
        memset(dp, -1, sizeof(dp));
        return helper(grid, 0, 0, grid[0].size() - 1);
    }
};
/*
Simple brute force toh ye hi ho jayega ki dono robot ko chlao apne apne point se
and then agr clash toh ek ka add warna dono ka, ab isme 4 cheeje change ho rahe
hai (i,j) of robot-1 and (r,c) of robot 2 toh dp[][][][] , this will result in
stack overflow. Har case m row toh badh hi rahi hai har robot ki, vo humesha
next row m jayega toh jab dono ke liye same hi hai toh ek hi lelo na, toh row,
c1, c2. Therefore - dp[][][];

Recursion - TC - O(3^n * 3^n) ~ exponential -- n rows hai and har row m 3 choices hai and alice and bob dono chlege.
SC - O(n) n rows recursion

TC - O(n*m*m) no. of states ki kitn states m jaa sakte hai
SC - O(n*m*m) * 9 + O(n) -- 3*3 ka loop bhi toh hai
Memoisation ki TC nikalte time bss ye dekhe karo ki dp array ka size kya hai simple.

*/

// TABULATION
class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        // same size hi rahega n m m
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, 0)));

        // base case - usme m if row = 0 isme ulta row = n-1 toh aisa hai toh and m last n-1 se hi start kar rha hu isme toh abhi vahi rahegi row aur koi toh hai ni toh same col toh only one add else both add
        for (int col1 = 0; col1 < m; col1++)
        {
            for (int col2 = 0; col2 < m; col2++)
            {
                if (col1 == col2)
                {
                    dp[n - 1][col1][col2] = grid[n - 1][col1];
                }
                else
                {
                    dp[n - 1][col1][col2] = grid[n - 1][col1] + grid[n - 1][col2];
                }
            }
        }

        // base case m n-1 ka kaam ho gya ab n-2 se start karo
        for (int row = n - 2; row >= 0; row--)
        {
            for (int col1 = m - 1; col1 >= 0; col1--)
            {
                for (int col2 = m - 1; col2 >= 0; col2--)
                {
                    int result = 0;

                    // Case when columns are same, row will always be increasing so every
                    // time, each robot will go to a new row and also row will be same for
                    // both as both will reach the end row at the same time
                    if (col1 == col2)
                    {
                        result += grid[row][col1];
                    }
                    else
                    {
                        result += grid[row][col1] + grid[row][col2];
                    }

                    int maxx = 0;

                    // -1 0 1 bss ye hi add karoge har baar, total possibilties = 9 as for
                    // every possibilty, we have 3 possibility
                    for (int j = -1; j <= 1; j++)
                    {
                        for (int k = -1; k <= 1; k++)
                        {
                            // agr m andar hi hu grid ke toh ye karna warna nhi
                            if (col1 + j >= 0 && col1 + j < m && col2 + k >= 0 && col2 + k < m)
                            {
                                maxx = max(maxx, dp[row + 1][col1 + j][col2 + k]);
                            }
                        }
                    }

                    result += maxx;

                    dp[row][col1][col2] = result;
                }
            }
        }

        // upr m start kar rha tha 0, 0, m-1 yahan ye return kardunga. Vo starting point tha ye ending point hai.
        return dp[0][0][m - 1];
    }
};
/*
TC - O(n*n*n*9)
SC - O(n*n*m)

*/

// SPACE OPTIMISATION
class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        // dekha jaye toh mujhe bss neeche wali row hi chahiye bss uska j1 j2 index so 3d ki jagah agr m 2d hi lelu that represent previous 2d it will work;
        // size will be m*m as pehle toh n m m tha but 3d ki jagah 2d hai toh only m*m
        vector<vector<int>> prev(m, vector<int>(m, 0));

        // base case - usme m if row = 0 isme ulta row = n-1 toh aisa hai toh and m last n-1 se hi start kar rha hu isme toh abhi vahi rahegi row aur koi toh hai ni toh same col toh only one add else both add
        for (int col1 = 0; col1 < m; col1++)
        {
            for (int col2 = 0; col2 < m; col2++)
            {
                if (col1 == col2)
                {
                    prev[col1][col2] = grid[n - 1][col1];
                }
                else
                {
                    prev[col1][col2] = grid[n - 1][col1] + grid[n - 1][col2];
                }
            }
        }

        // base case m n-1 ka kaam ho gya ab n-2 se start karo
        for (int row = n - 2; row >= 0; row--)
        {
            vector<vector<int>> curr(m, vector<int>(m, 0));
            for (int col1 = m - 1; col1 >= 0; col1--)
            {
                for (int col2 = m - 1; col2 >= 0; col2--)
                {
                    int result = 0;

                    // Case when columns are same, row will always be increasing so every
                    // time, each robot will go to a new row and also row will be same for
                    // both as both will reach the end row at the same time
                    if (col1 == col2)
                    {
                        result += grid[row][col1];
                    }
                    else
                    {
                        result += grid[row][col1] + grid[row][col2];
                    }

                    int maxx = 0;

                    // -1 0 1 bss ye hi add karoge har baar, total possibilties = 9 as for
                    // every possibilty, we have 3 possibility
                    for (int j = -1; j <= 1; j++)
                    {
                        for (int k = -1; k <= 1; k++)
                        {
                            // agr m andar hi hu grid ke toh ye karna warna nhi
                            if (col1 + j >= 0 && col1 + j < m && col2 + k >= 0 && col2 + k < m)
                            {
                                // previous row ke liye meine prev liya hi hai toh prev lo direct.
                                maxx = max(maxx, prev[col1 + j][col2 + k]);
                            }
                        }
                    }

                    result += maxx;

                    curr[col1][col2] = result;
                }
            }

            // ab jo curr hai vo aage ke liye prev ban jayega
            prev = curr;
        }

        // upr m start kar rha tha 0, 0, m-1 yahan ye return kardunga. Vo starting point tha ye ending point hai.
        return prev[0][m - 1];
    }
};
/*
That's how we space optimise them
1d -> variables
2d dp -> 1d
3d -> 2d

TC - O(n*m*m*9)
SC - O(m*m)
*/