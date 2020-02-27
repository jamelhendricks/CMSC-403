#include "Tokenizer.h"
#include <ctype.h>

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){

	char input[MY_CHAR_MAX] = "";
	char tokens[LEXEME_MAX][MY_CHAR_MAX];

	// string used to read in tokens and assing to array
	char *last_token;

	// temp string to split alphanum and symbols
	char temp_str[256];

	/*
		get the input from the file object (inf)
		and store in input string
	*/
	fgets(input, MY_CHAR_MAX, inf);

	// get the first by whitepsace and save to array
	int i = 0;
	last_token = strtok( input, " " );
	int h = 0;
		while(h < strlen(last_token)){
			
			int token_length = 0;

			// reset temp_str every loop
			for (int i = 0; i < strlen(temp_str); i++){
				temp_str[i] = '\0';
			}

			// get all the alphanum and assign as a token
			if (isalnum(last_token[h])){
				int start=h;
				while( (isalnum(last_token[h]) != 0) ){
					token_length++;
					h++;
				}

				strncat(temp_str, &last_token[start], h-start);

				// no longer alphanum, add the token
				strcpy(tokens[i], temp_str);
				i++;

			} else /* current char is not alphanum */ {
				// check if '!=' or '=='
				if (  (strcmp(&last_token[h], "!") == 0) && (strcmp(&last_token[h+1], "=") == 0 ) ) {
					strncat(temp_str, &last_token[h], 2);
					h++;
					h++;
					strcpy(tokens[i], temp_str);
					i++;
				} else if (  (strcmp(&last_token[h], "=") == 0) && (strcmp(&last_token[h+1], "=") == 0 ) ) {
					strncat(temp_str, &last_token[h], 2);
					h++;
					h++;
					strcpy(tokens[i], temp_str);
					i++;
				} else /* add regular non-alphanum one by one */ {
					strncpy(tokens[i], &last_token[h], 1);
					i++;
					h++;
				}
			}


		}

	// get the remaining tokens and save to array
	while( last_token != NULL ){
	    last_token = strtok( NULL, " " );

	    // make sure not to assign an empty string
		if (last_token == NULL){
			break;
		}

		int h = 0;
		while(h < strlen(last_token)){
			
			int token_length = 0;

			// reset temp_str every loop
			for (int i = 0; i < strlen(temp_str); i++){
				temp_str[i] = '\0';
			}

			// get all the alphanum and assign as a token
			if (isalnum(last_token[h])){
				int start=h;
				while( (isalnum(last_token[h]) != 0) ){
					token_length++;
					h++;
				}

				strncat(temp_str, &last_token[start], h-start);

				// no longer alphanum, add the token
				strcpy(tokens[i], temp_str);
				i++;

			} else /* current char is not alphanum */ {
				// check if '!=' or '=='
				if (  (strcmp(&last_token[h], "!") == 0) && (strcmp(&last_token[h+1], "=") == 0 ) ) {
					strncat(temp_str, &last_token[h], 2);
					h++;
					h++;
					strcpy(tokens[i], temp_str);
					i++;
				} else if (  (strcmp(&last_token[h], "=") == 0) && (strcmp(&last_token[h+1], "=") == 0 ) ) {
					strncat(temp_str, &last_token[h], 2);
					h++;
					h++;
					strcpy(tokens[i], temp_str);
					i++;
				} else /* add regular non-alphanum one by one */ {
					strncpy(tokens[i], &last_token[h], 1);
					i++;
					h++;
				}
			}


		}

	}

	// print 2d array of tokens
	printf("\n\n scanned in tokens: \n");
	for (int i = 0; tokens[i][0] != '\0'; i++){
		for(int h = 0; tokens[i][h] !='\0'; h++){
			printf("%c", tokens[i][h]);
		}
		printf("\n");
	}
		
	

return TRUE;

}
