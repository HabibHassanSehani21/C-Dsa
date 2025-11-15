# C++ Data Structures and Algorithms

A comprehensive collection of C++ implementations for data structures, algorithms, and common programming patterns with detailed explanations and complexity analysis.

## 📁 Repository Structure

### 1. **STL (Standard Template Library)**
- `vector.cpp` - Dynamic arrays and operations
- `stack.cpp` - LIFO data structure with balanced parentheses example
- `queue.cpp` - FIFO, Priority Queue, and Deque implementations
- `map.cpp` - Ordered and unordered maps, multimap
- `set.cpp` - Ordered and unordered sets, multiset

### 2. **Data Structures**
- `linked_list.cpp` - Singly and doubly linked lists
- `tree.cpp` - Binary Search Tree with traversals
- `graph.cpp` - Graph representation (adjacency list), BFS, DFS, cycle detection
- `trie.cpp` - Prefix tree for efficient string operations
- `union_find.cpp` - Disjoint Set Union for connectivity problems

### 3. **Sorting Algorithms**
- `bubble_sort.cpp` - O(n²) simple comparison sort
- `merge_sort.cpp` - O(n log n) divide and conquer
- `quick_sort.cpp` - O(n log n) average case, in-place
- `heap_sort.cpp` - O(n log n) using binary heap

### 4. **Search Algorithms**
- `binary_search.cpp` - O(log n) search in sorted arrays
- `linear_search.cpp` - O(n) sequential search

### 5. **Graph Algorithms**
- `dijkstra.cpp` - Shortest path (non-negative weights)
- `bellman_ford.cpp` - Shortest path (handles negative weights)
- `kruskal.cpp` - Minimum Spanning Tree (edge-based)
- `prim.cpp` - Minimum Spanning Tree (vertex-based)

### 6. **Dynamic Programming**
- `knapsack.cpp` - 0/1 Knapsack, Unbounded, Fractional
- `lcs.cpp` - Longest Common Subsequence
- `lis.cpp` - Longest Increasing Subsequence
- `edit_distance.cpp` - Levenshtein Distance

### 7. **Tree Algorithms**
- `lca.cpp` - Lowest Common Ancestor (multiple approaches)
- `diameter.cpp` - Longest path in tree
- `serialization.cpp` - Tree serialization/deserialization

### 8. **String Algorithms**
- `kmp.cpp` - Knuth-Morris-Pratt pattern matching
- `rabin_karp.cpp` - Rolling hash pattern matching

### 9. **Patterns & Techniques**
- `two_pointers.cpp` - Two Sum, Remove Duplicates, Palindrome
- `sliding_window.cpp` - Maximum Sum, Longest Substring
- `backtracking.cpp` - Subsets, Permutations, N-Queens

### 10. **Complexity Analysis**
- `complexity_analysis.cpp` - Time and space complexity guide

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++17 support (g++, clang++)
- Basic understanding of C++ and data structures

### Compilation
Each file is standalone and can be compiled individually:

```bash
g++ -std=c++17 STL/vector.cpp -o vector
./vector

g++ -std=c++17 Sorting/quick_sort.cpp -o quicksort
./quicksort

g++ -std=c++17 DynamicProgramming/knapsack.cpp -o knapsack
./knapsack
```

## 📊 Complexity Reference

### Time Complexity Hierarchy
```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2^n) < O(n!)
```

### Data Structure Operations
| Data Structure | Access | Search | Insert | Delete |
|---------------|---------|---------|---------|---------|
| Array | O(1) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1)* | O(1)* |
| Hash Table | - | O(1)† | O(1)† | O(1)† |
| Binary Search Tree | O(log n)† | O(log n)† | O(log n)† | O(log n)† |
| Heap | - | O(n) | O(log n) | O(log n) |

*at head/tail, †average case

### Sorting Algorithms
| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

## 💡 Features

Each implementation includes:
- ✅ Detailed inline comments
- ✅ Time and space complexity analysis
- ✅ Multiple examples and test cases
- ✅ Common variations and optimizations
- ✅ Practical applications
- ✅ Best practices and tips

## 🎯 Use Cases

- **Interview Preparation**: All common DSA interview topics covered
- **Learning Resource**: Clear explanations for each concept
- **Reference Guide**: Quick lookup for implementations
- **Competitive Programming**: Optimized algorithms ready to use

## 📚 Topics Covered

- Standard Template Library (STL) containers
- Linear and non-linear data structures
- Sorting and searching algorithms
- Graph algorithms (shortest path, MST)
- Dynamic programming problems
- Tree algorithms and traversals
- String matching algorithms
- Common coding patterns
- Complexity analysis

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Add new algorithms
- Improve existing implementations
- Fix bugs
- Add more examples
- Improve documentation

## 📝 License

This project is available for educational purposes.

## 📧 Contact

For questions or suggestions, please open an issue in the repository.

---

**Happy Coding! 🚀**