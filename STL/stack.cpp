// Stack - LIFO (Last In First Out) Data Structure in C++
#include <iostream>
#include <stack>
using namespace std;

void demonstrateStack() {
    cout << "=== Stack Operations ===" << endl;
    
    // Declaration
    stack<int> st;
    
    // Push elements
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);
    st.push(50);
    
    cout << "Top element: " << st.top() << endl;
    cout << "Size: " << st.size() << endl;
    cout << "Is empty: " << st.empty() << endl;
    
    // Display all elements (by popping)
    cout << "Stack elements (top to bottom): ";
    stack<int> temp = st; // Copy to preserve original
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
    
    // Pop elements
    cout << "Popping elements: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
    
    cout << "Is empty after popping: " << st.empty() << endl;
}

// Example: Balanced Parentheses using Stack
bool isBalanced(string expr) {
    stack<char> st;
    
    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) return false;
            
            char top = st.top();
            st.pop();
            
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return st.empty();
}

int main() {
    demonstrateStack();
    
    cout << "\n=== Balanced Parentheses Example ===" << endl;
    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    
    cout << expr1 << " is " << (isBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is " << (isBalanced(expr2) ? "balanced" : "not balanced") << endl;
    
    return 0;
}

/*
Time Complexity:
- Push: O(1)
- Pop: O(1)
- Top: O(1)
- Empty: O(1)

Space Complexity: O(n)
*/
