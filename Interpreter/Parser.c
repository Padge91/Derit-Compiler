#include "Parser.h"
#include "LexicalAnalyzer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



//----------------------------------------------------------------------------------------

//method to expand class nonterminal
struct class_nonterm get_class(struct token_list* l) 
{
	struct token tok;
	struct class_nonterm class;
	printf("class nonterminal start");
	
	get_next_token(&tok, l);

	if (tok.token != CLASS) 
	{
		printf("Error, expected token: MAIN");
	}
	
	class.n = get_name(l);

	get_next_token(&tok, l);
	
	if (tok.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}

	class.al = *get_action_list(l);

	get_next_token(&tok, l);	

	if (tok.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}

	printf("class nonterminal end");
	return class;
	
}


//----------------------------------------------------------------------------------------


//method to expand name nonterminal
struct name_nonterm get_name(struct token_list* l)
{
	struct token tok;
	struct name_nonterm name;
	printf("name nonterminal start");
	
	get_next_token(&tok, l);
	
	if ((tok.token == IDENTIFIER_NAME) || (tok.token == MAIN))
	{
		name.identifier = tok.lexeme;
	}
	else 
	{	
		printf("Error, expected token: IDENTIFIER_NAME");
	}
	printf("name nonterminal end");
	return name;
}


//----------------------------------------------------------------------------------------

//method to expand the action list nonterminal
struct action_list_nonterm* get_action_list(struct token_list* l)
{
	struct token* tok;
	struct action_list_nonterm* list;
	
	printf("action list nonterminal start");
	list -> a = get_action(l);

	tok = look_at_next_token(l);

	if ((tok -> token == RECORD) || (tok -> token == INT) || (tok -> token == FLOAT) || (tok -> token == CHAR) || (tok -> token ==  STRING) || (tok -> token == BOOLEAN))
	{
		list -> al = get_action_list(l);
	}
	else
	{
		list -> al = NULL;
	}

	printf("action list nonterminal end");
	return list;

}

//----------------------------------------------------------------------------------------

//method to expand action nonterminal
struct action_nonterm get_action(struct token_list* l)
{
	struct token* tok;
	struct action_nonterm action;

	printf("acton nonterminal start");
	tok = look_at_next_token(l);

	if (tok -> token == RECORD)
	{
		action.rl = *get_record_list(l);
	}
	else if ((tok -> token == INT) || (tok -> token == FLOAT) || (tok -> token == CHAR) || (tok -> token == STRING) || (tok -> token == BOOLEAN))
	{
		action.ml = *get_method_list(l);	
	}
	else 
	{
		printf("Error, expected token: INT, FLOAT, CHAR, STRING, BOOLEAN, or RECORD");
	}

	printf("action nonterminal end");
	return action;

}

//----------------------------------------------------------------------------------------

//method to expand record list nonterminal
struct record_list_nonterm* get_record_list(struct token_list* l)
{
	struct record_list_nonterm* record_list;
	struct token* tok;
	struct token t;
	
	printf("record list nonterminal start");
	record_list -> r = get_record(l);

	tok = look_at_next_token(l);	

	if (tok -> token == RECORD) 
	{
		record_list -> rl = get_record_list(l);
	}
	else 
	{
		record_list -> rl = NULL;
	}

	printf("record list nonterminal end");
	return record_list;
}

//----------------------------------------------------------------------------------------

//method to expand record nonterminal
struct record_nonterm get_record(struct token_list* l) 
{
	struct record_nonterm record;
	struct token t;

	printf("record nonterminal start");
	get_next_token(&t, l);

	if (t.token != RECORD)
	{
		printf("Error, expected token: RECORD");
	}

	record.n = get_name(l);

	get_next_token(&t, l);

	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}

	record.a = get_action_list(l);

	get_next_token(&t, l);

	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}

	printf("record nonterminal end");
	return record;
}


//----------------------------------------------------------------------------------------

//method to get method list nonterminal
struct method_list_nonterm* get_method_list(struct token_list* l)
{
	struct method_list_nonterm* method_list;
	struct token* t;	

	printf("method list nonterminal start");
	method_list -> m = get_method(l);

	t = look_at_next_token(l);

	if ((t -> token  == INT) || (t -> token == FLOAT) || (t -> token == CHAR) || (t -> token == STRING) || (t -> token ==  BOOLEAN))
	{
		method_list -> ml = get_method_list(l);
	}
	
	printf("method list nonterminal end");
	return method_list;

}


//----------------------------------------------------------------------------------------

//method to get method nonterminal
struct method_nonterm* get_method(struct token_list* l)
{
	struct method_nonterm* method;
	struct token t;
	printf("method nonterminal start");	

	method -> t = get_type(l);
	method -> n = get_name(l);
	
	get_next_token(&t, l);
	if (t.token != LEFT_PAREN)
	{
		printf("Error, expected token: LEFT_PAREN");
	}

	method -> fpl = *get_formal_parameter_list(l);
	
	get_next_token(&t, l);
	if (t.token != RIGHT_PAREN)
	{
		printf("Error, expected token: RIGHT_PAREN");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}

	method -> s = get_stmt_list(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}
	
	printf("method nonterminal end");
	return method;
}


//----------------------------------------------------------------------------------------

//get formal paramater list nonterminal
struct formal_parameter_l_nonterm* get_formal_parameter_list(struct token_list* l)
{
	struct formal_parameter_l_nonterm* plist;
	struct token t;
	struct token* t2;
	
	printf("formal paramater list nonterminal start");
	plist -> f1 = get_formal_parameter(l);

	t2 = look_at_next_token(l);
	if (t2 -> token == COMMA)
	{

		get_next_token(&t, l);
		t2 = look_at_next_token(l);	
	
		if ((t2 -> token == INT) || (t2 -> token == FLOAT) || (t2 -> token == CHAR) || (t2 -> token == STRING) || (t2 -> token == BOOLEAN))
		{
			plist -> f2 = get_formal_parameter_list(l);
		}
	}

	printf("formal parameter list nonterminal end");	
	return plist;
}


//----------------------------------------------------------------------------------------

//get formal parameter nonterminal
struct formal_parameter_nonterm get_formal_parameter(struct token_list* l)
{
	struct formal_parameter_nonterm fp;
	
	printf("formal paramater nonterminal start");
	fp.t = get_type(l);
	fp.n = get_name(l);

	printf("formal paramater nonterminal end");
	return fp;
}


//----------------------------------------------------------------------------------------

//get type nonterminal
struct type_nonterm get_type(struct token_list* l)
{
	struct type_nonterm type;
	token_type t;
	struct token to;
	printf("type nonterminal start");

	get_next_token(&to, l);
		
	t = to.token;

	printf("type nonterminal end");
	return type;
}


//----------------------------------------------------------------------------------------

//get stmt list nonterminal
struct stmt_list_nonterm* get_stmt_list(struct token_list* l)
{
	struct stmt_list_nonterm* list;
	struct token t;
	struct token* t2;

	printf("stmt list nonterminal start");
	list -> s1 = get_stmt(l);

	get_next_token(&t, l);

	if (t.token != SEMICOLON) 
	{
		printf("Error, expected token: SEMICOLON");
	}

	t2 = look_at_next_token(l);

	if ((t2 -> token == IF) || (t2 -> token == WHILE) || (t2 -> token == FOR) || (t2 -> token == IDENTIFIER_NAME) || (t2 -> token == PRINT) 
	|| (t2 -> token == READ) || (t2 -> token == LEFT_PAREN) || (t2 -> token == INT) || (t2 -> token == FLOAT) || (t2 -> token == CHAR)
	|| (t2 -> token == STRING) || (t2 -> token == BOOLEAN))
	{
		list -> s2 = get_stmt_list(l);
	}
	else
	{
		list -> s2 = NULL;
	}
	
	printf("stmt list nonterminal end");
	return list;
}

//----------------------------------------------------------------------------------------


//method to expand statement nonterminal
struct stmt_nonterm get_stmt(struct token_list* l)
{
	struct stmt_nonterm stmt;
	struct token* t;

	printf("stmt nonterminal start");
	t = look_at_next_token(l);

	if (t -> token == IF)
	{
		stmt.if2 = get_if_stmt(l);
	}
	else if (t -> token == WHILE)
	{
		stmt.w = get_while_stmt(l);
	}
	else if (t -> token == FOR)
	{
		stmt.f = get_for_stmt(l);
	}
	else if (t -> token == IDENTIFIER_NAME)
	{
		//is a method stmt or assign stm
		if ((t -> next -> token == ASSIGN) || (t -> next -> token == LEFT_SQUARE) || (t -> next -> next -> next -> token == ASSIGN))
		{
			stmt.a = get_assign_stmt(l);
		}
		else if ((t -> next -> token == LEFT_PAREN) || (t -> next -> next -> next -> token == LEFT_PAREN))
		{
			stmt.me = *get_method_stmt(l);
		}
		else printf("Error, unexpected token");
	}
	else if (t -> token == PRINT)
	{
		stmt.p = get_print_stmt(l);
	}
	else if (t -> token ==  READ)
	{	
		stmt.r = get_read_stmt(l);
	}
	else if (t -> token == LEFT_PAREN)
	{
		stmt.m = get_math_stmt(l);
	}
	else if ((t -> token == INT) || (t -> token == FLOAT) || (t -> token == CHAR) || (t -> token == STRING) || (t -> token == BOOLEAN))
	{
		stmt.v = get_var_declare(l);
	}
	else 
	{
		printf("Error, expected token: IF, WHILE, FOR, IDENTIFIER, PRINT, READ, or LEFT_PAREN");
	}

	printf("stmt nonterminal end");
	return stmt;
}


//----------------------------------------------------------------------------------------

//method to extend if statement
struct if_stmt_nonterm get_if_stmt(struct token_list* l)
{
	struct if_stmt_nonterm ifer;
	struct token t;

	printf("if stmt nonterminal start");
	//ignoring this token because it is IF	
	get_next_token(&t, l);

	get_next_token(&t, l);
	if (t.token != LEFT_PAREN)
	{
		printf("Error, expected token: LEFT_PAREN");
	}

	ifer.e = get_expression(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_PAREN)
	{
		printf("Error, expected token: RIGHT_PAREN");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}

	ifer.s1 = get_stmt_list(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}

	get_next_token(&t, l);
	if (t.token != ELSE)
	{
		printf("Error, expected token: ELSE");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}
	
	ifer.s2 = get_stmt_list(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}

	printf("if stmt nonterminal start");
	return ifer;
}


//----------------------------------------------------------------------------------------

//method to expand expression nonterminal
struct expression_nonterm* get_expression(struct token_list* l)
{
	struct expression_nonterm* exp;
	struct token t;
	struct token* t2;
	exp -> not = 0;

	printf("expression nonterminal start");
	t2 = look_at_next_token(l);
	if (t2 -> token == NOT)
	{
		get_next_token(&t, l);
		exp -> not = 1;
		exp -> e1 = get_expression(l);
	}
	else if ((t2 -> token == TRUE) || (t2 -> token == FALSE))
	{
		exp -> b = get_boolean(l);
	}
	else if (t2 -> token == LEFT_PAREN)
	{
		get_next_token(&t, l);

		if ((t.next -> token == IDENTIFIER_NAME) || (t.next -> token == INT) || (t.next -> token == FLOAT) || (t.next -> token == LEFT_PAREN))
		{
			exp -> r = get_relate_op(l);
		}
		else if ((t.next -> next -> token == LEFT_PAREN) || (t.next -> next -> token == TRUE) || (t.next -> next -> token == FALSE) || (t.next -> next -> token == NOT))
		{	
			exp -> e1 = get_expression(l);
			get_next_token(&t, l);
			exp -> r = get_relate_op(l);
			exp -> e2 = get_expression(l);
			
			get_next_token(&t, l);
			if (t.token != RIGHT_PAREN) printf("Error, expected token: RIGHT_PAREN");	
		}
		else printf("Error, unexpected token");
	}
	else printf("Error, expected token: LEFT_PAREN, BOOLEAN, NOT");
	
	printf("expression nonterminal end");
	return exp;
}


//----------------------------------------------------------------------------------------

//method to expand relate_op nonterminal
struct relate_op_nonterm get_relate_op(struct token_list* l)
{
	struct relate_op_nonterm relate;
	struct token t;
	struct token* t2;

	printf("relate op nonterminal start");
	t2 = look_at_next_token(l);
	
	if (t2 -> token == IDENTIFIER_NAME)
	{
		relate.n1 = get_name(l);
	
		t2 = look_at_next_token(l);
		if (t2 -> token == PERIOD)
		{
			get_next_token(&t, l);
			relate.n2 = get_name(l);			

		}
		else if ((t2 -> token == GREATER_THAN) || (t2 -> token == LESS_THAN) || (t2 -> token == LESS_THANEQUAL) 
		|| (t2 -> token == GREATER_THANEQUAL) || (t2 -> token == EQUAL) || (t2 -> token == NOT_EQUAL))
		{
			relate.o = get_operation(l);
			
			t2 = look_at_next_token(l);
			if (t2 -> token == IDENTIFIER_NAME)
			{
				relate.n2 = get_name(l);
			}
			else if ((t2 -> token == INT) || (t2 -> token == FLOAT))
			{
				relate.nu1 = get_number(l);
			}
			else
			{
				printf("Error, expected token: IDENTIFIER, INT, FLOAT");
			}
		}
		else printf("Error, expected token: PERIOD, GREATER_THAN, LESS_THAN, LESS_THANEQUAL, GREATER_THANEQUAL, EQUAL, NOT_EQUAL");	
	
	}
	else if ((t2 -> token == INT) || (t2 -> token == FLOAT))
	{
		relate.nu1 = get_number(l);
		
		
		if ((t2 -> token == GREATER_THAN) || (t2 -> token == LESS_THAN) || (t2 -> token == LESS_THANEQUAL) 
		|| (t2 -> token == GREATER_THANEQUAL) || (t2 -> token == EQUAL) || (t2 -> token == NOT_EQUAL))
		{
			relate.o = get_operation(l);
		
			relate.nu2 = get_number(l);
		}
		else printf("Error, expected token:GREATER_THAN, LESS_THAN, LESS_THANEQUAL, GREATER_THANEQUAL, EQUAL, NOT_EQUAL");	
	

	}

	printf("relate op nonterminal end");
	return relate;
}


//----------------------------------------------------------------------------------------

//method to expand operation nonterminal
struct operation_nonterm get_operation(struct token_list* l)
{
	struct operation_nonterm op;
	struct token t;
	printf("operation nonterminal start");
	
	get_next_token(&t, l);
	op.operation = t.token;

	printf("operation nonterminal end");
	return op;
}



//----------------------------------------------------------------------------------------

//method to expand while statement nonterminal
struct while_stmt_nonterm get_while_stmt(struct token_list* l)
{
	struct while_stmt_nonterm whiler;
	struct token t;
	
	printf("while stmt nonterminal start");
	get_next_token(&t, l);	
	if (t.token != WHILE)
	{
		printf("Error, expected token: WHILE");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_PAREN)
	{	
		printf("Error, expected token: LEFT_PAREN");
	}

	whiler.e = get_expression(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_PAREN)
	{
		printf("Error, expected token: RIGHT_PAREN");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected token: LEFT_CURLY_BRACE");
	}

	whiler.s = get_stmt_list(l);
	
	get_next_token(&t, l);
	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}

	printf("while stmt nonterminal end");
	return whiler;
}	


//----------------------------------------------------------------------------------------

//method to expand for statement nonterminal
struct for_stmt_nonterm get_for_stmt(struct token_list* l)
{
	struct for_stmt_nonterm forer;
	struct token t;

	printf("for stmt nonterminal start");	

	get_next_token(&t, l);
	if (t.token != FOR)
	{
		printf("Error, expected token: FOR");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_PAREN)
	{
		printf("Error, expected token: LEFT_PAREN");
	}

	forer.n = get_name(l);

	get_next_token(&t, l);
	if (t.token != COLON)
	{
		printf("Error, expected token: COLON");
	}

	forer.i = get_int(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_PAREN)
	{	
		printf("Error, expected token: RIGHT_PAREN");
	}

	get_next_token(&t, l);
	if (t.token != LEFT_CURLY_BRACE)
	{
		printf("Error, expected  token: LEFT_CURLY_BRACE");
	}

	forer.s = get_stmt_list(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_CURLY_BRACE)
	{
		printf("Error, expected token: RIGHT_CURLY_BRACE");
	}
	

	printf("for stmt nonterminal end");	
	return forer;
}	


//----------------------------------------------------------------------------------------

//method to expand print statement nonterminal
struct print_stmt_nonterm get_print_stmt(struct token_list* l)
{
	struct print_stmt_nonterm print;
	struct token t;

	printf("print stmt nonterminal start");
	get_next_token(&t, l);
	if (t.token != PRINT)
	{	
		printf("Error, expected token: PRINT");
	}

	print.v = get_value(l);

	printf("print stmt nonterminal end");
	return print;
}


//----------------------------------------------------------------------------------------

//method to expand read statement nonterminal
struct read_stmt_nonterm get_read_stmt(struct token_list* l)
{
	struct read_stmt_nonterm read;
	struct token t;

	printf("read stmt nonterminal start");
	get_next_token(&t, l);
	if (t.token != READ)
	{
		printf("Error, expected token: READ");
	}

	read.n = get_name(l);

	printf("read stmt nonterminal end");
	return read;
}

//----------------------------------------------------------------------------------------

//method to expand math statement nonterminale
struct math_stmt_nonterm* get_math_stmt(struct token_list* l)
{
	struct math_stmt_nonterm* math;
	struct token t;
	struct token* t2;

	printf("math stmt nonterminal start");
	get_next_token(&t, l);
	if (t.token != LEFT_PAREN)
	{
		printf("Error, expected token: LEFT_PAREN");
	}	

	math -> v1 = get_value(l);
	math -> mo = get_math_op(l);
	math -> v2 = get_value(l);

	get_next_token(&t, l);
	if (t.token != RIGHT_PAREN)
	{
		printf("Error, expected token: RIGHT_PAREN");
	}

	printf("math stmt nonterminal end");
	return math;
}


//----------------------------------------------------------------------------------------

//method to expand assignment statement nonterminal
struct assign_stmt_nonterm get_assign_stmt(struct token_list* l)
{
	struct assign_stmt_nonterm assign;
	struct token t;
	
	printf("assign stmt nonterminal start");
	assign.n1 = get_name(l);

	get_next_token(&t, l);
	if (t.token == ASSIGN)
	{
		assign.v = get_value(l);
	}
	else if (t.token == PERIOD)
	{
		assign.n2 = get_name(l);

		get_next_token(&t, l);
		if (t.token != ASSIGN)
		{
			printf("Error, expected token: ASSIGN");
		}
		assign.v = get_value(l);
	}
	else if (t.token == LEFT_SQUARE)
	{
		assign.i = get_int(l);
		get_next_token(&t, l);
		if (t.token != RIGHT_SQUARE) printf("Error, expected token: RIGHT_SQUARE");
		get_next_token(&t, l);
		if (t.token != ASSIGN) printf("Error, expected token: ASSIGN");
		assign.v = get_value(l);
	}
	else
	{
		printf("Error, expected token: ASSIGN, PERIOD, LEFT_SQUARE");
	}

	printf("assign stmt nonterminal end");
	return assign;
}

//----------------------------------------------------------------------------------------

//method to expand nonterminals for value method
struct value_nonterm get_value(struct token_list* l)
{
	struct value_nonterm value;
	struct token* t2;
	struct token t;
	
	printf("value nonterminal start");
	t2 = look_at_next_token(l);
	
	if (t2 -> token == IDENTIFIER_NAME)
	{
		if ((t2 -> next -> token == LEFT_PAREN) || (t2 -> next -> next -> next -> token == LEFT_PAREN))
		{
			value.m = get_method_stmt(l);
		}

		value.n1 = get_name(l);
		
		t2 = look_at_next_token(l);
		if (t2 -> token == PERIOD)
		{
			get_next_token(&t, l);
			value.n2 = get_name(l);
		}
			
	}
	else if (t2 -> token == CHAR)
	{
		value.c = get_char(l);
	}
	else if ((t2 -> token == TRUE) || (t2 -> token == FALSE))
	{
		value.b = get_boolean(l);
	}	
	else if ((t2 -> token == INT) || (t2 -> token == FLOAT) || (t2 -> token == LEFT_PAREN))
	{
		value.nu = get_number(l);
	}
	else
	{
		printf("Error, expected token: CHAR, IDENTIFIER, TRUE, or FALSE");
	}

	printf("value nonterminal end");
	return value;
}


//----------------------------------------------------------------------------------------

//method to expand the method statement nonterminal
struct method_stmt_nonterm* get_method_stmt(struct token_list* l)
{
	struct method_stmt_nonterm* method;
	struct token t;
	
	printf("method stmt nonterminal start");
	method -> n = get_name(l);
	
	get_next_token(&t, l);
	if (t.token == LEFT_PAREN)
	{

		method -> p = *get_parameters_list(l);

		get_next_token(&t, l);
		if (t.token != RIGHT_PAREN)
		{
			printf("Errpr, expected token: RIGHT_PAREN");
		}
	}
	else if (t.token == PERIOD)
	{
		method -> n2 = get_name(l);
		get_next_token(&t, l);
		if (t.token != LEFT_PAREN) printf("Error, expected token: LEFT_PAREN");
		method -> p = *get_parameters_list(l);

		get_next_token(&t, l);
		if (t.token != RIGHT_PAREN) printf("Error, expected token: RIGHT_PAREN");
	}
	else 
	{
		printf("Error, expected token: LEFT_PAREN, PERIOD");
	}
	
	printf("method stmt nonterminal end");
	return method;
}


//----------------------------------------------------------------------------------------

//method to expand the parameters list nonterminal
struct parameters_list_nonterm* get_parameters_list(struct token_list* l)
{
	struct parameters_list_nonterm* list;
	struct token t;
	struct token* t2;
		
	printf("parameters list nonterminal start");
	list -> v = get_value(l);
	
	t2 = look_at_next_token(l);

	if (t2 -> token == COMMA)
	{
		get_next_token(&t, l);
		list -> p = get_parameters_list(l);
	}

	printf("parameters list nonterminal end");
	return list;
}


//----------------------------------------------------------------------------------------

//method to expand the variable declare nonterminal
struct var_declare_nonterm get_var_declare(struct token_list* l)
{
	struct var_declare_nonterm var;
	struct token* t2;
	struct token t;
	
	printf("var declare nonterminal start");
	var.t = get_type(l);
	var.n = get_name(l);

	t2 = look_at_next_token(l);

	if (t2 -> token == ASSIGN)
	{
		get_next_token(&t, l);
		var.v = get_value(l);
	}
	else if (t2 -> token == LEFT_SQUARE)
	{
		//get next token and throw it away, should be left square
		get_next_token(&t, l);
	
		var.i = get_int(l);
		get_next_token(&t, l);
		if (t.token != RIGHT_SQUARE) printf("Error, expected token: RIGHT_SQUARE");
	}
	else
	{
		printf("Error, expected token: ASSIGN, LEFT_SQUARE");
	}
	
	printf("var declare nonterminal end");
	return var;
}

//----------------------------------------------------------------------------------------

//method to expand character nonterminal
struct char_nonterm get_char(struct token_list* l)
{
	struct char_nonterm ch;
	struct token t;

	printf("char nonterminal start");
	get_next_token(&t, l);

	if (t.token != QUOTE) printf("Error, token expected: QUOTE");

	get_next_token(&t, l);
	ch.c = t.lexeme[0];
	
	get_next_token(&t, l);
	if (t.token != QUOTE) printf("Error, expected token: QUOTE");

	printf("char nonterminal end");
	return ch;
}

//----------------------------------------------------------------------------------------

//method to expand number nonterminal
struct number_nonterm get_number(struct token_list* l)
{
	struct number_nonterm* nu;
	struct token* t2;

	printf("number nonterminal start");
	t2 = look_at_next_token(l);
	
	if (t2 -> token == INT)
	{
		nu -> i = get_int(l);
	}
	else if (t2 -> token == FLOAT)
	{
		nu -> f = get_float(l);
	}
	else if ((t2 -> token == IDENTIFIER_NAME) || (t2 -> token == LEFT_PAREN))
	{
		nu -> m = get_math_stmt(l);
	}
	else
	{
		printf("Error, expected token: MATH_STMT, INT, FLOAT");
	}

	printf("number nonterminal end");
	return *nu;
}


//----------------------------------------------------------------------------------------

//method to expand integer nonterminal
struct int_nonterm get_int(struct token_list* l)
{
	
	struct int_nonterm integer;
	struct token t;

	printf("int nonterminal start");
	get_next_token(&t, l);
	
	integer.i = atoi(t.lexeme);

	printf("int nonterminal end");
	return integer;
}


//----------------------------------------------------------------------------------------

//method to expand float nonterminal
struct float_nonterm get_float(struct token_list* l)
{
	struct float_nonterm floater;
	struct token t;
		
	printf("float nonterminal start");
	get_next_token(&t, l);

	floater.f = atof(t.lexeme);

	printf("float nonterminal end");
	return floater;
}


//----------------------------------------------------------------------------------------

//method to expand boolean nonterminal
struct boolean_nonterm get_boolean(struct token_list* l)
{
	struct boolean_nonterm boolean;
	struct token t;

	printf("boolean nonterminal start");
	get_next_token(&t, l);

	if (t.token == TRUE)
	{
		boolean.boolean = 1;
	}
	else if (t.token == FALSE)
	{
		boolean.boolean = 0;
	}
	else
	{
		printf("Error, expected token: TRUE, FALSE");
	}
	
	printf("boolean nonterminal end");
	return boolean;
}


//----------------------------------------------------------------------------------------

//method to expand math operator nonterminal
struct math_op_nonterm get_math_op(struct token_list* l)
{
	struct math_op_nonterm mop;
	struct token t;

	printf("math op nonterminal start");
	get_next_token(&t, l);

	mop.t = t.token;

	printf("math op nonterminal end");
	return mop;
}



//----------------------------------------------------------------------------------------

