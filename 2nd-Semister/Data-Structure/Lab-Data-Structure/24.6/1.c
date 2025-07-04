#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void insert(struct node **head, int value) 
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

int main() 
{
    struct node *head = NULL;
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    while (head)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("end\n");
    free(head);
    return 0;
}