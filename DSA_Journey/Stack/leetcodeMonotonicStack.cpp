//* LeetCode Questions on Monotonic Stacks

#include <bits/stdc++.h>
using namespace std;

//? 739. Daily Temperatures
//? Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

//* Topics : Stack, Monotonic stack

//* Intuition :
// Here we need to return the number of days what we have to wait to get e warmer temperature. So we need to wait till we get a greater temperature to the right of our current temperature. So this resembles next greater element to the right. Just a twist that here we need to return the number of days between them, so we store the indices and do the calculation accordingly. 

//* Solution

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size(); // Size of the given array
        vector<int> result(n, 0); // Acoording to question if no such day found then 0
        stack<int> st; // This will be our monotonically decreasing stack

        for(int i = n-1; i >= 0; i--) { // Traverse from right to left

            // Pop elements smaller than the current element
            while(!st.empty() && temperatures[i] >= temperatures[st.top()]) {
                st.pop();
            }
            // If stack is not empty (i.e a day is found) then at that location of the result vector put the indices difference
            if(!st.empty()) {
                result[i] = st.top() - i;
            }
            //Push the current element into the stack
            st.push(i); 
        }
        return result;
    }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)

// ------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------

//? 84. Largest Rectangle in Histogram 
//? Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

//TODO : REVISION IS A MUST

//* Topics : Stack, Monotonic stack

//* Intuition of brute force approach :
// Here I will find all the possible rectangles, their area, and their find the maximum among them

//* Solution :

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            int minHeight = heights[i];

            // Expand to the left and right from index i
            for (int j = i; j < n; j++) {
                minHeight = min(minHeight, heights[j]);
                int width = j - i + 1;
                int area = minHeight * width;
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }
};

//* Time Complexity : O(n^2)
//* Space Complexity : O(1)

//* Intuition of optimized approach :
// Here I need the rectangle with maximum area. Now for each bar I will try to find the maximum possible area and find the maximum among them. Now for this currArea the height will be the height of my bar. The main twist is the width, for width I need the next smallest element left to the current element which will be my start and I also need the next smallest element right to the current element which will be my end. Now this (end - start -1) will be my width. Then my maxArea will be the maximum of maxArea and currArea;

//* Solution :

class Solution {
public:
    void findEnd(vector<int>& heights, vector<int>& end) { // Find the start (Next smallest element to the left)
        int n = heights.size();
        stack<int> st;

        for(int i = n-1; i >= 0; i--) {
            while(!st.empty() && heights[i] <= heights[st.top()]) {
                st.pop();
            }
            if(!st.empty()) {
                end[i] = (st.top());
            }
            st.push(i);
        }
    }

    void findStart(vector<int>& heights, vector<int>& start) { // Find the end (Next smallest element to the right)
        int n = heights.size();
        stack<int> st;

        for(int i = 0; i < n; i++) {
            while(!st.empty() && heights[i] <= heights[st.top()]) {
                st.pop();
            }
            if(!st.empty()) {
                start[i] = (st.top());
            }
            st.push(i);
        }
    }

    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0; // Maximum area
        int n = heights.size();
        vector<int> end(n, n); // Will contain the end index for each height
        vector<int> start(n, -1); // Will contain the start index for each height

        findStart(heights, start);
        findEnd(heights, end);
        
        for(int i = 0; i < n; i++) { // Iterate through each height
            int currArea = heights[i] * (end[i] - start[i] - 1); // Current area
            maxArea = max(maxArea, currArea); // Updating maximum area
        }
        return maxArea;
    }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)

// ------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------

