#include <stdio.h>
#include <stdlib.h>
#include "archiver.h"
#include "compress.h"
#include "stream.h"

int main() {
    FILE *fid = sopen("input.txt", "r+b");
    BYTE ch;
    sseek(fid, 1, SEEK_CUR);
    sputc('d', fid);
    sseek(fid, -1, SEEK_CUR);
    ch = sgetc(fid);
    printf("%c\n", ch);
    return 0;
}
