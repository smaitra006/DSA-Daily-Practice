//* LeetCode Questions on recurssion

#include <bits/stdc++.h>
using namespace std;

//? Fibonacci Number
//? The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. Calculate fib(n) given n

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
//* SC: O(n!)

//? 51. N Queens
//?The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other. Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order. Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

//* Intuition :
// Here we also use our general backtracking template. We try to keep the queen at a position and keeping that we go and explore futher through recursion. If placing for all the n queens in possible then we add it to the result, otherwise we come back, try our queen in another position and explore again. In each row we can always place and also have to place 1 queen. Now before placing we also go and check if in any square in the current coloumn before our current square has a queen, or the left diagonal throught the square has a queen or the right diagonal through the square has a queen. If all of it doesnt have a queen hence this square is safe to place another queen and we explore ahead.

//* Solution :
class Solution
{
public:
  vector<vector<string>> result;

  bool isSafe(vector<string> &board, int row, int col)
  {
    int n = board.size();
    // Upward check
    for (int i = 0; i < row; i++)
    {
      if (board[i][col] == 'Q')
      {
        return false;
      }
    }
    // Left diagonal check
    int i = row, j = col;
    while (j >= 0 && i >= 0)
    {
      if (board[i][j] == 'Q')
      {
        return false;
      }
      i--;
      j--;
    }
    // Right diagonal check
    i = row, j = col;
    while (i >= 0 && col < n)
    {
      if (board[i][j] == 'Q')
      {
        return false;
      }
      i--;
      j++;
    }
    return true;
  }

  void solve(vector<vector<string>> &result, vector<string> &board, int row, int n)
  {
    // Base case
    if (row >= n)
    {
      result.push_back(board);
      return;
    }
    // We will try to place in every coloumn of each row
    for (int col = 0; col < n; col++)
    {
      // We will place only if the square is safe
      if (isSafe(board, row, col))
      {
        board[row][col] = 'Q';
        // Recursive call
        solve(result, board, row + 1, n);
        // To continue further checks we will redo our action (backtrack)
        board[row][col] = '.';
      }
    }
  }

  vector<vector<string>> solveNQueens(int n)
  {
    vector<string> board(n, string(n, '.'));
    solve(result, board, 0, n);
    return result;
  }
};

//* TC: O(n!)
//* SC: O(n)

//? Kth Symbol in Grammer
//?We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10. For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110. Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.

//* Intuition :
/*
The K-th Grammar problem follows a recursive pattern where each row is built from the previous row:
- Row 1: 0
- Row 2: 01
- Row 3: 0110
- Row 4: 01101001
Key observations:
1. Each character in row i generates exactly 2 characters in row i+1
2. '0' generates "01" and '1' generates "10"
3. Instead of building the entire string, we can work backwards from position k
The breakthrough insight is the parent-child relationship:
- Position k in row n comes from position ⌈k/2⌉ in row n-1
- If k is odd (1st child), it follows the transformation: 0→0, 1→1
- If k is even (2nd child), it follows the transformation: 0→1, 1→0

This allows us to recursively find the parent and determine the child value.
*/

//* Solution :
class Solution
{
public:
  int kthGrammar(int n, int k)
  {
    // Base case: First row always contains just "0"
    if (n == 1)
      return 0;

    // Find the parent position in the previous row
    // For position k, the parent is at position ⌈k/2⌉ -> ceiling
    // This can be calculated as: (k + 1) / 2 or k/2 + k%2
    int parent = kthGrammar(n - 1, (k + 1) / 2);

    // Determine if current position is odd (1st child) or even (2nd child)
    bool isOdd = (k % 2 == 1);

    // Apply transformation rules based on parent value and child position:
    // Parent = 0: generates "01" → 1st child = 0, 2nd child = 1
    // Parent = 1: generates "10" → 1st child = 1, 2nd child = 0
    if (parent == 0)
    {
      return isOdd ? 0 : 1; // 0 → "01"
    }
    else
    {
      return isOdd ? 1 : 0; // 1 → "10"
    }
  }
};

//* TC: O(n * log(k))
//* SC : O(n)

//? Sudoku Solver
//?

//* Intuition :
/*
1. Find an empty cell (marked with '.')
2. Try placing digits 1-9 in that cell
3. For each digit, check if it's valid (no conflicts in row, column, or 3x3 box)
4. If valid, place it and recursively solve the rest of the board
5. If the recursive call succeeds, we're done!
6. If it fails, backtrack: remove the digit and try the next one
7. If no digit works for this cell, the current path is impossible
Think of it like exploring a maze - when you hit a dead end, you backtrack
to the last decision point and try a different path.
*/

//* Solution :
class Solution
{
public:
  bool isValid(vector<vector<char>> &board, int row, int col, char digit)
  {
    // Horizontal check - check if digit exists in current row
    for (int i = 0; i < 9; i++)
    {
      if (board[row][i] == digit)
        return false;
    }

    // Vertical check - check if digit exists in current column
    for (int i = 0; i < 9; i++)
    {
      if (board[i][col] == digit)
        return false;
    }

    // 3x3 box check - check if digit exists in current 3x3 subgrid
    int startRow = (row / 3) * 3; // starting row of the 3x3 box
    int startCol = (col / 3) * 3; // starting col of the 3x3 box
    for (int i = startRow; i < startRow + 3; i++)
    {
      for (int j = startCol; j < startCol + 3; j++)
      {
        if (board[i][j] == digit)
          return false;
      }
    }

    return true; // digit can be placed safely
  }

  bool solve(vector<vector<char>> &board)
  {
    // Find the next empty cell
    for (int row = 0; row < 9; row++)
    {
      for (int col = 0; col < 9; col++)
      {
        // If we find an empty cell ('.')
        if (board[row][col] == '.')
        {
          // Try digits 1-9
          for (char digit = '1'; digit <= '9'; digit++)
          {
            // Check if this digit can be placed here
            if (isValid(board, row, col, digit))
            {
              // Place the digit
              board[row][col] = digit;

              // Recursively solve the rest of the board
              if (solve(board))
              {
                return true; // Solution found
              }

              // Backtrack: remove the digit if it doesn't lead to solution
              board[row][col] = '.';
            }
          }
          // If no digit works for this cell, return false
          return false;
        }
      }
    }
    // If no empty cells found, puzzle is solved
    return true;
  }

  void solveSudoku(vector<vector<char>> &board)
  {
    solve(board);
  }
};

//* TC: O(n ^ (no. of empty spaces))
//* SC: O(n)
