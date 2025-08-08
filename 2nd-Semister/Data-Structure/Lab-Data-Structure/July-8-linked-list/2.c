#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int roll;
    char name[20];
    struct node *next;
};

void print_list(struct node *head) {
    while (head) {
        printf("Roll : %d, Name : %s",head->roll, head->name);
        head = head->next;
    }
}

void insert(struct node **head, int roll, char name[20]) {
    struct node *new = malloc(sizeof(struct node));
    new->roll = roll;
    strcpy(new->name, name);
    new->next = *head;
    *head = new;
}

void delete(struct node *head) {
    struct node *curr = head;
    while (curr != NULL)
    {
        struct node *prev = curr;
        struct node *temp = prev->next;
        while (temp != NULL)
        {
            if (temp->roll==curr->roll) {
                struct node *dup = temp;
                prev->next=temp->next;
                temp=temp->next;
                free(dup);
            } else {
                prev=temp;
                temp=temp->next;
            }
        }
        curr=curr->next;
    }   
}

int main() {
    int num, roll;
    char name[20];
    printf("Enter number of student: ");
    scanf("%d", &num);
    getchar();

    struct node *head = NULL;

    for (int i = 0; i < num; i++)
    {
        printf("%d. Name: ", i + 1);
        fgets(name, sizeof name, stdin);
        printf("   Roll: ");
        scanf("%d", &roll);
        getchar();
        insert(&head, roll, name);
    }
    delete(head);
    print_list(head);
}