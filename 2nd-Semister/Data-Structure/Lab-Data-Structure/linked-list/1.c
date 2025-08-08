#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* createNode(int data) {
    struct node* new = (struct node*) malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    return new;
}

void insertAtFirst(struct node** head, int data) {
    struct node* new = createNode(data);
    new->next = *head;
    *head = new;
}

void insertAtLast(struct node** head, int data) {
    struct node* new = createNode(data);
    struct node* current = *head;
    if (*head == NULL) {
        *head = new;
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
}

struct node* searchNode(struct node** head, int data) {
    struct node* temp = *head;
    if (temp != NULL && temp->data == data) {
        return temp;
    }

    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        } 
        temp = temp->next;
    }
    return NULL;
}

struct node* previousNode(struct node** head, struct node* target) {
    if (*head == NULL) return NULL;
    struct node* current = *head;
    struct node* temp = NULL;
    while (current != NULL && current != target) {
        temp = current;
        current = current->next;
    }

    return temp;
} 

void delete(struct node** head, int data) {
    struct node* findNode = searchNode(head, data);
    if (findNode == NULL) return; // Node not found
    struct node* previous = previousNode(head, findNode);
    if (previous == NULL) {
        // Deleting head node
        *head = findNode->next;
    } else {
        previous->next = findNode->next;
    }
    free(findNode);
}

void printList(struct node** head) {
    struct node* current = *head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct node* head = NULL;

    // Insert elements at the beginning
    insertAtFirst(&head, 10);
    insertAtFirst(&head, 20);
    insertAtFirst(&head, 30);

    printf("List after insertAtFirst: ");
    printList(&head);

    // Insert elements at the end
    insertAtLast(&head, 40);
    insertAtLast(&head, 50);

    printf("List after insertAtLast: ");
    printList(&head);

    // Delete a node (middle)
    delete(&head, 20);
    printf("List after deleting 20: ");
    printList(&head);

    // Delete head node
    delete(&head, 30);
    printf("List after deleting 30 (head): ");
    printList(&head);

    // Delete last node
    delete(&head, 50);
    printf("List after deleting 50 (last): ");
    printList(&head);

    // Try to delete a non-existent node
    delete(&head, 100);
    printf("List after trying to delete 100 (not found): ");
    printList(&head);

    // Free remaining nodes
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}