#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Double Ended Queue (Deque) structure
struct Deque {
    int items[MAX];
    int front;
    int rear;
};

// Initialize deque
void initDeque(struct Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if deque is full
int isFull(struct Deque *dq) {
    return (dq->front == 0 && dq->rear == MAX - 1) || (dq->front == dq->rear + 1);
}

// Check if deque is empty
int isEmpty(struct Deque *dq) {
    return dq->front == -1;
}

// Insert at front
void insertFront(struct Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow! Cannot insert at front\n");
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX - 1;
    } else {
        dq->front--;
    }
    dq->items[dq->front] = value;
    printf("Inserted %d at front\n", value);
}

// Insert at rear
void insertRear(struct Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow! Cannot insert at rear\n");
        return;
    }
    if (isEmpty(dq)) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == MAX - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->items[dq->rear] = value;
    printf("Inserted %d at rear\n", value);
}

// Delete from front
int deleteFront(struct Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from front\n");
        return -1;
    }
    int item = dq->items[dq->front];
    if (dq->front == dq->rear) {
        // Only one element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == MAX - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
    return item;
}

// Delete from rear
int deleteRear(struct Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow! Cannot delete from rear\n");
        return -1;
    }
    int item = dq->items[dq->rear];
    if (dq->front == dq->rear) {
        // Only one element
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX - 1;
    } else {
        dq->rear--;
    }
    return item;
}

// Get front element
int getFront(struct Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->items[dq->front];
}

// Get rear element
int getRear(struct Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->items[dq->rear];
}

// Display deque
void display(struct Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements (front to rear): ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->items[i]);
        if (i == dq->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Get deque size
int size(struct Deque *dq) {
    if (isEmpty(dq))
        return 0;
    if (dq->rear >= dq->front)
        return dq->rear - dq->front + 1;
    else
        return MAX - dq->front + dq->rear + 1;
}

int main() {
    struct Deque deque;
    initDeque(&deque);
    
    int choice, value;
    
    printf("=== DOUBLE ENDED QUEUE (DEQUE) IMPLEMENTATION ===\n");
    
    while (1) {
        printf("\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n");
        printf("5. Get Front\n6. Get Rear\n7. Display\n8. Size\n");
        printf("9. Check Empty\n10. Check Full\n11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&deque, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&deque, value);
                break;
            case 3:
                value = deleteFront(&deque);
                if (value != -1)
                    printf("Deleted from front: %d\n", value);
                break;
            case 4:
                value = deleteRear(&deque);
                if (value != -1)
                    printf("Deleted from rear: %d\n", value);
                break;
            case 5:
                value = getFront(&deque);
                if (value != -1)
                    printf("Front element: %d\n", value);
                break;
            case 6:
                value = getRear(&deque);
                if (value != -1)
                    printf("Rear element: %d\n", value);
                break;
            case 7:
                display(&deque);
                break;
            case 8:
                printf("Deque size: %d\n", size(&deque));
                break;
            case 9:
                printf("Deque is %s\n", isEmpty(&deque) ? "empty" : "not empty");
                break;
            case 10:
                printf("Deque is %s\n", isFull(&deque) ? "full" : "not full");
                break;
            case 11:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
