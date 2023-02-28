#include "tar.h"
#include <stdlib.h>

struct stat fileStat;
struct dirent *dp;
int main(int argc, char *argv[])
{
    int debug = 0;
    printf("argc = %d\n", argc - 1);
    for(int ndx = 1; ndx != argc; ++ndx)
        printf("argv[%d] --> %s\n", ndx, argv[ndx]);
    
    FILE *fin_array[argc - 1];
    int i;
    for(i = 2; i < argc; i ++)
        fin_array[i] = fopen(argv[i], "r");

    char * out_filename = argv[1];
    char * first_filename = argv[2];
    FILE *fout = fopen(out_filename, "wb");
    char * str_out = 0;

    int HDR_NAME = 100;
    str_out = headbin(first_filename, HDR_NAME);
    fwrite(str_out, 1, HDR_NAME, fout);
    
    int HDR_MODE = 8;
    char * mode = getMode(first_filename);
    str_out = headbin(mode, HDR_MODE);
    fwrite(str_out, 1, HDR_MODE, fout);
    
    int HDR_UID = 8;
    char * uid = getUID(first_filename);
    str_out = headbin(uid, HDR_UID);
    fwrite(str_out, 1, HDR_UID, fout);
    
    int HDR_GID = 8;
    char * gid = getGID(first_filename);
    str_out = headbin(gid, HDR_GID);
    fwrite(str_out, 1, HDR_GID, fout);
    
    int HDR_SIZE = 12;
    char * size = getSize(first_filename);
    str_out = headbin(size, HDR_SIZE);
    fwrite(str_out, 1, HDR_SIZE, fout);
    
    int HDR_MTIME = 12;    
    char * mtime = "000";
    str_out = headbin(mtime, HDR_MTIME);
    fwrite(str_out, 1, HDR_MTIME, fout);
    
    int HDR_CHKSUM = 8;
    char * chksum = getChksum(first_filename);
    str_out = headbin(chksum, HDR_CHKSUM);
    fwrite(str_out, 1 ,HDR_CHKSUM, fout);
      
    int HDR_TYPEFLAG = 1;
    char * typeflag = getTypeflag(first_filename);
    str_out = headbin(typeflag, HDR_TYPEFLAG);
    fwrite(str_out, 1, HDR_TYPEFLAG, fout);
    
    int HDR_LINKNAME = 100;
    char * linkname = getLinkname(first_filename);
    str_out = headbin(first_filename, HDR_LINKNAME);
    fwrite(str_out, 1, HDR_LINKNAME, fout);
    
    int HDR_MAGIC = 6;
    char * magic = getMagic(first_filename);
    str_out = headbin("ustar", HDR_MAGIC);
    fwrite(str_out, 1, HDR_MAGIC, fout);
                                             
    int HDR_VERSION = 2;
    char * version = getVersion(first_filename);
    str_out = headbin(version, HDR_VERSION);
    fwrite(str_out, 1, HDR_VERSION, fout);
    
    int HDR_UNAME = 32;
    char * uname = getUname(first_filename);
    str_out = headbin(uname, HDR_UNAME);
    fwrite(str_out, 1, HDR_UNAME, fout);
    
    int HDR_GNAME = 32;    
    char * gname = getGname(first_filename);
    str_out = headbin(gname, HDR_GNAME);
    fwrite(str_out, 1, HDR_GNAME, fout);
    
    int HDR_DEVMAJOR = 8;
    str_out = headbin("20", HDR_DEVMAJOR);
    fwrite(str_out, 1, HDR_DEVMAJOR, fout);
    
    int HDR_DEVMINOR = 8;
    str_out = headbin("20", HDR_DEVMINOR);
    fwrite(str_out, 1, HDR_DEVMINOR, fout);
    
    int HDR_PREFIX = 155;
    str_out = headbin("", HDR_PREFIX);
    fwrite(str_out, 1, HDR_PREFIX, fout);
    
    
    int ret = fflush(fout);
    ret = fclose(fout);
    
    return 0;
}
char * headbin(char * tekst, int sizb)
{
    char * buf = 0;
    int i;
    buf = malloc(sizb);
    sprintf(buf, "%s" , tekst);
    for (i = strlen(tekst); i < sizb; i ++) 
        {
            buf[i] = 0;
        }	

    return buf;
}

char * getMode(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
     char  * sMode = calloc(10,sizeof(char));
    // sMode = malloc(8);
    
    sprintf(sMode, "%o ", fileStat.st_mode);

    sMode[0] = '0';
    return sMode;
     
}
char * getUID(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * sUID = calloc(10,sizeof(char));
//    sUID = malloc(8);
    sprintf(sUID, "%o ", fileStat.st_uid); 
    sprintf(sUID, "%s", strcat(ZERO3, sUID));

    return sUID;
    
}
char * getGID(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * sGID = calloc(10,sizeof(char));
    
    sprintf(sGID, "%o ", fileStat.st_gid);
    sprintf(sGID, "%s", strcat(ZERO3, sGID));
    return sGID;
    
}
char * getSize(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * size = calloc(10,sizeof(char));;
//    size = malloc(12);
    int i_size = fileStat.st_size;
    sprintf(size, "%o",  i_size);
    return size;
    
}
char * getMtime(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * mtime = calloc(20,sizeof(char));
    
    int i_mtime = fileStat.st_mtime;
    sprintf(mtime, "%d", i_mtime);
    return mtime;
    
}
char * getChksum(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    char * chksum = calloc(10,sizeof(char));
//  
    sprintf(chksum, "%s", "1234");
    
    return chksum;
    
}
char * getTypeflag(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    char * typeflag = calloc(2,sizeof(char));
//    typeflag = malloc(1);
    sprintf(typeflag, "%s", "0");
    
    return typeflag;
    
}

char * getLinkname(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * linkname = calloc(100,sizeof(char));
//    linkname = malloc(100);
    sprintf(linkname, "%s", fileName);
    return fileName;
    
}

char * getMagic(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * magic = calloc(10,sizeof(char));
//  
    sprintf(magic, "%s","ustar");
    return magic;
    
}
char * getVersion(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * version = calloc(10,sizeof(char));
//  
    sprintf(version, "%s","1");
    return version;
    
}
char * getUname(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * uname = calloc(32,sizeof(char));;
//  
    sprintf(uname, "%s","00bfries");
    return uname;
    
}
char * getGname(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * gname = calloc(32,sizeof(char));;
    
    sprintf(gname, "%s","utar");
    return gname;
    
}
char * getDevMajor(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * major = calloc(10,sizeof(char));
    
    sprintf(major, "%s", "20");
    
    return major;
    
}
char * getDevMinor(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * minor = calloc(10,sizeof(char));
    sprintf(minor, "%s", "20");
    
    return minor;     
}