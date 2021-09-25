#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "few argument\n");
		exit(-1);
	}
	if (0 != chroot(argv[1]))
	{
		perror("chroot");
		exit(-1);
	}
	chdir("/");
	execl("/bin/sh","/bin/sh", NULL);
	perror("/bin/sh");
	return 0;
}
