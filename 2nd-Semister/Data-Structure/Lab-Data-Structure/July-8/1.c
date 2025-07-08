#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node {
    int roll;
    char name[20];
    struct node *next;
}; 



void insert(struct node **head, int roll, char name[]) {
    struct node *new = malloc(sizeof(struct node));
    new->roll = roll;
    strcpy(new->name, name);
    new->next = *head;
    *head = new;
}

void delete_same_roll(struct node *head) {
    struct node *current_node = head;
    while (current_node != NULL) {
        struct node *previous_node = current_node;
        struct node *temp_node = current_node->next;
        while (temp_node != NULL) {
            if (temp_node->roll == current_node->roll) {
                previous_node->next = temp_node->next;
                free(temp_node);
            } else {
                previous_node = temp_node;
            }
        }
        current_node = current_node->next;
    }
}

void print_list(struct node *head) {
    while (head != NULL) {
        printf("Roll: %d, Name: %s", head->roll, head->name);
        head = head->next;
    }
}

int main() {
    struct node *head = NULL;
    int num;
    int roll;
    char name[20];
    printf("Enter total student: ");
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < num; i++) {
        printf("%d, Name: ", i + 1);
        fgets(name, sizeof name, stdin);
        printf("   Roll: ");
        scanf("%d", &roll);
        getchar();
        insert(&head, roll, name);
    }
    delete_duplicates(head);
    print_list(head);
}
