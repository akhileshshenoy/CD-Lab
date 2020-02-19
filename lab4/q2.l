%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int words = 0;
int chars = 0;
int line = 0;
int blank = 0;
%}

%%
[A-Za-z]+ {	words++;
			chars+=strlen(yytext);}
['\n'] {line++;}
[' '] {blank++;}
%%

int yywrap()
{
	return 1;
}

int main(int argc,char **argv)
{
	yyin=fopen("q1.txt","r");
	yylex();
	printf("%d words, %d chars, %d blanks and %d lines.",words,chars,blank,line+1);
	return 0;
}


