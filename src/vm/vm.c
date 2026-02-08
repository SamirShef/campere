#include <campere/list/list.h>
#include <campere/vm/bytecode.h>
#include <campere/vm/vm.h>

static int
getIndex(VM *vm, Chunk *c) {
    int res = 0;
    res += listGet(c->bytecode, vm->instPos++, unsigned char) << 16;
    res += listGet(c->bytecode, vm->instPos++, unsigned char) << 8;
    res += listGet(c->bytecode, vm->instPos++, unsigned char);
    return res;
}

static void
printStackSlot(StackSlot *ss) {
    switch (ss->type) {
#define PRINT(t, fmt, field) \
        case t: \
            printf("%" fmt "\n", ss->data.field); \
            break;

        PRINT(SSChar, "c", c);
        PRINT(SSShort, "d", s);
        PRINT(SSInt, "d", i);
        PRINT(SSLong, "ld", l);
        PRINT(SSFloat, "g", f);
        PRINT(SSDouble, "g", d);
        PRINT(SSString, "s", str->data);

#undef PRINT
    }
}

static StackSlot *
getBinary(char op, StackSlot *a, StackSlot *b) {
    // TODO: create logic for strings
    StackSlot *res = ssNew(*a);
    switch (b->type) {  // NOLINT
#define BIN(t, field_b) \
    case t: \
        switch (op) { \
            case '+': res = ssAdd(res, b->type, b->data.field_b); break; \
            case '-': res = ssSub(res, b->type, b->data.field_b); break; \
            case '*': res = ssMul(res, b->type, b->data.field_b); break; \
            case '/': res = ssDiv(res, b->type, b->data.field_b); break; \
            case '%': res = ssRem(res, b->type, b->data.field_b); break; \
        } \
        break;

    BIN(SSChar, c)
    BIN(SSShort, s)
    BIN(SSInt, i)
    BIN(SSLong, l)
    BIN(SSFloat, f)
    BIN(SSDouble, d)

#undef BIN
    }
    return res;
}

void
run(VM *vm) {
    while (1) {
        Chunk *c = listGet(vm->chunks, 0, Chunk *);
        switch (listGet(c->bytecode, vm->instPos++, unsigned char)) {
            case BcPush:
                vmPushVal(vm, listGet(vm->constants, getIndex(vm, c), StackSlot *));
                break;
            case BcAdd: {
                StackSlot *b = vmPopVal(vm);
                StackSlot *a = vmPopVal(vm);
                if (a->type != SSString && b->type != SSString) {
                    vmPushVal(vm, getBinary('+', a, b));
                }
                else {
                    if (a->type == SSString && b->type == SSString) {
                        vmPushVal(vm, ssNew((StackSlot) { .data.str = strConcat(a->data.str, b->data.str), .type = SSString }));
                    }
                    // TODO: create error
                }
                ssDel(a);
                ssDel(b);
                break;
            }
            case BcPrint:
                printStackSlot(vmPopVal(vm));
                break;
            case BcHalt:
                return;
        }
    }
}

void
disassemblyToFile(VM *vm, const char *fileName) {
    
}
