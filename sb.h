#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define SB_ERROR -1

typedef struct Node Node;

struct Node {
    int length;
    char *str;
    Node *next;
};

typedef struct StringBuilder {
    int length;
    Node *head;
    Node *body;
} StringBuilder;

StringBuilder *sb_init() {
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    assert(sb != NULL);

    return sb;
}

int sb_concat(StringBuilder *sb, char **retbuf)
{
    if (sb == NULL) {
        return SB_ERROR;
    }

    char *buf = malloc(sizeof(char) * (sb->length + 1));
    assert(buf != NULL);
    char *buf_head = buf;

    for (Node *node = sb->head; node; node = node->next) {
        memcpy(buf, node->str, node->length);
        buf += node->length;
    }

    *buf = '\0';

    *retbuf = buf_head;

    return 0;
}

int sb_append(StringBuilder *sb, const char *str)
{
    if (sb == NULL || str == NULL) {
        return SB_ERROR;
    }

    size_t str_len = strlen(str);

    Node *node = malloc(sizeof(Node));
    assert(node != NULL);
    node->str = malloc(sizeof(char) * str_len + 1);
    assert(node->str != NULL);

    node->length = str_len;
    node->next = NULL;
    memcpy(node->str, str, str_len + 1);

    if (sb->head == NULL) {
        sb->head = node;
        sb->body = node;
    } else {
        sb->body->next = node;
    }
    sb->body = node;
    sb->length += str_len;

    return str_len;
}

#define BUFMAX 2048
int sb_appendf(StringBuilder *sb, const char *fmt, ...)
{ 
    if (sb == NULL || fmt == NULL) {
        return SB_ERROR;
    }

    va_list ap;
    char buf[BUFMAX];

    va_start(ap, fmt);
    vsnprintf(buf, BUFMAX, fmt, ap);

    va_end(ap);

    return sb_append(sb, buf);
}

/* Returns the index of the first occurence of str. 
 * The index starts with 0. */
int sb_index_of(StringBuilder *sb, const char *str)
{
    if (sb == NULL || str == NULL) {
        return SB_ERROR;
    }

    int i = 0;
    for (Node *node = sb->head; node; node = node->next) {
        if (strstr(node->str, str) != NULL) {
            return i;
        }
        i++;
    }

    return SB_ERROR;
}

int sb_delete(StringBuilder *sb, int index)
{
    if (sb == NULL) {
        return SB_ERROR;
    }

    Node *node = sb->head;
    if (index == 0) {
        Node *temp = sb->head;
        sb->head = node->next;
        sb->body = node->next;
        free(temp);
    } else {
        for (int i = 0; node != NULL && i < index - 1; i++) {
            node = node->next;
        }
        Node *temp = node->next->next;
        free(node->next);
        node->next = temp;
    }
    
    return 0;
}

int sb_dump(StringBuilder *sb)
{
    if (sb == NULL) {
        return SB_ERROR;
    }
    
    for (Node *node = sb->head; node; node = node->next) {
        printf("%s\n", node->str);
    }

    return 0;
}

void sb_free(StringBuilder *sb)
{
    assert(sb != NULL);
    free(sb->body);
    free(sb);
}
