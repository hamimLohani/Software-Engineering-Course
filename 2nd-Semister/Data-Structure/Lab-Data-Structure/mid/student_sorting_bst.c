#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    int roll;
    float cgpa;
    int math;
    int socio;
    int dsa;
} student;

typedef struct node {
    student data;
    struct node *left;
    struct node *right;
} node;

node* createNode(student s) {
    node* newNode = malloc(sizeof(node));
    newNode->data = s;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Returns -1 if a should come before b, 1 if after, 0 if equal
int compare(student a, student b) {
    if (a.cgpa != b.cgpa)
        return (a.cgpa > b.cgpa) ? -1 : 1;
    int suma = a.math + a.socio + a.dsa;
    int sumb = b.math + b.socio + b.dsa;
    if (suma != sumb)
        return (suma > sumb) ? -1 : 1;
    if (a.math != b.math)
        return (a.math > b.math) ? -1 : 1;
    if (a.socio != b.socio)
        return (a.socio > b.socio) ? -1 : 1;
    if (a.dsa != b.dsa)
        return (a.dsa > b.dsa) ? -1 : 1;
    if (a.roll != b.roll)
        return (a.roll < b.roll) ? -1 : 1;  // Smaller roll comes first if all else equal
    return 0;
}

node* insert(node* root, student s) {
    if (root == NULL)
        return createNode(s);

    int comp = compare(s, root->data);
    if (comp == -1)
        root->left = insert(root->left, s);
    else
        root->right = insert(root->right, s);

    return root;
}

void inorder(node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("Roll: %d, CGPA: %.2f, Math: %d, Socio: %d, DSA: %d\n",
           root->data.roll, root->data.cgpa, root->data.math, root->data.socio, root->data.dsa);
    inorder(root->right);
}

int main() {
    FILE *file = fopen("in.txt", "r");
    if (!file) {
        printf("Failed to open file 'in.txt'\n");
        return 1;
    }

    node* root = NULL;
    student s;

    // File format per line:
    // roll cgpa math socio dsa
    while (fscanf(file, "%d %f %d %d %d", &s.roll, &s.cgpa, &s.math, &s.socio, &s.dsa) == 5) {
        root = insert(root, s);
    }

    fclose(file);

    printf("Students sorted by criteria:\n");
    inorder(root);

    return 0;
}
