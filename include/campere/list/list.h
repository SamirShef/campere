#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stddef.h>
#include <campere/error/error.h>

#define listAdd(l, v) (__listAdd((l), (void *)(v))) // NOLINT
#define listGet(l, i, t) ((t)__listGet((l), (i)))   // NOLINT
#define listGetTop(l, t) ((t)__listGetTop((l)))     // NOLINT
#define listPop(l, t) ((t)__listPop((l)))           // NOLINT

typedef struct {
    void **data;
    size_t count;
    size_t capacity;
} List;

static inline List *
listNew() {
    List *l = (List *)malloc(sizeof(List));
    l->capacity = 8;
    l->count = 0;
    l->data = (void **)malloc(sizeof(void *) * l->capacity);
    return l;
}

static inline void
__listAdd(List *l, void *v) {
    if (l->count >= l->capacity) {
        l->capacity *= 2;
        l->data = (void **)realloc(l->data, sizeof(void *) * l->capacity);
    }
    l->data[l->count++] = v;
}

static inline void *
__listGet(List *l, size_t i) {
    ERR(i < l->count, "Passed index out of range: count of list: %zu, but got index: %zu", l->count, i);
    return l->data[i];
}

static inline void *
__listGetTop(List *l) {
    ERR(l->count != 0, "List is empty");
    return l->data[l->count - 1];
}

static inline void *
__listPop(List *l) {
    void *top = __listGetTop(l);
    --l->count;
    return top;
}

static inline void
listDel(List *l) {
    free(l->data);
    free(l);
}

#endif
