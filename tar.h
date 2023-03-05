#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TMAGIC   "ustar"       /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

char * ZERO2 = "00";
char * ZERO3 = "000";
char * ZERO4 = "0000";
char * ZERO5 = "00000";


int HDR_NAME = 100;
int HDR_MODE = 8;
int HDR_UID = 8;
int HDR_GID = 8;
int HDR_SIZE = 12;
int HDR_MTIME = 12;
int HDR_CHECKSUM = 8;
int HDR_TYPEFLAG = 1;
int HDR_LINKNAME = 100; 
int HDR_MAGIC = 6;
int HDR_VERSION =2;
int HDR_UNAME = 32;
int HDR_GNAME =32;
int HDR_DEVMAJOR = 8;
int HDR_DEVMINOR = 8; 
int HDR_PREFIX = 155;

int makeName(char * filename, FILE *fout);
int makeMode(char * filenane, FILE *fout);
int makeUID(char * filename, FILE *fout);
int makeGID(char * filename, FILE *fout);
int makeSize(char * filename, FILE *fout);
int makeMtime(char * filename, FILE *fout);
int makeChksum(char * filename, FILE *fout);
int makeTypeflag(char * filename, FILE *fout);
int makeLinkname(char * filename, FILE *fout);
int makeMagic(char * filename, FILE *fout);
int makeVersion(char * filename, FILE *fout);
int makeUname(char * filename, FILE *fout);
int makeGname(char * filename, FILE *fout);
int makeDevmajor(char * filename, FILE *fout);		/* 329 */
int makeDevminor(char * filename, FILE *fout);		/* 337 */
int makePrefix(char * filename, FILE *fout);	

