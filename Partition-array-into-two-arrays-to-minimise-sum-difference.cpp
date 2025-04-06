class Solution
{
private:
    // For generating all possible subset sums. Can also be done via recursion.
    // If we take an element, add it to sum; otherwise, move forward.
    // Base case: if idx == n, push sum to ans.
    vector<vector<int>> helper(vector<int> &nums, int start, int end, int offset)
    {
        int n = end - start + 1;
        vector<vector<int>> ans(n + 1);

        // Looping from 0 to 2^n - this is equivalent to 2^n as there are a total of 2^n subsets.
        for (int i = 0; i < (1 << n); ++i)
        {
            // mujhe iske andar jo jo possible subsets hai na unka sum lena hai and count bhi lena hai ki agr m sirf 1 element lu toh kitne hai 2 lu toh kitne hai. 2^n subsets bante hai means 2 element hai toh aisa bhi ho sakta hai ki 2 hi element leliye toh for that ans size n+1
            int sum = 0, count = 0;

            // Looping through indices 0, 1, 2, ..., n
            for (int j = 0; j < n; ++j)
            {
                // If it is a set bit, then 1 && 1 gives 1 (which means take it),
                // and 0 means do not take it.
                // We iterate over n bits using left shift.
                if (i & (1 << j))
                {
                    sum += nums[j + offset];
                    count++;
                }
            }
            ans[count].push_back(sum);
        }
        return ans;
    }

public:
    int minimumDifference(vector<int> &nums)
    {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int halfSum = totalSum / 2;

        // Taking an offset because in the right half, the result will be in the range 0 to n/2.
        // However, we need to add the offset to ensure it moves to its respective right half.
        // In the left half, the offset remains 0.
        // 'left' contains all possible subset sums from the left half,
        // and 'right' contains all possible subset sums from the right half.
        vector<vector<int>> left = helper(nums, 0, n / 2 - 1, 0);
        vector<vector<int>> right = helper(nums, n / 2, n - 1, n / 2);

        // meet in the middle m right wala sort kardete hai 
        for (auto &vec : right)
        {
            sort(vec.begin(), vec.end());
        }

        // ab m ek ek karke har element lunga left ka and like m k element le rha hu left ke and array ko 2 part m divide kardiya toh half ka nikal rha hu bss ki half ke liye meine left se k liya toh ab mujhe right se n/2 - k lene padege. Just think about n/2 elements only half array. 1 yahan se liya toh n/2 wahan se lunga and then usme lower bound lagaunga ki max kitna element le sakta hu m.
        int ans = 1e9;
        for (int count = 0; count < left.size(); ++count)
        {
            for (auto &ele : left[count])
            {
                // uss index m jao basically uss count m right ke and then jo best value ho sakti hai vo lo.
                int right_idx = (n / 2) - count;

                int target = halfSum - ele;
                int idx = lower_bound(right[right_idx].begin(), right[right_idx].end(), target) - right[right_idx].begin();

                // agr meri range m hai toh then uss element ko lo right ke left wale ko add karo total sum aajayega ab dekho ye sum sirf half array ka hai isko 2 se multiply kardo poore array ka aajayega. Optimal toh ye hi hai ki half totalsum/2 ho and usko 2 se multiply means total sum par jyada km aayega toh usko total sum se minus karke dekhege kitna difference hai.

                // dono hi condition check karni padegi agr mil gya toh vo bhi and uss se pehle wala bhi ki optimal answer mile kyuki manlo target se bada mil gya toh uss se chotta lege toh pta uss se fayeda ho rha ho
                if (idx < right[right_idx].size())
                {
                    int current = ele + right[right_idx][idx];
                    ans = min(ans, abs(totalSum - 2 * current));
                }

                if (idx > 0)
                {
                    int current = ele + right[right_idx][idx - 1];
                    ans = min(ans, abs(totalSum - 2 * current));
                }
            }
        }
        return ans;
    }
};