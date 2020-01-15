#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct token
{
	int row,column;
	char lexeme[100];
	char type[100];
}token;

int main()
{
	char* types[]={"Arithmetic","Relational","Logical","Special","Keyword","Constant","String","Identifier"};
	const char *keywords[] = {
    "auto", "break", "case","char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", 
    "static","sizeof", "short", "struct", "switch", "typedef", "union", "void","while", "volatile", "unsigned","include"
};

	FILE *fa;
	fa=fopen("inp.c","rw");
	int ca,k=0,row=1,column=1,last=0,flag=0;
	token t; t.row=1; t.column=1;
	ca=getc(fa);
	while(ca!=EOF)
	{
		memset(t.lexeme,'\0',strlen(t.lexeme));
		while(ca=='#')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			while(ca!='\n')
				ca=getc(fa);
			ca=getc(fa);
			last=ftell(fa);
			row++;
		}
		if(ca=='/')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			ca=getc(fa);
			
			if(ca=='/')
			{
				while(ca!='\n')
					ca=getc(fa);
				last=ftell(fa);
				row++;
			}
			else if(ca=='*')
			{
				while(ca!='/')
				{
					while(ca!='*')
					{
						if(ca=='\n')
						{
							last=ftell(fa);
							row++;
						}
						ca=getc(fa);
					}
					ca=getc(fa);
				}
			}
			else
				fseek(fa,-1,SEEK_CUR);
		}
		else if(ca=='=')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[1]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='=')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='"')
		{
			memset(t.lexeme,'\0',100);
			strcpy(t.type,types[6]);
			ca=getc(fa);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			while(ca!='"')
			{
				if(ca=='\n')
				{
					last=ftell(fa);
					row++;
				}
				t.lexeme[k]=ca;
				k++;
				ca=getc(fa);
			}
			printf("<%s,%d,%d,%d,%s>\n",t.lexeme,k,t.row,t.column,t.type);
		}
		else if(ca=='('||ca==')'||ca==';'||ca==','||ca=='{'||ca=='}')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[3]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='!')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[2]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='|')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[2]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='|')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='&')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[2]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='&')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='<'||ca=='>')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[1]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='=')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		
		else if(ca=='+')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[0]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='='||ca=='+')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='-')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[0]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='='||ca=='-')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='*'||ca=='/')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[0]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			if(ca=='=')
				t.lexeme[k]=ca;
			else
				fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca=='%')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[0]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			//ca=getc(fa);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		
		else if(ca>'0'&&ca<'9')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			strcpy(t.type,types[5]);
			k=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			while(ca>='0'&&ca<='9')
			{
				if(ca=='.')
				{
					t.lexeme[k]=ca;
					k++;
					ca=getc(fa);
				}
				t.lexeme[k]=ca;
				k++;
				ca=getc(fa);
			}
			fseek(fa,-1,SEEK_CUR);
			printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
		}
		else if(ca>='a'&&ca<='z'||ca=='_')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			k=0;
			flag=0;
			t.column=ftell(fa)-last;
			t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			while((ca>=97&&ca<=122)||(ca>=48&&ca<=57)||ca=='_')
			{
				t.lexeme[k]=ca;
				k++;
				ca=getc(fa);
			}
			for(int i=0;i<33;i++)
			{
				flag=0;
				int n;
				if(strlen(t.lexeme)!=strlen(keywords[i]))
				{
					flag=1;
					continue;
				}
				else
					n=strlen(keywords[i]);
				for(int j=0;j<n;j++)
				{
					if(keywords[i][j]!=t.lexeme[j])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					strcpy(t.type,types[4]);
					printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
					break;
				}
			}
			if(flag==1)
			{
				strcpy(t.type,types[7]);
				printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
			}
			fseek(fa,-1,SEEK_CUR);
		}
		
		if(ca=='\n')
		{
			last=ftell(fa);
			row++;
			ca=getc(fa);
		}
		else
		ca=getc(fa);
	}
}
