#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa = fopen("1inp.c","r");
	if(fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("1op.c","w");

	ca = getc(fa);
	while(ca!=EOF)
	{
		if(ca == '\t')
			ca = ' ';
		else if(ca == ' ')
		{
			cb = getc(fa);
			if(cb == ' ')
			{
				while(cb==' ')
					cb = getc(fa);
			}
			putc(' ',fb);
			putc(cb,fb);
		}
		else
			putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}