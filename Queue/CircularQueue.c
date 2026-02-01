#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Circular Queue structure
struct CircularQueue {
    int items[MAX];
    int front;
    int rear;
};

// Initialize circular queue
void initQueue(struct CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
int isFull(struct CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Check if queue is empty
int isEmpty(struct CircularQueue *q) {
    return q->front == -1;
}

// Enqueue element
void enqueue(struct CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Circular Queue Overflow! Cannot enqueue %d\n", value);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    printf("Enqueued %d\n", value);
}

// Dequeue element
int dequeue(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Circular Queue Underflow! Cannot dequeue\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        // Queue becomes empty
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return item;
}

// Get front element
int getFront(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// Get rear element
int getRear(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->rear];
}

// Display circular queue
void display(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Circular Queue is empty!\n");
        return;
    }
    printf("Circular Queue elements: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
    printf("Front index: %d, Rear index: %d\n", q->front, q->rear);
}

// Get queue size
int size(struct CircularQueue *q) {
    if (isEmpty(q))
        return 0;
    if (q->rear >= q->front)
        return q->rear - q->front + 1;
    else
        return MAX - q->front + q->rear + 1;
}

int main() {
    struct CircularQueue queue;
    initQueue(&queue);
    
    int choice, value;
    
    printf("=== CIRCULAR QUEUE IMPLEMENTATION ===\n");
    printf("Maximum capacity: %d\n", MAX);
    
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
