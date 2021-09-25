#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>

struct option long_options[]={
	{"force",no_argument,NULL,'f'},
	{"recursive", no_argument, NULL, 'r'},
	{"dir", no_argument, NULL, 'd'},
	{NULL,0,NULL,0}
};
int recursive = 0;
int rmdir_flag = 0;
int force_flag = 0;

int rmdir_recursive(char* name);

int main(int argc, char** argv)
{
	if (argc<2)
	{
		fprintf(stderr, "less argument\n");
		exit(-1);
	}
	while(1)
	{
		int opt = getopt_long(argc, argv, "rf", long_options, NULL);
		if (opt==-1)break;
		switch (opt)
		{
			case '?':
				exit(-1);
			case 'r':
				recursive = 1;
				rmdir_flag = 1;
				break;
			case 'f':
				force_flag = 1;
				break;
			case 'd':
				rmdir_flag = 1;
				break;
		}
	}

	for (int i = optind; i < argc; i++)
	{
		struct stat file_stat;
		if (0 != stat(argv[i], &file_stat))
		{
			if (force_flag)continue;
			fprintf(stderr, "can not open file %s", argv[i]);
			perror(" ");
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			if (rmdir_flag == 0)
			{
				fprintf(stderr, "%s is a direction\n", argv[i]);
				exit(-1);
			}
			if (recursive)
			{
				rmdir_recursive(argv[i]);
			}
			else if (0 != rmdir(argv[i]))
			{
				fprintf(stderr, "fail to rmdir %s", argv[i]);
				perror(" ");
				exit(-1);
			}
		}
		else if (0 != unlink(argv[i]))
		{
			fprintf(stderr, "fail to unlink %s\n", argv[i]);
			exit(-1);
		}
	}
	return 0;
}

int rmdir_recursive(char* name)
{
	DIR* dir = opendir(name);
	assert(dir);
	struct dirent* entry;
	assert(chdir(name)==0);
	while (entry = readdir(dir))
	{
		if (0 == strcmp(entry->d_name, "."))continue;
		if (0 == strcmp(entry->d_name, ".."))continue;
		if (entry->d_type == DT_DIR)
		{
			rmdir_recursive(entry->d_name);
		}
		else
		{
			assert(unlink(entry->d_name)==0);
		}
	}
	assert(chdir("..")==0);
	assert(rmdir(name)==0);
}
