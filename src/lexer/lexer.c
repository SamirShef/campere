#include <campere/lexer/lexer.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    unsigned int line = lex->line;
    unsigned int col = lex->col;
    String *val = strNew("");
    char c;
    while ((c = peek(lex, 0)) && isalnum(c) || c == '_') {
        strConcatC(val, skip(lex));
    }
#define KEYWORD(t) TOK(t, val->data, POS(line, col))
    if (!strcmp(val->data, "let")) {
        return KEYWORD(TkLet);
    }
    else if (!strcmp(val->data, "print")) {
        return KEYWORD(TkLet);
    }
#undef KEYWORD
    return TOK(TkId, val->data, POS(line, col));
}

Token
lexTokenizeNum(Lexer *lex) {
    unsigned int line = lex->line;
    unsigned int col = lex->col;
    String *val = strNew("");
    char c;
    bool hasDot = false;
    while ((c = peek(lex, 0)) && isdigit(c) || c == '_' || c == '.') {
        if (c == '_') {
            skip(lex);
            continue;
        }
        if (c == '.') {
            if (hasDot) {
                perror("number contains double dots");
                exit(1);
            }
            hasDot = true;
        }
        strConcatC(val, skip(lex));
    }
    return TOK(TkNumLit, val->data, POS(line, col));
}

Token
lexTokenizeStr(Lexer *lex) {
    unsigned int line = lex->line;
    unsigned int col = lex->col;
    String *val = strNew("");
    skip(lex);
    char c;
    while ((c = peek(lex, 0)) && c != '"') {
        strConcatC(val, c);
    }
    skip(lex);
    return TOK(TkStrLit, val->data, POS(line, col));
}

Token
lexTokenizeOp(Lexer *lex) {
    unsigned int line = lex->line;
    unsigned int col = lex->col;
    char c = skip(lex);
    switch (c) {
        case '+':
            return TOK(TkPlus, "+", POS(line, col));
        case '-':
            return TOK(TkMinus, "-", POS(line, col));
        case '*':
            return TOK(TkStar, "*", POS(line, col));
        case '/':
            return TOK(TkSlash, "/", POS(line, col));
        case '%':
            return TOK(TkPercent, "%", POS(line, col));
        case '=':
            return TOK(TkEq, "=", POS(line, col));
        default:
            fprintf(stderr, "unsupported operator: '%c'", c);
            exit(1);
    }
}

const char
peek(Lexer *lex, unsigned int rpos) {
    if (lex->pos + rpos >= lex->src->len) {
        return '\0';
    }
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
