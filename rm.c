#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

struct option long_options[]={
	{"force",no_argument,NULL,'f'},
	{NULL,0,NULL,0}
};
int main(int argc, char** argv)
{
	if (argc<2)
	{
		fprintf(stderr, "less argument\n");
		exit(-1);
	}
	while(1)
	{
		int opt = getopt_long(argc, argv, "", long_options, NULL);
		if (opt==-1)break;
		switch (opt)
		{
			case 'f':
				break;
		}
	}
	if (0 != unlink(argv[optind]))
	{
		fprintf(stderr, "fail to unlink %s\n", argv[optind]);
		exit(-1);
	}
	return 0;
}
