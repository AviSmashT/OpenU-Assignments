#include "assembler.h"
#include "func.h"


/*** creating link between opcode, func and number of operands ***/
struct instraction commands[16] = {
	{ 0, -1,"mov",  2 ,     {0 ,1 ,3} , {1, 3,-1} },	
       { 1, -1, "cmp", 2,       {0 ,1 ,3} , {0, 1, 3} },
	{ 2, 1,"add", 2,        {0 ,1 ,3} , {1, 3,-1} },
	{ 2 ,2, "sub", 2,       {0 ,1 ,3} , {1, 3,-1} },
	{ 4, -1, "lea", 2,      {1 ,-1 ,-1} , {1, 3,-1} },
	{ 5, 1, "clr", 1,       {-1 ,-1 , -1} , {1, 3,-1} },
	{ 5, 2, "not", 1,       {-1 ,-1 , -1} , {1, 3,-1} },
	{ 5, 3 ,"inc", 1,       {-1 ,-1 , -1} , {1, 3,-1} },
	{ 5, 4, "dec", 1,       {-1 ,-1 , -1} , {1, 3,-1} },
	{ 9, 1, "jmp", 1,       {-1 ,-1 , -1} , {1, 2,-1} },
	{ 9, 2, "bne", 1,       {-1 ,-1 , -1} , {1, 2,-1} },
	{ 9, 3, "jsr", 1,       {-1 ,-1 , -1} , {1, 2,-1} },
	{ 12, -1, "red", 1,     {-1 ,-1 , -1} , {1, 3,-1} },
	{ 13, -1, "prn", 1,     {-1 ,-1 , -1} , {0, 1, 3} },
	{14, -1, "rts", 0,      {-1 ,-1 , -1} , {-1 ,-1 , -1} },
	{ 15, -1, "stop", 0,    {-1 ,-1 , -1} , {-1 ,-1 , -1} } };





/*** This function remove double spaces from the string that is recived as paramater ***/
void removedoublespaces(char * line) {
  int i = 0; /*all line index*/
  int j = 0; /*inside line index*/
  int n = 0; /*line length*/

  while ( *(line + n) != '\0'){ /*Check the length of the line*/
    n++;
  }

  while (i < n){ /*Loop to run through the line*/
    if ( *(line + i) == ' ' && ( *(line + i + 1) == ' ' || *(line + i - 1) == ' ')){ /*Checks if there is a space in current, next or previous index*/
      for (j = i; j < n; j++) { /*Run loop from index to replace every element in array -1*/
        *(line + j) = * (line + j + 1);
      }
      n--; /*reminder: line length*/
    } /*End of If*/
    else {
      i++; /*increase index accordingly*/
    }
  } /*End of loop*/
} /*End of function*/





/*** This function replace every "whitespaces" with 'regular' space. Changes made to the string that is recived as paramater ***/
void replaceWhiteSpaces(char * line) {
  int c = 0; /*line index*/
  
  for (c = 0; c < (strlen(line)); c++) { /*Loop to run through the line*/
    if ( * (line + c) == ' '){ /*Ignore regular space*/
      continue;
    }
    if (isspace( *(line + c)) != 0) {/*else replce non-regular space with regular space*/
      *(line + c) = ' ';
    }
  }
} /*End of function*/





/*** This function checks if the first word in the line is a lable
     incase the first word is a lable - return TRUE, else - return FALSE ***/
boolean isLable(char * lable) {
  int c = 0; /*index for lable characters check*/
  int i = 0; /*index for non-registers check*/
  
  if (strlen(lable) > LABLE_LENGTH) {
    ERROR = YES;
    printf("ERROR in file %s - line %d: Lable definition is too long\n", fileName, lineNumber);
  }
  if (lable[0] == 'r'){ /*Check lable is not named as a saved word for register*/
    for (i = 0; i < 9; i++) {
      if ((lable[1] - '0') == i) {
        if (lable[2] == ':')
          printf("error!");
        return FALSE;

      }
    }
  }

  if (lable[strlen(lable) - 1] == ':') { /* lable if the first word is consist of characters and digits and ending with ":" */
    for (c = 0; c < (strlen(lable)) - 1; c++) { /*Loop to run through the word but the last character*/
      if ((isdigit( * (lable + c)) == 0) && (isalpha( * (lable + c)) == 0)) { /*check the the character is either digit or a alpha*/
        return FALSE;
      }
    } /*End of loop*/
    return TRUE;
  }
  else
    return FALSE;
} /*End of function*/






/*** This function checks if a lable given as paramater can be a refrence to a lable
     incase the string can be a lable - return TRUE, else - return FALSE ***/
boolean isLableRef(char * lable){
  int c = 0; /*index for lable characters check*/
  int i = 0; /*index for non-registers check*/

  if (strlen(lable) > LABLE_LENGTH){ /*Check lable limit is not passed*/
    ERROR = YES;
    printf("ERROR in file %s - line %d: Lable definition is too long\n", fileName, lineNumber);
    return FALSE;
  }

  if (lable[0] == 'r'){ /*Check lable is not named as a saved word for register*/
    for (i = 0; i < 9; i++) {
      if ((lable[1] - '0') == i) {
        if (lable[2] == '\0' || lable[2] == ' ') {
          return FALSE;
        }
      }
    }
  }
  for (c = 0; c < (strlen(lable)); c++){ /*Loop to run through the word but the last character*/
    if ((isdigit( * (lable + c)) == 0) && (isalpha( * (lable + c)) == 0) && * (lable + strlen(lable) - 1) == '\0'){/*check the the character is either digit or a alpha*/
      return FALSE;
    }
  } /*End of loop*/
  return TRUE;

} /*End of function*/






/*** This function check which opcode givin in paramater as a string and 
     return the opcode number, if opcode is not exist - return 16 ***/
int whichOpcode(char * opcode, data_type * data){
  int j = 0;

  for (j = 0; j < NUM_OF_OP; j++){ /*Loop to go through opcodes*/
    if (strcmp(opcode, (char * ) commands[j].opcode_name) == 0){ /* compare opcode given as paramater */
      break; /*If there is a match - break (index i will indicate the command we will use (with switch))*/
    }
  }
  if (j == NUM_OF_OP){ /*If i equals 16, Its not an opcode */
    * data = isData(opcode); /* if paramater is not an opcode - check if .data or .string */
  }

  return j; /* Return opcode number or 16 - not an opcode */
}






/*** This function recive a string as paramater and copy to a part of it to strReturn 
     from paramater 'indexline' position to the point it reached the 'stop' paramater ***/
void strCut(char * line, char stop, int * indexline, char ** strReturn){
  int index = 0; /*Index to of strReturn copy*/
  int lineLen = strlen(line); /*line length*/
  int i = 0; /*Index for line*/
  char * ptrIsData = NULL; 
  char * ptrIsString = NULL;
  ptrIsString = strstr(line, ".string"); 
  ptrIsData = strstr(line, ".data"); 

  if ( * indexline >= lineLen){
    return;
  }
  
  i = *indexline; /*Initialize index line (the point to start copy from)*/

  if ((*(line + i)) == ' ') /*skip space if there is one*/
    i++;
  *strReturn = (char * ) malloc(sizeof(char));

  if (stop == '\0' && ptrIsData == NULL && ptrIsString == NULL) {
    /*Incase of non-data/string line type*/
    while (i < lineLen) { /*Copy strReturn (the opcode)*/
      if (( * (line + i)) == ',') {
        ERROR = YES;
        printf("ERROR in file %s - line %d: Extraneous text after end of instraction\n", fileName, lineNumber);
        free( * strReturn);
        * strReturn = NULL;
        return;
      }
      if ((*(line + i)) == (stop) || (*(line + i)) == '\n') { /*If position at 'stop' or end of line - break*/
        break;
      }
      *(*strReturn + index) = (*(line + i)); /*ELSE - write to strReturn*/
      index++; /*index strReturn*/
      *strReturn = (char *) realloc( * strReturn, (1 + index) * sizeof(char)); /*realloc for next writing*/
      if (!*strReturn){
        printf("ERROR in file %s - line %d: Program was unable to realloc memory in strCut function\n", fileName, lineNumber);
        ERROR = YES;
      }   
      i++; /*index line */
    }

  } else {
    while (i < lineLen) {
      /*Copy strReturn (the opcode)*/

      if ((*(line + i)) == (stop) || ( * (line + i)) == '\n') {
        break;
      }
      *(*strReturn + index) = (*(line + i));
      index++;
      *strReturn = (char *) realloc(*strReturn, (1 + index) * sizeof(char));
      if (!*strReturn){
        printf("ERROR in file %s - line %d: Program was unable to realloc memory in strCut function\n", fileName, lineNumber);
        ERROR = YES;
      }   
      i++;
    }

  }

  if (*(*strReturn + index - 1) == ' ')
    *(*strReturn + index - 1) = '\0'; /* end of string */
  else
    *(*strReturn + index) = '\0'; /* end of string */
  i++;
  *indexline = i;

} /*End of function*/





/*** This function check that there is no multiple commas in line ***/
boolean multipuleComma(char * line) {
  char * commaCheck;
  
  if (strstr(line, ".string") == NULL){ /*If line is type .string than double commas allowed*/
    commaCheck = strstr(line, ", ,");
    if (commaCheck != NULL) { /*If double commas found:*/
      ERROR = YES;
      printf("ERROR in file %s - line %d: Multiple consecutive commas\n", fileName, lineNumber);
      return TRUE;
    }
    commaCheck = strstr(line, ",,");
    if (commaCheck != NULL) { /*If double commas found:*/
      ERROR = YES;
      printf("ERROR in file %s - line %d: Multiple consecutive commas\n", fileName, lineNumber);
      return TRUE;
    }
  }
  return FALSE;
}





/*** This function adds lable to symbol table, if the lable is alreay 
     in the symbol table - don't insert to symbol table and place an error ***/
void addSymbol(char * lable, int DC, int IC, data_type data){
  int i = 0; /*Index to go through symbal table*/

  for (i = 0; i < Symbolrows; i++){ /*Loop to go through symbal table*/
    if (strcmp(lable, symbolTable[i].symbol_name) == 0){ /*compare lable to be insert to with the lables in symbol table*/
      ERROR = YES; /*lable already exist in the symbol table*/
      printf("ERROR in file %s - line %d: Lable suggested is alreay exist in symbol\n", fileName, lineNumber);
      break;
    }
  }

  if (ERROR == NO){ /*If flag is NO - create a new row in the symbol table and insert new lable data*/

    if (Symbolrows == 0) { /*REMINDER: Symbolrows is index of rows in symbol table, if number of rows is 1 insert lable data (without reallocation to symbolTable)*/
      strcpy(symbolTable[Symbolrows].symbol_name, lable); /*initialize symbol name*/
      if (data != NO_DATA) { /*if is data type initialize address DC + IC*/
        symbolTable[Symbolrows].symbol_address = DC + IC; 
      } 
      else{ /*ELSE initialize address = IC*/
        symbolTable[Symbolrows].symbol_address = IC; 
      }
      symbolTable[Symbolrows].symbol_type = data; /*initialize data type*/
      symbolTable[Symbolrows].entry_type = NO_DATA; /*initialize default*/

    } 
    else { /*ELSE: if number of rows is more than 1 - insert lable data (with realloc to symbolTable before that)*/
      symbolTable = (symbols * ) realloc( symbolTable, (Symbolrows + 1) * sizeof(symbols)); /*realloc to symbol table*/
      if (!symbolTable){
        printf("ERROR in file %s - line %d: Program was unable to realloc memory for symbol table\n", fileName, lineNumber);
        ERROR = YES;
      }

      strcpy(symbolTable[Symbolrows].symbol_name, lable); 
      if (data == STRING || data == DATA) { /*DATA = DC + IC*/
        symbolTable[Symbolrows].symbol_address = DC + IC; 
      } 
      else {/*CODE = IC*/
        symbolTable[Symbolrows].symbol_address = IC; 
      }
      symbolTable[Symbolrows].symbol_type = data; 
      symbolTable[Symbolrows].entry_type = NO_DATA; 
    }

    Symbolrows++; /*increase symbolTable index by 1*/

  }

}/*End of function*/






/*** This function check what data type (.data or .string) a given paramater - return data type or NO_DATA ***/
data_type isData(char * data) {

  if ((strcmp(data, ".data")) == 0)
    return DATA;
  if ((strcmp(data, ".string")) == 0)
    return STRING;
  return NO_DATA;
  
}





/*** This function recive operand (string) and return the method accordingly, also register 
     passed as paramater is Initialized incase of invalid operand - return 'no_method' value ***/
int whichaddressingmethod(char * operand, int * reg) {
  int i = 0; /* index for loop */
  
  
  if (operand[0] == '#'){ /*Check if immediate*/
    if (isdigitstr(operand + 1) == TRUE) {
      return immediate;
    }
  }
  if (operand[0] == 'r'){ /*Check if register*/
    for (i = 0; i < 9; i++) {
      if (isdigitstr(operand + 1) == TRUE) {
        if (i == atoi(operand + 1)) {
          * reg = i; /*Initialize the register given as paramater*/
          break;
        }
      }
    }
    if (i < 9)
      return diRegister;
  }
  if (operand[0] == '&') { /*Check if relative*/
    if (isLableRef(operand + 1) == TRUE) {
      return relative;
    }
  }

  if (isLableRef(operand) == TRUE){ /*Check if direct*/
    return direct;
  }

  return 4; /*If returning 4 - operand is invalid*/
}





/*** This function recive a number (type long) and convert to binary code (type string)
     the changes made to the paramater ***/
void decimalToBinaryData(long decimalNum, char * str){
  long binaryNum = 0; /*Hold the binary number */
  long remainder = 0; /*Hold the remainder of decimal number */
  long temp = 1; /* temp long for conversion */
  char tempstr[25]; /* them string for conversion */
  flag sign = NO; /*To indicate if is sign*/

  if (decimalNum >= 0){ /* initialize for positive number*/
    strcpy(str, "000000000000000000000000");
  } 
  else { /* initialize for negitive number*/
    strcpy(str, "111111111111111111111111");
    sign = YES; /*sign to use later the function 'twoCompCon'*/
  }

  while (decimalNum != 0){
    remainder  = decimalNum % 2; 
    decimalNum = decimalNum / 2; 
    binaryNum = binaryNum + remainder  * temp;
    temp = temp * 10; 
  }
  
  if (sign == YES) { /*If sign use 'twoCompCon' function before initialize binary number str*/
    intToStr(binaryNum, tempstr);
    twoCompCon(tempstr, strlen(tempstr));
    temp = 24 - strlen(tempstr);
    str[temp] = '\0';
    strcat(str, tempstr);
  }
  
  else{ /*Else without 'twoCompCon'*/
    intToStr(binaryNum, tempstr);
    temp = 24 - strlen(tempstr);
    str[temp] = '\0';
    strcat(str, tempstr);
  }
  
}/*End of function*/







/*** This function use Two-component method on binary number given as paramater (from type string), the size of 
     binary number also need to be send as paramater The changes made to the same binary string given as paramater ***/
void twoCompCon(char * str, int size) {
  int i;

  for (i = 0; i < size; i++){ /* First loop to go through the number */
    if (str[i] == '0'){ 
      str[i] = '1'; /*If digit is 0 replace with 1*/
    } 
    else if (str[i] == '1'){
      str[i] = '0'; /*else digit is 1 replace with 0*/
    }
  } /*End of for loop*/
  
  for (i = size - 1; i >= 0; i--){ /* Second loop to go through the number*/
    if (str[i] == '1') {
      str[i] = '0';
    } else if (str[i] == '0') {
      str[i] = '1';
      break;
    }
  } /*End of for loop*/
}





/*** This function checks the addressing method is compatible with the paramaters given:  opcode, method source and destenition and registers
     if the data is compatible and the is an immediate paramater - a call for 'addimmediate' function, else - incase of incompatibility - an error is sent ***/
void methodCheck(int * method_source, int * method_dest, char * str1, char * str2, int opcode, int * reg1, int * reg2, int * IC) {
  int j = 0; /*Index for loop of to check methods available for this opcode*/
  flag increased = NO; /*Flag to indicate and increase in value needed */


  /*Check for valid methods:*/
  * method_source = whichaddressingmethod(str1, reg1); /*Check addressing method of operand*/
  if (str2 == NULL){ /* If str2 is null - for this opcode only 1 operand required */
    /* initialize methods according to the opcode (1 operand):*/
    *method_dest = * method_source;
    *method_source = NOT_SET;
  }
  else{ /*Loop - compare methods available for this opcode with the operand method:*/
    for (j = 0; j < 3; j++){
      if (commands[opcode].op_source[j] == * method_source){ 
        break;
      }
    }/*End of for loop*/
  }
  if (j == 3){ /*If j is 3 - addressing method is not compatible with this opcode*/
    ERROR = YES;
    printf("ERROR in file %s - line %d: Source addressing method is not compatible with this opcode\n", fileName, lineNumber);
  }

  if (str2 != NULL) /*If there is 2 operands for this opcode - check str2 addressing method*/
   *method_dest = whichaddressingmethod(str2, reg2);
  for (j = 0; j < 3; j++){
    if (commands[opcode].op_dest[j] == * method_dest)
      break; 
  }
  if (j == 3){
    ERROR = YES;
    printf("ERROR in file %s - line %d: Destination addressing method is not compatible with this opcode\n", fileName, lineNumber);
  }

  /*Address stack insert:*/
  if (ERROR != YES){
    /*in those opcodes - method_source and method_dest will be inserted to address stack if methods are relative or direct*/
    if (opcode <= 4 && opcode >= 0){ 
      if ( * method_source == relative || * method_source == direct){ 
        if (addressStackIndex != 0) addressStack = (address_Stack * ) realloc(addressStack, (addressStackIndex + 1) * sizeof(address_Stack));
          if (!addressStack) {
            printf("ERROR in file %s - line %d: Program was unable to realloc memory for address stack\n", fileName, lineNumber);
            ERROR = YES;
          } 
        addressStack[addressStackIndex].address = (( * IC) + 1);
        increased = YES; /* flag that method_source is relative or direct and stacl increase (so method_dest needs to be increased by 2) */
        strcpy(addressStack[addressStackIndex].LABLE, str1); /* copy lable operand to stack */
        addressStackIndex++; /* increase index of stack */
        setPendingIC(); /* Call function to pend increase in IC value (will be increased after adding the main instraction word) */
      }
      if ( * method_dest == relative || * method_dest == direct){
        if (addressStackIndex != 0) addressStack = (address_Stack * ) realloc(addressStack, (addressStackIndex + 1) * sizeof(address_Stack));
          if (!addressStack) {
            printf("ERROR in file %s - line %d: Program was unable to realloc memory for address stack\n", fileName, lineNumber);
            ERROR = YES;
          } 
        (increased == YES) ? (addressStack[addressStackIndex].address = (( * IC) + 2)) : (addressStack[addressStackIndex].address = (( * IC) + 1));
        strcpy(addressStack[addressStackIndex].LABLE, str2); /* copy lable operand to stack */
        addressStackIndex++; /* increase index of stack */
        setPendingIC(); /* Call function to pend increase in IC value (will be increased after adding the main instraction word) */
      }

    }
    /*in those opcodes - only method_dest will be inserted to address stack if method is relative or direct*/
    if (opcode <= 13 && opcode >= 5) { 
      if ( * method_dest == relative || * method_dest == direct){
        if (addressStackIndex != 0) addressStack = (address_Stack * ) realloc(addressStack, (addressStackIndex + 1) * sizeof(address_Stack));
          if (!addressStack) {
            printf("ERROR in file %s - line %d: Program was unable to realloc memory for address stack\n", fileName, lineNumber);
            ERROR = YES;
          }   
        addressStack[addressStackIndex].address = (( * IC) + 1);
        strcpy(addressStack[addressStackIndex].LABLE, str1); 
        addressStackIndex++; 
        setPendingIC(); 
      }
    }

    /* incase of immediate methods - call function addImmediate and increse IC index accordingly:*/
    if ( * method_source == immediate) {
      addImmediate(str1, * IC + 1);
      if ( * method_dest == immediate) {
        addImmediate(str2, * IC + 2);
      }
    } else if ( * method_dest == immediate && str2 != NULL) {
      addImmediate(str2, * IC + 2);
    } else if ( * method_dest == immediate) {
      addImmediate(str1, * IC + 1);
    }
  }

} /* End of function*/





/*** This function programs the binary code to the data table according to paramaters passed ***/
void addCode(int opcode, int method_source, int method_dest, int firstReg, int secondReg, data_type data, int * L) {
  char tempBinary[25]; /*For binary conversion to be used with decimalToBinaryData*/

  if (ERROR == YES) /* return if there was an error in the program */
    return;

  /*opcode 6:*/
  decimalToBinaryData(commands[opcode].opcode, tempBinary);
  strcpy(data_code[IC].opcode, tempBinary + (24 - 6)); /*Copy WORD to data table*/

  /*source 2:*/
  if (opcode <= 13 && opcode >= 5) {
    strcpy(data_code[IC].source, "00"); /*Copy WORD to data table*/
  } else {
    decimalToBinaryData(method_source, tempBinary);
    strcpy(data_code[IC].source, tempBinary + (24 - 2)); /*Copy WORD to data table*/
    if (method_source == immediate) {
      * L = * L + 1;
    }
  }

  /*register_source 3:*/
  if (method_source == diRegister){
    decimalToBinaryData(firstReg, tempBinary);
    strcpy(data_code[IC].register_source, tempBinary + (24 - 3)); /*Copy WORD to data table*/
  } else {
    strcpy(data_code[IC].register_source, "000"); /*Copy WORD to data table*/

  }
  /*dest 2:*/
  if (commands[opcode].op_dest[0] == NOT_SET)
    strcpy(data_code[IC].dest, "00"); /*Copy WORD to data table*/
  else {
    decimalToBinaryData(method_dest, tempBinary);
    strcpy(data_code[IC].dest, tempBinary + (24 - 2)); /*Copy WORD to data table*/
    if (method_dest == immediate) {
      * L = * L + 1;
    }
  }

  /*register_dest 3:*/
  if (method_dest == diRegister) {
    decimalToBinaryData(secondReg, tempBinary);
    strcpy(data_code[IC].register_dest, tempBinary + (24 - 3)); /*Copy WORD to data table*/
  } else {
    strcpy(data_code[IC].register_dest, "000"); /*Copy WORD to data table*/
  }
  /*func 5:*/
  if (commands[opcode].func == NOT_SET) {
    strcpy(data_code[IC].func, "00000"); /*Copy WORD to data table*/
  } else {
    decimalToBinaryData(commands[opcode].func, tempBinary);
    strcpy(data_code[IC].func, tempBinary + (24 - 5)); /*Copy WORD to data table*/
  }
  /*R - Relocatable - code of an address (that is relocatable) and needs to be changed in the linking and loading oporation*/
  if (data == NO_DATA && opcode == 16) {
    strcpy(data_code[IC].A, "0"); 
    strcpy(data_code[IC].R, "1"); /*R flag os turned on*/
    strcpy(data_code[IC].E, "0"); 
  } else {
    strcpy(data_code[IC].A, "1"); /*A flag os turned on*/
    strcpy(data_code[IC].R, "0"); 
    strcpy(data_code[IC].E, "0"); 
  }

  IC++;

} /*End of function*/




/*** Check how digit long is a number passed as paramater, return int with number of digit ***/
int intLength(int num){
  if (num >= 100000) return 5;/* 6 digit */
  if (num >= 10000) return 4;
  if (num >= 1000) return 3;
  if (num >= 100) return 2;
  if (num >= 10) return 1;
  return 0; /* 1 digit */
}





/*** This function add immediate operand to code table***/
void addImmediate(char * str, int IC){

  char tempBinary[25]; /*For binary conversion to be used with decimalToBinaryData*/
  decimalToBinaryData(atoi(str + 1), tempBinary);
  strcpy(data_code[IC].opcode, tempBinary + (24 - 21)); /*Copy WORD to data table*/
  strcpy(data_code[IC].A, "1"); /* A flag is turned*/
  strcpy(data_code[IC].R, "0"); 
  strcpy(data_code[IC].E, "0"); 
  
}




/*** Convert number into string, check second paramater passed 'str'***/
void intToStr(long number, char * str) {
  if (number > 0) { /*Incase number is positive*/
    sprintf(str, "%ld", number);
  } 
  else { /*Incase number is negative - long abs*/
    sprintf(str, "%ld", labs(number));
  }
}








/*** Check if a string contain a number, return boolean ***/
boolean isdigitstr(char * str){
  int index = 0;
  int counternumbers = 0; /*count digits in the string*/
  int counternegative = 0; /*count negative sign*/
  int counterspaces = 0; /*count negative sign*/
  flag first = YES; /*flag for negative sign in number, making sure its first*/

  if (str[index] == '+')
    index++; /*Skip '+'*/
  for (; index < strlen(str); index++) {
    /*Loop until recived string ends*/
    if (isdigit(str[index]) != 0) {
      counternumbers++;
    } else if (str[index] == ' ') {
      counterspaces++;
    } else if (str[index] == '-') {
      counternegative++;
      if (index != 0) {
        /*Flag to check that the sign is in place*/
        first = NO;
      }
    }
  }
  if (counterspaces == 2) {
    if (str[0] == ' ' && str[strlen(str) - 1] == ' ') {
      index = index - 2;
    }
  }
  if (counterspaces == 1) {
    if (str[0] == ' ' || str[strlen(str) - 1] == ' ') {
      index = index - 1;
    }
  }
  if (str[0] == '+')
    index--; /*Skip '+'*/
  /*If the string is a number he will meet all those conditions and return TRUE*/
  if ((counternegative < 2) && (((counternumbers) + (counternegative)) == (index)) && first == YES && counternumbers != 0) {
    return TRUE;
  }
  return FALSE;
}





/*** This function checks if number from data type is valid and adds the number to data table ***/
void addData(char ** str, wordsData * data_table) {
  char * tempStr = NULL; /* Temp string to save numbers of .data (str) */
  int c = 0; /* index of current position in str */
  int copyC = 0; /* Copy index c to be used in strCut */
  char tempBinary[25]; /*For binary conversion to be used with decimalToBinaryData*/
  
  if (*(*str+0) == ','){
    printf("ERROR in file %s - line %d: Misplaced comma in data definition\n", fileName, lineNumber);
    ERROR = YES;
  }
  while (c < strlen( * str) + 1){ /*Loop to go through string of numbers*/
    if ( * ( * str + c) == ',' || copyC == 0){ /*proceed in case there is more numbers*/
      strCut( * str, ',', & copyC, & tempStr); /*Cut every time index position encountered a comma */
      /*check if data is a number*/
      if (isdigitstr(tempStr) == TRUE){ 
        decimalToBinaryData(atol(tempStr), tempBinary); /*Translte*/
        strcpy(data_table[DC].data, tempBinary); /*Copy WORD to data table*/
        DC++; /*increase DC accordingly*/
        c = copyC; /*Copy index to copyC - will be used as pointer to the position of last number*/
      }

      else {
        if (tempStr[0] == ','){
          printf("ERROR in file %s - line %d: Multiple consecutive commas\n", fileName, lineNumber);
          ERROR = YES;
        }
        else{
          printf("ERROR in file %s - line %d: Data number definition is not valid\n", fileName, lineNumber);
          ERROR = YES;
        }
        break;
      }
    } 
    else if (*(*str + c) == '\0'){ /*proceed in case there only one more numbers*/
      strCut(*str, '\0', &copyC, &tempStr);
      /*check if data is a number*/
      if (isdigitstr(tempStr) == TRUE) {
        decimalToBinaryData(atol(tempStr), tempBinary); /*Translte*/
        strcpy(data_table[DC].data, tempBinary); /*Copy WORD to data table*/
        DC++; /*increase DC accordingly*/
        break;
      }
      if (tempStr[0] == ','){
          printf("ERROR in file %s - line %d: Multiple consecutive commas\n", fileName, lineNumber);
          ERROR = YES;
        }
      else{
        printf("ERROR in file %s - line %d: Data number definition is not valid\n", fileName, lineNumber);
        ERROR = YES;
        }
        break;
    }
    
    c++; /*increase c accordingly*/
    
  } /* End of while loop */

}




/*** This function checks if string from data type is valid and adds the string to data table ***/
void addString(char ** str, wordsData * data_table) {
  int c = 0; /* index of current position in str */
  flag isString = NO;
  char tempBinary[25]; /*For binary conversion to be used with decimalToBinaryData*/
  
  if (*(*str+0) == ','){
    printf("ERROR in file %s - line %d: Misplaced comma in data string definition\n", fileName, lineNumber);
    ERROR = YES;
  }
  
  
  /*Str start and ends with '"'*/
  if ( * ( * str) == '"') { 
    if ( * ( * str + (strlen( * str)) - 1) == '"')
      isString = YES; /*Flag that this is a valid string*/
  }
  
  if (isString == YES){ /* If str is a valid string add to data table */
    while (c < strlen( * str) + 1) {
      if ( * ( * str + c) != ' ' && * ( * str + c) != '"' && * ( * str + c) != '\0') {
        decimalToBinaryData( * ( * str + c), tempBinary); /*Translte to binary*/
        strcpy(data_table[DC].data, tempBinary); /*initialize in data table */
        DC++; /*increase DC accordingly*/
      }
      c++;
    }
    strcpy(data_table[DC].data, "000000000000000000000000");
    DC++; /*increase DC accordingly*/
  } 
  else {
    printf("ERROR in file %s - line %d: Data type sring is not a valid string (Missing parentheses)\n", fileName, lineNumber);
    ERROR = YES;
  }
} /*End of function*/


