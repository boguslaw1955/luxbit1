#include "tar.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	struct stat fileStat;
    
	char * curr_in_file_name = calloc(20,sizeof(20));
	char * out_filename = argv[1];
    FILE *fout = fopen(out_filename, "wb");
    for (int i = 2; i < argc; i ++)
        {
            strcpy(curr_in_file_name, argv[i]);
            FILE *fin = fopen(curr_in_file_name, "r");
			
            int ret = 0;
            ret = makeName(curr_in_file_name, fout);
            ret = makeMode(curr_in_file_name, fout);
            ret = makeUID(curr_in_file_name, fout);
            ret = makeGID(curr_in_file_name, fout);
            ret = makeSize(curr_in_file_name, fout);
            ret = makeMtime(curr_in_file_name, fout);
            ret = makeChksum(curr_in_file_name, fout);
            ret = makeTypeflag(curr_in_file_name, fout);
            ret = makeLinkname(curr_in_file_name, fout);
            ret = makeMagic(curr_in_file_name, fout);
            ret = makeVersion(curr_in_file_name, fout);
            ret = makeUname(curr_in_file_name, fout);
            ret = makeGname(curr_in_file_name, fout);
            ret = makeDevmajor(curr_in_file_name, fout);		/* 329 */
            ret = makeDevminor(curr_in_file_name, fout);		/* 337 */
            ret = makePrefix(curr_in_file_name, fout);	
			
            fclose(fin);
        }
    fclose(fout);
    printf("%s", "  \nkoniec programu tar");
    return 0;
}
int makeName(char * in_file_name, FILE * fout)
{
    int i;
        char * buf = calloc(HDR_NAME, sizeof(char));
        sprintf(buf, "%s" , in_file_name );
        for (i = strlen(in_file_name); i < HDR_NAME; i ++) 
            {
                buf[i] = 0;
            }	
    
    fwrite(buf, 1, HDR_NAME, fout);
	free(buf);
    return 0;
}
int makeMode(char * in_file_name, FILE * fout)
{
    struct stat fileStat;
    if(stat(in_file_name, &fileStat) < 0) 
        return -1;
    char * buf = calloc(HDR_MODE, sizeof(char));
    sprintf(buf, "%o ", fileStat.st_mode);
    
    buf[0] = '0';
    int i;
    for (i = strlen(buf); i < HDR_MODE; i ++) 
        {
            buf[i] = 0;
        }
    
    fwrite(buf, 1, HDR_MODE, fout);
    free(buf);
    return 0;
}

int makeUID(char * in_file_name, FILE *fout)
{
    struct stat fileStat;
    if(stat(in_file_name, &fileStat) < 0) 
        return -1;
    char * buf = calloc(HDR_UID, sizeof(char));
    int ch = fileStat.st_uid;
	if(ch < 10){ sprintf(buf, "%s%o ", ZERO5,ch); }
	else if(ch < 100){ sprintf(buf, "%s%o ", ZERO4, ch); }
	else if (ch < 1000){ sprintf(buf, "%s%o ", ZERO3,ch); }
	else if (ch < 10000){ sprintf(buf, "%s%o ", ZERO2, ch); }
	else  sprintf(buf, "%s%o ", "0", ch);
    int i;
    for (i = strlen(buf); i < HDR_UID; i ++) 
        {
            buf[i] = 0;
        }	
	fwrite(buf,1, HDR_UID, fout);
	free(buf);
    return 0; 
    
}
int makeGID(char * in_file_name, FILE *fout)
{
    struct stat fileStat;
    if(stat(in_file_name, &fileStat) < 0) 
        return -1;
    char * buf = calloc(HDR_GID, sizeof(char));
	int ch = fileStat.st_gid;
	if(ch < 10){ sprintf(buf, "%s%o ", ZERO5, ch); }
	else if(ch < 100){ sprintf(buf, "%s%o ", ZERO4, ch); }
	else if (ch < 1000){ sprintf(buf, "%s%o ", ZERO3, ch); }
	else if (ch < 10000){ sprintf(buf, "%s%o ", ZERO2, ch); }
	else  sprintf(buf, "%s%o ", "0", ch);
    int i;
    for (i = strlen(buf); i < HDR_GID; i ++) 
    {
        buf[i] = 0;
    }
    fwrite(buf, 1, HDR_GID, fout);
	free(buf);
    return 0; 
    
}

int makeSize(char * in_file_name, FILE *fout)
{
    struct stat fileStat;
    if(stat(in_file_name, &fileStat) < 0) 
        return -1;
    
    char * buf = calloc(HDR_SIZE,sizeof(char));
    
    int ich = fileStat.st_size;
	
	if(ich < 10){ sprintf(buf, "%s00000%o ", ZERO5, ich); }
	else if(ich < 100){ sprintf(buf, "%s0000%o ", ZERO4, ich); }
	else if (ich < 1000){ sprintf(buf, "%s000%o ", ZERO3, ich); }
	else if (ich < 10000){ sprintf(buf, "%s00%o ", ZERO2, ich); }
	else  sprintf(buf, "%s%o ", "000000000000000000", ich);
    int i;
    for (i = strlen(buf); i < HDR_SIZE; i ++) 
        {
            buf[i] = 0;
        }
    fwrite(buf, 1, HDR_SIZE, fout);
	free(buf);
    return 0;
    
}
int makeMtime(char * in_file_name, FILE *fout)
{
    struct stat fileStat;
    if(stat(in_file_name, &fileStat) < 0) 
        return -1;
    
    char * buf = calloc(HDR_MTIME,sizeof(char));
    
    int i_mtime = fileStat.st_mtime;
    sprintf(buf,"%o ", i_mtime);
    int i;
    for (i = strlen(buf); i < HDR_MTIME; i ++) 
        {
            buf[i] = 0;
        }
    fwrite(buf, 1, HDR_MTIME, fout);
	free(buf);
    return 0;
    
}
int makeChksum(char * in_file_name, FILE *fout)
{
	fwrite("013760", 1, HDR_CHECKSUM, fout);
	return 0;
}

int makeTypeflag(char * in_file_name, FILE *fout)
{
    char * buf = calloc(HDR_TYPEFLAG,sizeof(char));
    buf[0] = '0';
    printf("%s", buf);
	fwrite(buf, 1, HDR_TYPEFLAG, fout);
    
    return 0;
}

int makeLinkname(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_LINKNAME,sizeof(char));
	sprintf(buf, "%s", "");
	int i;
	for (i = strlen(buf); i < HDR_LINKNAME; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_LINKNAME, fout);
	free(buf);
    return 0;
}

 int makeMagic(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_MAGIC,sizeof(char));
	sprintf(buf, "%s", TMAGIC );
	int i;
	for (i = strlen(buf); i < HDR_MAGIC; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_MAGIC, fout);
	free(buf);
    return 0;
}
int makeVersion(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_VERSION,sizeof(char));
	sprintf(buf, "%s", "00" );
	int i;
	for (i = strlen(buf); i < HDR_VERSION; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_VERSION, fout);
	free(buf);
    return 0;
}
int makeUname(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_UNAME,sizeof(char));
	sprintf(buf, "%s", "boguslaw" );
	int i;
	for (i = strlen(buf); i < HDR_UNAME; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_UNAME, fout);
	free(buf);
    return 0;
}
int makeGname(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_GNAME,sizeof(char));
	sprintf(buf, "%s", "staff" );
	int i;
	for (i = strlen(buf); i < HDR_GNAME; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_GNAME, fout);
	free(buf);
    return 0;
}
int makeDevmajor(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_DEVMAJOR,sizeof(char));
	sprintf(buf, "%s", "000000 " );
	int i;
	for (i = strlen(buf); i < HDR_DEVMAJOR; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_DEVMAJOR, fout);
	free(buf);
    return 0;
}/* 329 */
int makeDevminor(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_DEVMINOR,sizeof(char));
	sprintf(buf, "%s", "000000 " );
	int i;
	for (i = strlen(buf); i < HDR_DEVMINOR; i ++) 
		{
			buf[i] = 0;
		}
	fwrite(buf, 1, HDR_DEVMINOR, fout);
	free(buf);
    return 0;
}/* 337 */
int makePrefix(char * in_file_name, FILE *fout)
{
	char * buf = calloc(HDR_PREFIX,sizeof(char));
	int i;
	for (i = 0; i < HDR_PREFIX; i ++) 
		{
			buf[i] = 0;
		}	
	fwrite(buf, 1, HDR_PREFIX, fout);
    return 0;
}
