//* Recursion
//? This is scenario where function calls itself. To stop this recursion being infinte we set a base case and the recursion logic always leads to the base case.

//? We will try to implement solution for a part of the problem and call the function recursively for the rest of the part to be solved. We take a leap of faith, have belief and call the function.

//* Recurrance Relation
//? This is a mathematical relation we use to find time complexity of recursion

//* Tail Recursive
//? A recursive function where the last step is a recursion call
// Like the printReverse is tail recursion but factorial is not tail recursion as the last step in factorial is multiplication

#include <bits/stdc++.h>
using namespace std;

//? Print from n to 1
void printReverse(int n)
{
  // Base case
  if (n < 1)
  {
    return;
  }
  // Recursive logic
  cout << n << " ";
  printReverse(n - 1);
}

//? f(n) = print + f(n-1) => O(n) = O(1) + O(n-1) -> Recurrance relation

//? N factorial
int factorial(int n)
{
  // Base case
  if (n == 0)
  {
    return 1;
  }
  // Recursive call
  return (n * factorial(n - 1));
}

//? f(n) = multiply + f(n-1) => O(n) = O(1) + O(n-1)
/*
f(n)   = k + f(n-1)
f(n-1) = k + f(n-2)
f(n-2) = k + f(n-3)
.      = . + .
.      = . + .
.      = . + .
f(1)   = k + f(1)

After cutting from both sides we get
f(n) = k * n
*/
//! Time complexity: O(n)
//! Space complexity: O(n)

//! Always reccurance relation is not so intuitive. So we use the recursion tree.
//! Space complexity SC = Depth of recurssion tree * memeory in each call / SC = Height of callstack * memory in each call

//? Sum of n numbers
int sumTillN(int n)
{
  // Base case
  if (n == 0)
  {
    return 0;
  }
  // Recursive call
  return (n + sumTillN(n - 1));
}

//! TC: O(n)
//! SC: O(n)

//? Nth Fibonacci -> 0, 1, 1, 2, 3, 5, 8, 13, ...  f(n) = f(n-1) + f(n-2)
int fibonacci(int n)
{
  // Base case
  if (n == 1 || n == 0)
  {
    return n;
  }
  // Recursive call
  return fibonacci(n - 1) + fibonacci(n - 2);
}

//! TC: O(2^n)
//! SC: O(n)

//? Check if array is sorted
bool isSortedAsc(vector<int> nums, int n)
{
  // Base case
  if (n == 0 || n == 1)
  {
    return true;
  }
  // Recursive call
  return (nums[n - 1] >= nums[n - 2]) && isSortedAsc(nums, n - 1);
}

//! TC: O(n)
//! SC: O(n)

//? Recursive Binary search
int recursiveBinarySearch(vector<int> nums, int target, int start, int end)
{
  // Recursive call
  if (start <= end)
  {
    int mid = start + (end - start) / 2;
    if (target < nums[mid])
    {
      return recursiveBinarySearch(nums, target, start, mid - 1);
    }
    else if (target > nums[mid])
    {
      return recursiveBinarySearch(nums, target, mid + 1, end);
    }
    else
    {
      return mid;
    }
  }
  else
  {
    return -1;
  }
}

//! TC: O(log(n))
//! SC: O(log(n))

//* Backtracking
//? This is actually the coming back through the path in the call stack that we travelled during the recursive calls and doing something while coming back.

//? Print all subsets (Concept of Subsets) -> used in many questions
// For any vector having n elements there exits 2^n number of subsets. Now every element has an option to either enter the subset or not enter. If we have a vector with suppose 1 element [1], then finding subsets is very easy its either {1} or {}. This choice will give us the hint of backtracking.
void printSubsets(vector<int> nums, vector<int> &result, int i) // sending vector by reference so that changes are saved
{
  // Base case
  if (i == nums.size())
  {
    for (auto i : result)
    {
      cout << i;
    }
    cout << endl;
    return;
  }
  // If we want to include
  result.push_back(nums[i]);
  // Recursive call with the current element included
  printSubsets(nums, result, i + 1);

  // If we dont want to include (so while coming back during backtracking)
  result.pop_back();
  // Recursive call without the current element included after popping
  printSubsets(nums, result, i + 1);
}

//! TC: O((2^n) * n)
//! SC: O((2^n) * n)

//? Find all permutations (Concept of permutation)
// Here also at each blank we have choice of having any one of the number or not having it. A vector with n elements have n! number of permutations
void printPermutations(vector<int> nums, int n, vector<int> &temp, vector<vector<int>> &result, unordered_set<int> &st)
{
  // Base case
  if (temp.size() == n)
  {
    result.push_back(temp);
    return;
  }
  // We always start looping from the first and keep on checking it the element is already used
  for (int i = 0; i < n; i++)
  {
    // If element is not there in temp only then we
    if (st.find(nums[i]) == st.end())
    {
      temp.push_back(nums[i]);
      st.insert(nums[i]); // We insert the used element in set to keep check if its used
      // Recursive call after including
      printPermutations(nums, n, temp, result, st);
      // Exclude the element
      temp.pop_back();
      st.erase(nums[i]); // Erase it from the set because now we can include it
    }
  }
}

//* TC: O(n * n!)
//* SC: O(n + n!) -> O(n!)

int main()
{
  // printReverse(50);
  // cout << factorial(5) << endl;
  // cout << sumTillN(5) << endl;
  // cout << fibonacci(7) << endl;
  vector<int> nums = {1, 2, 3, 4, 5};
  int n = nums.size();
  // cout << isSortedAsc(nums, n) << endl;
  // cout << recursiveBinarySearch(nums, 4, 0, n - 1) << endl;
  // cout << recursiveBinarySearch(nums, 10, 0, n - 1) << endl;
  vector<int> result;
  // printSubsets(nums, result, 0);

  return 0;
}
