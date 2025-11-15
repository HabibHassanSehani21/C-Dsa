// Queue - FIFO (First In First Out) Data Structure in C++
#include <iostream>
#include <queue>
using namespace std;

void demonstrateQueue() {
    cout << "=== Queue Operations ===" << endl;
    
    // Declaration
    queue<int> q;
    
    // Enqueue elements (push)
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    
    cout << "Front element: " << q.front() << endl;
    cout << "Back element: " << q.back() << endl;
    cout << "Size: " << q.size() << endl;
    cout << "Is empty: " << q.empty() << endl;
    
    // Display all elements (by dequeuing)
    cout << "Queue elements (front to back): ";
    queue<int> temp = q; // Copy to preserve original
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
    
    // Dequeue elements
    cout << "Dequeuing elements: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    cout << "Is empty after dequeuing: " << q.empty() << endl;
}

void demonstratePriorityQueue() {
    cout << "\n=== Priority Queue Operations ===" << endl;
    
    // Max heap (default)
    priority_queue<int> maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(50);
    maxHeap.push(20);
    maxHeap.push(40);
    
    cout << "Max Heap elements: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);
    minHeap.push(40);
    
    cout << "Min Heap elements: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
}

void demonstrateDeque() {
    cout << "\n=== Deque (Double-Ended Queue) Operations ===" << endl;
    
    deque<int> dq;
    
    // Add elements at both ends
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);
    dq.push_front(1);
    
    cout << "Deque elements: ";
    for (auto x : dq) {
        cout << x << " ";
    }
    cout << endl;
    
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << endl;
    
    // Remove from both ends
    dq.pop_front();
    dq.pop_back();
    
    cout << "After removing front and back: ";
    for (auto x : dq) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    demonstrateQueue();
    demonstratePriorityQueue();
    demonstrateDeque();
    
    return 0;
}

/*
Time Complexity:
Queue:
- Push: O(1)
- Pop: O(1)
- Front/Back: O(1)

Priority Queue:
- Push: O(log n)
- Pop: O(log n)
- Top: O(1)

Deque:
- Push/Pop at both ends: O(1)
- Random access: O(1)

Space Complexity: O(n)
*/
