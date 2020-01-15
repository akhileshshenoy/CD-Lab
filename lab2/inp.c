#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa = fopen("2inp.c","r");
	if(fa==NULL)
	{
		printf("Cannot open file.\n");
		exit(0);
	}
	fb = fopen("2op.c","w");

	ca = getc(fa);
	while(ca!=EOF)
	{
		if(ca=='#')
		{
			cb = getc(fa);
			while(cb != '\n')
			{
				cb = getc(fa);
			}		
		}
		else if(ca=='\'')
		{
			putc(ca,fb);
			cb = getc(fa);
			while(cb != '\'')
			{
				putc(cb,fb);
				cb = getc(fa);
			}
			putc(cb,fb);		
		}
		else if(ca=='/')
		{
			putc(ca,fb);
			cb = getc(fa);
			if(cb == '/')
			{
				putc(cb,fb);
				while(ca != '\n')
				{
					ca = getc(fa);
					putc(ca,fb);
				}
			}
			else if(cb == '*')
			{
				putc(cb,fb);
				do
				{
					while(ca!='*')
					{
						ca = getc(fa);
						putc(ca,fb);
					}
					ca = getc(fa);
					putc(ca,fb);
				}while(ca != '/');
			}
			else
			{
				putc(cb,fb);
			}
		}
		// else if(ca=='"')
		// {
		// 	putc(ca,fb);
		// 	cb = getc(fa);
		// 	while(cb != '"')
			{
				putc(cb,fb);
				cb = getc(fa);
			}
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
