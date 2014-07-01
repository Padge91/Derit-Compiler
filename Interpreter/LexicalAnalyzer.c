#include "LexicalAnalyzer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

const char* class_string = "class";
const char* main_string = "main";
const char* record_string = "record";
const char* int_string = "int";
const char* float_string = "float";
const char* char_string = "char";
const char* boolean_string = "boolean";
const char* if_string = "if";
const char* else_string = "else";
const char* and_string = "&&";
const char* or_string = "||";
const char* while_string = "while";
const char* for_string = "for";
const char* print_string = "print";
const char* read_string = "read";
const char* true_string = "true";
const char* false_string = "false";


char* lexeme = NULL;
struct token* tok = NULL;
struct token_list list;

//--------------------------------------------------------------------------------------------------

//creates and returns a pointer to the token list
struct token_list create_list(char* file_name){
	list.size = 0;
	list.first = NULL;
	list.last = NULL;
	int line_number = 0;


	FILE* file;
	char* line;
	int * bytes_read;
	
	//use file name to open file and read it
	
	if ((file = fopen(file_name, "r") == NULL)
	{
		printf("Error in accessing file");
		return NULL;		
	}

	while (getline(&line, bytes_read, file) != -1)
	{
		(*line_number)++;
		if (process_line(&list, line, &line_number)) 
		{
			printf("error returned in process_line method");
		}	
	}

	return list;
}

//----------------------------------------------------------------------------------------------

//processes line by line the file given
int process_line(struct token_list* l, char* line, int* line_num)
{
	
	int done = 0, index = 0, i = 0, string_length = 0;
	token_type type;	


	if ((l == NULL) || (line == NULL)) 
	{
		printf("either list or string is null");
		return 0;
	}


	string_length = (int)strlen(line);

	//make char array lower case
	for (i = 0; i < string_length; i++) 
	{

		if ((isalpha(line[i])) && (isupper(line[i])))
		{
			line[i] = (char)tolower(line[i]); 
		}
	}

	i = 0;
	//actual workhorse piece of the code
	while (!done)
	{
		if (index == strlen(line)) 
		{
			done = 1;
		}
		else 
		{

			if (isdigit(line[i])) 
			{
				i = index;

				while ((isdigit(line[i])) && (i < strlen(line)))
				{		
					i++;
				}

				if (line[i] == '.') 
				{
					i++;
					while ((isdigit(line[i])) && (i < strlen(line))) 
					{
						i++;
					} 

					lexeme = malloc(i - index + 1);
					
					strncpy(lexeme, line + index, i-index);
					type = FLOAT;
					index = i;
				}
				else 
				{
					lexeme = malloc( i - index + 1);
				
					strncpy(lexeme, line + index, i-index);
					type = INT; 
					index = i;
				}
			}
			else if (isalpha(line[i]))
			{
				i = index;
				char* string;
				
				while ((i < strlen(line)) && ((isalpha(line[i])) || (isdigit(line[i])))) 
				{
					i++;
				}
				
				//get the lexeme we are looking for
				lexeme = malloc(i - index + 1);
				strncpy(lexeme, line + index, i - index);

				if (strlen(lexeme) ==1) {
					type = CHAR;
				}				
				else 
				{
					if (!strcmp(lexeme, main_string)) {
						type = MAIN;
					}	
					else if (!strcmp(lexeme, class_string)){
						type = CLASS;
					}
					else if (!strcmp(lexeme, record_string)) {
						type = RECORD;
					}
					else if (!strcmp(lexeme, int_string)) {
						type = INT_DECLARE;
					}
					else if (!strcmp(lexeme, float_string)){
						type = FLOAT_DECLARE;
					}
					else if (!strcmp(lexeme, char_string)){
						type = CHAR_DECLARE;
					}
					else if (!strcmp(lexeme, boolean_string)){
						type = BOOLEAN_DECLARE;
					}
					else if (!strcmp(lexeme, if_string)) {
						type = IF;
					}
					else if (!strcmp(lexeme, else_string)) {
						type = ELSE;
					}
					else if (!strcmp(lexeme, and_string)) {
						type = AND;
					}
					else if (!strcmp(lexeme, or_string)) {
						type = OR;
					}
					else if (!strcmp(lexeme, while_string)) {
						type = WHILE;
					}
					else if (!strcmp(lexeme, for_string)) {
						type = FOR;
					}
					else if (!strcmp(lexeme, print_string)) {
						type = PRINT;
					}
					else if (!strcmp(lexeme, read_string)) {
						type = READ;
					}
					else if (!strcmp(lexeme, true_string)) {
						type = TRUE;
					}
					else if (!strcmp(lexeme, false_string)) {
						type = FALSE;
					}
					else {
						//either identifier or string
						type = IDENTIFIER_NAME;
					}
	
					index = i;
				}
			}
			else 
			{
				i = index;


				//not a digit or character - must be some other operator
				if (line[i] == '{') {
					type = LEFT_CURLY_BRACE;
				}
				else if (line[i] == '}') {
					type = RIGHT_CURLY_BRACE;
				}
				else if (line[i] == '(') {
					type = LEFT_PAREN;
				}
				else if (line[i] == ')') {
					type = RIGHT_PAREN;
				}	
				else if (line[i] == ',') {
					type = COMMA;
				} 
				else if (line[i] == ';') {
					type = SEMICOLON;
				}
				else if (line[i] == '.') {
					type = PERIOD;
				}
				else if (line[i] == '>') {
					if (line[i+1] == '=') {
						type = GREATER_THANEQUAL;
					}
					else {
						type = GREATER_THAN;
					}
				}
				else if (line[i] == '<') {
					if (line[i+1] == '=') {
						type = LESS_THANEQUAL;
					}
					else {
						type = LESS_THAN;
					}
				}
				else if (line[i] == '=') {
					if (line[i+1] == '=') {
						type = EQUAL;
					}
					else {
						type = ASSIGN;
					}
				}
				else if (line[i] == '!') {
					if (line[i] == '=') {
						type = NOT_EQUAL;
					}
					else {
						type = NOT;
					}			
				}
				else if (line[i] == '[') {
					type = LEFT_SQUARE;
				}
				else if (line[i] == ']') {
					type = RIGHT_SQUARE;
				}
				else if (line[i] == '+'){
					type = ADD;
				}
				else if (line[i] == '-') {
					type = SUB;
				}
				else if (line[i] == '*') {
					type = MULT;
				}
				else if (line[i] == '/') {
					type = DIV;
				}
				else if (line[i] == '%') {
					type = MODULO;
				}
				else if (line[i] == ' ') {
					i++;
					index = i;
					continue;
				}
				else if (line[i] == '"') {
					type = QUOTE;
				}
				else {
					lexeme = NULL;
					//error because token not found
				}

			

				if ((type == EQUAL) || (type == GREATER_THANEQUAL) || (type == LESS_THANEQUAL) || (type == NOT_EQUAL)){
					i = i + 2;
					lexeme = malloc(2);
					strncpy(lexeme, line + index, i - index);
				}
				else 
				{
					i++;
					lexeme = malloc(1);
					strncpy(lexeme, line + index, i - index);
				}

				index = i;
			}

			tok = malloc(sizeof(struct token));
			make_token(tok, type, lexeme, line_num);
			add_to_list(l, tok);
		}
	}

return 0;

}

//--------------------------------------------------------------------------------------------

//add a token to the list
void  add_to_list(struct token_list* l, struct token* t)
{
	//error when accessing next

	if (l -> size) {

		l -> last -> next = malloc(sizeof(struct token));
		l -> last -> next = t;
		l -> last = t;		
		

	}
	else {
		l -> first = malloc(sizeof(struct token));
		l -> last = malloc(sizeof(struct token));
		l->first = t;
		l->last = t;
	}
	
	l->size++;
}

//-------------------------------------------------------------------------------------------

//get the next token from the list
void get_next_token(struct token* next_tok, struct token_list* list)
{
	next_tok = list->first;
	list->first = list->first->next;
}

//--------------------------------------------------------------------------------------------

//look at the next token in the list, but don't remove it
struct token* look_at_next_token(struct token_list* list)
{
	return list->first;
}

//-------------------------------------------------------------------------------------------

//checks to see if list is empty
int is_empty(struct token_list* l) 
{
	if (l->size) return 0; else return 1;
}

//-------------------------------------------------------------------------------------------

void make_token(struct token* t, token_type type, char* lexeme, int line_num)
{
	t -> next = 0;
	t -> token = type;
	t -> lineNumber = line_num;
	t -> lexeme = lexeme;
}

//--------------------------------------------------------------------------------------------

void empty_list(struct token_list* l) 
{
	struct token* temp = l -> first;
	//free all the tokens and then free the list	

	while (temp != NULL)
	{
		l -> first = l -> first -> next;
		free (temp);
		temp = l -> first;
	}
	free(l);
}










