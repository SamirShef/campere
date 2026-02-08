#ifndef VM_H
#define VM_H

#include <campere/list/list.h>
#include <campere/vm/bytecode.h>
#include "stackslot.h"
#include "chunk.h"

typedef struct {
    List *globals;
    List *chunks;
    List *evalStack;
    List *constants;
    size_t instPos;
} VM;

static inline VM *
vmNew() {
    VM *vm = (VM *)malloc(sizeof(VM));
    vm->globals = listNew();
    vm->chunks = listNew();
    vm->evalStack = listNew();
    vm->constants = listNew();
    vm->instPos = 0;
    return vm;
}

static inline void
vmAddChunk(VM *vm, Chunk *c) {
    listAdd(vm->chunks, c);
}

static inline size_t
vmPushConst(VM *vm, StackSlot *ss) {
    listAdd(vm->constants, ss);
    return vm->constants->count - 1;
}

static inline void
vmPushVal(VM *vm, StackSlot *ss) {
    listAdd(vm->evalStack, ss);
}

static inline StackSlot *
vmPopVal(VM *vm) {
    return listPop(vm->evalStack, StackSlot *);
}

static inline void
vmEmitPushConst(Chunk *c, int index) {
    chunkEmitByte(c, BcPush);
    chunkEmitByte(c, index >> 16);
    chunkEmitByte(c, (index >> 8) & 0xFF);
    chunkEmitByte(c, index & 0xFF);
}

static inline void
vmDel(VM *vm) {
    listDel(vm->globals);
    listDel(vm->chunks);
    listDel(vm->evalStack);
    listDel(vm->constants);
    free(vm);
}

void
run(VM *vm);

void
disassemblyToFile(VM *vm, const char *fileName);

#endif
