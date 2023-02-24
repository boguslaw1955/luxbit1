#include "tar.h"

struct stat fileStat;
struct dirent *dp;
int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for(int ndx = 1; ndx != argc; ++ndx)
        printf("argv[%d] --> %s\n", ndx, argv[ndx]);
    
    
    FILE *fin_array[argc - 1];
    int i;
    for(i = 2; i < argc; i ++)
        fin_array[i] = fopen(argv[i], "r");

    char * out_filename = argv[1];
    FILE *fout = fopen(out_filename, "wb");
    char * str_out;
    

    int HDR_NAME = 100;
    str_out = headbin(out_filename, HDR_NAME);
    fwrite(str_out, 1, HDR_NAME, fout);
    
    int HDR_MODE = 8;
    char * mode = getMode(out_filename);
    str_out = headbin(mode, HDR_MODE);
    fwrite(str_out, 1, HDR_MODE, fout);
    
    int HDR_UID = 8;
    char * uid = getUID(out_filename);
    str_out = headbin(uid, HDR_UID);
    fwrite(str_out, 1, HDR_UID, fout);
    
    int HDR_GID = 8;
    char * gid = getGID(out_filename);
    str_out = headbin(gid, HDR_GID);
    fwrite(str_out, 1, HDR_GID, fout);
    
    int HDR_SIZE = 12;
    char * size = getSize(out_filename);
    str_out = headbin(size, HDR_SIZE);
    fwrite(str_out, 1, HDR_SIZE, fout);
    
    int HDR_CHKSUM = 8;
    char * chksum = getChksum(out_filename);
    str_out = headbin(chksum, HDR_CHKSUM);
    fwrite(str_out, 1, HDR_CHKSUM, fout);
    
    int HDR_TYPEFLAG = 1;
    str_out = headbin("0", HDR_TYPEFLAG);
    fwrite(str_out, 1, HDR_TYPEFLAG, fout);
    
    int HDR_LINKNAME = 100;
    str_out = headbin("1", HDR_LINKNAME);
    fwrite(str_out, 1, HDR_LINKNAME, fout);
    
    int HDR_MAGIC = 6;
    str_out = headbin("ustar", HDR_MAGIC);
    fwrite(str_out, 1, HDR_MAGIC, fout);
    
    int HDR_VERSION = 2;
    str_out = headbin("00", HDR_VERSION);
    fwrite(str_out, 1, HDR_VERSION, fout);
    
    int HDR_UNAME = 32;
    str_out = headbin("boguslawfries", HDR_UNAME);
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
    
    
    int ret = fflush(fout);
    ret = fclose(fout);
    
    return 0;
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

char * getMode(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * sMode;
    
    sprintf(sMode, "%o", fileStat.st_mode);
    return sMode;
     
}
char * getUID(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * sUID;
    
    sprintf(sUID, "%o", fileStat.st_uid);
    return sUID;
    
}
char * getGID(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * sGID;
    
    sprintf(sGID, "%o", fileStat.st_gid);
    return sGID;
    
}
char * getSize(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * size;
    
    int i_size = fileStat.st_size;
    sprintf(size, "%d",  i_size);
    return size;
    
}
char * getMtime(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * mtime;
    int i_mtime = fileStat.st_mtime;
    sprintf(mtime, "%o", i_mtime);
    return mtime;
    
}
char * getChksum(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    char * chksum;

    sprintf(chksum, "%s", "000000000000");
    
    return chksum;
    
}
char * getLinkname(char * fileName)
{
    if(stat(fileName, &fileStat) < 0) 
        return NULL;
    
    char * linkname;
    
    sprintf(linkname, "%s","1");
    return linkname;
    
}