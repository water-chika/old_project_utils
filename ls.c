#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

struct option options[]={
	{"version",no_argument, NULL, 'v'},
	{"help",no_argument, NULL, 'h'},
	{"color",optional_argument,NULL,'c'},
	{NULL, 0, NULL, 0},
};

int all_flag = 0;
int long_flag = 0;

void print_entry(struct dirent* entry);
void print_file(const char* path);
void ls(const char* path);

int main(int argc, char** argv)
{
	while (1)
	{
		int option_index;
		int opt = getopt_long(argc, argv, "l", options, &option_index);
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
			case 'l':
				long_flag = 1;
				break;
		}
	}
	if (optind == argc)ls(".");
	else for (int i = optind; i < argc; i++)
	{
		ls(argv[i]);
	}
	putchar('\n');
	return 0;
}
void print_file(const char* path)
{
	const char* name = strrchr(path, '/');
	if (name == NULL)name = path;
	else name = name + 1;
	printf("%s  ", name);
}
void print_entry(struct dirent* entry)
{
	if (long_flag)
	{
		struct stat file_stat;
		if (0 != stat(entry->d_name, &file_stat))
		{
			fprintf(stderr, "can not access attributes of %s", entry->d_name);
			exit(-1);
		}
		printf("%d %d %s\n", 
				file_stat.st_uid, file_stat.st_gid,
				entry->d_name);
	}
	else
	{
		if (entry->d_type == DT_DIR)
		{
			printf("\x1b[34m%s\x1b[0m  ", entry->d_name);
		}
		else
		{
			printf("%s  ", entry->d_name);
		}
	}
}
void ls(const char* path)
{
	struct stat file_stat;
	if (0 != stat(path, &file_stat))
	{
		fprintf(stderr, "can not access %s", path);
		perror(" ");
		exit(-1);
	}
	if (!S_ISDIR(file_stat.st_mode))
	{
		print_file(path);
		return;
	}
	DIR* dir = opendir(path);
	char* cwd = getcwd(NULL, 0);
	if (0!=chdir(path))
	{
		fprintf(stderr, "can not access %s", path);
		perror(" ");
		exit(-1);
	}
	if (dir != NULL)
	{
		struct dirent* dir_entry;
		while (dir_entry = readdir(dir))
		{
			if (0 == strcmp(dir_entry->d_name, "."))continue;
			if (0 == strcmp(dir_entry->d_name, ".."))continue;
			if (dir_entry->d_name[0] == '.')continue;

			print_entry(dir_entry);
		}
		closedir(dir);
	}
	else
	{
		fprintf(stderr, "can not access \'%s\'",path);
		perror(" ");
	}
	chdir(cwd);
	free(cwd);
}
