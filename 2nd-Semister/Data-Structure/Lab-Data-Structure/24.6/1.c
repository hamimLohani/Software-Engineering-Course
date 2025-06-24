#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int main() 
{
    struct node *one = (struct node *) malloc(sizeof(struct node));
    struct node *two = (struct node *) malloc(sizeof(struct node));
    struct node *three = (struct node *) malloc(sizeof(struct node));

    one->data = 3;
    two->data = 4;
    three->data = 5;

    struct node *head;
    head = one;
    one->next = two;
    two->next = three;

    while (head)
    {
        printf(" -> %d", head->data);
        head = head->next;
    }
    printf("\n");
}