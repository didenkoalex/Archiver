#ifndef __INCLUDE_DATASTREAM_H
#define __INCLUDE_DATASTREAM_H
#include <stdio.h>
typedef unsigned char BYTE;

typedef struct t_stream {
    long pos, len, end;
    FILE *fid;
} t_stream;

//открывет входной поток
t_stream * sopen(const char *name, const char * stat) {
    t_stream *st = (t_stream *)malloc(sizeof(t_stream));
    st->fid = fopen(name, stat);
    return st;
}

//Выводит данные из буфера в поток:
size_t swrite(const void *buff, size_t size, size_t count, t_stream *stream) {
    return fwrite(buff, size, count, stream->fid);
}

//Читает данные из потока в буфер:
size_t sread(void *buff, size_t size, size_t count, t_stream *stream) {
    return sread(buff, size, count, stream->fid);
}

//Выводит символ в поток:
int sputc(BYTE ch, t_stream *stream) {
    fputc(ch, stream->fid);
}

//Читает символ из потока:
int sgetc(t_stream *stream) {
    //if(src->pos==src->end) return EOF;
    //src->pos++;
    return fgetc(stream->fid);
}

//Сбрасывает буфер потока (если такая операция предусмотрена):
int sflush(t_stream *stream) {
    return fflush(stream->fid);
}

//Смещает текущую позицию в потоке:
int sseek(t_stream *stream, long offset, int origin) {
    return fseek(stream->fid, offset, origin);
}


//Возвращает текущую позицию в потоке:
long stell(t_stream *stream) {
    return ftell(stream->fid);
}

//Проверяет окончание потока:
int seof(t_stream *stream) {
    return feof(stream->fid);
}

//Проверяет наличие ошибки при выполнении последней операции с потоком:
int serror(t_stream *stream) {
    return ferror(stream->fid);
}

#endif //__INCLUDE_DATASTREAM_H
