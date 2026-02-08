#ifndef CHUNK_H
#define CHUNK_H

#include <campere/list/list.h>

typedef struct {
    List *bytecode;
} Chunk;

static inline Chunk *
chunkNew() {
    Chunk *c = (Chunk *)malloc(sizeof(Chunk));
    c->bytecode = listNew();
    return c;
}

static inline size_t
chunkEmitByte(Chunk *c, unsigned char b) {
    listAdd(c->bytecode, b);
    return c->bytecode->count - 1;
}

#endif
