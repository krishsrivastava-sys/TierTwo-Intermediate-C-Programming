#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// simple fixed-size circular queue (array)
typedef struct {
    int *data;
    int capacity;
    int head; // index of next element to dequeue
    int tail; // index where next enqueue will place element
    int size;
} CQueue;

void cq_init(CQueue *q, int cap) {
    q->data = malloc(cap * sizeof(int));
    q->capacity = cap;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}
bool cq_is_full(CQueue *q) { return q->size == q->capacity; }
bool cq_is_empty(CQueue *q) { return q->size == 0; }

bool cq_enqueue(CQueue *q, int v) {
    if (cq_is_full(q)) return false;
    q->data[q->tail] = v;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

bool cq_dequeue(CQueue *q, int *out) {
    if (cq_is_empty(q)) return false;
    *out = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return true;
}