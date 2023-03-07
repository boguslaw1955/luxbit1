#include "tar.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	struct stat fileStat;
	char * out_filename = argv[1];
    remove(out_filename);
    FILE *fout = fopen(out_filename, "wb");
    char *buf = calloc(512, sizeof(char) ); 
    for (int i = 2; i < argc; i ++)
        {
            FILE *fin = fopen(argv[i], "r");
            int checksum = 0;
			
            int ret = 0;
            ret = makeBuffer(buf);
            ret = makeName(argv[i], PNAME, SNAME, buf);
            ret = makeMode(argv[i], PMODE, SMODE, buf);
            ret = makeUID(argv[i], PUID, SUID, buf);
            ret = makeGID(argv[i], PGID, SGID, buf);
            ret = makeSize(argv[i], PSIZE, SSIZE, buf);
            ret = makeMtime(argv[i], PMTIME, SMTIME, buf);
            ret = makeChksum(argv[i], PCHECKSUM, SCHECKSUM, buf);
            ret = makeTypeflag(argv[i], PTYPEFLAG, STYPEFLAG, buf);
            ret = makeLinkname(argv[i], PLINKNAME, SLINKNAME, buf);
            ret = makeMagic(argv[i], PMAGIC, SMAGIC, buf);
            ret = makeVersion(argv[i], PVERSION, SVERSION, buf);
            ret = makeUname(argv[i], PUNAME, SUNAME, buf);
            ret = makeGname(argv[i], PGNAME, SGNAME, buf);
            ret = makeDevmajor(argv[i], PMAJOR, SMAJOR, buf);		/* 329 */
            ret = makeDevminor(argv[i], PMINOR, SMINOR, buf);		/* 337 */
            ret = makePrefix(argv[i], PREFIX, SPREFIX, buf);	
            ret = writeHeader(buf, fout);
        
            fclose(fin);
        }
    fclose(fout);
    printf("%s", "  \nkoniec programu tar");
    return 0;
}
int makeBuffer(char * buf)
{
    int i;
    buf = calloc(BUFFSIZE, sizeof(char));
    for (i = 0; i < BUFFSIZE; i ++) {
        buf[i] = 0;
    }
    return 0;
}
int writeHeader(char * buf, FILE * fout)
{
    fwrite(buf, 1, BUFFSIZE, fout); 
    int i;
    for (i = 0; i < BUFFSIZE; i ++) {
        buf[i] = 0;
    }
    fwrite(buf, 1, BUFFSIZE, fout); 
    fwrite(buf, 1, BUFFSIZE, fout); 
    return 0;
}
int makeName(char * in_filename, int pos, int size, char * buf)
{
    sprintf(buf, "%s" , in_filename );	
    
    return 0;
}
int makeMode(char * in_filename, int pos, int size, char * buf)
{
    struct stat fileStat;
    if(stat(in_filename, &fileStat) < 0) 
        return -1;
    sprintf(buf + PMODE, "%o ", fileStat.st_mode);
    
    (buf + PMODE)[0] = '0';
    return 0;
}

int makeUID(char * in_filename, int pos, int size, char * buf)
{
    struct stat fileStat;
    if(stat(in_filename, &fileStat) < 0) 
        return -1;
    int ch = fileStat.st_uid;
    
	if(ch < 10){ sprintf(buf + PUID, "%s%o ", ZERO5,ch); }
	else if(ch < 100){ sprintf(buf + PUID, "%s%o ", ZERO4, ch); }
	else if (ch < 1000){ sprintf(buf + PUID, "%s%o ", ZERO3,ch); }
	else if (ch < 10000){ sprintf(buf + PUID, "%s%o ", ZERO2, ch); }
	else  sprintf(buf + PUID, "%s%o ", "0", ch);
    
    return 0; 
    
}
int makeGID(char * in_filename, int pos, int size, char * buf)
{
    struct stat fileStat;
    if(stat(in_filename, &fileStat) < 0) 
        return -1;
	int ch = fileStat.st_gid;
	if(ch < 10){ sprintf(buf + PGID, "%s%o ", ZERO5, ch); }
	else if(ch < 100){ sprintf(buf + PGID, "%s%o ", ZERO4, ch); }
	else if (ch < 1000){ sprintf(buf + PGID, "%s%o ", ZERO3, ch); }
	else if (ch < 10000){ sprintf(buf + PGID, "%s%o ", ZERO2, ch); }
	else  sprintf(buf + PGID, "%s%o ", "0", ch);

    return 0; 
    
}

int makeSize(char * in_filename, int pos, int size, char * buf)
{
    struct stat fileStat;
    if(stat(in_filename, &fileStat) < 0) 
        return -1;
    
    int ich = fileStat.st_size;
	
	if(ich < 10){ sprintf(buf + PSIZE, "%s00000%o ", ZERO5, ich); }
	else if(ich < 100){ sprintf(buf + PSIZE, "%s0000%o ", ZERO4, ich); }
	else if (ich < 1000){ sprintf(buf + PSIZE, "%s000%o ", ZERO3, ich); }
	else if (ich < 10000){ sprintf(buf + PSIZE, "%s00%o ", ZERO2, ich); }
	else  sprintf(buf + PSIZE, "%s%o ", "0", ich);

    return 0;
    
}
int makeMtime(char * in_filename, int pos, int size, char * buf)
{
    struct stat fileStat;
    if(stat(in_filename, &fileStat) < 0) 
        return -1;
    
    int i_mtime = fileStat.st_mtime;
    sprintf(buf + PMTIME,"%o ", i_mtime);
    sprintf(buf + PMTIME, "%s", "14373174110");
    buf[147] = ' ';
    return 0;
}
int makeChksum(char * in_filename, int pos, int size, char * buf)
{
    sprintf(buf + PCHECKSUM,"%s", "013760");
	return 0;
}

int makeTypeflag(char * in_filename, int pos, int size, char * buf)
{
    sprintf(buf + PTYPEFLAG - 1, "%s", " ");
    sprintf(buf + PTYPEFLAG, "%s", "0");
    return 0;
}

int makeLinkname(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PLINKNAME, "%s", "");
    return 0;
}

 int makeMagic(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PMAGIC, "%s", TMAGIC);
    return 0;
}
int makeVersion(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PVERSION, "%s", TVERSION );
    return 0;
}
int makeUname(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PUNAME, "%s", "boguslaw" );
    return 0;
}
int makeGname(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PGNAME, "%s", "staff" );
    return 0;
}
int makeDevmajor(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PMAJOR, "%s", "000000 " );
    return 0;
}/* 329 */
int makeDevminor(char * in_filename, int pos, int size, char * buf)
{
	sprintf(buf + PMINOR, "%s", "000000 " );
    return 0;
}/* 337 */
int makePrefix(char * in_filename, int pos, int size, char * buf)
{
	return 0;
}
