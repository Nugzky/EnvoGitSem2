#include <stdio.h>
#include <stdlib.h>

// 1. The Structure
// Notice how similar this is to your Doubly Linked List!
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 2. Create a Node
// Standard memory allocation, setting left and right to NULL
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 3. Insert a Node (Using Recursion)
// Recursion is the easiest way to traverse a tree. It means the function calls itself.
Node* insert(Node* root, int value) {
    // BASE CASE: If we found an empty spot (NULL), put the new node here!
    if (root == NULL) {
        return createNode(value);
    }

    // If the value is SMALLER than current node, go LEFT
    if (value < root->data) {
        root->left = insert(root->left, value);
    } 
    // If the value is LARGER than current node, go RIGHT
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    // Note: If value == root->data, we do nothing. Standard BSTs don't allow duplicates.
    
    // Return the unchanged node pointer back up the chain
    return root;
}

// 4. Inorder Traversal (Left -> Root -> Right)
// Magic trick: If you read a BST this way, it prints the numbers in perfectly sorted order!
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);  // 1. Go as far left as possible (smallest numbers)
        printf("%d ", root->data);     // 2. Print the current node
        inorderTraversal(root->right); // 3. Go right (larger numbers)
    }
}

// 5. Search for a value
Node* search(Node* root, int target) {
    // If we hit a dead end, or if we found the target, return this node
    if (root == NULL || root->data == target) {
        return root;
    }

    // If target is smaller, search the left side
    if (target < root->data) {
        return search(root->left, target);
    }
    
    // If target is larger, search the right side
    return search(root->right, target);
}

int main() {
    Node* root = NULL; // Start with an empty tree

    // Inserting nodes
    // We capture the return value in 'root' to keep track of the very top of the tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Let's print it to see if it worked. 
    // It should print: 20 30 40 50 60 70 80
    printf("Inorder Traversal (Sorted): ");
    inorderTraversal(root);
    printf("\n");

    // Let's test the search function
    int numberToFind = 60;
    Node* foundNode = search(root, numberToFind);
    if (foundNode != NULL) {
        printf("Found %d in the tree!\n", foundNode->data);
    } else {
        printf("%d is not in the tree.\n", numberToFind);
    }

    return 0;
}