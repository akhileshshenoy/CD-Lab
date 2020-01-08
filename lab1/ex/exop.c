#include <stdio.h>
#include <stdlib.h>

int main()
{
		FILE *fa, *fb;
	int ca, cb;
	
	fa = fopen("./exinp.c","r");
	if(fa == NULL)
	{
		printf("Cannot open file \n"); 		exit(0);
	}
	printf("opened file inp\n");
	fb = fopen("./exop.c","w");
	printf("opened file op"\n);
	ca = getc(fa);
	
	while(ca!=EOF)
	{
		if(ca == '/')
		{
			cb = getc(fa);
			if(cb == '/')
			{
				while(ca != '\n')
					ca = getc(fa);
			}
			else if(cb == '*')
			{
				do
				{
					while(ca!='*')
						ca = getc(fa);
				}while(ca != '/');
			}
			else
			{
				putc(ca,fb);
				putc(cb,fb);
			}
		}
		else
		{
			putc(ca,fb);
		}
		ca = getc(fa);
	}
		fclose(fa);
		fclose(fb);
	return 0;
}