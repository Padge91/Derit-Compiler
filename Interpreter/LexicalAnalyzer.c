#include "LexicalAnalyzer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

const char* main_string = "main";
const char* record_string = "record";
const char* int_string = "int";
const char* float_string = "float";
const char* char_string = "char";
const char* str_string = "string";
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
struct token_list create_list(char* s){
	list.size = 0;
	list.first = NULL;
	list.last = NULL;
	
	//break file down to one line, and then send it into process_line method

	printf("in create_list call\n");
	if (process_line(&list, s)) 
	{
		printf("error returned in process_line method");
	}	

	return list;
}

//----------------------------------------------------------------------------------------------

//processes line by line the file given
int process_line(struct token_list* l, char* line)
{
	printf("starting process_line call\n");
	printf("String: %s\n", line);
	
	int done = 0, index = 0, i = 0, string_length = 0;
	token_type type;	

	printf("starting process_line 2\n");	

	if ((l == NULL) || (line == NULL)) 
	{
		printf("either list or string is null");
		return 0;
	}

	printf("list and string are not null\n");

	//error in next line somewhere

	printf("string length: %u\n", (unsigned)strlen(line));
	string_length = (int)strlen(line);
	printf("string_length is assigned as %d\n", string_length);

	//make char array lower case
	for (i = 0; i < string_length; i++) 
	{
		printf("making lowercase loop: %d\n", i);		

		if ((isalpha(line[i])) && (isupper(line[i])))
		{
			line[i] = (char)tolower(line[i]); 
		}
	}

	printf("starting workhorse code\n");
	i = 0;
	//actual workhorse piece of the code
	while (!done)
	{
		
		if (index == strlen(line)) 
		{
			printf("finished\n");
			done = 1;
		}
		else 
		{
			printf("is not done\n");

			if (isdigit(line[i])) 
			{
				printf("if it is a digit\n");
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
				printf("if it is a character\n");
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
					else if (!strcmp(lexeme, str_string)){
						type = STRING_DECLARE;
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

				printf("if it is a grammar thing\n");

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
					printf("found whitespace\n");
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
			make_token(tok, type, lexeme, 1);
			printf("right before add to list call\n");
			printf("token address: %p\n", tok);
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

	printf("started adding to list. size: %d\n", l -> size);	
	if (l -> size) {

		printf("because list isnt empty:1\n");
		l -> last -> next = malloc(sizeof(struct token));
		l -> last -> next = t;
		l -> last = t;		
		

	}
	else {
		printf("because list is empty\n");
		l -> first = malloc(sizeof(struct token));
		l -> last = malloc(sizeof(struct token));
		l->first = t;
		l->last = t;
	}
	
	l->size++;
	printf("actually add to list\n");
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
	printf("token address: %p\n", t);
	t -> next = 0;
	t -> token = type;
	t -> lineNumber = line_num;
	t -> lexeme = lexeme;
	printf("actually made token: lexeme: %s\n", t -> lexeme);
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










