// MEMOISATION
#include <bits/stdc++.h>
using namespace std;

int fibo(int n, vector<int> &dp)
{
    // base case
    // returning n means ki n=0 hai toh 0 return and n=1 hai toh 1 return
    if (n <= 1)
    {
        return n;
    }

    // memoisaton
    if (dp[n] != -1)
    {
        return dp[n];
    }

    // recursive case
    return dp[n] = fibo(n - 1, dp) + fibo(n - 2, dp);
}

int main()
{
    int n = 10;
    vector<int> dp(n + 1, -1);
    cout << fibo(n, dp) << endl;
    return 0;
}

// TABULATION
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 10;
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// SPACE OPTIMISATION
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Space optimised DP
    // TC - O(n);
    // SC = O(1);
    int n = 10;
    int prev1 = 1;
    int prev2 = 0;
    for (int i = 2; i <= n; i++)
    {
        int curr = prev2 + prev1;
        prev2 = prev1;
        prev1 = curr;
    }

    // at last answer will be stored in prev1.
    cout << prev1 << endl;

    return 0;
}

/*
Try to make a vector and pass it by refernce, this will also work as taking global variables are considered not as a good practice
*/