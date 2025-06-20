//* LeetCode Questions on recurssion

#include <bits/stdc++.h>
using namespace std;

//? Fibonacci Number
//? The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. Calculate fib(n) given n

//* Topics: Recursion

//* Intuition :
// We simply know that fibonacci(n) = finbonacci(n-1) + fibonacci(n-2). Just used that logic in recursion

//* Solution :
class Solution
{
public:
  int fib(int n)
  {
    if (n == 1)
      return 1;
    if (n == 0)
      return 0;
    return (fib(n - 1) + fib(n - 2));
  }
};

//* TC: O(2^n)
//* SC: O(n)

//? Subsets
//?Given an integer array nums of unique elements, return all possible subsets (the power set). The solution set must not contain duplicate subsets. Return the solution in any order.

//* Topics: Backtracking

//* Intuition :
// Already learnt about subsets in recursionBasics

//* Solution :
class Solution
{
private:
  void solve(int idx, vector<int> &arr, vector<int> &curr, vector<vector<int>> &result)
  {
    if (idx == arr.size())
    {
      result.push_back(curr);
      return;
    }
    solve(idx + 1, arr, curr, result);
    curr.push_back(arr[idx]);
    solve(idx + 1, arr, curr, result);
    curr.pop_back();
  }

public:
  vector<vector<int>> subsets(vector<int> &nums)
  {
    vector<vector<int>> result;
    vector<int> curr;
    solve(0, nums, curr, result);
    return result;
  }
};

//* TC: O((2^n) * n)
//* SC: O((2^n) * n)

//? Subsets II
//? Given an integer array nums that may contain duplicates, return all possible subsets (the power set). The solution set must not contain duplicate subsets. Return the solution in any order.

//* Intuition :
// This is similar to the Subsets question but a slight twist that it has duplicate elements and we dont want any duplicate subset in it. Now suppose I encountered a number a decided to take the two routes include and exclude, again for the same never ever if I take the decision of include and exclude it will make duplicates, so first my target is to sort the array to get all the similar elements one after another. When i have dont sorting I will use the include exclude logic for one such element and skip it for all rest similar elements. And in every such problem we have a general template to remove duplicates after sorting.

//* Solution :
class Solution
{
public:
  void subsetFinder(vector<int> nums, vector<int> &currAns, vector<vector<int>> &result, int i)
  {
    // Base case
    if (i == nums.size())
    {
      result.push_back(currAns);
      return;
    }
    // If we want to include the current element
    currAns.push_back(nums[i]);
    // Recursive call when included
    subsetFinder(nums, currAns, result, i + 1);

    // If we want to exclude the element
    currAns.pop_back();
    // general remove duplicate template
    i++;
    while (i < nums.size() && nums[i] == nums[i - 1])
    {
      i++;
    }
    // Recursive call when excluded
    subsetFinder(nums, currAns, result, i);
  }

  vector<vector<int>> subsetsWithDup(vector<int> &nums)
  {
    // Lets sort the array so that all similar elemets come one after another, then we can remove duplicates
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> currAns;
    subsetFinder(nums, currAns, result, 0);
    return result;
  }
};

//* TC: O(n(logn) + ((2^n) * n)) -> O((2^n) * n)
//* SC: O((2^n) * n)

//? Permutations
//? Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

//* Intuition :
// Here we use the basic concept of permutations as seen in recursionBasics. Every blank space will have option to choose from the left over elements which have not been used to fill any previous blank

//* Solution :
class Solution
{
public:
  int n;
  vector<vector<int>> result;
  unordered_set<int> st;

  void solve(vector<int> &nums, vector<int> &temp)
  {
    // Base case
    if (temp.size() == n)
    {
      result.push_back(temp);
      return;
    }
    // We will always loop through all elements and keep on checking in set
    for (int i = 0; i < n; i++)
    {
      // Let us include only if its not present in temp
      if (st.find(nums[i]) == st.end())
      {
        temp.push_back(nums[i]);
        st.insert(nums[i]);
        // Recursively call
        solve(nums, temp);
        // Let us now exclude during backtracking
        temp.pop_back();
        st.erase(nums[i]);
      }
    }
  }

  vector<vector<int>> permute(vector<int> &nums)
  {
    n = nums.size();
    vector<int> temp;
    solve(nums, temp);

    return result;
  }
};

//* TC: O(n * n!)
//* SC: O(n * n!)
