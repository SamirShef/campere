#include "token.h"

typedef enum {
    LSHighLevel,  // analyzing of high-level code
    LSByteCode,   // analyzing of byte-code
} LexState;

typedef struct {
    LexState state;
    String *src;
    size_t pos;
    unsigned int line;
    unsigned int col;
} Lexer;

static inline Lexer
lexInit(LexState state, String *src) {
    return (Lexer) { .state = state, .src = src, .pos = 0,
                     .line = 1, .col = 1  };
}

Token
lexNextTok(Lexer *lex);

Token
lexTokenizeId(Lexer *lex);

Token
lexTokenizeNum(Lexer *lex);

Token
lexTokenizeStr(Lexer *lex);

Token
lexTokenizeOp(Lexer *lex);
