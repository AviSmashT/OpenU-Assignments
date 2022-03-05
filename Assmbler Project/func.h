#define MAX_LINE_SIZE 81
#define LINE_BUFFER 90
#define WORD_LENGTH 25
#define ERROR_LINE_SKIP\
        ERROR = YES;\
        lineNumber++;\
        continue; 
#define NO_OPCODE 16

/*Struct linking opcode*/
struct instraction{
int opcode;
int func;
char *opcode_name;
int numOfOps;
int op_source[3];
int op_dest[3];
};


/*Varibles Declorations:*/
int PendingIC; /*Pending to increace*/
int lineIndex; /* Index to current position in the line */
int lineNumber; /*Index of line*/


/*** Function Declorations: ***/
void addData(char ** str, wordsData * data_table);
void addString(char ** str, wordsData *data_table);
void addCode(int opcode, int method_source, int method_dest, int firstReg, int secondReg, data_type data , int * L);
void addSymbol(char *lable, int DC, int IC, data_type data);
int intLength(int num);
void addImmediate(char * str, int IC);
void setPendingIC();
void pendingIncreaseIC();
void addMissingCode(int FinalIndex);
boolean multipuleComma(char * line);
void removedoublespaces(char *line); 
void replaceWhiteSpaces(char *line);
boolean isLable(char *lable); 
boolean isLableRef(char *lable);
int whichOpcode(char *opcode, data_type *data);
data_type isData(char *data);
int whichaddressingmethod(char *operand , int * reg);
void methodCheck(int *method_source, int *method_dest, char * str1 , char * str2 , int opcode, int * reg1 , int * reg2, int * IC);
void twoCompCon(char * str, int size);
void intToStr(long number, char * str);
void decimalToBinaryData(long decimalnum, char * str);
boolean isdigitstr(char* str);
