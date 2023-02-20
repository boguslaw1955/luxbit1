#include "tar.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for(int ndx = 1; ndx != argc; ++ndx)
        printf("argv[%d] --> %s\n", ndx, argv[ndx]);
    
    
    FILE *fin_array[argc - 1];
    int i;
    for(i = 2; i < argc; i ++)
        fin_array[i] = fopen(argv[i], "r");

    FILE *fout = fopen(argv[1], "wb");
    char * str_out;
    
    int HDR_NAME = 100;
    str_out = headbin(argv[1], HDR_NAME);
    fwrite(str_out, 1, HDR_NAME, fout);
    
    int HDR_MODE = 8;
    str_out = headbin("000644 ", HDR_MODE);
    fwrite(str_out, 1, HDR_MODE, fout);
    
    int HDR_UID = 8;
    str_out = headbin("000765 ", HDR_UID);
    fwrite(str_out, 1, HDR_UID, fout);
    
    int HDR_GID = 8;
    str_out = headbin("000024 ", HDR_GID);
    fwrite(str_out, 1, HDR_GID, fout);
    
    int HDR_SIZE = 12;
    str_out = headbin("12345678912 ", HDR_SIZE);
    fwrite(str_out, 1, HDR_SIZE, fout);
    
    int HDR_MTIME = 12;
    str_out = headbin("14361112131 ", HDR_MTIME);
    fwrite(str_out, 1, HDR_MTIME, fout);
    
    int HDR_CHKSUM = 8;
    str_out = headbin("1234567 ", HDR_CHKSUM);
    fwrite(str_out, 1, HDR_CHKSUM, fout);
    
    int HDR_TYPEFLAG = 1;
    str_out = headbin("0", HDR_TYPEFLAG);
    fwrite(str_out, 1, HDR_TYPEFLAG, fout);
    
    int HDR_LINKNAME = 100;
    str_out = headbin("", HDR_LINKNAME);
    fwrite(str_out, 1, HDR_LINKNAME, fout);
    
    int HDR_MAGIC = 6;
    str_out = headbin("ustar", HDR_MAGIC);
    fwrite(str_out, 1, HDR_MAGIC, fout);
    
    int HDR_VERSION = 2;
    str_out = headbin("00", HDR_VERSION);
    fwrite(str_out, 1, HDR_VERSION, fout);
    
    int HDR_UNAME = 32;
    str_out = headbin("boguslaw", HDR_UNAME);
    fwrite(str_out, 1, HDR_UNAME, fout);
    
    int HDR_GNAME = 32;
    str_out = headbin("staff", HDR_GNAME);
    fwrite(str_out, 1, HDR_GNAME, fout);
    
    int HDR_DEVMAJOR = 8;
    str_out = headbin("0000000", HDR_DEVMAJOR);
    fwrite(str_out, 1, HDR_DEVMAJOR, fout);
    
    int HDR_DEVMINOR = 8;
    str_out = headbin("0000000", HDR_DEVMINOR);
    fwrite(str_out, 1, HDR_DEVMINOR, fout);
    
    int HDR_PREFIX = 155;
    str_out = headbin("", HDR_PREFIX);
    fwrite(str_out, 1, HDR_PREFIX, fout);
    
    fflush(fout);
    fclose(fout);
}
char * headbin(char * tekst, int sizb)
{
    char * buf;
    int i;
    buf = (char *) malloc(sizb);
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