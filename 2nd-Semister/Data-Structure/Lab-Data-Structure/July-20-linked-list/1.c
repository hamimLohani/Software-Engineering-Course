#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left, *right, *parent;
} Node;

Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

void treeInsert(Node **root, int key)
{
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = *root;

    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

Node *Minimum(Node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

void treeDelete(Node **root, Node *z)
{
    
    if (z->left == NULL && z->right == NULL)
    {
        if (z->parent == NULL) 
            *root = NULL;
        else if (z == z->parent->left)
            z->parent->left = NULL;
        else
            z->parent->right = NULL;
        free(z);
    }
    
    else if (z->left == NULL)
    {
        if (z->parent == NULL) 
            *root = z->right;
        else if (z == z->parent->left)
            z->parent->left = z->right;
        else
            z->parent->right = z->right;

        if (z->right != NULL)
            z->right->parent = z->parent;
        free(z);
    }
    
    else if (z->right == NULL)
    {
        if (z->parent == NULL) 
            *root = z->left;
        else if (z == z->parent->left)
            z->parent->left = z->left;
        else
            z->parent->right = z->left;

        if (z->left != NULL)
            z->left->parent = z->parent;
        free(z);
    }
    
    else
    {
        Node *successor = Minimum(z->right);

        int temp = z->key;
        z->key = successor->key;
        successor->key = temp;
        
        treeDelete(root, successor);
    }
}

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

Node *treeSearch(Node *root, int key)
{
    if (root == NULL || key == root->key)
        return root;
    if (key < root->key)
        return treeSearch(root->left, key);
    else
        return treeSearch(root->right, key);
}

int main()
{
    Node *root = NULL;

    treeInsert(&root, 8);
    treeInsert(&root, 6);
    treeInsert(&root, 18);
    treeInsert(&root, 3);
    treeInsert(&root, 7);
    treeInsert(&root, 10);
    treeInsert(&root, 22);

    printf("Inorder before deletion: ");
    inorder(root);
    printf("\n");

    int keyToDelete = 18;
    Node *node = treeSearch(root, keyToDelete);
    if (node != NULL)
        treeDelete(&root, node);

    printf("Inorder after deleting %d: ", keyToDelete);
    inorder(root);
    printf("\n");

    return 0;
}
