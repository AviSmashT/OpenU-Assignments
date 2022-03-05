#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>

/*Defines:*/
#define FIRST_DIG 0 /*first digit in string "numbers"*/
#define SECOND_DIG 1 /*second digit in string "numbers"*/
#define NUMNER_SIZE 3 /*size of string "numbers"*/
#define STRING_NUM_SIZE 20 /*size of string "textToNum"*/

/*enum: */
typedef enum {FALSE, TRUE} boolean; /*Creating boolean data type: */
typedef enum {YES, NO} flag; /*Creating flag data type*/

/*Declaration of functions:*/
boolean peekNext(int c , FILE * stream);
void numToText(char number[], char temp[]);
void resetValues(int *bufcon, char *textToNum, char *numbers);
boolean CheckNextDig(int c , FILE * stream);
