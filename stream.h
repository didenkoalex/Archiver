#ifndef __INCLUDE_DATASTREAM_H
#define __INCLUDE_DATASTREAM_H
#include <stdlib.h>
#include <stdio.h>
typedef unsigned char BYTE;

//Структура таблицы виртуальных функций:
typedef struct t_vtable {
	size_t (*swrite) (const void *buff, size_t size, size_t count, void *stream);
	size_t (*sread)  (void *buff, size_t size, size_t count, void *stream);
	int    (*sputc)  (int ch, void *stream);
	int    (*sgetc)  (void *stream);
	int    (*sseek)  (void *stream, long offset, int origin);
	long   (*stell)  (void *stream);
	int    (*seof)   (void *stream);
	int    (*serror) (void *stream);
	int    (*sclose) (void *stream);
	//...
} t_vtable;



//Структура виртуального потока:
typedef struct t_stream {
	const t_vtable *vtbl;
	void *data;
} t_stream;

#ifdef __GNUC__
#define PREFIX static inline
#else
#define PREFIX
#endif

//Создает виртуальный поток:
PREFIX t_stream *new_stream(void *data, const t_vtable *vtbl) {
	t_stream *stream = (t_stream *) malloc(sizeof(t_stream));
	if (stream == NULL) return NULL;
	stream->data = data;
	stream->vtbl = vtbl;
	return stream;
}

//Выводит данные из буфера в поток:
PREFIX size_t put_stream_buff(const void *buff, size_t size, size_t count, t_stream *stream) {
	return stream->vtbl->swrite(buff, size, count, stream->data);
}

//Читает данные из потока в буфер:
PREFIX size_t get_stream_buff(void *buff, size_t size, size_t count, t_stream *stream) {
	return stream->vtbl->sread(buff, size, count, stream->data);
}

//Выводит символ в поток:
PREFIX int put_stream_char(int ch, t_stream *stream) {
	return stream->vtbl->sputc(ch, stream->data);
}

//Читает символ из потока:
PREFIX int get_stream_char(t_stream *stream) {
	return stream->vtbl->sgetc(stream->data);
}

//Смещает текущую позицию в потоке:
PREFIX int run_stream_seek(t_stream *stream, long offset, int origin) {
	return stream->vtbl->sseek(stream->data, offset, origin);
}

//Возвращает текущую позицию в потоке:
PREFIX long get_stream_tell(t_stream *stream) {
	return stream->vtbl->stell(stream->data);
}

//Проверяет окончание потока:
PREFIX int get_stream_eof(t_stream *stream) {
	return stream->vtbl->seof(stream->data);
}

//Проверяет наличие ошибки:
PREFIX int get_stream_error(t_stream *stream) {
	return stream->vtbl->serror(stream->data);
}

//Закрывает поток:
PREFIX int off_stream(t_stream *stream) {
	if ((stream == NULL) || (stream->data == NULL)) return 0;
	stream->vtbl->sclose(stream->data);
	free(stream);
	return 0;
}

#endif //__INCLUDE_DATASTREAM_H
