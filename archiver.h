#ifndef __INCLUDE_ARCHIVER_H
#define __INCLUDE_ARCHIVER_H

#include "compress.h"
#include "stream.h"
#include <stdio.h>
#include <time.h>

//Тип содержимого элементов архива: {каталог, несжатый файл, сжатый файл [алгоритмом RLE], сжатый файл [алгоритмом Хаффмана], сжатый файл [алгоритмом LZW]}
typedef enum { IS_FLD, IS_DAT, IS_RLE, IS_HUF, IS_LZW } t_arch_type;

#define MIN_LEN_OF_DATA_SIZE (sizeof(t_arch_attr) + 2 * sizeof(long))
#define MAX_LEN_OF_ITEM_NAME (255)

//Структура для хранения атрибутов файла:
typedef struct {
	char name[MAX_LEN_OF_ITEM_NAME + 1];	//Символьное имя файла (представлено в виде нуль-терминированной строки);
	size_t size_outer;	//Для каталогов -- число ссылок; для файлов -- истинный размер файла [без сжатия];
	size_t size_inter;	//Для каталогов -- число ссылок; для файлов -- размер сжатого файла;
	t_arch_type type;	//Тип содержимого;
	time_t time;	//Время создания;
	//...
} t_arch_attr;

//Тип дескриптора для архива:
typedef struct t_arch_hand t_arch_hand;

//Тип дескриптора для файла/каталога:
typedef struct t_arch_item t_arch_item;

//Создает новый архив с заданными атрибутами [с указанием размера блока данных]:
t_arch_hand *new_arch(const char *file_name, size_t block_size);

//Открывает существующий архив:
t_arch_hand *get_arch(const char *file_name, int read_only);

//Возвращает суммарный размер всех файлов в архиве (без учета сжатия):
size_t get_arch_size(t_arch_hand *arch);

//Возвращает дескриптор файла/каталога по его имени (указывается полный путь к файлу внутри архива):
t_arch_item *get_arch_item(t_arch_hand *arch, const char *full_path);

//Возвращает дескриптор файла/каталога в текущем каталоге по его имени:
t_arch_item *get_arch_item_by_str(t_arch_item *fldr, const char *str);

//Возвращает дескриптор файла/каталога в текущем каталоге по его номеру (начиная с нулевого):
t_arch_item *get_arch_item_by_ind(t_arch_item *fldr, int ind);

//Возвращает дескриптор корневого каталога:
t_arch_item *get_arch_root(t_arch_hand *arch);

//Возвращает атрибуты файла/каталога:
t_arch_attr get_arch_item_attr(t_arch_item *item);

//Возвращает тип элемента:
t_arch_type get_arch_item_type(t_arch_item *item);

//Для каталогов -- возвращает общее число ссылок; для файлов -- возвращает размер файла в архиве:
size_t get_arch_item_size(t_arch_item *item);

//Выполняет вставку нового файла из файловой системы в текущий каталог архива (указывается тип сжатия):
t_arch_item *add_arch_item(t_arch_item *fldr, const char *file_name, t_arch_type type);

//Создает новый подкаталог в текущем каталоге архива:
t_arch_item *new_arch_item(t_arch_item *fldr, const char *item_name);

//Возвращает поток данных, связанный с текущим файлом (для каталогов возвращает NULL):
//t_stream *get_arch_item_stream(t_arch_item *item);

//Выполняет распаковку файла/каталога в указанную директорию:
int cpy_arch_item_to_path(t_arch_item *item, const char *path);

//Выполняет копирование файла/каталога в заданный каталог текущего (либо другого) архива:
int cpy_arch_item(t_arch_item *fldr, t_arch_item *item);

//Выполняет перемещение файла/каталога в заданный каталог текущего (либо другого) архива:
int mov_arch_item(t_arch_item *fldr, t_arch_item *item);

//Выполняет удаление файла/каталога, связанного с текущим дескриптором:
int del_arch_item(t_arch_item *item);

//Освобождает дескриптор файла/каталога:
int off_arch_item(t_arch_item *item);

//Завершает работу с файловым архивом:
int off_arch(t_arch_hand *arch);

#endif //__INCLUDE_ARCHIVER_H
