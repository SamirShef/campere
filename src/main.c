#include <campere/lexer/lexer.h>
#include <stdio.h>

int
main(int argc, char **argv) {
    String *s = strNew("test prog");
    Lexer lex = lexInit(LSHighLevel, s);
    Token t;
    int i = 0;
    while ((t = lexNextTok(&lex)).type != TkEof) {
        printf("'%s' (%d:%d)\n", t.val->data,
                                 t.pos.line, t.pos.col);
        if (i == 10) {
            break;
        }
        ++i;
    }
    strDel(s);
    return 0;
}
