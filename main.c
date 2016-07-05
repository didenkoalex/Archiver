#include <stdio.h>
#include <stdlib.h>
/*#include "archiver.h"
#include "compress.h"
#include "stream.h"
*/
typedef unsigned char BYTE;

typedef struct t_stream {
    long pos, len, end;
    FILE *fid;
} t_stream;

t_stream * sopen(const char *name, const char * stat) {
    t_stream *st = (t_stream *)malloc(sizeof(t_stream));
    st->fid = fopen(name, stat);
    return st;
}

int sgetc(t_stream *src) {
    if(src->pos==src->end) return EOF;
    src->pos++;
    return fgetc(src->fid);
}

int sputc(BYTE ch, t_stream *src) {
    fputc(ch, src->fid);
}

int sseek(t_stream *src, long offset, int origin) {
    return fseek(src, offset, origin);
}

struct t_arch_head {
    size_t block_size, block_cnt;
    long offset_free;
};
/*
struct t_item_head {
    char name[256];
    t_arch_type type;
    long offset_last;
};

struct t_data_head {
    BYTE data[];
    long offset_next;
};

t_stream *get_arch_item_stream(t_arch_item *item);
*/
int main() {
    FILE *fid = sopen("input.txt", "r+b");
    fseek(fid, 0, SEEK_END);
    sputc(97, fid);
    fseek(fid, -1, SEEK_END);
    BYTE ch = sgetc(fid);
    printf("%c\n", ch);
    return 0;
}
