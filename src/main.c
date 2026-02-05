#include <campere/lexer/lexer.h>
#include <stdio.h>

String *
openFile(const char *fileName);

int
main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <fileName>\n", argv[0]);
        return 1;
    }
    String *s = openFile(argv[1]);
    Lexer lex = lexInit(LSHighLevel, s);
    Token t;
    while ((t = lexNextTok(&lex)).type != TkEof) {
        printf("'%s' : %s (%d:%d)\n", t.val->data, tokTypeToStr(t.type),
                                      t.pos.line, t.pos.col);
    }
    strDel(s);
    return 0;
}

String *
openFile(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        fprintf(stderr, "file %s does not exists\n", fileName);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    unsigned int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = (char *)malloc(len);
    fread(buf, 1, len, f);
    fclose(f);
    String *s = strNew(buf);
    free(buf);
    return s;
}
