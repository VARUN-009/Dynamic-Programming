// USING STACK
class Solution
{
private:
    vector<int> previousSmaller(vector<int> &heights)
    {
        int n = heights.size();
        stack<int> st;
        st.push(-1);
        vector<int> left(n);
        for (int i = 0; i < n; i++)
        {
            while (st.top() != -1 && heights[st.top()] >= heights[i])
            {
                st.pop();
            }

            left[i] = st.top();
            st.push(i);
        }
        return left;
    }

    vector<int> nextSmaller(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> right(n);
        stack<int> st;
        st.push(-1);
        for (int i = n - 1; i >= 0; i--)
        {
            while (st.top() != -1 && heights[st.top()] >= heights[i])
            {
                st.pop();
            }

            right[i] = st.top();
            st.push(i);
        }
        return right;
    }

    int largestRectangleArea(vector<int> &heights)
    {
        int maxArea = INT_MIN;
        int n = heights.size();
        vector<int> previous = previousSmaller(heights);
        vector<int> next = nextSmaller(heights);
        for (int i = 0; i < n; i++)
        {
            int breadth = heights[i];
            if (next[i] == -1)
            {
                next[i] = n;
            }
            int length = next[i] - previous[i] - 1;
            int area = length * breadth;
            maxArea = max(area, maxArea);
        }

        return maxArea;
    }

public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int maxArea = INT_MIN;
        vector<int> heights(matrix[0].size(), 0);

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] == '1')
                {
                    heights[j]++;
                }
                else
                {
                    heights[j] = 0;
                }
            }

            int area = largestRectangleArea(heights);
            maxArea = max(area, maxArea);
        }

        return maxArea;
    }
};

// TC - O(n*m) O(n) monotnonic stack
