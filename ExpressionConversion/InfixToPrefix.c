#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

// Push to stack
void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++top] = c;
}

// Pop from stack
char pop() {
    if (top == -1) {
        return '\0';
    }
    return stack[top--];
}

// Peek top element
char peek() {
    if (top == -1) {
        return '\0';
    }
    return stack[top];
}

// Check if stack is empty
int isEmpty() {
    return top == -1;
}

// Get precedence of operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

// Reverse a string
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Swap parentheses
void swapParentheses(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
    }
}

// Convert Infix to Prefix
void infixToPrefix(char *infix, char *prefix) {
    int i = 0, j = 0;
    char c;
    char temp[MAX];
    
    // Copy infix to temp
    strcpy(temp, infix);
    
    // Step 1: Reverse the infix expression
    reverse(temp);
    
    // Step 2: Swap parentheses
    swapParentheses(temp);
    
    // Reset stack
    top = -1;
    
    // Step 3: Get postfix of modified expression
    while (temp[i] != '\0') {
        c = temp[i];
        
        // Skip whitespace
        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }
        
        // If operand, add to output
        if (isalnum(c)) {
            prefix[j++] = c;
        }
        // If opening bracket, push to stack
        else if (c == '(') {
            push(c);
        }
        // If closing bracket, pop until opening bracket
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                prefix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop();
            }
        }
        // If operator
        else if (isOperator(c)) {
            // For prefix, we use >= for right-to-left associativity simulation
            while (!isEmpty() && peek() != '(' && precedence(peek()) > precedence(c)) {
                prefix[j++] = pop();
            }
            push(c);
        }
        
        i++;
    }
    
    // Pop remaining operators
    while (!isEmpty()) {
        if (peek() != '(') {
            prefix[j++] = pop();
        } else {
            pop();
        }
    }
    
    prefix[j] = '\0';
    
    // Step 4: Reverse the result to get prefix
    reverse(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];
    
    printf("=== INFIX TO PREFIX CONVERSION ===\n\n");
    
    while (1) {
        printf("Enter infix expression (or 'exit' to quit): ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = '\0';
        
        if (strcmp(infix, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        
        infixToPrefix(infix, prefix);
        
        printf("Infix:  %s\n", infix);
        printf("Prefix: %s\n\n", prefix);
    }
    
    return 0;
}
