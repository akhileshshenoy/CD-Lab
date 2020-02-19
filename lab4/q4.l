%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int s = 0;
int p = 0;
%}

%%
"scanf" {s++;
		fprintf(yyout,"READ");}
"printf" {p++;
		fprintf(yyout,"WRITE");}

%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("q1.txt","r");
	yyout = fopen("q1o.txt","w");
	yylex();
	printf("%d scanf,%d printf.",s,p);
	return 0;
}


