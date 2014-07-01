#ifndef _PARSER_H
#define _PARSER_H
#include "LexicalAnalyzer.h"


typedef enum {
	CLASS_N, NAME_N, ACTION_LIST_N, ACTION_N, RECORD_LIST_N, RECORD_N, METHOD_LIST_N, METHOD_N, 
	FORMAL_PARAMETER_LIST_N, FORMAL_PARAMETER_N, TYPE_N, STMT_LIST_N, STMT_N, IF_STMT_N,
	EXPRESSION_N, RELATE_OP_N, OPERATION_N, WHILE_STMT_N, FOR_STMT_N, PRINT_STMT_N, READ_STMT_N,
	MATH_STMT_N, ASSIGN_STMT_N, VALUE_N, METHOD_STMT_N, PARAMETERS_LIST_N, VAR_DECLARE_N,
	CHAR_N, NUMBER_N, INT_N, FLOAT_N, BOOLEAN_N
} non_term;

struct math_op_nonterm {
	non_term type;
	token_type t;
};

struct boolean_nonterm {
	non_term type;
	int boolean;
};

struct float_nonterm {
	non_term type;
	float f;
};

struct int_nonterm {
	non_term type;
	int i;
};

struct number_nonterm {
	non_term type;
	struct int_nonterm i;
	struct float_nonterm f;
	struct math_stmt_nonterm* m;
};

struct char_nonterm {
	non_term type;
	char c;
};


struct type_nonterm {
	non_term type;
};

struct name_nonterm {
	non_term type;
	char* identifier;
};


struct value_nonterm {
	non_term type;
	struct number_nonterm nu;
	struct name_nonterm n1;
	struct char_nonterm c;
	struct boolean_nonterm b;
	struct int_nonterm i;
	struct method_stmt_nonterm* m;
	struct name_nonterm n2;
};

struct var_declare_nonterm {
	non_term type;
	struct type_nonterm t;
	struct name_nonterm n;
	struct value_nonterm v;
	struct int_nonterm i;
};

struct parameters_list_nonterm {
	non_term type;
	struct value_nonterm v;
	struct parameters_list_nonterm* p;
};

struct method_stmt_nonterm {
	non_term type;
	struct name_nonterm n;
	struct parameters_list_nonterm p;
	struct name_nonterm n2;
};


struct assign_stmt_nonterm {
	non_term type;
	struct name_nonterm n1;
	struct value_nonterm v;
	struct int_nonterm i;
	struct name_nonterm n2;
};

struct math_stmt_nonterm{
	non_term type;
	struct value_nonterm v1;
	struct math_op_nonterm mo;
	struct value_nonterm v2;
};


struct read_stmt_nonterm {
	non_term type;
	struct name_nonterm n;
};

struct print_stmt_nonterm {
	non_term type;
	struct value_nonterm v;
};

struct for_stmt_nonterm {
	non_term type;
	struct name_nonterm n;
	struct int_nonterm i;
	struct stmt_list_nonterm* s; 
};


struct operation_nonterm {
	non_term type;
	token_type operation;	
};

struct relate_op_nonterm {
	non_term type;
	struct operation_nonterm o;
	struct number_nonterm nu1;
	struct number_nonterm nu2;
	struct name_nonterm n1;
	struct name_nonterm n2;
};


struct expression_nonterm {
	struct boolean_nonterm b;
	struct expression_nonterm* e1;
	struct expression_nonterm* e2;
	struct relate_op_nonterm r;
	non_term type;	
	int not;
	token_type relation;
};


struct while_stmt_nonterm {
	non_term type;
	struct expression_nonterm* e;
	struct stmt_list_nonterm* s;	
};

struct if_stmt_nonterm {
	non_term type;
	struct expression_nonterm* e;
	struct stmt_list_nonterm* s1;
	struct stmt_list_nonterm* s2;
};

struct stmt_nonterm {
	struct if_stmt_nonterm if2;
	struct while_stmt_nonterm w;
	struct for_stmt_nonterm f;
	struct assign_stmt_nonterm a;
	struct math_stmt_nonterm* m;
	struct method_stmt_nonterm me;
	struct var_declare_nonterm v;
	struct print_stmt_nonterm p;
	struct read_stmt_nonterm r;
	non_term type;
};

struct stmt_list_nonterm {
	struct stmt_nonterm s1;
	struct stmt_list_nonterm* s2;	
	non_term type;
};


struct formal_parameter_nonterm {
	struct type_nonterm t;
	struct name_nonterm n;
	non_term type;
};


struct formal_parameter_l_nonterm {
	struct formal_parameter_l_nonterm* f2;
	struct formal_parameter_nonterm f1;
	non_term type;
};

struct method_nonterm {
	struct type_nonterm t;
	struct name_nonterm n;
	struct formal_parameter_l_nonterm fpl;
	struct stmt_list_nonterm* s;
	non_term type;
};

struct method_list_nonterm {
	non_term type;
	struct method_nonterm* m;
	struct method_list_nonterm* ml;
};

struct record_nonterm {
	non_term type;
	struct name_nonterm n;
	struct action_list_nonterm* a;
};

struct record_list_nonterm {
	non_term type;
	struct record_nonterm r;
	struct record_list_nonterm* rl;
};

struct action_nonterm {
	non_term type;
	struct method_list_nonterm ml;
	struct record_list_nonterm rl;
};

struct action_list_nonterm {
	non_term type;
	struct action_nonterm a;
	struct action_list_nonterm* al;
};


struct class_nonterm {
	non_term type;
	struct name_nonterm n;
	struct action_list_nonterm al;
};



//------------------------------------------------------------------------
//method signatures start here


struct class_nonterm get_class(struct token_list* l);

struct name_nonterm get_name(struct token_list* l);

struct action_list_nonterm* get_action_list(struct token_list* l);

struct action_nonterm get_action(struct token_list* l);

struct record_list_nonterm* get_record_list(struct token_list* l);

struct record_nonterm get_record(struct token_list* l);

struct method_list_nonterm* get_method_list(struct token_list* l);

struct method_nonterm* get_method(struct token_list* l);

struct formal_parameter_l_nonterm* get_formal_parameter_list(struct token_list* l);

struct formal_parameter_nonterm get_formal_parameter(struct token_list* l);

struct type_nonterm get_type(struct token_list* l);

struct stmt_list_nonterm* get_stmt_list(struct token_list* l);

struct stmt_nonterm get_stmt(struct token_list* l);

struct if_stmt_nonterm get_if_stmt(struct token_list* l);

struct expression_nonterm* get_expression(struct token_list* l);

struct relate_op_nonterm get_relate_op(struct token_list* l);

struct operation_nonterm get_operation(struct token_list* l);

struct while_stmt_nonterm get_while_stmt(struct token_list* l);

struct for_stmt_nonterm get_for_stmt(struct token_list* l);

struct print_stmt_nonterm get_print_stmt(struct token_list* l);

struct read_stmt_nonterm get_read_stmt(struct token_list* l);

struct math_stmt_nonterm* get_math_stmt(struct token_list* l);

struct assign_stmt_nonterm get_assign_stmt(struct token_list* l);

struct value_nonterm get_value(struct token_list* l);

struct method_stmt_nonterm* get_method_stmt(struct token_list* l);

struct parameters_list_nonterm* get_parameters_list(struct token_list* l);

struct var_declare_nonterm get_var_declare(struct token_list* l);

struct string_nonterm get_string(struct token_list* l);

struct char_nonterm get_char(struct token_list* l);

struct number_nonterm get_number(struct token_list* l);

struct int_nonterm get_int(struct token_list* l);

struct float_nonterm get_float(struct token_list* l);

struct boolean_nonterm get_boolean(struct token_list* l);

struct math_op_nonterm get_math_op(struct token_list* l);



#endif












