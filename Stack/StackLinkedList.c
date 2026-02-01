#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Stack structure
struct Stack {
    struct Node *top;
    int size;
};

// Create new node
struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize stack
void initStack(struct Stack *s) {
    s->top = NULL;
    s->size = 0;
}

// Check if stack is empty
int isEmpty(struct Stack *s) {
    return s->top == NULL;
}

// Push element onto stack
void push(struct Stack *s, int value) {
    struct Node *newNode = createNode(value);
    if (newNode == NULL) return;
    
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
    printf("Pushed %d onto stack\n", value);
}

// Pop element from stack
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    }
    
    struct Node *temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return value;
}

// Peek top element
int peek(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->top->data;
}

// Display stack
void display(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack elements (top to bottom): ");
    struct Node *current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Get stack size
int size(struct Stack *s) {
    return s->size;
}

// Free stack memory
void freeStack(struct Stack *s) {
    struct Node *current = s->top;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    s->top = NULL;
    s->size = 0;
}

int main() {
    struct Stack stack;
    initStack(&stack);
    
    int choice, value;
    
    printf("=== STACK USING LINKED LIST ===\n");
    
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Size\n6. Check Empty\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1)
                    printf("Popped: %d\n", value);
                break;
            case 3:
                value = peek(&stack);
                if (value != -1)
                    printf("Top element: %d\n", value);
                break;
            case 4:
                display(&stack);
                break;
            case 5:
                printf("Stack size: %d\n", size(&stack));
                break;
            case 6:
                printf("Stack is %s\n", isEmpty(&stack) ? "empty" : "not empty");
                break;
            case 7:
                freeStack(&stack);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
