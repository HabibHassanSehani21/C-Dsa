// Backtracking - Recursive Problem Solving Technique
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 1. Generate all subsets (Power Set)
void generateSubsetsHelper(const vector<int>& nums, int index, 
                           vector<int>& current, vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = index; i < nums.size(); i++) {
        current.push_back(nums[i]);
        generateSubsetsHelper(nums, i + 1, current, result);
        current.pop_back();  // Backtrack
    }
}

vector<vector<int>> generateSubsets(const vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    generateSubsetsHelper(nums, 0, current, result);
    return result;
}

// 2. Generate all permutations
void permuteHelper(vector<int>& nums, int start, vector<vector<int>>& result) {
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }
    
    for (int i = start; i < nums.size(); i++) {
        swap(nums[start], nums[i]);
        permuteHelper(nums, start + 1, result);
        swap(nums[start], nums[i]);  // Backtrack
    }
}

vector<vector<int>> permute(vector<int> nums) {
    vector<vector<int>> result;
    permuteHelper(nums, 0, result);
    return result;
}

// 3. Generate all combinations of k elements
void combineHelper(int n, int k, int start, vector<int>& current, 
                   vector<vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }
    
    for (int i = start; i <= n; i++) {
        current.push_back(i);
        combineHelper(n, k, i + 1, current, result);
        current.pop_back();  // Backtrack
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> current;
    combineHelper(n, k, 1, current, result);
    return result;
}

// 4. N-Queens Problem
bool isSafe(const vector<string>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    
    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    
    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    
    return true;
}

void solveNQueensHelper(int n, int row, vector<string>& board, 
                        vector<vector<string>>& result) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            solveNQueensHelper(n, row + 1, board, result);
            board[row][col] = '.';  // Backtrack
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    solveNQueensHelper(n, 0, board, result);
    return result;
}

// 5. Sudoku Solver
bool isValidSudoku(vector<vector<char>>& board, int row, int col, char num) {
    // Check row
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num) return false;
    }
    
    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) return false;
    }
    
    // Check 3x3 box
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) return false;
        }
    }
    
    return true;
}

bool solveSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValidSudoku(board, i, j, num)) {
                        board[i][j] = num;
                        
                        if (solveSudoku(board)) {
                            return true;
                        }
                        
                        board[i][j] = '.';  // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// 6. Generate Parentheses
void generateParenthesisHelper(int n, int open, int close, 
                               string current, vector<string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    
    if (open < n) {
        generateParenthesisHelper(n, open + 1, close, current + "(", result);
    }
    
    if (close < open) {
        generateParenthesisHelper(n, open, close + 1, current + ")", result);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    generateParenthesisHelper(n, 0, 0, "", result);
    return result;
}

// 7. Letter Combinations of Phone Number
const vector<string> keyboard = {"", "", "abc", "def", "ghi", "jkl", 
                                 "mno", "pqrs", "tuv", "wxyz"};

void letterCombinationsHelper(const string& digits, int index, 
                              string current, vector<string>& result) {
    if (index == digits.length()) {
        result.push_back(current);
        return;
    }
    
    int digit = digits[index] - '0';
    for (char c : keyboard[digit]) {
        letterCombinationsHelper(digits, index + 1, current + c, result);
    }
}

vector<string> letterCombinations(const string& digits) {
    if (digits.empty()) return {};
    
    vector<string> result;
    letterCombinationsHelper(digits, 0, "", result);
    return result;
}

// 8. Word Search in Grid
bool wordSearchHelper(vector<vector<char>>& board, const string& word, 
                     int row, int col, int index) {
    if (index == word.length()) return true;
    
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
        board[row][col] != word[index]) {
        return false;
    }
    
    char temp = board[row][col];
    board[row][col] = '#';  // Mark as visited
    
    bool found = wordSearchHelper(board, word, row + 1, col, index + 1) ||
                 wordSearchHelper(board, word, row - 1, col, index + 1) ||
                 wordSearchHelper(board, word, row, col + 1, index + 1) ||
                 wordSearchHelper(board, word, row, col - 1, index + 1);
    
    board[row][col] = temp;  // Backtrack
    
    return found;
}

bool wordSearch(vector<vector<char>>& board, const string& word) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (wordSearchHelper(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cout << "=== Backtracking Techniques ===" << endl;
    
    cout << "\n1. Generate All Subsets" << endl;
    vector<int> nums1 = {1, 2, 3};
    cout << "Array: ";
    for (int x : nums1) cout << x << " ";
    cout << "\nSubsets:" << endl;
    auto subsets = generateSubsets(nums1);
    for (const auto& subset : subsets) {
        cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    cout << "\n2. Generate All Permutations" << endl;
    vector<int> nums2 = {1, 2, 3};
    cout << "Array: ";
    for (int x : nums2) cout << x << " ";
    cout << "\nPermutations:" << endl;
    auto perms = permute(nums2);
    for (const auto& perm : perms) {
        cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            cout << perm[i];
            if (i < perm.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    cout << "\n3. Generate Combinations" << endl;
    int n = 4, k = 2;
    cout << "n = " << n << ", k = " << k << endl;
    cout << "Combinations:" << endl;
    auto combs = combine(n, k);
    for (const auto& comb : combs) {
        cout << "[";
        for (int i = 0; i < comb.size(); i++) {
            cout << comb[i];
            if (i < comb.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    cout << "\n4. N-Queens Problem (n=4)" << endl;
    auto solutions = solveNQueens(4);
    cout << "Number of solutions: " << solutions.size() << endl;
    cout << "First solution:" << endl;
    if (!solutions.empty()) {
        for (const string& row : solutions[0]) {
            cout << row << endl;
        }
    }
    
    cout << "\n5. Generate Parentheses (n=3)" << endl;
    auto parens = generateParenthesis(3);
    cout << "Valid combinations: " << endl;
    for (const string& p : parens) {
        cout << p << endl;
    }
    
    cout << "\n6. Letter Combinations (Phone)" << endl;
    string digits = "23";
    cout << "Digits: " << digits << endl;
    cout << "Letter combinations:" << endl;
    auto letters = letterCombinations(digits);
    for (const string& combo : letters) {
        cout << combo << " ";
    }
    cout << endl;
    
    return 0;
}

/*
Time Complexity:
- Subsets: O(2^n * n)
- Permutations: O(n! * n)
- Combinations: O(C(n,k) * k)
- N-Queens: O(n!)
- Sudoku: O(9^m) where m is empty cells

Space Complexity: O(n) for recursion stack

Backtracking Pattern:
1. Choose: Make a choice
2. Explore: Recursively explore with that choice
3. Unchoose: Backtrack and try another choice

When to Use:
- Generate all solutions
- Find any valid solution
- Constraint satisfaction problems
- Combinatorial problems

Common Problems:
- Subsets, Permutations, Combinations
- N-Queens, Sudoku
- Generate Parentheses
- Word Search
- Path finding with constraints

Key Insights:
- Try all possibilities systematically
- Prune invalid branches early
- Use constraints to reduce search space
- Backtrack when constraint violated

Optimization Techniques:
- Early termination
- Constraint propagation
- Heuristics for ordering choices
- Memoization when applicable
*/
