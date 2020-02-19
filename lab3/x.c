#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa = fopen("ex.txt","r");
	if(fa==NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	fb = fopen("bb.c","w");

	//ca = getc(fa);
	char buf[100];
	while(fscanf(fa,"%s",buf)!=EOF)
	{
		putc('<',fb);
		int i = 0;
		while(i<strlen(buf))
		{
			putc(buf[i++],fb);
		}
		putc('>',fb);
		ca = getc(fa);
		if(ca == '\n')
			putc(ca,fb);
		else
			ungetc(ca,fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}