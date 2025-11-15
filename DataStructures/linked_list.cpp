// Linked List - Linear Data Structure with Nodes
#include <iostream>
using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    // Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    
    // Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Insert at position
    void insertAtPosition(int val, int pos) {
        if (pos == 0) {
            insertAtBeginning(val);
            return;
        }
        
        Node* newNode = new Node(val);
        Node* temp = head;
        
        for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        
        if (temp == nullptr) {
            cout << "Position out of bounds" << endl;
            delete newNode;
            return;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
    }
    
    // Delete from beginning
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    // Delete from end
    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        
        delete temp->next;
        temp->next = nullptr;
    }
    
    // Delete by value
    void deleteByValue(int val) {
        if (head == nullptr) return;
        
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != val) {
            temp = temp->next;
        }
        
        if (temp->next == nullptr) {
            cout << "Value not found" << endl;
            return;
        }
        
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
    
    // Search for value
    bool search(int val) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }
    
    // Reverse the list
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
    }
    
    // Display list
    void display() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    
    // Get length
    int length() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    
    // Destructor
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Doubly Linked List Node
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    void insertAtEnd(int val) {
        DNode* newNode = new DNode(val);
        
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    void display() {
        DNode* temp = head;
        cout << "NULL <-> ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    
    ~DoublyLinkedList() {
        while (head != nullptr) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    cout << "=== Singly Linked List ===" << endl;
    LinkedList ll;
    
    ll.insertAtEnd(10);
    ll.insertAtEnd(20);
    ll.insertAtEnd(30);
    ll.insertAtBeginning(5);
    ll.insertAtPosition(15, 2);
    
    cout << "List: ";
    ll.display();
    cout << "Length: " << ll.length() << endl;
    
    cout << "Search 20: " << (ll.search(20) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (ll.search(100) ? "Found" : "Not Found") << endl;
    
    ll.deleteFromBeginning();
    cout << "After deleting from beginning: ";
    ll.display();
    
    ll.deleteFromEnd();
    cout << "After deleting from end: ";
    ll.display();
    
    ll.reverse();
    cout << "After reversing: ";
    ll.display();
    
    cout << "\n=== Doubly Linked List ===" << endl;
    DoublyLinkedList dll;
    dll.insertAtEnd(100);
    dll.insertAtEnd(200);
    dll.insertAtEnd(300);
    dll.display();
    
    return 0;
}

/*
Time Complexity:
- Insert at beginning: O(1)
- Insert at end: O(n) for singly, O(1) for doubly
- Insert at position: O(n)
- Delete: O(n)
- Search: O(n)
- Reverse: O(n)

Space Complexity: O(n)
*/
