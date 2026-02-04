#include <campere/lexer/lexer.h>
#include <ctype.h>
#include <assert.h>

#define TOK(t, s, p) \
    ((Token) { .type = t, .val = strNew(s), .pos =  p })

#define POS(l, c) \
    ((Position) { .line = l, .col = c })

const char
peek(Lexer *lex, unsigned int rpos);

const char
skip(Lexer *lex);

Token
lexNextTok(Lexer *lex) {
    for (; isspace(peek(lex, 0)); skip(lex));

    const char c = peek(lex, 0);
    if (c == '\0') {
        return TOK(TkEof, "<eof>", POS(lex->line, lex->col));
    }
    if (isalpha(c) || c == '_') {
        return lexTokenizeId(lex);
    }
    if (isdigit(c)) {
        return lexTokenizeNum(lex);
    }
    if (c == '"') {
        return lexTokenizeStr(lex);
    }
    return lexTokenizeOp(lex);
}

Token
lexTokenizeId(Lexer *lex) {
    return TOK(TkId, "id", POS(lex->line, lex->col)); // stub
}

Token
lexTokenizeNum(Lexer *lex) {
    return TOK(TkId, "id", POS(lex->line, lex->col)); // stub
}

Token
lexTokenizeStr(Lexer *lex) {
    return TOK(TkId, "id", POS(lex->line, lex->col)); // stub
}

Token
lexTokenizeOp(Lexer *lex) {
    return TOK(TkId, "id", POS(lex->line, lex->col)); // stub
}

const char
peek(Lexer *lex, unsigned int rpos) {
    assert(lex->pos + rpos < lex->src->len);
    return lex->src->data[lex->pos + rpos];
}

const char
skip(Lexer *lex) {
    assert(lex->pos < lex->src->len + 1);
    const char c = peek(lex, 0);
    ++lex->pos;
    ++lex->col;
    if (c == '\n') {
        ++lex->line;
        lex->col = 1;
    }
    return c;
}

#undef POS
#undef TOK
