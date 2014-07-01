#include "LexicalAnalyzer.h"
#include <stdio.h>
#include "Parser.h"

char* string = "main { } d3 record ( ) , 9 12.8 char \" int c float string boolean true false ; if else && || . > < >= <= == != = ! while : print read [ ] + - * / % \0";

int main() {

	printf("start\n");
		
	//create_list
	struct token_list list = create_list(string);

	//create parser
	struct class_nonterm class = get_class(&list);

	printf("end");
	return 0;
}
