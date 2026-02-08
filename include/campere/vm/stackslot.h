#ifndef STACK_SLOT_H
#define STACK_SLOT_H

#include <campere/error/error.h>
#include <campere/string/string.h>
#include <math.h>

typedef struct {
    union {
        char c;
        short s;
        int i;
        long l;
        float f;
        double d;
        String *str;
    } data;

#define SSType(name) name,
    enum {
#include "stackslottypes.def"
    } type;
#undef SSType
} StackSlot;

static inline StackSlot *
ssNew(StackSlot ss) {
    StackSlot *ssAlloca = (StackSlot *)malloc(sizeof(StackSlot));
    ssAlloca->data = ss.data;
    ssAlloca->type = ss.type;
    return ssAlloca;
}

static inline double
ssGetNum(StackSlot ss) {
    switch (ss.type) {
#define SSType(t, field) \
        case t: \
            return ss.data.field;

        SSType(SSChar, c)
        SSType(SSShort, s)
        SSType(SSInt, i)
        SSType(SSLong, l)
        SSType(SSFloat, f)
        SSType(SSDouble, d)
        case SSString:
            ERR(0, "Expected number, but got string");

#undef SSType
    }
}   // NOLINT

static inline StackSlot *
ssAdd(StackSlot *ss, int ssType, double v) {
    switch (ss->type) {
#define ADD(t, field) \
        case t: ss->data.field += v; ss->type = ssType > ss->type ? ssType : ss->type; return ss;

    ADD(SSChar, c)
    ADD(SSShort, s)
    ADD(SSInt, i)
    ADD(SSLong, l)
    ADD(SSFloat, f)
    ADD(SSDouble, d)
    case SSString:
        ERR(0, "Expected number, but got string");

#undef ADD
    }
}   // NOLINT

static inline StackSlot *
ssSub(StackSlot *ss, int ssType, double v) {
    switch (ss->type) {
#define SUB(t, field) \
    case t: ss->data.field -= v; ss->type = ssType > ss->type ? ssType : ss->type; return ss;

    SUB(SSChar, c)
    SUB(SSShort, s)
    SUB(SSInt, i)
    SUB(SSLong, l)
    SUB(SSFloat, f)
    SUB(SSDouble, d)
    case SSString:
        ERR(0, "Expected number, but got string");

#undef SUB
    }
}   // NOLINT

static inline StackSlot *
ssMul(StackSlot *ss, int ssType, double v) {
    switch (ss->type) {
#define MUL(t, field) \
    case t: ss->data.field *= v; ss->type = ssType > ss->type ? ssType : ss->type; return ss;

    MUL(SSChar, c)
    MUL(SSShort, s)
    MUL(SSInt, i)
    MUL(SSLong, l)
    MUL(SSFloat, f)
    MUL(SSDouble, d)
    case SSString:
        ERR(0, "Expected number, but got string");

#undef MUL
    }
}   // NOLINT

static inline StackSlot *
ssDiv(StackSlot *ss, int ssType, double v) {
    switch (ss->type) {
#define DIV(t, field) \
    case t: ss->data.field /= v; ss->type = ssType > ss->type ? ssType : ss->type; return ss;

    DIV(SSChar, c)
    DIV(SSShort, s)
    DIV(SSInt, i)
    DIV(SSLong, l)
    DIV(SSFloat, f)
    DIV(SSDouble, d)
    case SSString:
        ERR(0, "Expected number, but got string");

#undef DIV
    }
}   // NOLINT

static inline StackSlot *
ssRem(StackSlot *ss, int ssType, double v) {
    switch (ss->type) {
#define REM(t, field) \
    case t: ss->data.field = fmod(ss->data.field, v); ss->type = ssType > ss->type ? ssType : ss->type; return ss;

    REM(SSChar, c)
    REM(SSShort, s)
    REM(SSInt, i)
    REM(SSLong, l)
    REM(SSFloat, f)
    REM(SSDouble, d)
    case SSString:
        ERR(0, "Expected number, but got string");

#undef REM
    }

}   // NOLINT

static inline void
ssDel(StackSlot *ss) {
    if (ss->type == SSString) {
        strDel(ss->data.str);
    }
    free(ss);
}

#endif
