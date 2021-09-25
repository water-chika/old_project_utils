#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	unsigned int sum = 0;
	for (int i = 1; i < argc; i++)
	{
		char* tail;
		unsigned int x = strtoul(argv[i],&tail, 0);
		sum+=x;
	}
	sleep(sum);
	return 0;
}
