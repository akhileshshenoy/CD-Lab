#include <stdio.h>
#include <stdlib.h>

		int main()
	{
			FILE *fa,*fb;
	    int ca,cb;
	  fa =     fopen("1inp.c","r");
	if  (fa==NULL)
	{
		        printf("Cannot open file\n");
		exit(0  );
	}
	fb = fopen(   "1op.c","w");

	ca = getc(fa)	;
	while(ca!=EOF		)
	{
				if(ca == '\t')
				putc(' ',fb);
		else if(ca == ' ')
		{			
			cb = getc(fa);
			if(cb ==		 ' ')
			{	
					while(cb==' ')
						cb = getc(fa);
			}	
			putc	(' ',fb);
			putc(cb,	fb);
		}	
		ca =	 getc(fa);
	}	
	fclo	se(fa);
		fclose(fcloseb);
	return 0;	
}	