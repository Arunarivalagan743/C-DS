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

// Check associativity (1 = left to right, 0 = right to left)
int isLeftAssociative(char op) {
    if (op == '^')
        return 0; // Right associative
    return 1;     // Left associative
}

// Convert Infix to Postfix
void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;
    
    // Reset stack
    top = -1;
    
    while (infix[i] != '\0') {
        c = infix[i];
        
        // Skip whitespace
        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }
        
        // If operand (letter or digit), add to output
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // If opening bracket, push to stack
        else if (c == '(') {
            push(c);
        }
        // If closing bracket, pop until opening bracket
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop(); // Remove the '('
            }
        }
        // If operator
        else if (isOperator(c)) {
            while (!isEmpty() && peek() != '(' &&
                   (precedence(peek()) > precedence(c) ||
                    (precedence(peek()) == precedence(c) && isLeftAssociative(c)))) {
                postfix[j++] = pop();
            }
            push(c);
        }
        
        i++;
    }
    
    // Pop remaining operators
    while (!isEmpty()) {
        if (peek() != '(') {
            postfix[j++] = pop();
        } else {
            pop();
        }
    }
    
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("=== INFIX TO POSTFIX CONVERSION ===\n\n");
    
    while (1) {
        printf("Enter infix expression (or 'exit' to quit): ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = '\0'; // Remove newline
        
        if (strcmp(infix, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        
        infixToPostfix(infix, postfix);
        
        printf("Infix:   %s\n", infix);
        printf("Postfix: %s\n\n", postfix);
    }
    
    return 0;
}
