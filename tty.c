#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (isatty(0))
	{
		printf("%s\n",ttyname(0));
	}
	else
	{
		printf("no a tty\n");
	}
	return 0;
}
