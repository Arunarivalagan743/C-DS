#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Queue structure
struct Queue {
    struct Node *front;
    struct Node *rear;
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

// Initialize queue
void initQueue(struct Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Check if queue is empty
int isEmpty(struct Queue *q) {
    return q->front == NULL;
}

// Enqueue element
void enqueue(struct Queue *q, int value) {
    struct Node *newNode = createNode(value);
    if (newNode == NULL) return;
    
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    printf("Enqueued %d\n", value);
}

// Dequeue element
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue\n");
        return -1;
    }
    
    struct Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return value;
}

// Get front element
int getFront(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->front->data;
}

// Get rear element
int getRear(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->rear->data;
}

// Display queue
void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue elements (front to rear): ");
    struct Node *current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Get queue size
int size(struct Queue *q) {
    return q->size;
}

// Free queue memory
void freeQueue(struct Queue *q) {
    struct Node *current = q->front;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int main() {
    struct Queue queue;
    initQueue(&queue);
    
    int choice, value;
    
    printf("=== QUEUE USING LINKED LIST ===\n");
    
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Front\n4. Rear\n5. Display\n6. Size\n7. Check Empty\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&queue, value);
                break;
            case 2:
                value = dequeue(&queue);
                if (value != -1)
                    printf("Dequeued: %d\n", value);
                break;
            case 3:
                value = getFront(&queue);
                if (value != -1)
                    printf("Front element: %d\n", value);
                break;
            case 4:
                value = getRear(&queue);
                if (value != -1)
                    printf("Rear element: %d\n", value);
                break;
            case 5:
                display(&queue);
                break;
            case 6:
                printf("Queue size: %d\n", size(&queue));
                break;
            case 7:
                printf("Queue is %s\n", isEmpty(&queue) ? "empty" : "not empty");
                break;
            case 8:
                freeQueue(&queue);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
