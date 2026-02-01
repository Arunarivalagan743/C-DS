#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Initialize queue
void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
int isFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

// Check if queue is empty
int isEmpty(struct Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Enqueue element
void enqueue(struct Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->items[++q->rear] = value;
    printf("Enqueued %d\n", value);
}

// Dequeue element
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue\n");
        return -1;
    }
    return q->items[q->front++];
}

// Get front element
int getFront(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// Get rear element
int getRear(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->rear];
}

// Display queue
void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements (front to rear): ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

// Get queue size
int size(struct Queue *q) {
    if (isEmpty(q))
        return 0;
    return q->rear - q->front + 1;
}

int main() {
    struct Queue queue;
    initQueue(&queue);
    
    int choice, value;
    
    printf("=== QUEUE IMPLEMENTATION ===\n");
    
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Front\n4. Rear\n5. Display\n6. Size\n7. Check Empty\n8. Check Full\n9. Exit\n");
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
                printf("Queue is %s\n", isFull(&queue) ? "full" : "not full");
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
