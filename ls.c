#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <stdlib.h>

struct option options[]={
	{"version",no_argument, NULL, 'v'},
	{"help",no_argument, NULL, 'h'},
	{"color",optional_argument,NULL,'c'},
	{NULL, 0, NULL, 0},
};

int all_flag = 0;

int main(int argc, char** argv)
{
	while (1)
	{
		int option_index;
		int opt = getopt_long(argc, argv, "", options, &option_index);
		if (opt == -1)break;
		switch (opt)
		{
			case '?':
				printf("try ls --help\n");
				exit(-1);
			case 'v':
				printf("water ls\n");
				exit(0);
			case 'h':
				printf("this ls is made by water\n");
				exit(0);
			case 'c':
				break;
		}
	}
	const char* path = ".";
	if (optind != argc)
	{
		path = argv[optind];
	}
	DIR* dir = opendir(path);
	if (dir != NULL)
	{
		struct dirent* dir_entry;
		while (dir_entry = readdir(dir))
		{
			if (0 == strcmp(dir_entry->d_name, "."))continue;
			if (0 == strcmp(dir_entry->d_name, ".."))continue;
			if (dir_entry->d_name[0] == '.')continue;
			if (dir_entry->d_type == DT_DIR)
			{
				printf("\x1b[34m%s\x1b[0m  ", dir_entry->d_name);
			}
			else
			{
				printf("%s  ", dir_entry->d_name);
			}
		}
		closedir(dir);
	}
	else
	{
		fprintf(stderr, "%s: can not access \'%s\'", argv[0], path);
		perror(" ");
	}
	putchar('\n');
	return 0;
}
