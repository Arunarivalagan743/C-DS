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

// Convert Postfix to Prefix
void postfixToPrefix(char *postfix, char *prefix) {
    int i = 0;
    char c;
    char operand[2];
    char temp[MAX];
    
    // Reset stack
    top = -1;
    
    while (postfix[i] != '\0') {
        c = postfix[i];
        
        // Skip whitespace
        if (c == ' ' || c == '\t') {
            i++;
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
                strcpy(prefix, "Error");
                return;
            }
            
            char *op2 = pop();
            char *op1 = pop();
            
            // Create: operator op1 op2
            sprintf(temp, "%c%s%s", c, op1, op2);
            push(temp);
        }
        
        i++;
    }
    
    if (top == 0) {
        strcpy(prefix, stack[top]);
    } else {
        printf("Invalid expression!\n");
        strcpy(prefix, "Error");
    }
}

int main() {
    char postfix[MAX], prefix[MAX];
    
    printf("=== POSTFIX TO PREFIX CONVERSION ===\n\n");
    
    while (1) {
        printf("Enter postfix expression (or 'exit' to quit): ");
        fgets(postfix, MAX, stdin);
        postfix[strcspn(postfix, "\n")] = '\0';
        
        if (strcmp(postfix, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        
        postfixToPrefix(postfix, prefix);
        
        printf("Postfix: %s\n", postfix);
        printf("Prefix:  %s\n\n", prefix);
    }
    
    return 0;
}
