#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


char * TMAGIC  = "ustar";
char * TVERSION = "00";
char * ZERO2 = "00";
char * ZERO3 = "000";
char * ZERO4 = "0000";
char * ZERO5 = "00000";

int BUFFSIZE = 512;
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
int HDR_VERSION = 2;
int HDR_UNAME = 32;
int HDR_GNAME = 32;
int HDR_DEVMAJOR = 8;
int HDR_DEVMINOR = 8; 
int HDR_PREFIX = 155;
int CONTENT = 512;

int PNAME = 0;
int PMODE = 100;
int PUID = 108;
int PGID = 116;
int PSIZE = 124;
int PMTIME = 136;
int PCHECKSUM = 148;
int PTYPEFLAG = 156;
int PLINKNAME = 157;
int PMAGIC = 257;
int PVERSION = 263;
int PUNAME = 265;
int PGNAME = 297;
int PMAJOR = 329;
int PMINOR = 337;
int PREFIX = 345;

int SNAME = 100;
int SMODE = 8;
int SUID = 8;
int SGID = 8;
int SSIZE = 12;
int SMTIME = 12;
int SCHECKSUM = 8;
int STYPEFLAG = 1;
int SLINKNAME = 100;
int SMAGIC = 6;
int SVERSION = 2;
int SUNAME = 32;
int SGNAME = 32;
int SMAJOR = 8;
int SMINOR = 8;
int SPREFIX = 155;

int makeBuffer(char * buf);
int makeName(char * in_filename, int pos, int size, char * buf);
int makeMode(char * in_filename, int pos, int size, char * buf);
int makeUID(char * in_filename, int pos, int size, char * buf);
int makeGID(char * in_filename, int pos, int size, char * buf);
int makeSize(char * in_filename, int pos, int size, char * buf);
int makeMtime(char * in_filename, int pos, int size, char * buf);
int makeTypeflag(char * in_filename, int pos, int size, char * buf);
int makeLinkname(char * in_filename, int pos, int size, char * buf);
int makeMagic(char * in_filename, int pos, int size, char * buf);
int makeVersion(char * in_filename, int pos, int size, char * buf);
int makeDevmajor(char * in_filename, int pos, int size, char * buf);		/* 329 */
int makeDevminor(char * in_filename, int pos, int size, char * buf);		/* 337 */
int makePrefix(char * in_filename, int pos, int size, char * buf);
int makeChksum(char * buf);
int writeHeader(char * buf, FILE * out_file_name);
int makeContent();
