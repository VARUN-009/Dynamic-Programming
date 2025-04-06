
// Going from 0th to n
class Solution
{
private:
    int help(int stair, int n)
    {
        // base case
        if (stair == n || stair == n - 1)
        {
            return 1;
        }

        // recursive case
        // currently I am in 0th step and then 1 step m 1st stair m jaunga and then 2 step m 2nd step m jaunga
        int one = help(stair + 1, n);
        int two = help(stair + 2, n);

        return one + two;
    }

public:
    int climbStairs(int n)
    {
        return help(0, n);
    }
};

// Going from n to 0 as m 0 se n m jau ya n se 0 m jau baat toh ek hi hai step mujhe 1 ya 2 hi lene hai toh 1 2 upr lelo ya 1 2 neeche lelo.
class Solution
{
private:
    int help(int n)
    {
        // base case
        // agr m nth stair m aagya means I found a way so i will return 1 ki haa bhai mujhe ek way mil gya hai. Also, agr m n-1 stair m aagya means m 1 hi step lunga ab then nth stair m, 2 step ni le sakta as 1-2=-1 m aage chle jaunga toh that's why pehle hi check karliya.
        if (n == 0 || n == 1)
        {
            return 1;
        }

        // recursive case
        // currently I am in 0th step and then 1 step m 1st stair m jaunga and then 2 step m 2nd step m jaunga
        int one = help(n - 1);
        int two = help(n - 2);

        return one + two;
    }

public:
    int climbStairs(int n)
    {
        return help(n);
    }
};

// MEMOISATION - going from required answer to base case
class Solution
{
private:
    int help(int n, vector<int> &dp)
    {
        // base case
        // agr m nth stair m aagya means I found a way so i will return 1 ki haa bhai mujhe ek way mil gya hai. Also, agr m n-1 stair m aagya means m 1 hi step lunga ab then nth stair m, 2 step ni le sakta as 1-2=-1 m aage chle jaunga toh that's why pehle hi check karliya.
        if (n == 0 || n == 1)
        {
            return 1;
        }

        // DP
        if (dp[n] != -1)
        {
            return dp[n];
        }

        // recursive case
        // currently I am in 0th step and then 1 step m 1st stair m jaunga and then 2 step m 2nd step m jaunga
        int one = help(n - 1, vec);
        int two = help(n - 2, vec);

        return dp[n] = one + two;
    }

public:
    int climbStairs(int n)
    {
        vector<int> dp(n + 1, -1);
        return help(n, dp);
    }
};

// TABULATION - going from base case to required answer
// 1. sabse pehle dp array fill karo same as memoisation
// 2. base case se jana hai toh base case se fill karo then keep calculating till n.
class Solution
{

public:
    int climbStairs(int n)
    {
        // memo m m n se 0 jaa rha hu and isme m 0 se n jaunga - question m waise 0 se n jana hai par 0 se n jao ya n se 0 jao baat ek hi hai toh 0 1 ka kaam ho gya ab bacha 2 se kaam till n. jabhi n+1 lena padega as we want n sabme -1 daal bhi sakte ho ya nhi
        vector<int> dp(n + 1);
        dp[0] = dp[1] = 1;

        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

// SPACE OPTIMISATION
class Solution
{

public:
    int climbStairs(int n)
    {
        // now what I can see is that ki current value meri previous 2 values pe depend karti hai i-1 and i-2. so why to take a dp array when i can store them in a variable and then change it's values
        int first = 1; // denoting dp[0]
        int second = 1; // denoting dp[1]
        for (int i = 2; i <= n; i++)
        {
            // dp[i] = dp[i-1] + dp[i-2]
            int curr = first + second;
            second = first;
            first = curr;
        }

        // at last answer mera first m hoga toh return this.
        return first;
    }
};

#include <bits/stdc++.h>
using namespace std;

int main()
{

    return 0;
}