class Solution
{
public:
    int dp[501][501];
    int helper(string &word1, string &word2, int n, int m)
    {
        // base case
        // agr meri word1 ki string khatam ho gayi means word2 m abhi bhi characters bache hai toh unko same bnane ke liye word1 m vo sab add karne padege toh m+1 as - based indexing hai like m=0 and n=-1 so m mein 1 character hai toh m+1 means 0+1 so 1 character add karna hai.
        if (n < 0)
        {
            return m + 1;
        }

        // agr word2 ke sab khatam ho gaye toh means word1 m faltu hai toh vo faltu sab delete kardo. n+1 as 0 based indexing hai.
        if (m < 0)
        {
            return n + 1;
        }

        if (dp[n][m] != -1)
        {
            return dp[n][m];
        }

        // recursive case
        // agr match karte hai toh sahi hai, ek character toh same ho gya na ab
        // baaki aage ke check kar ki kaise convert karega
        if (word1[n] == word2[m])
        {
            return dp[n][m] = helper(word1, word2, n - 1, m - 1);
        }
        // agr same ni hai toh you have 3 steps - insert, delete, replace
        else
        {
            int insertChar = helper(word1, word2, n, m - 1);
            int deleteChar = helper(word1, word2, n - 1, m);
            int replaceChar = helper(word1, word2, n - 1, m - 1);

            return dp[n][m] = min({insertChar, deleteChar, replaceChar}) + 1;
        }
    }
    int minDistance(string word1, string word2)
    {
        memset(dp, -1, sizeof(dp));
        int n = word1.length();
        int m = word2.length();
        return helper(word1, word2, n - 1, m - 1);
    }
};
/*
It is always possible as saare delete kardo and them m add kardo so at max n+m steps
Recursion TC - O(3^n) SC - O(n+m)
BASE CASE
agr ek string hai aur ek string ni hai toh toh jo bchi hui hai string
hai, uski jitni length hai vo hi answer hua na ki bhai itne
characters chahaiye tujhe ab. aur ye bhi ho sakta hai ki bhai itne
characters delete karde vice versa like a -> aabc  or  aabc -> a dono
m 3 characters chahiye pehle m 3 insert karne padege and dusre m 3
remove karne padege

insert
insert toh vahi character karega na jo tujhe chahiye toh insert kardiya toh last
ke dono ke same ho gaye par jisme insert kara usme 1 extra aagya toh length toh
same hi rahegi jo pehle thi but dusre wali ki -1 becuase match ho gya na

delete
delete kardiya last wala kyuki match ni kar rha toh pehle wale ki length km hui
dusre wali ki toh as it is rahi na

replace
same karane ke liye replace kardiya toh same ho gaye dono last ke toh dono ko ek
ek km kardo

aur agr same hi hai last wale toh dono ko em ek km kardo
TC - O(n*m)
SC - O(n*m) + O(n+m)
*/

// TABULATION
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // base case hai ki n<0 and m<0 toh less than -1 index toh hoga ni toh m 1 extra index leke chl leta hu n<0 means n==0 and m<0 means m==0
        // When word1 is empty (n == 0), you need m insertions to convert "" to word2.

        // When word2 is empty (m == 0), you need n deletions to convert word1 to "".

        // You do not need i + 1, you just need i (or j) insertions/deletions.
        // it is also i and i as now you are using 1-based indexing eg-i=3 means second index to it will return 3 so return i
        for (int i = 0; i <= m; i++)
        {
            dp[0][i] = i;
        }

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = i;
        }

        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                if (word1[len1 - 1] == word2[len2 - 1])
                {
                    dp[len1][len2] = dp[len1 - 1][len2 - 1];
                }
                // agr same ni hai toh you have 3 steps - insert, delete, replace
                else
                {
                    int insertChar = dp[len1][len2 - 1];
                    int deleteChar = dp[len1 - 1][len2];
                    int replaceChar = dp[len1 - 1][len2 - 1];

                    dp[len1][len2] = min({insertChar, deleteChar, replaceChar}) + 1;
                }
            }
        }

        return dp[n][m];
    }
};

// SPACE OPTIMISATION
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        // base case hai ki n<0 and m<0 toh less than -1 index toh hoga ni toh m
        // 1 extra index leke chl leta hu n<0 means n==0 and m<0 means m==0 When
        // word1 is empty (n == 0), you need m insertions to convert "" to
        // word2.

        // When word2 is empty (m == 0), you need n deletions to convert word1
        // to "".

        // You do not need i + 1, you just need i (or j) insertions/deletions.
        // 1d space m ab ye wala toh same hi rahega ki word1 ke tunne 0 liye and
        // word2 ke 0 toh 0 operations, word2 ka 1 liya toh 1, 2 liye toh 2 and
        // so on...ab par column ke bhi karna hai isme toh n==0 and column m tha
        // m==0
        for (int i = 0; i <= m; i++)
        {
            prev[i] = i;
        }

        for (int len1 = 1; len1 <= n; len1++)
        {
            // isme ab curr[0] humesha uspe depend karta hai ki kitne characters
            // liye hai word1 ke kyuki ab tu neeche jaa rha hai len1 shows word1
            // so 0 to n and word2 ke 0 hai characters toh word1 ke 2 lega toh
            // word2 ke 0 hai toh delete 2 chars similarly 3 toh delete 3 chars
            // so curr[0] will depend on the current value of len1.

            // base case tha na ki har row ka 0th index mera row number ke equal hoga toh curr means current row so har curr ke liye m uska [0] mera row number ke equal hoga so len1 ke equal hoga
            curr[0] = len1;
            for (int len2 = 1; len2 <= m; len2++)
            {
                if (word1[len1 - 1] == word2[len2 - 1])
                {
                    curr[len2] = prev[len2 - 1];
                }
                // agr same ni hai toh you have 3 steps - insert, delete,
                // replace
                else
                {
                    int insertChar = curr[len2 - 1];
                    int deleteChar = prev[len2];
                    int replaceChar = prev[len2 - 1];

                    curr[len2] = min({insertChar, deleteChar, replaceChar}) + 1;
                }
            }

            prev = curr;
        }

        return prev[m];
    }
};
