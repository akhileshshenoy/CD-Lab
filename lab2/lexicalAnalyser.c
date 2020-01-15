//Lexical Analyser

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//enum type{"Arithmetic","Relational","Logical","Special","Keywords","Numerical","String","Identifier"};
// char types

typedef struct token
{
	char lexeme[20];
	unsigned int row,column;
	unsigned int type;
}TOKEN;

const char *keywords[] = {
    "auto", 
    "break", 
    "case", 
    "char", 
    "continue", 
    "do", 
    "default", 
    "const", 
    "double", 
    "else", 
    "enum", 
    "extern", 
    "for", 
    "if", 
    "goto", 
    "float", 
    "int", 
    "long", 
    "register", 
    "return", 
    "signed", 
    "static", 
    "sizeof", 
    "short", 
    "struct", 
    "switch", 
    "typedef", 
    "union", 
    "void", 
    "while", 
    "volatile", 
    "unsigned",
    "include",
    "if"
};

int line=1,col=1,flag=0,last=0;

TOKEN getToken(FILE *fa)
{
	TOKEN tk;

	int ca = getc(fa),cb;
	char buf[100];
	

	while(ca!=EOF)
	{
		if(ca=='#')
		{
			ca = getc(fa);
			while(ca != '\n')
			{
				ca = getc(fa);
			}	
			printf("#\n");	
			line++;
			col = 1;
			last=ftell(fa);
		}
		else if(ca=='/')
		{
			ca = getc(fa);
			if(cb == '/')
			{
				while(ca != '\n')
				{
					ca = getc(fa);
				}
				line++;
				col = 1;
			}
			else if(cb == '*')
			{
				do
				{
					while(ca!='*')
					{
						if(ca == '\n')
						{
							line++;
							col =1;
							last=ftell(fa);
						}
						ca = getc(fa);
					}
					ca = getc(fa);
				}while(ca != '/');
				}
			else
			{
				strcpy(tk.lexeme,"/");
				tk.type = 0;
				tk.row = 0;
				tk.column = 0;
				return tk;
			}
		}
		else if(ca == '\n')
		{
			printf("el,%d\n",line);
			line++;
			col = 1;
			last=ftell(fa);
		}
		else
		{
			
			ungetc(ca,fa);
			int x =ftell(fa);
			fscanf(fa, "%s", buf);
			int y=ftell(fa);
			flag=0;
			for(int i=0;i<33;i++)
			{
				flag=0;
				int n;
				if(strlen(buf)<strlen(keywords[i]))
					n=strlen(buf);
				else
					n=strlen(keywords[i]);
				for(int j=0;j<n;j++)
				{
					if(keywords[i][j]!=buf[j])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					strcpy(tk.lexeme,keywords[i]);
					tk.row = line;
					printf("line = %d,ftell = %ld ,flast = %ld \n",line,x,y );
					tk.column = x-last;//-strlen(keywords[i])+1;
					tk.type = 4;
					return tk;
					break;
				}
			}
		}
		//last=ftell(fa);
		ca = getc(fa);

	}	
}

int main()
{
	FILE *fa;
	int ca,cb;
	fa = fopen("inp.c","r");

	if(fa==NULL)
	{
		printf("Cannot open file.\n");
		exit(0);
	}

	ca = getc(fa);
	while(ca!=EOF)
	{
		ungetc(ca,fa);
		TOKEN tk = getToken(fa);
		printf("<%s,%d,%d,%d>\n",tk.lexeme,tk.row,tk.column,tk.type);
		ca = getc(fa);
	}  

	fclose(fa);
	return 0;
}