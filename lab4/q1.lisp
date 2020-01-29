%{
/* need this for the call to atof() below */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
int cons = 0;
int vow =  0;
%}

[aeiouAEIOU] {vow++;}
[^aeiouAEIOU] {cos++}


%%

main(int argc,char **argv)
{
	yylex();
	printf("%d vowels and %d cons.",vow,cons);
}


