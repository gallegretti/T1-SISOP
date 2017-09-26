#include "../include/cthread.h"
#include <stdio.h>

int main()
{
	char buffer[100];
	cidentify(buffer, 100);
	printf("%s", buffer);
	return 0;
}
