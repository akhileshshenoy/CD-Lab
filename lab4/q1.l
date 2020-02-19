%{
#include<stdio.h>
#include<stdlib.h>
int c = 0;
int vow = 0;
%}

%%
[aeiouAEIOU] {vow++;}
[A-Za-z] {c++;}
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
	return 0;
}


