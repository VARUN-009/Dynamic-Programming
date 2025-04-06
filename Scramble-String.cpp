// MEMOISATION is more than enough for this O(n*n) 2 strings, * O(n) inner loop * O(n) map check takes O(n) in worst case so O(n^4) and SC - O(N^3) as Total pairs = O(n²) (for each length) × n lengths = O(n³) dono ki length n hai toh n length s1 ki and n length s2 ki and jo length hai substring ki vo tu 1 se n tak ki le sakta hai. har ek length ke liye O(n^2) possibilities hai left m 1 character liya toh right m tu koi sa bhi 1 character le sakta hai...so n^2
class Solution
{
private:
    // taking a map as index string toh ni ho sakta na toh 2d vector ni le sakte the toh dono string ka store karte raho ki abhi tak ka answer kya hai.
    unordered_map<string, bool> mp;
    bool helper(string s1, string s2)
    {
        // base case
        // 1. If same directly return true na
        // 2. If dono ki length alg hai phir toh kabhi bhi dono same ni ho sakte
        // toh return false
        // 3. Minimum ek character hona chahiye is already fulfilled in the loop
        // from 1 to n-1.
        if (s1 == s2)
        {
            return true;
        }

        if (s1.size() != s2.size())
        {
            return false;
        }

        // DP
        // using _ as 1. a & bc and ab & c -- dono m same hi aayega abc agr _ ni liya toh so to resolve ambiguity
        string str = s1 + "_" + s2;
        if (mp.find(str) != mp.end())
        {
            return mp[str];
        }

        // recursive case
        bool ans = false;
        int n = s1.length();
        // starting from 1 as left m minimum 1 character toh chahiye hi and
        // right m minimum 1 character toh chahiye hi and s1 ko check karna hai
        // ki s2 ki scramble string hai ki toh s1 ki length nikalo usme hi
        // iterate kar rahe hai. Patern will be of MCM, har possible substring m
        // check karke dekho.
        for (int i = 1; i < n; i++)
        {
            // agr m swap ni kar rha hu toh bss toh iska left part 2nd string ke
            // left part se check karo equal hai ki nhi and iska right part 2nd
            // string ke right part se check karo. substr function (start_pos,
            // length) aise format m values leta hai
            bool not_swapped = helper(s1.substr(0, i), s2.substr(0, i)) &&
                               helper(s1.substr(i, n - i), s2.substr(i, n - i));

            if (not_swapped)
            {
                ans = true;
                // break as aage dekhne ki need nhi hai ab, directly break and return the answer.
                break;
            }
            // agr swap kar rha hai toh iska left part 2nd string ke right part
            // se compare and iska right part second string ke left part se. M
            // swapping kar ni rha par agr swap karoge toh means ki ulta ho
            // jayega na toh swap kare bina hi check karlo
            bool swapped = helper(s1.substr(0, i), s2.substr(n - i, i)) &&
                           helper(s1.substr(i, n - i), s2.substr(0, n - i));

            if (swapped)
            {
                ans = true;
                break;
            }
        }

        return mp[str] = ans;
    }

public:
    bool isScramble(string s1, string s2)
    {
        return helper(s1, s2);
    }
};
/*
Memoization is more than enough for this problem.
We have two strings of length n, so that gives us O(n * n) possible substrings.
Then there's an inner loop that runs up to O(n) times (we split at every index),
and each lookup in the map (unordered_map) takes O(n) time in the worst case (due to string keys).
So overall, the time complexity becomes O(n⁴).

The space complexity is O(n³) because:
We are comparing substrings of both strings.

Both s1 and s2 have n possible starting points.

The substring length can be anything from 1 to n.
So for each length, we can have O(n²) combinations (starting point in s1 × starting point in s2).
And since we can take substring lengths from 1 to n, we multiply by n lengths.
So the total number of stored subproblems (i.e., keys in the map) is O(n³).

*/