#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "archiver.h"
#include "auxiliary_functions.h"

//Создает новый архив с заданными атрибутами [с указанием размера блока данных]:
t_arch_hand * new_arch (const char *arch_name, size_t block_size) {
	t_arch_hand *hArchive = (t_arch_hand *)malloc(sizeof(t_arch_hand));
	hArchive->arch = fopen(arch_name, "w+b");
	t_arch_head arch_head = read_arch_head(block_size, 0, 0, sizeof(t_arch_head)+1);
	print_arch_head(hArchive->arch, &arch_head);
	return hArchive;
}

//Открывает существующий архив:
t_arch_hand * get_arch (const char *arch_name, int read_only) {
	t_arch_hand *hArchive = (t_arch_hand *)malloc(sizeof(t_arch_hand));
	hArchive->arch = read_only ? fopen(arch_name, "rb") : fopen(arch_name, "r+b");
	return hArchive;
}

//Возвращает суммарный размер всех файлов в архиве (без учета сжатия):
size_t get_arch_size (t_arch_hand *arch) {
	return arch->size_decode_files;
}

//Возвращает дескриптор файла/каталога по его имени (указывается полный путь к файлу внутри архива):
t_arch_item * get_arch_item (t_arch_hand *arch, const char *full_path) {
	if(!arch->arch_head.block_count)
		return NULL;
}

//Создает новый подкаталог:
t_arch_item * new_arch_item (t_arch_item *hItem, const char *name) {
	if(hItem->item_head.item_attributes.type != IS_FLD)
		return NULL;
	fseek(hItem->hArchive->arch, hItem->offset_item + sizeof(t_item_head), SEEK_SET)
	if(hItem->item_head.item_attributes.size_outer * sizeof(long) < hItem->hArchive->head_block_data_size) {
		fseek(hItem->hArchive->arch, hItem->item_head.item_attributes.size_outer * sizeof(long), SEEK_CUR);
		long offset_free_block = get_offset_free_block(hItem->hArchive); 
		fwrite(offset_free_block, sizeof(long), 1, hItem->hArchive->arch);
		fseek(hItem->hArchive->arch, offset_free_block, SEEK_SET);
		fwrite(fill_item_head(name, time(NULL), 0), sizeof(t_item_head), 1, hItem->hArchive->arch);
		fseek(hItem->hArchive->arch, hItem->hArchive->arch_head.block_size - sizeof(t_item_head) - sizeof(long), SEEK_CUR);
		fread(hItem->hArchive->arch_head.offset_free_block, sizeof(ling), 1, hItem->hArchive->arch);
		fseek(hItem->hArchive->arch, -sizeof(long), SEEK_CUR);
		fwrite(0, sizeof(long), 1, hItem->hArchive->arch);
		//Перед закрытием нужно перезаписать заголовок архива на диск.
	}
	(hItem->item_head.item_attributes.size_outer) * sizeof(long)
}
