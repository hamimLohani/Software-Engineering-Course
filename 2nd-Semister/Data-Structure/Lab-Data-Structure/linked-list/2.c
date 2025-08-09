#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* createNode(int data) {
    struct node* new = (struct node*) malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;
    return new;
}

void insertion(struct node** head, int data) {
    struct node* new = createNode(data);
    struct node* current = *head;

    if (current == NULL) {
        *head = new;
        return;
    }

    while (current != NULL && current->data < data) {
        current = current->next;
    }

    new->next = current->next;
    current->next = new;
    
}