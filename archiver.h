#ifndef __INCLUDE_ARCHIVER_H
#define __INCLUDE_ARCHIVER_H

#include "compress.h"
#include "stream.h"
#include <stdio.h>
#include <time.h>

//���� ��������� � ������: {�������, �������� ����, ������ ���� [���������� RLE], ������ ���� [���������� ��������], ������ ���� [���������� LZW]}
typedef enum { IS_FLD, IS_DAT, IS_RLE, IS_HUF, IS_LZW } t_arch_type;

#define MIN_LEN_OF_DATA_SIZE (sizeof(t_arch_attr) + 2 * sizeof(long))
#define MAX_LEN_OF_ITEM_NAME (255)

//��������� ��� �������� ��������� �����:
typedef struct {
	char name[MAX_LEN_OF_ITEM_NAME + 1];	//���������� ��� ����� (������������ � ���� ����-��������������� ������);
	size_t size_outer;	//��� ��������� -- ����� ������; ��� ������ -- �������� ������ ����� [��� ������];
	size_t size_inter;	//��� ��������� -- ����� ������; ��� ������ -- ������ ������� �����;
	t_arch_type type;	//��� �������� ��������;
	time_t time;	//����� ��������;
	//...
} t_arch_attr;

//��� ����������� ��� ������:
typedef struct t_arch_hand t_arch_hand;

//��� ����������� ��� �����/��������:
typedef struct t_arch_item t_arch_item;

//������� ����� ����� � ��������� ���������� [� ��������� ������� ����� ������]:
t_arch_hand *new_arch(const char *arch_name, size_t block_size);

//��������� ������������ �����:
t_arch_hand *get_arch(const char *arch_name, int read_only);

//���������� ��������� ������ ���� ������ � ������ (��� ����� ������):
size_t get_arch_size(t_arch_hand *arch);

//���������� ���������� �����/�������� �� ��� ����� (����������� ������ ���� � ����� ������ ������):
t_arch_item *get_arch_item(t_arch_hand *arch, const char *full_path);

//���������� ���������� �����/�������� � ������� �������� �� ��� �����:
t_arch_item *get_arch_item_by_str(t_arch_item *item, const char *str);

//���������� ���������� �����/�������� � ������� �������� �� ��� ������ (������� � ��������):
t_arch_item *get_arch_item_by_ind(t_arch_item *item, int ind);

//���������� ���������� ��������� ��������:
t_arch_item *get_arch_root(t_arch_hand *arch);

//���������� �������� �����/��������:
t_arch_attr get_arch_item_attr(t_arch_item *item);

//���������� ��� ��������:
t_arch_type get_arch_item_type(t_arch_item *item);

//��� ��������� -- ���������� ����� ����� ������; ��� ������ -- ���������� ������ ����� � ������:
size_t get_arch_item_size(t_arch_item *item);

//��������� �������� �����/��������, ���������� � ������� ������������:
int del_arch_item(t_arch_item *item);

//����������� ���������� �����/��������:
int off_arch_item(t_arch_item *item);

//��������� ������� ������ ����� � ������� ������� ������ (����������� ��� ������):
t_arch_item *add_arch_item(t_arch_item *item, const char *name, t_arch_type type);

//������� ����� ����������:
t_arch_item *new_arch_item(t_arch_item *item, const char *name);

//���������� ����� ������, ��������� � ������� ������ (��� ��������� ���������� NULL):
//t_stream *get_arch_item_stream(t_arch_item *item);

//��������� ���������� �����/�������� � ��������� ����������:
int cpy_arch_item(t_arch_item *item, const char *path);

//��������� ������ � �������� �������:
int off_arch(t_arch_hand *arch);

#endif //__INCLUDE_ARCHIVER_H
