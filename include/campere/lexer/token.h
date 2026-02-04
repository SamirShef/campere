#include "token_type.h"
#include  <campere/string/string.h>
#include <campere/pos.h>

typedef struct {
    TokenType type;
    String *val;
    Position pos;
} Token;
