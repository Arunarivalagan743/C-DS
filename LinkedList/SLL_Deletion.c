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
struct Node* deleteAtBegin(struct Node* head);
void deleteAtEnd(struct Node* head);
void deleteAtPosition(struct Node** head);

/* ===== MAIN ===== */
int main() {

    struct Node* head = NULL;

    head = createList();
    display(head);

    // head = deleteAtBegin(head);
    // display(head);

    // deleteAtEnd(head);
    // display(head);

    deleteAtPosition(&head);
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

/* ===== delete AT BEGIN ===== */
struct Node* deleteAtBegin(struct Node* head) {

   

    printf("delete at beginning: ");
    

    struct Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

/* ===== Delete AT END ===== */
void deleteAtEnd(struct Node* head) {

    

    printf("\n remove  at end: ");
  struct Node* temp = head;
  struct Node* prev_temp;
  while(temp->next!=NULL)
  {
    prev_temp = temp;
    temp =  temp->next;
    printf("%p",temp->next);
  }
  prev_temp->next = NULL;
  free(temp);

}
void deleteAtPosition(struct Node** head) {

    int p, i = 1;
    struct Node* temp = *head;
    struct Node* prev_temp = NULL;

    printf("\nEnter position: ");
    scanf("%d", &p);

    // Empty list
    if (*head == NULL)
        return;

    // Delete at beginning
    if (p == 0) {
        temp = *head;
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse using your logic
    while (i < p && temp != NULL) {
        prev_temp = temp;
        temp = temp->next;
        i++;
    }

    // Invalid position
    if (i < p || prev_temp == NULL) {
        printf("Invalid position\n");
        return;
    }

    prev_temp->next = temp->next;
    free(temp);
}
