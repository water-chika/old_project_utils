#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char* cwd = getcwd(NULL, 0);
	puts(cwd);
	free(cwd);
	return 0;
}
