#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char** argv)
{
	int src = open(argv[1], O_RDONLY);
	assert(src > 0);
	int dest = open(argv[argc-1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
	assert(dest > 0);
	int count = copy_file_range(src, NULL, dest, NULL, 512*512, 0);
	assert(count < 512*512);
	return 0;
}
