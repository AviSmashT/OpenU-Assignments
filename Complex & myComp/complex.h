#define LINK_VARS_LENGTH 7
#define LINK_CMD_LENGTH 9
#define RESULT 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum {FALSE, TRUE} boolean; /*Creating boolean data type*/
typedef enum {YES, NO} flag; /*Creating flag data type*/

/*Struct for complex number*/
typedef struct complexN{
double real;
double imaginary;
}complexNum;

/*Struct linking complex number*/
typedef struct {
char *name;
struct complexN *compNumAddress;
 }linkCompNums;

/*Struct linking functions*/
typedef struct {
char *name;
int functionIndex;
int numOfParams;
char *des;
}linkFunctions;

/*Decloration:*/
void read_comp(struct complexN *pointer, double temp1, double temp2);
void print_comp(struct complexN *pointer);
void add_comp(struct complexN *pointer, struct complexN *pointer2, struct complexN *result);
void sub_comp(struct complexN *pointer, struct complexN *pointer2, struct complexN *result);
void mult_comp_real(struct complexN *pointer, double temp1, struct complexN *result);
void mult_comp_img(struct complexN *pointer, double temp1, struct complexN *result);
void mult_comp_comp(struct complexN *pointer, struct complexN *pointer2, struct complexN *result);
double abs_comp(struct complexN *pointer);
flag stop(void);
flag cmdExtrect( char **userInput, char **str_cmd);
flag cmdCompare ( char *userInput, char *str_cmd, linkFunctions *commands);
flag firstParamExtrect(  char **userInput, char **str_param1);
flag seconedParamExtrect(  char **userInput, char **str_param2);
flag thirdParamExtrect(  char **userInput, char **str_param3);
flag paramEquals(linkFunctions *commands);
void rest(void);
void tansData(int *cmdIndex, int *param1Index, int *param2Index);
linkCompNums* getVars(void);
boolean isdigitstr(char* str);
int input(char **str);
