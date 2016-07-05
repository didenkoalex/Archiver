#ifndef __INCLUDE_DATASTREAM_H
#define __INCLUDE_DATASTREAM_H

typedef struct t_stream t_stream;

#include <stdio.h>

//Выводит данные из буфера в поток:
size_t swrite(const void *buff, size_t size, size_t count, t_stream *stream);

//Читает данные из потока в буфер:
size_t sread(void *buff, size_t size, size_t count, t_stream *stream);

//Выводит символ в поток:
int sputc(int ch, t_stream *stream);

//Читает символ из потока:
int sgetc(t_stream *stream);

//Сбрасывает буфер потока (если такая операция предусмотрена):
int sflush(t_stream *stream);

//Смещает текущую позицию в потоке:
int sseek(t_stream *stream, long offset, int origin);

//Возвращает текущую позицию в потоке:
long stell(t_stream *stream);

//Проверяет окончание потока:
int seof(t_stream *stream);

//Проверяет наличие ошибки при выполнении последней операции с потоком:
int serror(t_stream *stream);

//ВРЕМЕННОЕ РЕШЕНИЕ (ТОЛЬКО ДЛЯ ТЕСТОВЫХ ПРОЕКТОВ)!!!
#define __IS_TEST_PROJECT
#ifdef  __IS_TEST_PROJECT
#define t_stream FILE
#define swrite fwrite
#define sread fread
#define sputc fputc
#define sgetc fgetc
#define sflush fflush
#define sseek fseek
#define stell ftell
#define seof feof
#define serror ferror
#endif

#endif //__INCLUDE_DATASTREAM_H
