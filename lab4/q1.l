%{
#include<stdio.h>
#include<stdlib.h>
int c = 0;
int vow = 0;
%}

%%
[aeiouAEIOU] {vow++;}
[^aeiouAEIOU] {c++;}
%%

int yywrap()
{
	return 1;
}

int main(int argc,char **argv)
{
	yyin=fopen("q1.txt","r");
	yylex();
	printf("%d vowels and %d cons.",vow,c);
	printf("aa");

	return 0;
}


