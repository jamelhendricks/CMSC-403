#include "Parser.h"

#include "Givens.h"

_Bool parser(struct lexics * someLexics, int numberOfLexics) {
  int currentLex = 0;
  return (func_func(someLexics, numberOfLexics, & currentLex));
}

// check the function
// function--> header body
_Bool func_func(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (!(header(someLexics, numberOfLexics, index))) {
    return FALSE;
  }
  if (!(body(someLexics, numberOfLexics, index))) {
    return FALSE;
  }
  if ( * index != numberOfLexics) {
    return FALSE;
  }
  return TRUE;
}

// check the header
// header--> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
_Bool header(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == VARTYPE) {
    * index = * index + 1;
    if (someLexics[ * index].token == IDENTIFIER) {
      * index = * index + 1;
      if (someLexics[ * index].token == LEFT_PARENTHESIS) {
        * index = * index + 1;
        if (someLexics[ * index].token == RIGHT_PARENTHESIS) {
          * index = * index + 1;
          return TRUE;
        } else {
          if (arg_decl(someLexics, numberOfLexics, index) && someLexics[ * index].token == RIGHT_PARENTHESIS) {
            * index = * index + 1;
            return TRUE;
          }
        }
      }
    }
  }
  return FALSE;
}

// check arg-decl
// arg-decl--> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
_Bool arg_decl(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == VARTYPE) {
    * index = * index + 1;
    if (someLexics[ * index].token == IDENTIFIER) {
      * index = * index + 1;
      int prevIndex = * index;
      _Bool loop = TRUE;
      while (loop) {
        if (someLexics[ * index].token == COMMA) {
          * index = * index + 1;
          if (someLexics[ * index].token == VARTYPE) {
            * index = * index + 1;
            if (someLexics[ * index].token == IDENTIFIER) {
              * index = * index + 1;
              prevIndex = * index;
            } else {
              loop = FALSE;
            }
          } else {
            loop = FALSE;
          }
        } else {
          loop = FALSE;
        }
      }
      * index = prevIndex;
      return TRUE;
    }
  }
  return FALSE;
}

// check body
// body--> LEFT_BRACKET [statement-list] RIGHT_BRACKET
_Bool body(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == LEFT_BRACKET) {
    * index = * index + 1;
    if (someLexics[ * index].token == RIGHT_BRACKET) {
      * index = * index + 1;
      return TRUE;
    } else {
      if (statement_list(someLexics, numberOfLexics, index) && someLexics[ * index].token == RIGHT_BRACKET) {
        * index = * index + 1;
        return TRUE;
      }
    }
  }
  return FALSE;
}

// check statement-list
// statement-list--> statement {statement}
_Bool statement_list(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (!(statement(someLexics, numberOfLexics, index))) { //if statement() returns false
    return FALSE;
  }
  int prevIndex = * index;
  while (statement(someLexics, numberOfLexics, index)) {
    prevIndex = * index;
  }
  * index = prevIndex;
  return TRUE;
}

// check statement
// statement--> while-loop | return | assignment | body
_Bool statement(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (while_loop(someLexics, numberOfLexics, index) || ret_func(someLexics, numberOfLexics, index) || assignment(someLexics, numberOfLexics, index) || body(someLexics, numberOfLexics, index)) {
    return TRUE;
  }
  return FALSE;
}

// check while-loop
// while-loop--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
_Bool while_loop(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == WHILE_KEYWORD) {
    * index = * index + 1;
    if (someLexics[ * index].token == LEFT_PARENTHESIS) {
      * index = * index + 1;
      if (expression(someLexics, numberOfLexics, index)) {
        if (someLexics[ * index].token == RIGHT_PARENTHESIS) {
          * index = * index + 1;
          if (statement(someLexics, numberOfLexics, index)) {
            return TRUE;
          }
        }
      }
    }
  }
  return FALSE;
}

// check return
// return--> RETURN_KEYWORD expression EOL
_Bool ret_func(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == RETURN_KEYWORD) {
    * index = * index + 1;
    if (expression(someLexics, numberOfLexics, index)) {
      if (someLexics[ * index].token == EOL) {
        * index = * index + 1;
        return TRUE;
      }
    }
  }
  return FALSE;
}

// check assignment
// assignment--> IDENTIFIER EQUAL expression EOL
_Bool assignment(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == IDENTIFIER) {
    * index = * index + 1;
    if (someLexics[ * index].token == EQUAL) {
      * index = * index + 1;
      if (expression(someLexics, numberOfLexics, index)) {
        if (someLexics[ * index].token == EOL) {
          * index = * index + 1;
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

// check expression
// expression--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
_Bool expression(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (term(someLexics, numberOfLexics, index)) {
    int prevIndex = * index;
    _Bool loop = TRUE;
    while (loop) {
      if (someLexics[ * index].token == BINOP) {
        * index = * index + 1;
        if (term(someLexics, numberOfLexics, index)) {
          prevIndex = * index;
        } else {
          loop = FALSE;
        }
      } else {
        loop = FALSE;
      }
    }
    * index = prevIndex;
    return TRUE;
  } else if (someLexics[ * index].token == LEFT_PARENTHESIS) {
    * index = * index + 1;
    if (expression(someLexics, numberOfLexics, index)) {
      if (someLexics[ * index].token == RIGHT_PARENTHESIS) {
        * index = * index + 1;
        return TRUE;
      }
    }
  }
  return FALSE;
}

// check term
// term--> IDENTIFIER | NUMBER
_Bool term(struct lexics * someLexics, int numberOfLexics, int * index) {
  if (someLexics[ * index].token == IDENTIFIER || someLexics[ * index].token == NUMBER) {
    * index = * index + 1;
    return TRUE;
  }
  return FALSE;
}