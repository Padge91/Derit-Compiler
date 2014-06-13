#ifndef _PARSER_H
#define _PARSER_H

typedef enum {
	CLASS, NAME, ACTION_LIST, ACTION, RECORD_LIST, RECORD, METHOD_LIST, METHOD, 
	FORMAL_PARAMETER_LIST, FORMAL_PARAMETER, TYPE, STMT_LIST, STMT, IF_STMT,
	EXPRESSION, RELATE_OP, OPERATION, WHILE_STMT, FOR_STMT, PRINT_STMT, READ_STMT,
	MATH_STMT, ASSIGN_STMT, VALUE, METHOD_STMT, PARAMETERS_LIST, VAR_DECLARE,
	STRING, CHAR, NUMBER, INT, FLOAT, BOOLEAN, MATH_STMT
}non_term;

struct class_nonterm {
	non_term = CLASS;
	struct name_nonterm;
	struct action_list_nonterm;
};

struct name_nonterm {
	non_term = NAME;
	char* identifier;
};

struct action_list_nonterm {
	non_term = ACTION_LIST;
	struct action_nonterm;
	struct action_list_nonterm;
};

struct action_nonterm {
	non_term = ACTION;
	struct method_list_nonterm;
	struct record_list_nonterm;
};

struct record_list_nonterm {
	non_term = RECORD_LIST;
	struct record_nonterm;
	struct record_list_nonterm;
};

struct record_nonterm {
	non_term = RECORD;
	struct name_nonterm;
	struct action_list_nonterm;
};

struct method_list_nonterm {
	non_term = METHOD_LIST;
	struct method_nonterm;
	struct method_list_nonterm;
};

struct method_nonterm {
	non_term = METHOD;
	struct type_nonterm;
	struct name_nonterm;
	struct formal_parameter_list_nonterm;
	struct stmt_list_nonterm;
};

struct formal_parameter_list_nonterm {
	non_term = FORMAL_PARAMETER_LIST;
	struct formal_parameter_nonterm;
	struct formal_parameter_list_nonterm;
};

struct formal_parameter_nonterm {
	non_term = FORMAL_PARAMETER;
	struct type_nonterm;
	struct name_nonterm;
};

struct type_nonterm {
	non_term = TYPE;
};

struct stmt_list_nonterm {
	non_term = STMT_LIST;
	struct stmt_nonterm;
	struct stmt_list_nonterm;
};

struct stmt_nonterm {
	non_term = STMT;
	struct if_stmt_nonterm;
	struct while_stmt_nonterm;
	struct for_stmt_nonterm;
	struct assign_stmt_nonterm;
	struct math_stmt_nonterm;
	struct method_stmt_nonterm;
	struct var_declare_nonterm;
	struct print_stmt_nonterm;
	struct read_stmt_nonterm;
};

struct if_stmt_nonterm {
	non_term = IF_STMT;
	struct expression_nonterm;
	struct stmt_list_nonterm;
	struct stmt_list_nonterm;
};

struct expression_nonterm {
	non_term = EXPRESSION;
	struct boolean_nonterm;
	struct expression_nonterm;
	struct expression_nonterm;
	struct relate_op_nonterm;
};

struct relate_op_nonterm {
	non_term = RELATE_OP;
	struct operation_nonterm;
	struct number_nonterm;
	struct number_nonterm;
	struct name_nonterm;
	struct name_nonterm;
};

struct operation_nonterm {
	non_term = OPERATION;
};

struct while_stmt_nonterm {
	non_term = WHILE_STMT;
	struct expression_nonterm;
	struct stmt_list_nonterm;	
};

struct for_stmt_nonterm {
	non_term = FOR_STMT;
	struct name_nonterm;
	struct int_nonterm;
	struct stmt_list_nonterm;
};

struct print_stmt_nonterm {
	non_term = PRINT_STMT;
	struct value_nonterm;
};

struct read_stmt_nonterm {
	non_term = READ_STMT;
	struct name_nonterm;
};

struct math_stmt_nonterm {
	non_term = MATH_STMT;
	struct math_stmt_nonterm;
	struct name_nonterm;
	struct math_op_nonterm;
	struct name_nonterm;
};

struct assign_stmt_nonterm {
	non_term = ASSIGN_STMT;
	struct name_nonterm;
	struct value_nonterm;
	struct int_nonterm;
	struct name_nonterm;
};

struct value_nonterm {
	non_term = VALUE;
	struct number_nonterm;
	struct name_nonterm;
	struct string_nonterm;
	struct char_nonterm;
	struct boolean_nonterm;
	struct int_nonterm;
	struct method_stmt_nonterm;
	struct name_nonterm;
};

struct method_stmt_nonterm {
	non_term = METHOD_STMT;
	struct name_nonterm;
	struct parameters_list_nonterm;
	struct name_nonterm;
};

struct parameters_list_nonterm {
	non_term = PARAMETERS_LIST;
	struct value_nonterm;
	struct parameters_list_nonterm;
};

struct var_declare_nonterm {
	non_term = VAR_DECLARE;
	struct type_nonterm;
	struct name_nonterm;
	struct value_nonterm;
	struct int_nonterm;
};

struct string_nonterm {
	non_term = STRING;
	char* string_literal;
};

struct char_nonterm {
	non_term = CHAR;
	char c;
};

struct number_nonterm {
	non_term = NUMBER;
	struct int_nonterm;
	struct float_nonterm;
	struct math_stmt_nonterm;
};

struct int_nonterm {
	non_term = INT;
	int i;
};

struct float_nonterm {
	non_term = FLOAT;
	float f;
};

struct boolean_nonterm {
	non_term = BOOLEAN;
	int boolean;
};

struct math_op_nonterm {
	non_term = MATH_OP;
};

//------------------------------------------------------------------------
//method signatures start here

void evaluate(non_term t);


struct class_nonterm get_class();

struct name_nonterm get_name();

struct action_list_nonterm get_action_list();

struct action_nonterm get_action();

struct record_list_nonterm get_record_list();

struct record_nonterm get_record();

struct method_list_nonterm get_method_list();

struct method_nonterm get_method();

struct formal_parameter_list get_formal_parameter_list();

struct formal_parameter get_formal_parameter();

struct type_nonterm get_type();

struct stmt_list_nonterm get_stmt_list();

struct stmt_nonterm get_stmt();

struct if_stmt_nonterm get_if_stmt();

struct expression_nonterm get_expression();

struct relate_op_nonterm get_relate_op();

struct operation_nonterm get_operation();

struct while_stmt_nonterm get_while_stmt();

struct for_stmt_nonterm get_for_stmt();

struct print_stmt_nonterm get_print_stmt();

struct read_stmt_nonterm get_read_stmt();

struct math_stmt_nonterm get_math_stmt();

struct assign_stmt_nonterm get_assign_stmt();

struct value_nonterm get_value();

struct method_stmt_nonterm get_method_stmt();

struct parameters_list_nonterm get_parameters_list();

struct var_declare_nonterm get_var_declare();

struct string_nonterm get_string();

struct char_nonterm get_char();

struct number_nonterm get_number();

struct int_nonterm get_int();

struct float_nonterm get_float();

struct boolean_nonterm get_boolean();

struct math_op_nonterm get_math_op();



#endif












