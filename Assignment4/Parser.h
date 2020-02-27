#include "Givens.h"

/****
	-each function returns a boolean indicating whether it passes or fails
	- for nonterminals, the subsequent checker will automatically be called
	- calling only parser will initiate the check of the entire grammar
		- each method is called by a parent, which leads up to the "grandparent"
		  method, parser
****/

// parent function which starts at the root of the grammar
_Bool parser(struct lexics * someLexics, int numberOfLexics);

// checks the function part of the grammar and its sub tokens
_Bool func_func(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the header part of the grammar and its sub tokens
_Bool header(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the argument declaration part of the grammar and its sub tokens
_Bool arg_decl(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the body part of the grammar and its sub tokens
_Bool body(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the statement list part of the grammar and its sub tokens
_Bool statement_list(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the statement part of the grammar and its sub tokens
_Bool statement(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the while loop part of the grammar and its sub tokens
_Bool while_loop(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the return part of the grammar and its sub tokens
_Bool ret_func(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the assignment part of the grammar and its sub tokens
_Bool assignment(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the expression part of the grammar and its sub tokens
_Bool expression(struct lexics * someLexics, int numberOfLexics, int * index);

// checks the term part of the grammar and its sub tokens
_Bool term(struct lexics * someLexics, int numberOfLexics, int * index);