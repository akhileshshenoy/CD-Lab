%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int pInt = 0;
int pFloat = 0;
int nInt = 0;
int nFloat = 0;
%}

%%
"-"+[0-9]+^. {nInt++;}
"+"?[0-9]+ {pInt++;}
"+"?[0-9]+"."[0-9]+ {pFloat++;}
"-"+[0-9]+"."[0-9]+ {nFloat++;}
%%

int yywrap()
{
	return 1;
}

int main(int argc,char **argv)
{
	yyin=fopen("q1.txt","r");
	yylex();
	printf("%d +ve integers, %d -ve integers, %d +ve floats and %d -ve floats.",pInt,nInt,pFloat,nFloat);
	return 0;
}


