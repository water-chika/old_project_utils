#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct option long_options[] = {


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "miss argument\n");
		exit(-1);
	}
	for (int i = 1; i< argc; i++)
	{
		if (0 != mkdir(argv[i], S_IRUSR | S_IWUSR | S_IXUSR))
		{
			fprintf(stderr, "can not create directory %s", argv[i]);
			perror(" ");
			exit(-1);
		}
	}
	return 0;
}
