#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    int items[MAX];
    int top;
};

// Initialize stack
void initStack(struct Stack *s) {
    s->top = -1;
}

// Check if stack is full
int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

// Check if stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Push element onto stack
void push(struct Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->items[++s->top] = value;
    printf("Pushed %d onto stack\n", value);
}

// Pop element from stack
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    }
    return s->items[s->top--];
}

// Peek top element
int peek(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->items[s->top];
}

// Display stack
void display(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

// Get stack size
int size(struct Stack *s) {
    return s->top + 1;
}

int main() {
    struct Stack stack;
    initStack(&stack);
    
    int choice, value;
    
    printf("=== STACK IMPLEMENTATION ===\n");
    
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Size\n6. Check Empty\n7. Check Full\n8. Exit\n");
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
                printf("Stack is %s\n", isFull(&stack) ? "full" : "not full");
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
