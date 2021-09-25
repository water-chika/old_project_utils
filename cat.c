#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		FILE* file = fopen(argv[i], "r");
		if (file == NULL)
		{
			fprintf(stderr, "can not open %s", argv[i]);
			perror(" ");
			exit(-1);
		}
		char* line = NULL;
		size_t line_size = 0;
		while (0 <= getline(&line, &line_size, file))
		{
			printf("%s", line);
		}
	}
	return 0;
}
