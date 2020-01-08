
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
	"#include"
	//#include
		ca = getc(fa);
	while(ca!=EOF)
	{
		if(ca=='#')
		{
			cb = getc(fa);
			while(cb != '\n')
				getc(cb);
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
		else if(ca=='"')
		{
			putc(ca,fb);
			cb = getc(fa);
			while(cb!='"')
			{
				cb = getc(fa);
				putc(cb,fb);
			}
		}
		else
			putc(ca,fb);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}
