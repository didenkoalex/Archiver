#include <stdio.h>
#include <stdlib.h>

typedef struct t_arch_head {
	size_t block_size, block_count, size_decode_files;
	long offset_root_block, offset_free_block;
	size_t head_block_data_size;
	size_t block_data_size;
} t_arch_head;

//Дескриптор архива
typedef struct t_arch_hand {
	FILE *arch;
	t_arch_head arch_head;
} t_arch_hand;

typedef struct t_item_head {
	t_arch_attr item_attributes;
	long offset_last_block;
} t_item_head;

typedef struct t_head_block {
	t_item_head item_head;
	BYTE *data;
	long offset_next_block;
} t_head_block;

//Дескриптор файла/каталога
typedef struct t_arch_item {
	t_arch_hand *hArchive;
	t_item_head item_head
	long offset_item;
} t_arch_item;

typedef struct t_data_block {
	BYTE *data;
	long offset_next_block;
} t_data_block;