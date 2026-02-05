typedef enum {
    TkId,
    TkNumLit,
    TkStrLit,
    TkLet,
    TkEq,
    TkPlus,
    TkMinus,
    TkStar,
    TkSlash,
    TkPercent,
    TkPrint,
    TkEof,
} TokenType;

static inline const char *
tokTypeToStr(TokenType t) {
    switch (t) {
        case TkId:
            return "<id>";
        case TkNumLit:
            return "<num>";
        case TkStrLit:
            return "<str>";
        case TkLet:
            return "let";
        case TkEq:
            return "<eq>";
        case TkPlus:
            return "<plus>";
        case TkMinus:
            return "<minus>";
        case TkStar:
            return "<star>";
        case TkSlash:
            return "<slash>";
        case TkPercent:
            return "<percent>";
        case TkPrint:
            return "<print>";
        case TkEof:
            return "<eof>";
    }
}
