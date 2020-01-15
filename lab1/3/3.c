#include<stdio.h>
#include <string.h>
int main()
{
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
    "include"
};
	FILE *fa;
	char buf[100];
	int line=1,col=1,flag=0,last=0;
	fa=fopen("abc.c","rw");
	int ca;
	while( fscanf(fa, "%s", buf) != EOF )
	{
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
				printf("Line: %d, Column: %d, ",line,ftell(fa)-last-strlen(keywords[i])+1);
				for(int j=0;j<strlen(keywords[i]);j++)
					printf("%c",keywords[i][j]-32);
				printf("\n");
				break;
			}
		}
		ca=getc(fa);
		last=ftell(fa);
		if(ca=='\n')
		{
			line+=1;
			col=1;;
		}
	}
}