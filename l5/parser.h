#include "lexer.h"

/* Grammar : 
 * P -> main() { STMT_LIST }
 *
 * STMT_LIST -> STMT STMT_LIST | ϵ
 *
 * STMT -> ASSIGN_STMT; | DCL; | LOOPING_STMT | DECISION_STMT
 *
 * LOOP_STMT -> while(EXPR) { STMT_LIST } | for(ASSIGN_STMT;EXPR;ASSIGN_STMT) { STMT_LIST }
 *
 * DECISION_STMT -> if(EXPR) { STMT_LIST } DECISION_LADDER
 *
 * DECISION_LADDER -> else DECISION_STMT | else { STMT_LIST } | ϵ
 *
 * DCL -> DATA_TYPE ID_LIST 
 *
 * ID_LIST -> id | id,ID_LIST | id[NUMBER],ID_LIST | id[NUMBER]
 *
 * ASSIGN_STMT -> id = EXPR | id	// Not an assignment, but a statement nonetheless
 *
 * EXPR -> E REL_EXPR
 *
 * REL_EXPR -> REL E | ϵ
 *
 * E -> T E_prime
 *
 * E_prime -> AS T E_prime | ϵ
 *
 * T -> F T_prime
 * 
 * T_prime -> MDM F T_prime | ϵ
 *
 * F -> (E) | id | NUMBER
 * 
 * MDM -> * | / | %
 *
 * REL -> == | != | <= | >=
 *
 * AS -> + | -
 *
 */

#define PARAM FILE **file, int *row, int *column, enum TOKEN state

void P(PARAM);
void STMT(PARAM);
void STMT_LIST(PARAM);
void LOOP_STMT(PARAM);
void DECISION_STMT(PARAM);
void DECISION_LADDER(PARAM);
void DCL(PARAM);
void ID_LIST(PARAM);
void ASSIGN_STMT(PARAM);
void EXPR(PARAM);
void REL_EXPR(PARAM);
void E(PARAM);
void E_prime(PARAM);
void T(PARAM);
void T_prime(PARAM);
void F(PARAM);
void MDM(PARAM);
void REL(PARAM);
void AS(PARAM);

// typedef struct{
// 	long offset;	// FILE pointer
// 	int row;
// 	int column;
// }Lexer_state;

// void resetLexer(Lexer_state lex, FILE **file, int *row, int *column){

// 	fseek(*file,lex.offset,SEEK_SET);	// Reset file pointer
// 	*row = lex.row;
// 	*column = lex.column;
// }

// void saveState(Lexer_state *lex, FILE **file, int *row, int *column){

// 	(*lex).offset = ftell(*file);
// 	(*lex).row = *row;
// 	(*lex).column = *column;
// }

void error(char *string, int row, int column){
	printf("%s : %d,%d\n",string,row,column);
	exit(0);
}

void P(PARAM){

	Token token = getNextToken(file,row,column,state);
	while(strcmp(token.lexeme,"main"))
	{
		token = getNextToken(file,row,column,state);
	}

	if(!strcmp(token.lexeme,"main")){

		char *rule[] = {"(",")","{"}; 
		int rule_length = 3;

		for(int i=0;i < rule_length;i++){

			token = getNextToken(file,row,column,state);

			if(strcmp(token.lexeme,rule[i])){

				char err[20];
				sprintf(err,"%s %s","Expected",rule[i]);
				error(err,token.row,token.column);

			}
		}

		STMT_LIST(file,row,column,state);

		token = getNextToken(file,row,column,state);

		if(strcmp(token.lexeme,"}"))	error("Expected }",token.row,token.column);

		printf("Parsed successfully.");

	}
	else error("Expected main",token.row,token.column);
}

void STMT_LIST(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	STMT(file,row,column,state);

	if(org_lex.offset == ftell(*file))	return; 	// Could not match STMT

	STMT_LIST(file,row,column,state);
}

void STMT(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	ASSIGN_STMT(file,row,column,state);

	if(org_lex.offset != ftell(*file)){

		Token token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,";"))  error("Expected ;",*row,*column);

		return;	
	}

	saveState(&org_lex,file,row,column);

	DCL(file,row,column,state);

	if(org_lex.offset != ftell(*file)){

		Token token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,";"))  error("Expected ;",token.row,token.column);

		return;
	}

	saveState(&org_lex,file,row,column);

	LOOP_STMT(file,row,column,state);

	if(org_lex.offset != ftell(*file))	return;

	DECISION_STMT(file,row,column,state);

}

//TODO: Add for(;;)
void LOOP_STMT(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	Token token = getNextToken(file,row,column,state);  

	if(!strcmp(token.lexeme,"while")){

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"(")) 	error("Expected (",token.row,token.column);

			EXPR(file,row,column,state);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,")")) 	error("Expected )",token.row,token.column);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"{")) 	error("Expected {",token.row,token.column);

			STMT_LIST(file,row,column,state);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"}")) 	error("Expected }",token.row,token.column);

			return;

	}

	if(!strcmp(token.lexeme,"for")){

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,"(")) 	error("Expected (",token.row,token.column);

		ASSIGN_STMT(file,row,column,state);

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,";")) 	error("Expected ;",token.row,token.column);

		EXPR(file,row,column,state);

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,";")) 	error("Expected ;",token.row,token.column);

		ASSIGN_STMT(file,row,column,state);

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,")")) 	error("Expected )",token.row,token.column);

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,"{")) 	error("Expected {",token.row,token.column);

		STMT_LIST(file,row,column,state);

		token = getNextToken(file,row,column,state);
		if(strcmp(token.lexeme,"}")) 	error("Expected }",token.row,token.column);

		return;
	}

	resetLexer(org_lex,file,row,column);
}

void DECISION_STMT(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	Token token = getNextToken(file,row,column,state);  

	if(!strcmp(token.lexeme,"if")){

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"(")) 	error("Expected (",token.row,token.column);

			EXPR(file,row,column,state);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,")")) 	error("Expected )",token.row,token.column);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"{")) 	error("Expected {",token.row,token.column);

			STMT_LIST(file,row,column,state);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"}")) 	error("Expected }",token.row,token.column);

			DECISION_LADDER(file,row,column,state);

			return;

	}

	resetLexer(org_lex,file,row,column);	
}

void DECISION_LADDER(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};
	
	Token token = getNextToken(file,row,column,state);

	if(!strcmp(token.lexeme,"else")){

		saveState(&org_lex,file,row,column);

		DECISION_STMT(file,row,column,state);

		if(org_lex.offset == ftell(*file)){
	
			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"{")) 	error("Expected {",token.row,token.column);

			STMT_LIST(file,row,column,state);

			token = getNextToken(file,row,column,state);
			if(strcmp(token.lexeme,"}")) 	error("Expected }",token.row,token.column);

		}
	}
	else resetLexer(org_lex,file,row,column);
}

//TODO: Add support for initialization
void DCL(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	Token token = getNextToken(file,row,column,state);

	if(isDataType(token.lexeme))	ID_LIST(file,row,column,state);
	else 				resetLexer(org_lex,file,row,column);

}

void ID_LIST(PARAM){


	Token token = getNextToken(file,row,column,state);
	Lexer_state org_lex = {ftell(*file),*row,*column};

	if(token.token_type != IDENTIFIER) error("Expected identifier",token.row,token.column);

	token = getNextToken(file,row,column,state);

	//Check for arrays 

	if(!strcmp(token.lexeme,"[")){

		token = getNextToken(file,row,column,state);

		if(token.token_type == NUMBER){

			// Check if number if integer
			int lexeme_length = strlen(token.lexeme);
			int isFloat = 0;

			for(int i=0;i<lexeme_length;i++)	// . | e | E means float
				if(token.lexeme[i]=='.' || token.lexeme[i]=='e' || token.lexeme[i]=='E')	isFloat = 1;

			if(isFloat)	error("Array size cannot be float.",token.row,token.column);

			token = getNextToken(file,row,column,state);	// Accept id[]
		}

		if(strcmp(token.lexeme,"]"))	error("Expected ]",token.row,token.column);	

		saveState(&org_lex,file,row,column);

		token = getNextToken(file,row,column,state);
	}

	if(!strcmp(token.lexeme,","))	ID_LIST(file,row,column,state);
	else				resetLexer(org_lex,file,row,column);

}

void ASSIGN_STMT(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};
	Token token = getNextToken(file,row,column,state);

	if(token.token_type == IDENTIFIER){

		saveState(&org_lex,file,row,column);
		token = getNextToken(file,row,column,state);

		if(!strcmp(token.lexeme,";")){			// x; is a valid statement
			
			resetLexer(org_lex,file,row,column);	
			return; 
		}
		
		if(strcmp(token.lexeme,"="))	error("Expected = ",token.row,token.column);

		EXPR(file,row,column,state);

	}
	else 	resetLexer(org_lex,file,row,column);
}

void EXPR(PARAM){

	E(file,row,column,state);
	REL_EXPR(file,row,column,state);
}

void REL_EXPR(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	REL(file,row,column,state);

	if(org_lex.offset == ftell(*file))	return;	// Not relational expression

	E(file,row,column,state);
}

void REL(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};
	Token token = getNextToken(file,row,column,state);

	if(token.token_type != RELATION_OPERATOR)	resetLexer(org_lex,file,row,column);
}

void E(PARAM){

	T(file,row,column,state);
	E_prime(file,row,column,state);

}

void E_prime(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	AS(file,row,column,state);

	if(org_lex.offset == ftell(*file))	return;

	T(file,row,column,state);
	E_prime(file,row,column,state);
}

void T(PARAM){

	F(file,row,column,state);
	T_prime(file,row,column,state);
}

void T_prime(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	MDM(file,row,column,state);

	if(org_lex.offset == ftell(*file))	return;

	F(file,row,column,state);
	T_prime(file,row,column,state);
}

//TODO: Add support for short hand and increment/decrement
void MDM(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};

	Token token = getNextToken(file,row,column,state);

	if(token.token_type == ARITH_OPERATOR){

		if(token.lexeme[0] == '+' || token.lexeme[0] == '-')	resetLexer(org_lex,file,row,column);

	}
	else resetLexer(org_lex,file,row,column);
}

void F(PARAM){

	Token token = getNextToken(file,row,column,state);

	if(!strcmp(token.lexeme,"(")){

		E(file,row,column,state);
		token = getNextToken(file,row,column,state);

		if(strcmp(token.lexeme,")"))	error("Expected )",token.row,token.column);
		return;
	}

	if(token.token_type == IDENTIFIER)	return;
	if(token.token_type == NUMBER)		return;

	error("Invalid expression",token.row,token.column);
}

void AS(PARAM){

	Lexer_state org_lex = {ftell(*file),*row,*column};
	Token token = getNextToken(file,row,column,state);

	if(token.lexeme[0] == '+' || token.lexeme[1] =='-')	return;
	resetLexer(org_lex,file,row,column);
}
