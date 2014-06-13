#include "LexicalAnalyzer.h"
#include <stdio.h>

char* string = "main { } d3 record ( ) , 9 12.8 char \" int c float string boolean true false ; if else && || . > < >= <= == != = ! while : print read [ ] + - * / % \0";

int main() {

	printf("start\n");
		
	//error somewhere in create_list
	struct token_list list = create_list(string);

	printf("got the list\n");
	//print out every token type in the list

	printf("%s\n", list.first -> lexeme);

	return 0;
}
