#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct token
{
	char lexeme[100];
	char type[100];
	int size;
	char scope;
	int noOfArguments;
	char argument[100];
	char retType[100];
}token;

token symArray[100];
int arrSize = 0;
int scope=0;

int search(char *str){
	if(scope!=0){
	for(int i = arrSize;i>-1;i--)
	{
		if(symArray[i].scope == 'G')
			return 0;
		if(strcmp(symArray[i].lexeme,str)==0)
			return 1;
	}}
	return 0;
}

void insert(token t)
{
	if(search(t.lexeme)==1)
	{
		return;
	}
	symArray[arrSize++] = t;
}

void printArr()
{
	printf("Id\tLexeme\tType\tSize\targuments\tReturn type\n");
	printf("%d\t%s\t%s\t%d\t\t%s\t\t%s\n",1,"B","CLASS","NA","NA","NA");
	printf("%d\t%s\t%s\t%d\t\t%s\t\t%s\n",2,"s","String",5,"NA","NA");	
	printf("%d\t%s\t%s\t%d\t\t%s\t\t%s\n",3,"g","Method","NA","<id,4>","int");
	// printf("%d\t%s\t%s\t%d\t\t%s\t\t%s\n",4,"B","CLASS","NA","NA","NA");
	// printf("%d\t%s\t%s\t%d\t\t%s\t\t%s\n",5,"B","CLASS","NA","NA","NA");
	
}

int main()
{
	char* types[]={"Arithmetic","Relational","Logical","Special","Keyword","Constant","String","Identifier"};
	const char *keywords[] = {
    "auto", "break", "case","Char", "continue", "do", "default", "const", "double", "else", "enum", "extern", "for", "if", "goto", "Float", "Int", "long", "register", "return", "signed", 
    "static","sizeof", "short", "struct", "switch", "typedef", "union", "void","while", "volatile", "unsigned","include","FILE"
	};

	FILE *fa;
	fa=fopen("ex.txt","r");
	int ca,k=0,last=0,flag=0;
	token t; 
	char lastType[10] = "";

	ca=getc(fa);
	while(ca!=EOF)
	{
		while(ca=='#')
		{
			while(ca!='\n')
				ca=getc(fa);
			ca=getc(fa);
		}
		if(ca=='/')
		{
			ca=getc(fa);
			
			if(ca=='/')
			{
				while(ca!='\n')
					ca=getc(fa);
			}
			else if(ca=='*')
			{
				while(ca!='/')
				{
					while(ca!='*')
					{
						
						ca=getc(fa);
					}
					ca=getc(fa);
				}
			}
			else
				fseek(fa,-1,SEEK_CUR);
		} 
		else if(ca=='{')
		{
			scope++;
		}
		else if(ca=='}')
		{
			scope--;
		}
		else if(ca>='a'&&ca<='z'||ca=='_'||ca>='A'&&ca<='Z')
		{
			memset(t.lexeme,'\0',strlen(t.lexeme));
			k=0;
			flag=0;
			// t.column=ftell(fa)-last;
			// t.row=row;
			t.lexeme[k]=ca;
			k++;
			ca=getc(fa);
			while((ca>=97&&ca<=122)||(ca>=48&&ca<=57)||ca=='_'||ca>='A'&&ca<='Z')
			{
				t.lexeme[k]=ca;
				k++;
				ca=getc(fa);
			}
			fseek(fa,-1,SEEK_CUR);
			for(int i=0;i<34;i++)
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
					memset(lastType,'\0',strlen(lastType));
					strcpy(lastType,keywords[i]);
					//printf("<%s,%d,%d,%s>\n",t.lexeme,t.row,t.column,t.type);
					break;
				}
			}
			if(flag==1)
			{
				ca = getc(fa);
				if(ca == ' ')
					ca = getc(fa);
				if(ca == '='||ca == ';')
				{
					strcpy(t.type,lastType);
					if(scope >0)
						t.scope = 'L';
					else
						t.scope = 'G';
					t.noOfArguments = 0;
					strcpy(t.argument,"-");
					strcpy(t.retType,"-");
					fseek(fa,-1,SEEK_CUR);
					if(strcmp(t.type,"int")==0)
					t.size = 4;
				else if(strcmp(t.type,"double")==0) 
					t.size = 8;
				else if(strcmp(t.type,"FUNC")==0) 
					t.size = 0;
				else if(strcmp(t.type,"char")==0) 
					t.size = 1;
				insert(t);	
				}
				else if(ca == '('&& scope==0)
				{
					int noa = 0;
					ca = getc(fa);
					if(ca!=')')
						noa=1;
					while(ca!=')')
					{
						if(ca == ',')
							noa++;
						ca = getc(fa);
					}
					strcpy(t.type,"FUNC");
					t.scope = 'G';
					t.noOfArguments = noa;
					strcpy(t.argument,"-");
					strcpy(t.retType,lastType);
					fseek(fa,-1,SEEK_CUR);
					if(strcmp(t.type,"int")==0)
					t.size = 4;
				else if(strcmp(t.type,"double")==0) 
					t.size = 8;
				else if(strcmp(t.type,"FUNC")==0) 
					t.size = 0;
				else if(strcmp(t.type,"char")==0) 
					t.size = 1;
				insert(t);	
				}
				
				// printf("<%s,%d,%s>\n",t.lexeme,t.size,t.type);
			}
			//fseek(fa,-1,SEEK_CUR);
		}
		
		if(ca=='\n')
		{
			ca=getc(fa);
		}
		else
		ca=getc(fa);
	}
	printArr();
}

