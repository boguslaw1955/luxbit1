
#include "tar.h"
int main_new(int argc, char *argv[]) {
	
	printf("argc = %d\n", argc);
	for(int ndx = 1; ndx != argc; ++ndx)
		printf("argv[%d] --> %s\n", ndx, argv[ndx]);
	
	
	FILE *fin_array[argc - 1];
	int i;
	for(i = 2; i < argc; i ++)
		fin_array[i] = fopen(argv[i], "r");
	
	char * out_filename;
	strcpy(out_filename, argv[1]);
	FILE *fout = fopen(out_filename, "wb");
	char * str_out;
	
	printf("%s", out_filename);
	fclose(fout);
	return 0;
}