#include <stdio.h>
#include <stdlib.h>

// Define a maximum stack size for the iterative traversal
// This is used for the explicit stack necessary for the iterative inorder traversal.
#define STACK_SIZE 100

// --- Structure Definitions ---

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Simple Stack for Iterative Traversal
struct Node* stack[STACK_SIZE];
int top = -1;

void push(struct Node* node) {
    if (top < STACK_SIZE - 1) {
        stack[++top] = node;
    }
}

struct Node* pop() {
    if (top > -1) {
        return stack[top--];
    }
    return NULL;
}

// --- Basic Utility Functions ---

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ------------------------------------------------------------------
// --- 1. Non-Recursive (Iterative) Insertion Function ---
// ------------------------------------------------------------------

struct Node* insertIterative(struct Node* root, int data) {
    // 1. Handle the case of an empty tree (Base Case)
    if (root == NULL) {
        return createNode(data);
    }

    // Pointers for traversal
    struct Node* current = root;
    struct Node* parent = NULL; // Tracks the node before 'current'

    // 2. Loop to find the insertion spot
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            // Move left
            current = current->left;
        } else if (data > current->data) {
            // Move right
            current = current->right;
        } else {
            // Data already exists, do nothing (assuming no duplicates)
            printf("Data %d already exists. Not inserting.\n", data);
            return root;
        }
    }

    // 3. Create the new node
    struct Node* newNode = createNode(data);

    // 4. Link the new node to the parent
    if (data < parent->data) {
        parent->left = newNode;
    } else { // data > parent->data
        parent->right = newNode;
    }

    return root; // Return the original root
}

// ------------------------------------------------------------------
// --- 2. Non-Recursive (Iterative) Inorder Traversal Function ---
// ------------------------------------------------------------------

void inorderTraversalIterative(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* current = root;
    top = -1; // Reset stack pointer before traversal

    while (current != NULL || top > -1) {
        // Reach the leftmost node of the current subtree
        while (current != NULL) {
            push(current);
            current = current->left;
        }

        // Current must be NULL at this point, so we pop the element from stack
        current = pop();

        // Print the data (Visit the Root)
        printf("%d ", current->data);

        // Move to the right subtree
        current = current->right;
    }
}


// ------------------------------------------------------------------
// --- Main Function (Menu) ---
// ------------------------------------------------------------------

int main() {
    struct Node* root = NULL;
    int choice, data;
    
    do {
        printf("\n--- Binary Search Tree Operations (Iterative) ---\n");
        printf("1. Insert a node\n");
        printf("2. Display tree (Iterative Inorder Traversal)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        // Ensure input is successfully read
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Clearing buffer.\n");
            // Clear input buffer to prevent infinite loop
            while (getchar() != '\n');
            choice = 0; // Set choice to an invalid value
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid input for data. Clearing buffer.\n");
                    while (getchar() != '\n');
                    break;
                }
                root = insertIterative(root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversalIterative(root);
                printf("\n");
                break;
            case 3:
                printf("Exiting program. (Note: Tree memory is not explicitly freed for simplicity.)\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
