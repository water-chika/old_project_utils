#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "miss argument\n");
		exit(-1);
	}
	for (int i = 1; i< argc; i++)
	{
		mkdir(argv[i], S_IRUSR | S_IWUSR | S_IXUSR);
	}
	return 0;
}
