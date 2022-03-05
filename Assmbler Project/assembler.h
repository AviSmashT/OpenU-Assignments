#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define NUM_OF_OP 16
#define NOT_SET -1
#define LABLE_LENGTH 32
#define FILE_EXTENSION_SIZE 3

typedef enum {FALSE, TRUE} boolean; /*Creating boolean data type*/
typedef enum {YES, NO} flag; /*Creating flag YES/NO type*/
typedef enum {immediate = 0, direct = 1, relative = 2, diRegister = 3, no_method = 4} addressing_method; /*Creating flag addressing method type*/
typedef enum {DATA, STRING, EXTERNAL, ENTRY, NO_DATA} data_type; /*Creating flag data type*/

/*Struct for symaol table*/
typedef struct {
  char symbol_name[32];
  int symbol_address;
  data_type symbol_type;
  data_type entry_type;
}symbols;

/*Struct for WORDS CODE*/
typedef struct {
char opcode[6];
char source[2];
char register_source[3];
char dest[2];
char register_dest[3];
char func[5];
char A[1];
char R[1];
char E[2]; /*end of word (need to add '\0')*/
}wordsCode;
 
/*Struct for DATA WORDS CODE*/
typedef struct{
  char data[25];
}wordsData;

/*Struct for stack of addresses - contain the location of missing WORDS (direct or relative) */
typedef struct{
  int address; /*The address of lable*/
  char LABLE[32]; /*size of lable*/
}address_Stack;

/*varibles Declorations:*/
int ICF; /*Final Instruction Counter*/
int DCF; /*Final Data Counter*/
wordsData data_table[1000]; /*Data type table*/
wordsCode data_code[1000]; /*Instruction/Code type table*/
address_Stack * addressStack; /*  stack of addresses - contain the location of missing WORDS (direct or relative)*/
int addressStackIndex; /*Index of stack addresses */
symbols * symbolTable; /*Symbol table initialize*/
int Symbolrows; /*Index of rows in symbol table */
int IC; /*Instruction Counter*/
int DC; /*Data Counter*/
char * fileName; /*Will be used to store file name*/
int ExtC; /*Couner for extern words*/
flag ERROR; /*Flag to indicate an error in the input file*/


/*** Function Declorations: ***/
void firstFileCheck(FILE * file);
void secondFileCheck(FILE * file);
void strCut(char *line, char stop, int *indexline, char **strReturn);
void writeFiles();
