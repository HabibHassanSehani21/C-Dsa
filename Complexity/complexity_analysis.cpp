// Time and Space Complexity Analysis - Examples and Guide
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
using namespace std;

// ==================== TIME COMPLEXITY EXAMPLES ====================

// O(1) - Constant Time
int constantTime(int n) {
    return n * 2;  // Single operation, independent of input size
}

// O(log n) - Logarithmic Time
int logarithmicTime(int n) {
    int count = 0;
    while (n > 1) {
        n = n / 2;
        count++;
    }
    return count;
}

// O(n) - Linear Time
int linearTime(const vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return sum;
}

// O(n log n) - Linearithmic Time
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // Merge operation (O(n))
    }
}

// O(n²) - Quadratic Time
int quadraticTime(const vector<int>& arr) {
    int count = 0;
    int n = arr.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count++;
        }
    }
    
    return count;
}

// O(n³) - Cubic Time
int cubicTime(const vector<int>& arr) {
    int count = 0;
    int n = arr.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                count++;
            }
        }
    }
    
    return count;
}

// O(2^n) - Exponential Time (Fibonacci - naive)
int exponentialTime(int n) {
    if (n <= 1) return n;
    return exponentialTime(n - 1) + exponentialTime(n - 2);
}

// O(n!) - Factorial Time (Permutations)
void factorialTime(vector<int>& arr, int start, int& count) {
    if (start == arr.size()) {
        count++;
        return;
    }
    
    for (int i = start; i < arr.size(); i++) {
        swap(arr[start], arr[i]);
        factorialTime(arr, start + 1, count);
        swap(arr[start], arr[i]);
    }
}

// ==================== SPACE COMPLEXITY EXAMPLES ====================

// O(1) - Constant Space
int constantSpace(int n) {
    int a = 1;
    int b = 2;
    return a + b;
}

// O(n) - Linear Space
vector<int> linearSpace(int n) {
    vector<int> arr(n);
    return arr;
}

// O(n²) - Quadratic Space
vector<vector<int>> quadraticSpace(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    return matrix;
}

// Recursion Space - O(n) stack space
int recursionSpace(int n) {
    if (n <= 0) return 0;
    return n + recursionSpace(n - 1);
}

// ==================== COMPLEXITY COMPARISONS ====================

void demonstrateComplexities() {
    cout << "=== Time Complexity Demonstration ===" << endl;
    cout << "\nFor input size n = 10:" << endl;
    
    int n = 10;
    
    cout << "O(1) - Constant: 1 operation" << endl;
    cout << "O(log n) - Logarithmic: ~" << (int)log2(n) << " operations" << endl;
    cout << "O(n) - Linear: " << n << " operations" << endl;
    cout << "O(n log n) - Linearithmic: ~" << (int)(n * log2(n)) << " operations" << endl;
    cout << "O(n²) - Quadratic: " << n * n << " operations" << endl;
    cout << "O(n³) - Cubic: " << n * n * n << " operations" << endl;
    cout << "O(2^n) - Exponential: " << (1 << n) << " operations" << endl;
    
    cout << "\n=== Growth Rate Comparison ===" << endl;
    cout << "n\tO(1)\tO(log n)\tO(n)\tO(n log n)\tO(n²)\tO(2^n)" << endl;
    
    for (int size : {1, 10, 100, 1000}) {
        cout << size << "\t1\t";
        cout << (int)log2(size) << "\t\t";
        cout << size << "\t";
        cout << (int)(size * log2(size)) << "\t\t";
        cout << size * size << "\t";
        if (size <= 20) {
            cout << (1 << size);
        } else {
            cout << "huge";
        }
        cout << endl;
    }
}

// ==================== COMMON DATA STRUCTURE COMPLEXITIES ====================

void dataStructureComplexities() {
    cout << "\n=== Data Structure Time Complexities ===" << endl;
    
    cout << "\nArray/Vector:" << endl;
    cout << "  Access: O(1)" << endl;
    cout << "  Search: O(n)" << endl;
    cout << "  Insert at end: O(1) amortized" << endl;
    cout << "  Insert at position: O(n)" << endl;
    cout << "  Delete: O(n)" << endl;
    
    cout << "\nLinked List:" << endl;
    cout << "  Access: O(n)" << endl;
    cout << "  Search: O(n)" << endl;
    cout << "  Insert at head: O(1)" << endl;
    cout << "  Insert at position: O(n)" << endl;
    cout << "  Delete: O(n)" << endl;
    
    cout << "\nHash Table (unordered_map/unordered_set):" << endl;
    cout << "  Search: O(1) average, O(n) worst" << endl;
    cout << "  Insert: O(1) average, O(n) worst" << endl;
    cout << "  Delete: O(1) average, O(n) worst" << endl;
    
    cout << "\nBinary Search Tree:" << endl;
    cout << "  Search: O(log n) average, O(n) worst" << endl;
    cout << "  Insert: O(log n) average, O(n) worst" << endl;
    cout << "  Delete: O(log n) average, O(n) worst" << endl;
    
    cout << "\nBalanced BST (map/set):" << endl;
    cout << "  Search: O(log n)" << endl;
    cout << "  Insert: O(log n)" << endl;
    cout << "  Delete: O(log n)" << endl;
    
    cout << "\nHeap/Priority Queue:" << endl;
    cout << "  Find min/max: O(1)" << endl;
    cout << "  Insert: O(log n)" << endl;
    cout << "  Delete min/max: O(log n)" << endl;
    
    cout << "\nStack/Queue:" << endl;
    cout << "  Push/Enqueue: O(1)" << endl;
    cout << "  Pop/Dequeue: O(1)" << endl;
    cout << "  Peek: O(1)" << endl;
}

// ==================== SORTING ALGORITHM COMPLEXITIES ====================

void sortingComplexities() {
    cout << "\n=== Sorting Algorithm Complexities ===" << endl;
    cout << "\nAlgorithm\t\tBest\t\tAverage\t\tWorst\t\tSpace" << endl;
    cout << "Bubble Sort\t\tO(n)\t\tO(n²)\t\tO(n²)\t\tO(1)" << endl;
    cout << "Selection Sort\t\tO(n²)\t\tO(n²)\t\tO(n²)\t\tO(1)" << endl;
    cout << "Insertion Sort\t\tO(n)\t\tO(n²)\t\tO(n²)\t\tO(1)" << endl;
    cout << "Merge Sort\t\tO(n log n)\tO(n log n)\tO(n log n)\tO(n)" << endl;
    cout << "Quick Sort\t\tO(n log n)\tO(n log n)\tO(n²)\t\tO(log n)" << endl;
    cout << "Heap Sort\t\tO(n log n)\tO(n log n)\tO(n log n)\tO(1)" << endl;
    cout << "Counting Sort\t\tO(n+k)\t\tO(n+k)\t\tO(n+k)\t\tO(k)" << endl;
    cout << "Radix Sort\t\tO(nk)\t\tO(nk)\t\tO(nk)\t\tO(n+k)" << endl;
}

// ==================== TIPS FOR COMPLEXITY ANALYSIS ====================

void complexityTips() {
    cout << "\n=== Tips for Analyzing Complexity ===" << endl;
    
    cout << "\n1. Loop Analysis:" << endl;
    cout << "   - Single loop: O(n)" << endl;
    cout << "   - Nested loops: Multiply complexities" << endl;
    cout << "   - Sequential loops: Add complexities (take dominant)" << endl;
    
    cout << "\n2. Recursion Analysis:" << endl;
    cout << "   - Count recursive calls at each level" << endl;
    cout << "   - Multiply by work done at each call" << endl;
    cout << "   - Use recurrence relations or Master Theorem" << endl;
    
    cout << "\n3. Space Complexity:" << endl;
    cout << "   - Consider auxiliary space used" << endl;
    cout << "   - Recursion uses O(depth) stack space" << endl;
    cout << "   - Don't count input/output space" << endl;
    
    cout << "\n4. Best Practices:" << endl;
    cout << "   - Drop constants: O(2n) → O(n)" << endl;
    cout << "   - Drop non-dominant terms: O(n² + n) → O(n²)" << endl;
    cout << "   - Consider average case for practical analysis" << endl;
    cout << "   - Consider worst case for guarantees" << endl;
    
    cout << "\n5. Common Patterns:" << endl;
    cout << "   - Dividing by 2 repeatedly: O(log n)" << endl;
    cout << "   - All subsets: O(2^n)" << endl;
    cout << "   - All permutations: O(n!)" << endl;
    cout << "   - Sorted array search: O(log n)" << endl;
    cout << "   - Tree traversal: O(n)" << endl;
}

int main() {
    cout << "======================================" << endl;
    cout << " TIME AND SPACE COMPLEXITY ANALYSIS" << endl;
    cout << "======================================" << endl;
    
    demonstrateComplexities();
    dataStructureComplexities();
    sortingComplexities();
    complexityTips();
    
    cout << "\n=== Big-O Notation Hierarchy ===" << endl;
    cout << "O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2^n) < O(n!)" << endl;
    cout << "\nFaster ←→ Slower" << endl;
    
    return 0;
}

/*
KEY CONCEPTS:

Big-O Notation:
- Describes upper bound (worst case)
- Focuses on growth rate, not exact operations
- Ignores constants and lower-order terms

Big-Omega (Ω):
- Describes lower bound (best case)

Big-Theta (Θ):
- Describes tight bound (average case)

Master Theorem (for divide-and-conquer):
T(n) = aT(n/b) + f(n)
- If f(n) = O(n^c) where c < log_b(a): T(n) = Θ(n^(log_b(a)))
- If f(n) = Θ(n^c) where c = log_b(a): T(n) = Θ(n^c log n)
- If f(n) = Ω(n^c) where c > log_b(a): T(n) = Θ(f(n))

Amortized Analysis:
- Average time per operation over worst-case sequence
- Example: Dynamic array resize is O(1) amortized

Space-Time Tradeoff:
- Often can reduce time by using more space
- Or reduce space at cost of more time
- Choose based on constraints
*/
