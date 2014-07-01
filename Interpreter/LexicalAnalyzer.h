#ifndef _LEXICAL_H
#define _LEXICAL_H

//enumerated types to represent different token types
typedef enum {
	CLASS, MAIN, LEFT_CURLY_BRACE, RIGHT_CURLY_BRACE, IDENTIFIER_NAME, RECORD,
	LEFT_PAREN, RIGHT_PAREN, COMMA, INT, INT_DECLARE, FLOAT, FLOAT_DECLARE, 
	CHAR, CHAR_DECLARE, STRING, STRING_DECLARE, BOOLEAN, BOOLEAN_DECLARE,
	SEMICOLON, IF, ELSE, AND, OR, PERIOD, GREATER_THAN, LESS_THAN, 
	LESS_THANEQUAL, GREATER_THANEQUAL, EQUAL, NOT_EQUAL, NOT, WHILE, FOR,
	COLON, PRINT, READ, ASSIGN, LEFT_SQUARE, RIGHT_SQUARE, ADD, SUB, MULT,
	DIV, MODULO, TRUE, FALSE, QUOTE

}token_type;

//token stuct to hold the token type, pointer to next token, a char* to the actual lexeme, and the line number
struct token {
	token_type token;
	struct token* next;
	char* lexeme;
	int lineNumber;
};

//list of tokens, with pointers to first and last elements, as well as the size
struct token_list {
	struct token* first;
	struct token* last;
	int size;
};

//creates and returns a pointer to the token list
struct token_list create_list(char* s);

//processes line by line the file given
int process_line(struct token_list* l, char* this_line);

//add a token to the list
void add_to_list(struct token_list* l, struct token* t);

//get the next token from the list
void get_next_token(struct token* next_tok, struct token_list* list);

//look at the next token in the list, but don'tremove it 
struct token* look_at_next_token(struct token_list* list);

//returns if the token list is empty or not
int is_empty(struct token_list* l);

//call this method to empty the list
void empty_list(struct token_list* l);

//makes a new token
void make_token(struct token* t, token_type type, char* lexeme, int line_num);

#endif
