//This program revoes comments
//commentKiller
#include <stdio.h> 
#include <stdlib.h> 
int main()
{
	//init 2 f pointers
	FILE *fa, *fb;
	int ca, cb;
	/* open 2 files
	one to read from
	one to write to
	*/

	fa = fopen("./exinp.c","r");
	#define x 5;printf("x\n");
	if(fa == NULL)
	{
		
		printf("Cannot open file \n"); //file doesn't exist
		
		exit(0);
	}
	printf("opened file inp\n");
	fb = fopen("./exop.c","w");
	printf("opened file op\n");
	ca = getc(fa);
	/*logic to remove comments*/
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
	//comment
	fclose(fa);
	//close the files ffs
	fclose(fb);
	return 0;
}


