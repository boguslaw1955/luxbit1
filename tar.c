#include "tar.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for(int ndx = 0; ndx != argc; ++ndx)
        printf("argv[%d] --> %s\n", ndx, argv[ndx]);
    
    
    FILE *fin_array[argc - 1];
    int i;
    for(i = 2; i < argc; i ++)
        fin_array[i] = fopen(argv[i], "r");

    FILE *fout = fopen(argv[1], "wb");
    char * str_out;
    
    int BLK_NAME = 100;
    str_out = headbin(argv[1], BLK_NAME);
    fwrite(str_out, 1, BLK_NAME, fout);
    int BLK_MODE = 8;
    str_out = headbin("000644 ", BLK_MODE);
    fwrite(str_out, 1, BLK_MODE, fout);
    
    
    fflush(fout);
    fclose(fout);
}
char * headbin(char * tekst, int sizb)
{
    char * buf;
    int i;
    buf = (char *) malloc(sizb);
    int temp = strlen(tekst);
    sprintf(buf, "%s" , tekst);
    for (i = strlen(tekst); i < sizb; i ++) 
        {
            buf[i] = 0;
        }	
    return buf;
}
/*

struct posix_header
{				/* byte offset */
char name[100];		/*   0 */
char mode[8];			/* 100 */
char uid[8];			/* 108 */
char gid[8];			/* 116 */
char size[12];		/* 124 */
char mtime[12];		/* 136 */
char chksum[8];		/* 148 */
char typeflag;		/* 156 */
char linkname[100];		/* 157 */
char magic[6];		/* 257 */
char version[2];		/* 263 */
char uname[32];		/* 265 */
char gname[32];		/* 297 */
char devmajor[8];		/* 329 */
char devminor[8];		/* 337 */
char prefix[155];		/* 345 */
/* 500 */