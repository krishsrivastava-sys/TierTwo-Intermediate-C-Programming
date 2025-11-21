#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;

int createNode(Node **head, int data) {
    printf("[i] Inserting node...");
    Node *node = malloc(1 * sizeof(Node));// We have created a node directly in the heap.
    if(node == NULL) {
        // memory allocation failed.
        printf("[i] Failed node insertion...");
        return 0;
    }
    node->data = data;
    node->next = *head;
    *head = node;
    return 1;
}

int removeNode(Node **head, int data, char mode[4]) {
    printf("[i] Searching for the node(s)...");
    if(*head == NULL) {
        printf("[!] Error: The list is empty.");
        return 0;
    }
    if(strcmp(mode, "dex") == 0) {
        int index = data;
        if(index == 0) {
            Node *delIndex = *head;
            *head = (*head)->next;
            free(delIndex);
            return 1;
        }
        Node *temp = *head;
        if((temp->next) == NULL) return 0;
        for(int i = 0; i < index - 1;i++) {// we are moving the temp node to the position where the user's chosen node is - 1;
            temp = temp->next;
        } 
        if(temp->next == NULL) return 0;// User gave a wrong index.
        Node *delIndex = temp->next;
        temp->next = temp->next->next;// we will be deleting the first next in this one, not the second.
        free(delIndex);
        return 1;
    } else if(strcmp(mode, "all") == 0) {
        // Until it comes to the point where the first elments are not equal in line.
        while (*head != NULL && (*head)->data == data) {
            Node *del = *head;
            *head = (*head)->next;
            free(del);
        }
        if (*head == NULL) return 1;
        Node *temp = *head;
        while (temp->next != NULL) {
            if (temp->next->data == data) {
                Node *del = temp->next;
                temp->next = temp->next->next;
                free(del);
            } else {
                temp = temp->next;
            }
        }
    }
}



int printNodes(Node *head) {
    printf("\n[LINKED LIST]");
    int count = 0;
    if (head == NULL) {
        printf("[!] The linked list is currently empty!\n");
        return 0;
    }
    printf("\n[ ");
    Node *temp = head;
    while (temp != NULL) {
        count++;
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("]\n");
    printf("[Linked List Statistics]\n%d: Number of elements.\n", count);

    return count;
}


int main() {
    Node *head = NULL;// Created a head pointer and directed it to null.
    int data = 25;
    int addnode = createNode(&head, data);
    printNodes(head);
    return 0;
}
/*
For a pointer, the type is pointer.
but for an value 'pointer' the argument type is a double pointer OR:
*ptr = NULL;
**ptr = *ptr;

*/