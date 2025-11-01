/*
- [ ]  Queue (enqueue/dequeue).
    
    → Arrays or linked lists, FIFO principle, queue ADT.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
// The Concept of Linked Lists:
/*
Head -> Top Element;
tail -> Generally Null.
*/
typedef struct Node {
    int item;
    struct Node *next;
} Node;

int queue_size(Node *head) {
    int count = 0;
    for (Node *p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;
}

/*
A single star passes a copy of the real pointer to the function, not giving the permission to change the real value
Two stars would pass the real path to the function, that way the function gets permission to change the real value.
*/

// remove and return the first element; returns false if empty
bool dequeue(Node **head, int *out_value) {
    if (head == NULL || *head == NULL) {
        return false;
    }
    Node *tmp = *head;
    *out_value = tmp->item;
    *head = tmp->next;
    free(tmp);
    return true;
}

// add element at the tail (requeue)
void enqueue(Node **head, int value) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->item = value;
    n->next = NULL;
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node *p = *head;
    while (p->next) p = p->next;
    p->next = n;
}

void print_queue(Node *head) {
    printf("Queue: ");
    for (Node *p = head; p != NULL; p = p->next) {
        printf("%d ", p->item);
    }
    printf("\n");
}

int main(void) {
    Node *queue = NULL; // empty queue (points to head)
    bool e_finish = false;

    while (!e_finish) {
        int choice;
        printf("-->> Welcome to the Queue <<--\nQueue Length: %d\nChoose your operations:\n1. DeQueue\n2. Requeue\n3. Print Queue\n4. Exit\n\n[INPUT] Enter your choice> ", queue_size(queue));
        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("[ERROR] Invalid input.\n");
            continue;
        }

        if (choice == 1) {
            int removed;
            if (dequeue(&queue, &removed)) {
                printf("[INFO] Removed: %d\n", removed);
            } else {
                printf("[INFO] Queue is empty.\n");
            }
        } else if (choice == 2) {
            int v;
            printf("Value to enqueue> ");
            if (scanf("%d", &v) != 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("[ERROR] Invalid value.\n");
                continue;
            }
            enqueue(&queue, v);
            printf("[INFO] Enqueued: %d\n", v);
        } else if (choice == 3) {
            print_queue(queue);
        } else if (choice == 4) {
            e_finish = true;
            printf("[INFO] Program execution terminated.\n");
        } else {
            printf("[ERROR] Unknown choice.\n");
        }
    }

    // free remaining nodes
    while (queue) {
        Node *tmp = queue;
        queue = queue->next;
        free(tmp);
    }

    return 0;
};