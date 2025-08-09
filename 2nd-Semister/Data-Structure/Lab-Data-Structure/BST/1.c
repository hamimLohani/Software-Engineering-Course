#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
} Node;

Node* createNode(int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    if (new == NULL) {
        printf("Not enough memory.\n");
        return NULL;
    }
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    return new;
}

void insert(Node** root, int data) {
    Node* new = createNode(data);
    if (new == NULL) return;
    if (*root == NULL) {
        *root = new;
        return;
    }
    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            free(new);
            return;
        }
    }
    new->parent = parent;
    if (data < parent->data) {
        parent->left = new;
    } else {
        parent->right = new;
    }
}

Node* search(Node** root, int data) {
    Node* current = *root;
    if (current == NULL || current->data == data) {
        return current;
    }
    while (current != NULL) {
        if (current->data == data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    printf("%d Not found.\n", data);
    return NULL;
}

Node* findMin(Node** root) {
    Node* current = *root;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* findMax(Node** root) {
    Node* current = *root;
    while (current != NULL && current->right != NULL) {
        current = current->right;
    }
    return current;
}

void delete(Node** root, int data) {
    Node* nodeToDelete = search(root, data);
    if (nodeToDelete == NULL) {
        printf("Node is not found.\n");
        return;
    }
    Node* parent = nodeToDelete->parent;
    // Case 1: Node has no children (leaf)
    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
        if (parent == NULL) {
            *root = NULL;
        } else if (parent->left == nodeToDelete) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(nodeToDelete);
        return;
    }
    // Case 2: Node has one child
    if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
        Node* child = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
        if (parent == NULL) {
            *root = child;
            child->parent = NULL;
        } else if (parent->left == nodeToDelete) {
            parent->left = child;
            child->parent = parent;
        } else {
            parent->right = child;
            child->parent = parent;
        }
        free(nodeToDelete);
        return;
    }
    // Case 3: Node has two children
    Node* successor = findMin(&(nodeToDelete->right));
    nodeToDelete->data = successor->data;
    // Recursively delete successor
    delete(&(nodeToDelete->right), successor->data);
}

void inorder(Node** root) {
    printf("\nInorder Traversal : ");
    if (*root != NULL) {
        inorder(&((*root)->left));
        printf("%d ", (*root)->data);
        inorder(&((*root)->right));
    }
}

void preorder(Node** root) {
    printf("\nPreorder Traversal : ");
    if (*root != NULL) {
        printf("%d ", (*root)->data);
        preorder(&((*root)->left));
        preorder(&((*root)->right));
    }
}

void postorder(Node** root) {
    printf("\nPostorder Traversal : ");
    if (*root != NULL) {
        postorder(&((*root)->left));
        postorder(&((*root)->right));
        printf("%d ", (*root)->data);
    }
}

int main() {
    Node* root;
    insert(&root, 3);
    insert(&root, 1);
    insert(&root, 4);
    insert(&root, 2);
    insert(&root, 5);
    insert(&root, 7);
    insert(&root, 6);

    inorder(&root);
    preorder(&root);
    postorder(&root);

    search(&root, 4);
    search(&root, 10);

    delete(&root, 1);
    inorder(&root);
    delete(&root, 3);
    inorder(&root);
    
}