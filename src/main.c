#include <campere/string/string.h>
#include <stdio.h>

int
main(int argc, char **argv) {
    String *s1 = strNew("Hello");
    String *s2 = strNew(", world!");
    strConcat(s1, s2);
    printf("%s: %zu, %zu\n", s1->data, s1->len,
                             s1->capacity);
    strDel(s1);
    strDel(s2);
    return 0;
}
