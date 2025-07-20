#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right, *parent;
} TreeNode;

TreeNode *createNode(int key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = node->right = node->parent = NULL;
    return node;
}

void treeInsert(TreeNode **root, int key)
{
    TreeNode *z = createNode(key);
    TreeNode *y = NULL;
    TreeNode *x = *root;

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

TreeNode *treeMinimum(TreeNode *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

TreeNode *treeSuccessor(TreeNode *x)
{
    if (x->right != NULL)
        return treeMinimum(x->right);
    TreeNode *y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

void transplant(TreeNode **root, TreeNode *u, TreeNode *v)
{
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void treeDelete(TreeNode **root, TreeNode *z)
{
    if (z->left == NULL)
        transplant(root, z, z->right);
    else if (z->right == NULL)
        transplant(root, z, z->left);
    else
    {
        TreeNode *y = treeMinimum(z->right);
        if (y->parent != z)
        {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
}

void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

TreeNode *treeSearch(TreeNode *root, int key)
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
    TreeNode *root = NULL;

    
    treeInsert(&root, 15);
    treeInsert(&root, 6);
    treeInsert(&root, 18);
    treeInsert(&root, 3);
    treeInsert(&root, 7);
    treeInsert(&root, 17);
    treeInsert(&root, 20);

    printf("Inorder before deletion: ");
    inorder(root);
    printf("\n");

    
    TreeNode *node = treeSearch(root, 6);
    if (node != NULL)
        treeDelete(&root, node);

    printf("Inorder after deleting 6: ");
    inorder(root);
    printf("\n");

    return 0;
}
