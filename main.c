#include <stdio.h>
#include <stdlib.h>
#include "archiver.h"
#include "compress.h"
#include "stream.h"
#include "r_stream.h"



int main() {
    const static t_vtable tbl = {&r_swrite, &r_sread, &r_sputc, &r_sgetc, &r_sseek, &r_stell, &feof, &ferror, &fclose};
	const char *str = "0123456789abcdefghijklmnopqrstuvwxyz!!!";
	t_stream *fid = new_stream(fopen("input.txt", "wt"), &tbl);
	put_stream_buff(str, 1, strlen(str), fid);
	put_stream_char('\n', fid);
	off_stream(fid);
	return 0;
}
