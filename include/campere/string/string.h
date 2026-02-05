#include <stddef.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t len;
    size_t capacity;
} String;

static inline String *
strNew(const char *s) {
    size_t len = strlen(s);
    size_t capacity = len < 8 ? 8 : len * 2;
    String *res = (String *)malloc(sizeof(String));
    res->data = strdup(s);
    res->len = len;
    res->capacity = capacity;
    return res;
}

static inline void
strConcat(String *s1, String *s2) {
    size_t len = s1->len + s2->len;
    if (len > s1->capacity) {
        s1->capacity *= 2;
    }
    s1->data = len < s1->capacity ? s1->data :
               (char *)realloc(s1->data, s1->capacity);
    s1->data = strcat(strdup(s1->data), strdup(s2->data));
    s1->len = len;
}

static inline void
strConcatS(String *s1, const char *s2) {
    size_t len = s1->len + strlen(s2);
    if (len > s1->capacity) {
        s1->capacity *= 2;
    }
    s1->data = len < s1->capacity ? s1->data :
               (char *)realloc(s1->data, s1->capacity);
    s1->data = strcat(strdup(s1->data), strdup(s2));
    s1->len = len;
}

static inline void
strConcatC(String *s1, char c) {
    size_t len = s1->len + 1;
    if (len > s1->capacity) {
        s1->capacity *= 2;
    }
    s1->data = len < s1->capacity ? s1->data :
               (char *)realloc(s1->data, s1->capacity);
    char s2[2] = { c, '\0' };
    s1->data = strcat(strdup(s1->data), s2);
    s1->len = len;
}

static inline void
strDel(String *s) {
    free(s->data);
    free(s);
}
