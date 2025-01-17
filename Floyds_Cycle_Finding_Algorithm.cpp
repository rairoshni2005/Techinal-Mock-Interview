// Implement a function to detect a cycle in a singly linked list and return the starting node of the cycle, if present. If no cycle exists, return None. Your solution should use Floyd's Cycle-Finding Algorithm (Tortoise and Hare) and must run in O(n) time complexity.
// Additionally, implement a helper function to remove the cycle (if present), effectively "breaking" the cycle and making the list acyclic.
// Constraints : You must solve this problem using constant space (O(1)) in addition to the input list.

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to detect a cycle and return the starting node of the cycle
ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) { // Cycle detected
            slow = head;
            while (slow != fast) { // Find the start of the cycle
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // Return the starting node of the cycle
        }
    }
    return nullptr; // No cycle
}

// Function to remove a cycle
void removeCycle(ListNode* head) {
    ListNode* cycleStart = detectCycle(head);
    if (!cycleStart) return;

    ListNode* temp = cycleStart;
    while (temp->next != cycleStart) {
        temp = temp->next;
    }
    temp->next = nullptr; // Break the cycle
}

// Function to create a linked list from user input
ListNode* createLinkedList() {
    int n;
    cout << "Enter the number of nodes in the list: ";
    cin >> n;

    if (n <= 0) return nullptr;

    cout << "Enter the values of the nodes: ";
    int val;
    cin >> val;
    ListNode* head = new ListNode(val);
    ListNode* current = head;

    for (int i = 1; i < n; ++i) {
        cin >> val;
        current->next = new ListNode(val);
        current = current->next;
    }

    int cyclePos;
    cout << "Enter the position to create a cycle (0 for no cycle): ";
    cin >> cyclePos;

    if (cyclePos > 0) {
        ListNode* temp = head;
        for (int i = 1; i < cyclePos; ++i) {
            temp = temp->next;
        }
        current->next = temp; // Create the cycle
    }

    return head;
}

int main() {
    // Create linked list from user input
    ListNode* head = createLinkedList();

    // Detect cycle
    ListNode* cycleStart = detectCycle(head);
    if (cycleStart) {
        cout << "Output: Cycle starts at node with value " << cycleStart->val << "\n";
        removeCycle(head);
        cout << "Cycle removed.\n";
    } else {
        cout << "Output: None (no cycle)\n";
    }

    // Print the modified list
    cout << "Modified List: ";
    ListNode* temp = head;
    while (temp) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";

    return 0;
}
