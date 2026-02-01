#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// ===================== STACK IMPLEMENTATIONS =====================

// Character stack for operators
char charStack[MAX];
int charTop = -1;

void pushChar(char c) {
    if (charTop == MAX - 1) return;
    charStack[++charTop] = c;
}

char popChar() {
    if (charTop == -1) return '\0';
    return charStack[charTop--];
}

char peekChar() {
    if (charTop == -1) return '\0';
    return charStack[charTop];
}

int isCharStackEmpty() {
    return charTop == -1;
}

void resetCharStack() {
    charTop = -1;
}

// String stack for expressions
char strStack[MAX][MAX];
int strTop = -1;

void pushStr(char *str) {
    if (strTop == MAX - 1) return;
    strcpy(strStack[++strTop], str);
}

char* popStr() {
    if (strTop == -1) return NULL;
    return strStack[strTop--];
}

int isStrStackEmpty() {
    return strTop == -1;
}

void resetStrStack() {
    strTop = -1;
}

// ===================== UTILITY FUNCTIONS =====================

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isLeftAssociative(char op) {
    return (op != '^');
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void swapParentheses(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

// ===================== CONVERSION FUNCTIONS =====================

// 1. Infix to Postfix
void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;
    resetCharStack();
    
    while (infix[i] != '\0') {
        c = infix[i];
        if (c == ' ' || c == '\t') { i++; continue; }
        
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            pushChar(c);
        } else if (c == ')') {
            while (!isCharStackEmpty() && peekChar() != '(') {
                postfix[j++] = popChar();
            }
            if (!isCharStackEmpty()) popChar();
        } else if (isOperator(c)) {
            while (!isCharStackEmpty() && peekChar() != '(' &&
                   (precedence(peekChar()) > precedence(c) ||
                    (precedence(peekChar()) == precedence(c) && isLeftAssociative(c)))) {
                postfix[j++] = popChar();
            }
            pushChar(c);
        }
        i++;
    }
    
    while (!isCharStackEmpty()) {
        if (peekChar() != '(') postfix[j++] = popChar();
        else popChar();
    }
    postfix[j] = '\0';
}

// 2. Infix to Prefix
void infixToPrefix(char *infix, char *prefix) {
    int i = 0, j = 0;
    char c;
    char temp[MAX];
    
    strcpy(temp, infix);
    reverseString(temp);
    swapParentheses(temp);
    resetCharStack();
    
    while (temp[i] != '\0') {
        c = temp[i];
        if (c == ' ' || c == '\t') { i++; continue; }
        
        if (isalnum(c)) {
            prefix[j++] = c;
        } else if (c == '(') {
            pushChar(c);
        } else if (c == ')') {
            while (!isCharStackEmpty() && peekChar() != '(') {
                prefix[j++] = popChar();
            }
            if (!isCharStackEmpty()) popChar();
        } else if (isOperator(c)) {
            while (!isCharStackEmpty() && peekChar() != '(' && precedence(peekChar()) > precedence(c)) {
                prefix[j++] = popChar();
            }
            pushChar(c);
        }
        i++;
    }
    
    while (!isCharStackEmpty()) {
        if (peekChar() != '(') prefix[j++] = popChar();
        else popChar();
    }
    prefix[j] = '\0';
    reverseString(prefix);
}

// 3. Postfix to Infix
void postfixToInfix(char *postfix, char *infix) {
    int i = 0;
    char c, operand[2], temp[MAX];
    resetStrStack();
    
    while (postfix[i] != '\0') {
        c = postfix[i];
        if (c == ' ' || c == '\t') { i++; continue; }
        
        if (isalnum(c)) {
            operand[0] = c; operand[1] = '\0';
            pushStr(operand);
        } else if (isOperator(c)) {
            char *op2 = popStr();
            char *op1 = popStr();
            sprintf(temp, "(%s%c%s)", op1, c, op2);
            pushStr(temp);
        }
        i++;
    }
    strcpy(infix, strStack[strTop]);
}

// 4. Prefix to Infix
void prefixToInfix(char *prefix, char *infix) {
    int len = strlen(prefix);
    char c, operand[2], temp[MAX];
    resetStrStack();
    
    for (int i = len - 1; i >= 0; i--) {
        c = prefix[i];
        if (c == ' ' || c == '\t') continue;
        
        if (isalnum(c)) {
            operand[0] = c; operand[1] = '\0';
            pushStr(operand);
        } else if (isOperator(c)) {
            char *op1 = popStr();
            char *op2 = popStr();
            sprintf(temp, "(%s%c%s)", op1, c, op2);
            pushStr(temp);
        }
    }
    strcpy(infix, strStack[strTop]);
}

// 5. Postfix to Prefix
void postfixToPrefix(char *postfix, char *prefix) {
    int i = 0;
    char c, operand[2], temp[MAX];
    resetStrStack();
    
    while (postfix[i] != '\0') {
        c = postfix[i];
        if (c == ' ' || c == '\t') { i++; continue; }
        
        if (isalnum(c)) {
            operand[0] = c; operand[1] = '\0';
            pushStr(operand);
        } else if (isOperator(c)) {
            char *op2 = popStr();
            char *op1 = popStr();
            sprintf(temp, "%c%s%s", c, op1, op2);
            pushStr(temp);
        }
        i++;
    }
    strcpy(prefix, strStack[strTop]);
}

// 6. Prefix to Postfix
void prefixToPostfix(char *prefix, char *postfix) {
    int len = strlen(prefix);
    char c, operand[2], temp[MAX];
    resetStrStack();
    
    for (int i = len - 1; i >= 0; i--) {
        c = prefix[i];
        if (c == ' ' || c == '\t') continue;
        
        if (isalnum(c)) {
            operand[0] = c; operand[1] = '\0';
            pushStr(operand);
        } else if (isOperator(c)) {
            char *op1 = popStr();
            char *op2 = popStr();
            sprintf(temp, "%s%s%c", op1, op2, c);
            pushStr(temp);
        }
    }
    strcpy(postfix, strStack[strTop]);
}

// ===================== EVALUATION FUNCTIONS =====================

// Evaluate Postfix Expression
int evaluatePostfix(char *postfix) {
    int stack[MAX], top = -1;
    int i = 0;
    char c;
    
    while (postfix[i] != '\0') {
        c = postfix[i];
        if (c == ' ' || c == '\t') { i++; continue; }
        
        if (isdigit(c)) {
            stack[++top] = c - '0';
        } else if (isOperator(c)) {
            int op2 = stack[top--];
            int op1 = stack[top--];
            int result;
            switch (c) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '%': result = op1 % op2; break;
                case '^': {
                    result = 1;
                    for (int j = 0; j < op2; j++) result *= op1;
                    break;
                }
                default: result = 0;
            }
            stack[++top] = result;
        }
        i++;
    }
    return stack[top];
}

// Evaluate Prefix Expression
int evaluatePrefix(char *prefix) {
    int stack[MAX], top = -1;
    int len = strlen(prefix);
    char c;
    
    for (int i = len - 1; i >= 0; i--) {
        c = prefix[i];
        if (c == ' ' || c == '\t') continue;
        
        if (isdigit(c)) {
            stack[++top] = c - '0';
        } else if (isOperator(c)) {
            int op1 = stack[top--];
            int op2 = stack[top--];
            int result;
            switch (c) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '%': result = op1 % op2; break;
                case '^': {
                    result = 1;
                    for (int j = 0; j < op2; j++) result *= op1;
                    break;
                }
                default: result = 0;
            }
            stack[++top] = result;
        }
    }
    return stack[top];
}

// ===================== MAIN FUNCTION =====================

int main() {
    char expression[MAX];
    char result[MAX];
    int choice;
    
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║     ALL EXPRESSION CONVERSIONS - INFIX/PREFIX/POSTFIX     ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n┌───────────────────────────────────────┐\n");
        printf("│          CONVERSION OPTIONS           │\n");
        printf("├───────────────────────────────────────┤\n");
        printf("│  1. Infix   → Postfix                 │\n");
        printf("│  2. Infix   → Prefix                  │\n");
        printf("│  3. Postfix → Infix                   │\n");
        printf("│  4. Postfix → Prefix                  │\n");
        printf("│  5. Prefix  → Infix                   │\n");
        printf("│  6. Prefix  → Postfix                 │\n");
        printf("├───────────────────────────────────────┤\n");
        printf("│          EVALUATION OPTIONS           │\n");
        printf("├───────────────────────────────────────┤\n");
        printf("│  7. Evaluate Postfix (digits only)    │\n");
        printf("│  8. Evaluate Prefix  (digits only)    │\n");
        printf("├───────────────────────────────────────┤\n");
        printf("│  9. Show All Conversions at Once      │\n");
        printf("│  0. Exit                              │\n");
        printf("└───────────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        if (choice == 0) {
            printf("Exiting... Goodbye!\n");
            break;
        }
        
        if (choice >= 1 && choice <= 8) {
            printf("Enter expression: ");
            fgets(expression, MAX, stdin);
            expression[strcspn(expression, "\n")] = '\0';
        }
        
        switch (choice) {
            case 1:
                infixToPostfix(expression, result);
                printf("\n  Infix:   %s\n", expression);
                printf("  Postfix: %s\n", result);
                break;
            case 2:
                infixToPrefix(expression, result);
                printf("\n  Infix:  %s\n", expression);
                printf("  Prefix: %s\n", result);
                break;
            case 3:
                postfixToInfix(expression, result);
                printf("\n  Postfix: %s\n", expression);
                printf("  Infix:   %s\n", result);
                break;
            case 4:
                postfixToPrefix(expression, result);
                printf("\n  Postfix: %s\n", expression);
                printf("  Prefix:  %s\n", result);
                break;
            case 5:
                prefixToInfix(expression, result);
                printf("\n  Prefix: %s\n", expression);
                printf("  Infix:  %s\n", result);
                break;
            case 6:
                prefixToPostfix(expression, result);
                printf("\n  Prefix:  %s\n", expression);
                printf("  Postfix: %s\n", result);
                break;
            case 7:
                printf("\n  Postfix Expression: %s\n", expression);
                printf("  Result: %d\n", evaluatePostfix(expression));
                break;
            case 8:
                printf("\n  Prefix Expression: %s\n", expression);
                printf("  Result: %d\n", evaluatePrefix(expression));
                break;
            case 9: {
                printf("Enter INFIX expression: ");
                fgets(expression, MAX, stdin);
                expression[strcspn(expression, "\n")] = '\0';
                
                char postfix[MAX], prefix[MAX];
                char infixFromPost[MAX], infixFromPre[MAX];
                char preFromPost[MAX], postFromPre[MAX];
                
                infixToPostfix(expression, postfix);
                infixToPrefix(expression, prefix);
                postfixToInfix(postfix, infixFromPost);
                prefixToInfix(prefix, infixFromPre);
                postfixToPrefix(postfix, preFromPost);
                prefixToPostfix(prefix, postFromPre);
                
                printf("\n╔═══════════════════════════════════════════════════════════╗\n");
                printf("║                   ALL CONVERSIONS                         ║\n");
                printf("╠═══════════════════════════════════════════════════════════╣\n");
                printf("║  Original Infix      : %-35s ║\n", expression);
                printf("╠═══════════════════════════════════════════════════════════╣\n");
                printf("║  Infix → Postfix     : %-35s ║\n", postfix);
                printf("║  Infix → Prefix      : %-35s ║\n", prefix);
                printf("╠═══════════════════════════════════════════════════════════╣\n");
                printf("║  Postfix → Infix     : %-35s ║\n", infixFromPost);
                printf("║  Postfix → Prefix    : %-35s ║\n", preFromPost);
                printf("╠═══════════════════════════════════════════════════════════╣\n");
                printf("║  Prefix → Infix      : %-35s ║\n", infixFromPre);
                printf("║  Prefix → Postfix    : %-35s ║\n", postFromPre);
                printf("╚═══════════════════════════════════════════════════════════╝\n");
                break;
            }
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
