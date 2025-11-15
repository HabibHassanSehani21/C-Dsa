// 0/1 Knapsack Problem - Dynamic Programming
#include <iostream>
#include <vector>
using namespace std;

// 0/1 Knapsack - Return maximum value
int knapsack01(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                // Max of including or excluding current item
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], 
                              dp[i-1][w]);
            } else {
                // Can't include current item
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

// 0/1 Knapsack with item selection tracking
pair<int, vector<int>> knapsack01WithItems(const vector<int>& weights, 
                                           const vector<int>& values, 
                                           int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], 
                              dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    // Backtrack to find selected items
    vector<int> selectedItems;
    int i = n, w = capacity;
    
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i-1][w]) {
            selectedItems.push_back(i-1);
            w -= weights[i-1];
        }
        i--;
    }
    
    reverse(selectedItems.begin(), selectedItems.end());
    
    return {dp[n][capacity], selectedItems};
}

// Space-optimized 0/1 Knapsack
int knapsack01Optimized(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; i++) {
        // Traverse from right to left to avoid using updated values
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }
    
    return dp[capacity];
}

// Unbounded Knapsack (can take unlimited items of each type)
int knapsackUnbounded(const vector<int>& weights, const vector<int>& values, int capacity) {
    vector<int> dp(capacity + 1, 0);
    
    for (int w = 1; w <= capacity; w++) {
        for (int i = 0; i < weights.size(); i++) {
            if (weights[i] <= w) {
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }
    }
    
    return dp[capacity];
}

// Fractional Knapsack (Greedy approach - not DP but related)
struct Item {
    int weight, value;
    double ratio;
    
    Item(int w, int v) : weight(w), value(v) {
        ratio = (double)value / weight;
    }
    
    bool operator<(const Item& other) const {
        return ratio > other.ratio;
    }
};

double knapsackFractional(vector<int> weights, vector<int> values, int capacity) {
    int n = weights.size();
    vector<Item> items;
    
    for (int i = 0; i < n; i++) {
        items.push_back(Item(weights[i], values[i]));
    }
    
    sort(items.begin(), items.end());
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    for (const Item& item : items) {
        if (remainingCapacity >= item.weight) {
            totalValue += item.value;
            remainingCapacity -= item.weight;
        } else {
            // Take fraction of item
            totalValue += item.value * ((double)remainingCapacity / item.weight);
            break;
        }
    }
    
    return totalValue;
}

int main() {
    cout << "=== 0/1 Knapsack Problem ===" << endl;
    
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;
    
    cout << "Items:" << endl;
    for (int i = 0; i < values.size(); i++) {
        cout << "Item " << i << ": weight=" << weights[i] 
             << ", value=" << values[i] << endl;
    }
    cout << "Knapsack capacity: " << capacity << endl;
    
    int maxValue = knapsack01(weights, values, capacity);
    cout << "\nMaximum value: " << maxValue << endl;
    
    cout << "\n=== 0/1 Knapsack with Item Selection ===" << endl;
    
    auto [maxVal, selectedItems] = knapsack01WithItems(weights, values, capacity);
    
    cout << "Maximum value: " << maxVal << endl;
    cout << "Selected items: ";
    for (int idx : selectedItems) {
        cout << idx << " ";
    }
    cout << endl;
    
    cout << "Details:" << endl;
    int totalWeight = 0;
    for (int idx : selectedItems) {
        cout << "Item " << idx << ": weight=" << weights[idx] 
             << ", value=" << values[idx] << endl;
        totalWeight += weights[idx];
    }
    cout << "Total weight: " << totalWeight << endl;
    
    cout << "\n=== Space-Optimized 0/1 Knapsack ===" << endl;
    
    int maxValueOpt = knapsack01Optimized(weights, values, capacity);
    cout << "Maximum value (optimized): " << maxValueOpt << endl;
    
    cout << "\n=== Unbounded Knapsack ===" << endl;
    
    vector<int> values2 = {10, 40, 50, 70};
    vector<int> weights2 = {1, 3, 4, 5};
    int capacity2 = 8;
    
    cout << "Items (unlimited quantity):" << endl;
    for (int i = 0; i < values2.size(); i++) {
        cout << "Item " << i << ": weight=" << weights2[i] 
             << ", value=" << values2[i] << endl;
    }
    cout << "Knapsack capacity: " << capacity2 << endl;
    
    int maxValueUnbounded = knapsackUnbounded(weights2, values2, capacity2);
    cout << "Maximum value: " << maxValueUnbounded << endl;
    
    cout << "\n=== Fractional Knapsack (Greedy) ===" << endl;
    
    double maxValueFractional = knapsackFractional(weights, values, capacity);
    cout << "Maximum value (fractional): " << maxValueFractional << endl;
    
    return 0;
}

/*
Time Complexity:
- 0/1 Knapsack: O(n * W) where n = items, W = capacity
- Unbounded Knapsack: O(n * W)
- Fractional Knapsack: O(n log n)

Space Complexity:
- Basic DP: O(n * W)
- Optimized: O(W)

Problem Variants:
1. 0/1 Knapsack: Each item can be taken at most once
2. Unbounded Knapsack: Unlimited quantity of each item
3. Fractional Knapsack: Can take fractions of items (greedy)
4. Bounded Knapsack: Limited quantity of each item

Applications:
- Resource allocation
- Budget management
- Cargo loading
- Portfolio optimization
- Memory allocation
- Investment decisions

Key Insights:
- DP builds solution bottom-up
- Each subproblem: max value with capacity w using first i items
- Recurrence: dp[i][w] = max(dp[i-1][w], value[i] + dp[i-1][w-weight[i]])
- Space optimization: only need previous row of DP table
*/
