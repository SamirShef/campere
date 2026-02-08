#ifndef BYTECODE_H
#define BYTECODE_H

#define BC(name) name,
typedef enum : unsigned {
#include "instructions.def"
} ByteCodeKind;
#undef BC

#endif
