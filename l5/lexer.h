#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum TOKEN{	
	KEYWORD,
	ARITH_OPERATOR,
	RELATION_OPERATOR,
	LOGICAL_OPERATOR,
	ASSIGNMENT_OPERATOR,
	SPECIAL_SYMBOL,
	NUMBER,
	STRING_LITERAL,
	IDENTIFIER };

typedef struct {
	int row;
	int column;
	char lexeme[30];
	enum TOKEN token_type;
}Token;

typedef struct{
	long offset;	// FILE pointer
	int row;
	int column;
}Lexer_state;

void resetLexer(Lexer_state lex, FILE **file, int *row, int *column){

	fseek(*file,lex.offset,SEEK_SET);	// Reset file pointer
	*row = lex.row;
	*column = lex.column;
}

void saveState(Lexer_state *lex, FILE **file, int *row, int *column){

	(*lex).offset = ftell(*file);
	(*lex).row = *row;
	(*lex).column = *column;
}


int readc(FILE** file,int* row,int* column){

	int ch;
	if((ch=getc(*file))=='\n'){	(*row)++;	(*column) = 1;}
	else (*column)++;

	return ch;
}

void unreadc(FILE **file,int ch,int *row,int *column){

	if(ch == '\n')	(*row)--;	// column not reset
	else 		(*column)--;
	ungetc(ch,*file);
}

int isSpecialSymbol(char ch){

	return strchr("(){}$@~[];,",ch) != NULL;
}

char* keywords[] = {"int","char","double","float","long","enum","if","else","while","do","return","break","for","continue","const",
	"continue","extern"};		// datatypes first

int datatype_size[] = {4, 1, 8, 4, 8};

int isDataType(char* word){

	int size = 5;	// Datatypes in keywords array

	for(int i=0;i<size;i++)
		if(!strcmp(word,keywords[i]))	return 1;

	return 0;
}

int getSize(char* dType){

	int size = 5;
	for(int i=0;i<size;i++)		
		if(!strcmp(dType,keywords[i]))	return datatype_size[i] ;

	return 0;
}

int isKeyword(char* word){

	int size = 17; // current size of dictionary

	for(int i=0;i<size;i++)
		if(!strcmp(word,keywords[i]))	return 1;

	return 0;
}

Token createToken(int row,int column,char lexeme[30],enum TOKEN type){
	Token token;
	
	token.row = row;
	token.column = column;
	strcpy(token.lexeme,lexeme);
	token.token_type = type;

	return token;
}

Token getNextToken(FILE** file,int *row, int *column,enum TOKEN state){

	Token token;

	int ch = readc(file,row,column);

	if(ch == EOF){ 		// When the file ends with white spaces.
		token.row = -1;
		token.column = -1;
		return token;
	}

	if(ch == '#'){
		while(ch!='\n')	ch = readc(file,row,column);
		return getNextToken(file,row,column,state);
	}
	else if(isspace(ch)){
		return getNextToken(file,row,column,state);
	}
	else if(isSpecialSymbol(ch)){

		token.row =*row;
		token.column = *column;
		token.token_type = SPECIAL_SYMBOL;
		token.lexeme[0] = ch;
		token.lexeme[1] = '\0';

		return token;
	}
	else if(ch == '/'){

		ch = readc(file,row,column);

		if(ch == '/'){
			while(ch!='\n') ch = readc(file,row,column);
			return getNextToken(file,row,column,state);
		}
		else if(ch == '*'){

			while(1){
				while(ch!='*') ch = readc(file,row,column);
				if((ch=readc(file,row,column))=='/') return getNextToken(file,row,column,state);		 
			}
		}
		else if(state == NUMBER || state == IDENTIFIER){

			token.row =*row;
			token.column = *column;
			token.token_type = ARITH_OPERATOR;
			strcpy(token.lexeme,"/");

			unreadc(file,ch,row,column);

			return token;
		}
		else	unreadc(file,ch,row,column);		
	}
	else if(state == NUMBER || state == IDENTIFIER || state == SPECIAL_SYMBOL || state == STRING_LITERAL){

		token.row = *row;
		token.column = *column;

		int next_char = readc(file,row,column);
		unreadc(file,next_char,row,column);

		if(ch == '=' && (isalnum(next_char) || next_char ==' ' || next_char == '(')){

			token.token_type = ASSIGNMENT_OPERATOR;
			strcpy(token.lexeme,"=");

			return token;

		}
		else if( ch=='<' || ch=='>' || ( ( ch=='=' || ch=='!') && next_char=='=')){

			token.lexeme[0] = ch;
			token.lexeme[1] = '\0';
			token.token_type = RELATION_OPERATOR;

			if(next_char == '='){			
				token.lexeme[1] = '=';
				token.lexeme[2] = '\0';
				readc(file,row,column); 
			}	

			return token;

		}
		else if(((ch=='&' || ch=='|') && ch==next_char ) || ( ch=='!' && ( isalnum(next_char) || ch=='_' || isspace(ch)) )){
			
			token.lexeme[0] = ch;
			token.lexeme[1] = '\0';
			token.token_type = LOGICAL_OPERATOR;

			if(next_char == ch){
				token.lexeme[1] = ch;
				token.lexeme[2] = '\0';
				readc(file,row,column);
			}

			return token;
			
		}
		else if( ch=='+' || ch=='-' || ch=='*' || ch == '%'){

			token.lexeme[0] = ch;
			token.lexeme[1] = '\0';
			token.token_type = ARITH_OPERATOR;

			if(next_char == '=' || ( ((ch=='+')||(ch=='-')) && next_char==ch)){
				token.lexeme[1] = next_char;
				token.lexeme[2] = '\0';
				readc(file,row,column);
			}

			return token;
		}
	}
	else if(ch == '\''){

		ch = readc(file,row,column);
		
		token.row = *row;
		token.column = *column;
		token.lexeme[0] = ch;
		token.lexeme[1] = '\0';
	       	token.token_type = NUMBER;

		readc(file,row,column); // Consume the last quote

		return token;
	}

	char word[20];
	int index = 0;

	if(ch == '"'){
		while((ch=readc(file,row,column))!='"') word[index++] = ch;
		word[index] = '\0';

		token.row = *row;
		token.column = *column;
		token.token_type = STRING_LITERAL;
		strcpy(token.lexeme,word);

		return token;
	}

	if(isdigit(ch)){
		word[index++] = ch;
		while(isdigit(ch=readc(file,row,column)) || ch=='.') word[index++] = ch;
		word[index] ='\0';
		unreadc(file,ch,row,column);

		if(isalpha(ch) || ch=='_')	 printf("\nINVALID TOKEN ENCOUNTERED.\n");	

		token.row = *row;
		token.column = *column;
		token.token_type = NUMBER;
		strcpy(token.lexeme,word);

		return token;
	}

	word[index++] = ch;
	while(isalnum(ch=readc(file,row,column)) || ch=='_')	word[index++] = ch;
	word[index] = '\0';
	unreadc(file,ch,row,column);

	token.row = *row;
	token.column = *column;
	strcpy(token.lexeme,word);

	if(isKeyword(word))	token.token_type = KEYWORD;
	else 			token.token_type = IDENTIFIER;

	return token;

}

char *string_tokens[] = { 
	"KEYWORD",
	"ARITH_OPERATOR",
	"RELATION_OPERATOR",
	"LOGICAL_OPERATOR",
	"ASSIGNMENT_OPERATOR",
	"SPECIAL_SYMBOL",
	"NUMBER",
	"STRING_LITERAL",
	"IDENTIFIER" };

void printToken(Token T){
	printf("\n< %s, %d, %d, %s>\n",T.lexeme,T.row,T.column,string_tokens[T.token_type]);
}


