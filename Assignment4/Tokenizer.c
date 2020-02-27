#include "Tokenizer.h"

#include <ctype.h>

_Bool tokenizer(struct lexics * aLex, int * numLex, FILE * inf) {

  char temp_in[MY_CHAR_MAX] = "";
  char input[MY_CHAR_MAX] = "";
  char lexemes[LEXEME_MAX][MY_CHAR_MAX];

  // string used to read in lexemes and assing to array
  char * last_token;

  // temp string to split alphanum and symbols
  char temp_str[256];

  /*
  	get the input from the file object (inf)
  	and store in input string
  */

  // be sure to get the entire file by using a while loop
  while (fgets(temp_in, MY_CHAR_MAX, inf) != NULL) {
    strcat(input, temp_in);
  }

  // get the first by whitepsace and save to array
  int i = 0;
  char delimit[] = " \t\r\n\v\f"; // whitespace characters
  last_token = strtok(input, delimit);
  int h = 0;
  while (h < strlen(last_token)) {

    int token_length = 0;

    // reset temp_str every loop
    for (int i = 0; i < strlen(temp_str); i++) {
      temp_str[i] = '\0';
    }

    // get all the alphanum and assign as a token
    if (isalnum(last_token[h])) {
      int start = h;
      while ((isalnum(last_token[h]) != 0)) {
        token_length++;
        h++;
      }

      strncat(temp_str, & last_token[start], h - start);

      // no longer alphanum, add the token
      strcpy(lexemes[i], temp_str);
      i++;

    } else /* current char is not alphanum */ {
      // check if '!=' or '=='
      if ((strncmp( & last_token[h], "!", 1) == 0) && (strncmp( & last_token[h + 1], "=", 1) == 0)) {
        strncat(temp_str, & last_token[h], 2);
        h++;
        h++;
        strcpy(lexemes[i], temp_str);
        i++;
      } else if ((strncmp( & last_token[h], "=", 1) == 0) && (strncmp( & last_token[h + 1], "=", 1) == 0)) {
        strncat(temp_str, & last_token[h], 2);
        h++;
        h++;
        strcpy(lexemes[i], temp_str);
        i++;
      } else /* add regular non-alphanum one by one */ {
        strncpy(lexemes[i], & last_token[h], 1);
        i++;
        h++;
      }
    }

  }

  while (last_token != NULL) {
    last_token = strtok(NULL, delimit);

    // make sure not to assign an empty string
    if (last_token == NULL) {
      continue;
    }

    int h = 0;
    while (h < strlen(last_token)) {

      int token_length = 0;

      // reset temp_str every loop
      for (int i = 0; i < strlen(temp_str); i++) {
        temp_str[i] = '\0';
      }

      // get all the alphanum and assign as a token
      if (isalnum(last_token[h])) {
        int start = h;
        while ((isalnum(last_token[h]) != 0)) {
          token_length++;
          h++;
        }

        strncat(temp_str, & last_token[start], h - start);

        // no longer alphanum, add the token
        strcpy(lexemes[i], temp_str);
        i++;

      } else /* current char is not alphanum */ {
        // check if '!=' or '=='
        if ((strncmp( & last_token[h], "!", 1) == 0) && (strncmp( & last_token[h + 1], "=", 1) == 0)) {
          strncat(temp_str, & last_token[h], 2);
          h++;
          h++;
          strcpy(lexemes[i], temp_str);
          i++;
        } else if ((strncmp( & last_token[h], "=", 1) == 0) && (strncmp( & last_token[h + 1], "=", 1) == 0)) {
          strncat(temp_str, & last_token[h], 2);
          h++;
          h++;
          strcpy(lexemes[i], temp_str);
          i++;
        } else /* add regular non-alphanum one by one */ {
          strncpy(lexemes[i], & last_token[h], 1);
          i++;
          h++;
        }
      }

    }

  }

  // iterate through each lexeme and create a token from it
  char current_lex[256];
  int token_num;
  char token_lex[256];

  for (int i = 0; lexemes[i][0] != '\0'; i++) {

    // reset current_lex
    for (int j = 0; j < strlen(current_lex); j++) {
      current_lex[j] = '\0';
    }

    // concat character(s) of the lexeme to current_lex
    for (int h = 0; lexemes[i][h] != '\0'; h++) {
      strncat(current_lex, & lexemes[i][h], 1);
    }

    // find out which token it is, then add to lexics array
    if (isdigit(current_lex[0]) != 0) {

      token_num = NUMBER;
      strcpy(token_lex, current_lex);

    } else if (isalpha(current_lex[0]) != 0) {

      if (strcmp(current_lex, "int") == 0) {
        token_num = VARTYPE;
        strcpy(token_lex, current_lex);
      } else if (strcmp(current_lex, "void") == 0) {
        token_num = VARTYPE;
        strcpy(token_lex, current_lex);
      } else if (strcmp(current_lex, "while") == 0) {
        token_num = WHILE_KEYWORD;
        strcpy(token_lex, current_lex);
      } else if (strcmp(current_lex, "return") == 0) {
        token_num = RETURN_KEYWORD;
        strcpy(token_lex, current_lex);
      } else {
        token_num = IDENTIFIER;
        strcpy(token_lex, current_lex);
      }
    } else if (strlen(current_lex) == 1) {

      switch (current_lex[0]) {

      case '(':
        token_num = LEFT_PARENTHESIS;
        strcpy(token_lex, current_lex);
        break;
      case ')':
        token_num = RIGHT_PARENTHESIS;
        strcpy(token_lex, current_lex);
        break;
      case '{':
        token_num = LEFT_BRACKET;
        strcpy(token_lex, current_lex);
        break;
      case '}':
        token_num = RIGHT_BRACKET;
        strcpy(token_lex, current_lex);
        break;
      case ';':
        token_num = EOL;
        strcpy(token_lex, current_lex);
        break;
      case '+':
        token_num = BINOP;
        strcpy(token_lex, current_lex);
        break;
      case '*':
        token_num = BINOP;
        strcpy(token_lex, current_lex);
        break;
      case '%':
        token_num = BINOP;
        strcpy(token_lex, current_lex);
        break;
      case '=':
        token_num = EQUAL;
        strcpy(token_lex, current_lex);
        break;

      }
    } else if (strlen(current_lex) == 2) {
      switch (current_lex[0]) {
      case ('!'):
        token_num = BINOP;
        strcpy(token_lex, current_lex);
        break;

      case ('='):
        token_num = BINOP;
        strcpy(token_lex, current_lex);
      }
    }

    // create new struct lexics and add to array pointer of lexics
    struct lexics * newLex = (struct lexics * ) malloc(sizeof(struct lexics));
    newLex-> token = token_num;
    strcpy(newLex-> lexeme, current_lex);

    aLex[i] = * newLex;
    * numLex = i;
  }

  // create new struct lexics and add to array pointer of lexics
  struct lexics * newLex = (struct lexics * ) malloc(sizeof(struct lexics));
  newLex-> token = token_num;
  strcpy(newLex-> lexeme, current_lex);

  aLex[i + 1] = * newLex;
  * numLex = i;

  return TRUE;

}