%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

%}

%%
[^.^"and"^"but]+"."  {printf("%s is compound.\n",yytext);}
[^.]+"." {printf("%s is simple.\n",yytext);}
%%

int yywrap()
{
	return 1;
}

int main()
{
	yyin=fopen("q1.txt","r");
	yylex();

	return 0;
}


