#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack for strings
char stack[MAX][MAX];
int top = -1;

// Push to stack
void push(char *str) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(stack[++top], str);
}

// Pop from stack
char* pop() {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}

// Check if stack is empty
int isEmpty() {
    return top == -1;
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

// Convert Prefix to Postfix
void prefixToPostfix(char *prefix, char *postfix) {
    int i;
    int len = strlen(prefix);
    char c;
    char operand[2];
    char temp[MAX];
    
    // Reset stack
    top = -1;
    
    // Read from right to left
    for (i = len - 1; i >= 0; i--) {
        c = prefix[i];
        
        // Skip whitespace
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        // If operand, push to stack
        if (isalnum(c)) {
            operand[0] = c;
            operand[1] = '\0';
            push(operand);
        }
        // If operator
        else if (isOperator(c)) {
            if (top < 1) {
                printf("Invalid expression!\n");
                strcpy(postfix, "Error");
                return;
            }
            
            char *op1 = pop();
            char *op2 = pop();
            
            // Create: op1 op2 operator
            sprintf(temp, "%s%s%c", op1, op2, c);
            push(temp);
        }
    }
    
    if (top == 0) {
        strcpy(postfix, stack[top]);
    } else {
        printf("Invalid expression!\n");
        strcpy(postfix, "Error");
    }
}

int main() {
    char prefix[MAX], postfix[MAX];
    
    printf("=== PREFIX TO POSTFIX CONVERSION ===\n\n");
    
    while (1) {
        printf("Enter prefix expression (or 'exit' to quit): ");
        fgets(prefix, MAX, stdin);
        prefix[strcspn(prefix, "\n")] = '\0';
        
        if (strcmp(prefix, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        
        prefixToPostfix(prefix, postfix);
        
        printf("Prefix:  %s\n", prefix);
        printf("Postfix: %s\n\n", postfix);
    }
    
    return 0;
}
