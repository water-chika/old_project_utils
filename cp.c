#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
void copy_file(int src, int dest);
int main(int argc, char** argv)
{
	struct stat dest_stat;
	if (0 != stat(argv[argc-1], &dest_stat))
	{
		perror("stat");
		exit(-1);
	}
	if (S_ISDIR(dest_stat.st_mode))
	{
		int* src = (int*)malloc(sizeof(int)*(argc-2));
		for (int i = 1; i < argc-1; i++)
		{
			src[i-1] = open(argv[i], O_RDONLY);
			if (src[i-1] == -1)
			{
				fprintf(stderr, "can not open file %s", argv[i]);
				perror(" ");
				exit(-1);
			}
		}
		chdir(argv[argc-1]);
		for (int i = 0; i < argc-2; i++)
		{
			char* name = strrchr(argv[i+1], '/');
			if (name == NULL)name = argv[i+1];
			else name = name+1;
			int dest = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
			if (dest == -1)
			{
				fprintf(stderr, "can not open file %s", name);
				perror(" ");
				exit(-1);
			}
			
			copy_file(src[i], dest);

			close(src[i]);
			close(dest);
		}
		free(src);
	}
	else
	{
		assert(argc == 3);
		int src = open(argv[1], O_RDONLY);
		if (src == -1)
		{
			fprintf(stderr, "can not open file %s", argv[1]);
			perror(" ");
			exit(-1);
		}

		int dest = open(argv[argc-1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
		assert(dest > 0);
		copy_file(src,dest);

		close(src);
		close(dest);
	}
	return 0;
}
void copy_file(int src, int dest)
{
	int count = copy_file_range(src, NULL, dest, NULL, 512*512, 0);
	assert(count < 512*512);
}
