/*
Performing stack Operations onto an Linked List
*/
#include <stdio.h>
#include <stdlib.h>

// Stack implemented as a singly linked list

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push(Node **top_ref, int value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->next = *top_ref;
    *top_ref = n;
}

int pop(Node **top_ref, int *out) {
    if (!*top_ref) return 0; // empty
    Node *tmp = *top_ref;
    *out = tmp->data;
    *top_ref = tmp->next;
    free(tmp);
    return 1;
}

int peek(Node *top, int *out) {
    if (!top) return 0;
    *out = top->data;
    return 1;
}

int is_empty(Node *top) {
    return top == NULL;
}

void display(Node *top) {
    if (!top) {
        printf("[empty stack]\n");
        return;
    }
    printf("Top -> ");
    for (Node *p = top; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
    }
    printf("\n");
}

void free_stack(Node **top_ref) {
    int tmp;
    while (pop(top_ref, &tmp)) { /* popping frees nodes */ }
}

int main(void) {
    Node *stack = NULL;
    int choice;
    int value;
    int ok;

    while (1) {
        printf("\nStack operations (linked list)\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek (top)\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            // bad input: clear stdin
            int c;
            while ((c = getchar()) != EOF && c != '\n') {}
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter integer to push: ");
                if (scanf("%d", &value) != 1) {
                    int c; while ((c = getchar()) != EOF && c != '\n') {}
                    printf("Invalid number.\n");
                    break;
                }
                push(&stack, value);
                printf("Pushed %d\n", value);
                break;
            case 2:
                ok = pop(&stack, &value);
                if (ok) printf("Popped %d\n", value);
                else printf("Stack is empty.\n");
                break;
            case 3:
                ok = peek(stack, &value);
                if (ok) printf("Top = %d\n", value);
                else printf("Stack is empty.\n");
                break;
            case 4:
                display(stack);
                break;
            case 5:
                free_stack(&stack);
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}