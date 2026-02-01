#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* create();
void inorder(struct Node* root);

struct Node* create() {
    int x;
    struct Node* newNode;

    printf("Enter data (-1 for no node): ");
    scanf("%d", &x);

    if (x == -1) {
        return NULL;
    }

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;

    printf("Enter left child of %d\n", x);
    newNode->left = create();

    printf("Enter right child of %d\n", x);
    newNode->right = create();

    return newNode;
}

void inorder(struct Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;

    root = create();

    printf("\nInorder Traversal: ");
    inorder(root);

    return 0;
}
