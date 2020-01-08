#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fa,*fb;
	int ca,cb;
	int line = 1;
	fa = fopen("ad1inp.c","r");
	if(fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}

	ca = getc(fa);
	while(ca!=EOF)
	{
		printf("%d\t%c",line,ca);

		while(ca!='\n')
		{

			ca = getc(fa);
			if(ca == EOF)
			{
				exit(0); 
			}
			printf("%c",ca);
		}
		line++;
		ca = getc(fa);
	}
	fclose(fa);
	
	return 0;
}