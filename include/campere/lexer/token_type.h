#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#define TT(name) name,
typedef enum {
#include "token_type.def"
} TokenType;
#undef TT

static inline const char *
tokTypeToStr(TokenType t) {
    switch (t) {
#define TO_STR(t, s) \
    case t: \
        return s;

        TO_STR(TkId, "<id>")
        TO_STR(TkNumLit, "<num>")
        TO_STR(TkStrLit, "<str>")
        TO_STR(TkLet, "let")
        TO_STR(TkEq, "<eq>")
        TO_STR(TkPlus, "<plus>")
        TO_STR(TkMinus, "<minus>")
        TO_STR(TkStar, "<star>")
        TO_STR(TkSlash, "<slash>")
        TO_STR(TkPercent, "<percent>")
        TO_STR(TkPrint, "<print>")
        TO_STR(TkEof, "<eof>")

#undef TO_STR
    }
}

#endif
