#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

char * ZERO3 = "000";
int HDR_NAME = 100;
int HDR_MODE = 8;
int HDR_UID = 8;
int HDR_GID = 8;
int HDR_SIZE = 12;
int HDR_MTIME = 12;

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

