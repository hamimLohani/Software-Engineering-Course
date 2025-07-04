#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void insertAtIndex(struct node **head, int value, int index) 
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct node *temp = *head;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Index out of bounds\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}