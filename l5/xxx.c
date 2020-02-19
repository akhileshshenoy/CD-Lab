
#include "parser.h"

int main()
{
	FILE *fa;
	fa=fopen("program.c","rw");
	int row = 0,col = 0;
	enum TOKEN tk;
	P(&fa,&row,&col,tk);
	return 0;
}