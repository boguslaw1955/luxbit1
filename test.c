#include "tar.h"

int main_old(int argc, char *argv[]) {
	
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
	
	int HDR_TYPEFLAG = 1;
	str_out = headbin("0", HDR_TYPEFLAG);
	fwrite(str_out, 1, HDR_TYPEFLAG, fout);
	
	int HDR_MTIME = 12;
	char * mtime = getMtime(out_filename);
	str_out = headbin(mtime, HDR_MTIME);
	fwrite(str_out, 1, HDR_MTIME, fout);
	
	int HDR_LINKNAME = 100;
	str_out = headbin("1", HDR_LINKNAME);
	fwrite(str_out, 1, HDR_LINKNAME, fout);
	
	int HDR_MAGIC = 6;
	str_out = headbin("ustar", HDR_MAGIC);
	fwrite(str_out, 1, HDR_MAGIC, fout);
	
	int HDR_VERSION = 2;
	str_out = headbin("00", HDR_VERSION);
	fwrite(str_out, 1, HDR_VERSION, fout);
	
	int ret = fclose(fout);
	return 0;
	
}