#include <stdlib.h>
#include <stdio.h>
#include "stream.h"


t_stream * sopen(char *name, char *type) {
    t_stream *st = (t_stream *) malloc(sizeof(t_stream));
    st->data = fopen(name, type);
    return st;
}

size_t r_swrite (const void *buff, size_t size, size_t count, void *stream) {
    return fwrite(buff, size, count, stream);
}

size_t r_sread  (void *buff, size_t size, size_t count, void *stream) {
    return fread(buff, size, count, stream);
}
int    r_sputc  (int ch, void *stream) {
    return fputc(ch, stream);
}

int    r_sgetc  (void *stream) {
    return fgetc(stream);
}

int    r_sseek  (void *stream, long offset, int origin) {
    return fseek(stream, offset, origin);
}

long   r_stell  (void *stream) {
    return ftell(stream);
}

/*int    r_seof   (void *stream) {
    return feof(stream);
}

int    r_serror (void *stream) {
    return ferror(stream);
}
*/
int    r_sclose (void *stream) {
    return fclose(stream);
}
