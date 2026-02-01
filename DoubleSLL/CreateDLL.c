#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;
struct Node* temp = NULL;

struct Node* create(struct Node* head, int val)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    return head;
}

void display(struct Node* head)
{
    temp = head;
    while (temp != NULL) {
        printf("Prev:%p Data:%d Next:%p\n",
               (void*)temp->prev, temp->data, (void*)temp->next);
        temp = temp->next;
    }
}

struct Node* insertbeg(struct Node* head, int choice)
{
    while (choice) {
        int n;
        scanf("%d", &n);

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = n;
        newNode->prev = NULL;
        newNode->next = head;

        if (head != NULL)
            head->prev = newNode;
        else
            tail = newNode;

        head = newNode;
        scanf("%d", &choice);
    }
    return head;
}

struct Node* insertend(struct Node* head, int choice)
{
    while (choice) {
        int n;
        scanf("%d", &n);

        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->data = n;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        scanf("%d", &choice);
    }
    return head;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        head = create(head, val);
    }

    display(head);

    int choice = 1;
    head = insertend(head, choice);
    display(head);

    return 0;
}
