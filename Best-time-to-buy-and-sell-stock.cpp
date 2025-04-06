class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int ans = 0;
        int minSoFar = INT_MAX;

        // m chahta hu ki buy m sabse km price m karu toh agr minSoFar se km
        // mila then usko minSoFar bna do and then uss se bada koi mila aage toh
        // unka difference lete raho
        // toh bss sabse chota m set karunga and then aage m bss subtract karte
        // rahunga and check karte rahunga ki sabse bada difference kiska hai
        for (int i = 0; i < prices.size(); i++)
        {
            if (prices[i] < minSoFar)
            {
                minSoFar = prices[i];
            }
            else
            {
                ans = max(ans, prices[i] - minSoFar);
            }
        }

        return ans;
    }
};
/*
TC - O(n) SC - O(1)

*/