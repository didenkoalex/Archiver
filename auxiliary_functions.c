#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "archiver.h"

t_arch_head fill_arch_head (size_t block_size, size_t block_count, long offset_root_block, long offset_free_block) {
	t_arch_head result = {0, block_count, offset_root_block, offset_free_block};
	result.head_block_data_size = (block_size - sizeof(long) - sizeof(t_item_head)) / sizeof(long) * sizeof(long);
	result.block_data_size = result.head_block_data_size + sizeof(t_item_head);
	result.block_size = result.block_data_size + sizeof(long);
	result->size_decode_files = 0;
	return result;
}

t_item_head fill_item_head (const char name_item[MAX_LEN_OF_ITEM_NAME+1], time_t creation_time, long offset_last_block) {
	t_item_head result = {{name_item, 0, 0, IS_FLD, creation_time}, offset_last_block};
	return result;
}

void read_arch_head (t_arch_hand *hArchive) {
	rewind(hArchive->arch);
	fread(&hArchive->arch_head, sizeof(t_arch_head), 1, hArchive->arch);
}

void print_arch_head (t_arch_hand *hArchive) {
	rewind(hArchive->arch);
	fwrite(&hArchive->arch_head, sizeof(t_arch_head), 1, hArchive->arch);
}

long get_offset_free_block (t_arch_hand *hArchive) {
	return hArchive->offset_free_block;
}
