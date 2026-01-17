#include <stdio.h>

#include "./sb.h"

int main(void)
{
    StringBuilder sb = {0};
    char *strings[] = {"hello ", "world ", "HELLO ", "WORLD "};
    char *buf = NULL;

    for (int i = 0; i < 4; i++) {
        sb_append(&sb, strings[i]);
    }
    sb_appendf(&sb, "%s%s", "abc", "def");

    printf("%d\n", sb_index_of(&sb, "hello"));
    printf("size: %d\n", sb.size);

    printf("sb_dump():\n");
    sb_dump(&sb);
    sb_delete(&sb, 4);
    sb_dump(&sb);
    
    printf("sb_concat():\n");
    sb_concat(&sb, &buf);
    printf("%s\n", buf);

    free(buf);
    sb_free(&sb);

    return 0;
}
