#include <stdio.h>
#include <stdlib.h>

/* ===== Structure ===== */
struct Node {
    int data;
    struct Node* next;
};

/* ===== Function Declarations ===== */
struct Node* createList();
void display(struct Node* head);
int length(struct Node* head);
struct Node* insertAtBegin(struct Node* head);
void insertAtEnd(struct Node* head);
void insertAtPosition(struct Node* head);

/* ===== MAIN ===== */
int main() {

    struct Node* head = NULL;

    head = createList();
    display(head);

    head = insertAtBegin(head);
    display(head);

    insertAtEnd(head);
    display(head);

    insertAtPosition(head);
    display(head);

    return 0;
}

/* ===== CREATE LINKED LIST ===== */
struct Node* createList() {

    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    int choice = 1;

    while (choice) {
        newNode = (struct Node*)malloc(sizeof(struct Node));

        printf("Enter value: ");
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if (head == NULL) {
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }

        printf("Continue (1/0): ");
        scanf("%d", &choice);
    }
    return head;
}

/* ===== DISPLAY ===== */
void display(struct Node* head) {
    struct Node* temp = head;
    printf("\nLinked List: ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL)
            printf(" -> ");
        temp = temp->next;
    }
    printf("\n");
}

/* ===== LENGTH ===== */
int length(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

/* ===== INSERT AT BEGIN ===== */
struct Node* insertAtBegin(struct Node* head) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("\nEnter value to insert at beginning: ");
    scanf("%d", &newNode->data);

    newNode->next = head;
    head = newNode;

    return head;
}

/* ===== INSERT AT END ===== */
void insertAtEnd(struct Node* head) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp = head;

    printf("\nEnter value to insert at end: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

/* ===== INSERT AT GIVEN POSITION (USING YOUR LOGIC STYLE) ===== */
void insertAtPosition(struct Node* head) {

    int p, k = 1;
    struct Node* temp = head;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("\nEnter position: ");
    scanf("%d", &p);

    printf("Enter value: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    while (k < p) {          // 👈 your logic
        temp = temp->next;
        k++;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}
