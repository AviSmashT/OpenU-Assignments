#include "assembler.h"
#include "func.h"


  void firstFileCheck(FILE * file){
    char line [LINE_BUFFER]; /* Maximum length of line in assembly file is 80 */
    char *str1 = NULL; 
    char *str2 = NULL;  
    char *str3 = NULL;
    char *str4 = NULL;
    lineNumber = 1;
    Symbolrows = 0; /*Index of rows in symbol table */
    addressStackIndex = 0; /*Index of addresses stack (will be used in file check)*/
    /*Data counters:*/
    IC = 100; /*Instruction Counter*/
    DC = 0; /*Data Counter (Symbol table)*/
    PendingIC = 0; 
    ERROR = NO;


    /*Creating symbol table and address stack*/
    addressStack = (address_Stack *)malloc(sizeof(address_Stack)); /* Creating stack of addresses */
      if(!addressStack){
        printf("Unable to realloc memory for Addresses stack\n");
        ERROR = YES;
      }
      symbolTable = (symbols *)malloc(sizeof(symbols)); /* Creating the symbol table*/
      if(!symbolTable){
        printf("Unable to realloc memory for Symbol table\n");
        ERROR = YES;
      }
  
  while(fgets(line, MAX_LINE_SIZE , file) != NULL ){ /* read a line */
    int lineLength = 0; /* to set current line length */
    flag islable = NO; /* To indicate if a line have a lable */
    data_type data = NO_DATA; /* To indicate and set the type of data of lable */
    int opcode = NOT_SET; /* To indicate the opcode, if there is any, in the line */
    int method_source = NOT_SET; /* Addressing method of source */
    int method_dest = NOT_SET; /* Addressing method of destenition */
    int firstReg = NOT_SET;
    int secondReg = NOT_SET;
    int L = 0;
    lineIndex = 0; /* Index to current position in the line */
    lineLength = strlen(line); /*Check line length to be used later*/

        
    /***Input: check inpit is valid and preparation for input analysis***/
    if(lineLength > MAX_LINE_SIZE){
      ERROR = YES;
      printf("ERROR in file %s - line %d: Line is too long (limit is 80 character)\n", fileName, lineNumber);
      lineNumber++;
      continue;
    }
    replaceWhiteSpaces(line); /*Replace all types of whitespaces with space*/
    removedoublespaces(line); /*Remove double spaces - if there is 2 or more spaces, it will be replced with onlu one space (to deal better with input)*/
    
    
    
    /*****Start of input analysis:*****/
     if(line[0] == ';' || strlen(line) == 1){ /*Skip line starting with ';' - indicate note */
       lineNumber++; /* Skip line = increase lineNumber */
       continue;
     }
     
     /*Multiple commas check*/
     if(  (multipuleComma(line)) == TRUE){
       lineNumber++;
        continue; 
     }
     
     
      /*entry check:*/
     strCut(line, ' ', &lineIndex, &str1); /* Copy first word in line to str1 (until ' ' is reached)*/
     if (strcmp(str1 , ".entry") == 0){ /*Check if the first element in line is '.entry' - if it is - skip */
       free(str1); /*free memory pointed by str1*/
       lineNumber++; /* Skip line = increase lineNumber */
       continue;
     }
     /***End of entry check***/
     
     
     
     /*extern line check:*/
    if (strcmp(str1 , ".extern") == 0){ /*Check if the first element in line is '.extern' */
      strCut(line, '\0', &lineIndex, &str2); /* Copy extern to str2 */
      if(str2 != NULL){ /*If str2 is null than the extern lable is missing*/
      if(isLableRef(str2) == TRUE){ /*Check that str2 can be a lable*/
        addSymbol(str2 , 0 , 0 , EXTERNAL ); /*Add to lable to symbol table*/
        free(str1); /*free memory pointed by str1*/
        str1 = NULL;
        if(str2 != NULL){
          free(str2); /*free memory pointed by str2*/
          str2 = NULL;
        }
        lineNumber++; /* Skip line = increase lineNumber */
        continue;
      }
      else{ /*If str2 can't be a lable = error*/
        printf("ERROR in file %s - line %d: extern lable definition is not valid\n", fileName, lineNumber);
        ERROR_LINE_SKIP
      }
      opcode = NOT_SET; /*Set opcode to skip switch later (skip to next line)*/
      }
      else{
        printf("ERROR in file %s - line %d: extern lable definition is missing\n", fileName, lineNumber);
        ERROR_LINE_SKIP
      }
    }
    /***End of extern line check***/
    
    
    
    /***Data line check***/
    data = isData(str1); /* Check if first element in line is '.string' or '.data' */
    if(data != NO_DATA){ /* If data or string... */
      if(data == DATA){ /*If .data*/
        strCut(line, '\0', &lineIndex, &str2); /* copy all .data from line to str2 */
        if(str2 != NULL){ /*If str2 is null than data sequence is missing*/
          addData(&str2, data_table); /* Add data to data table */
          opcode = NOT_SET; /*to skip switch*/
        }
        else{
          printf("ERROR in file %s - line %d: Invalid data or string sequence is missing\n", fileName, lineNumber);
          ERROR_LINE_SKIP
        }
      }
      else if(data == STRING){ /*If .string*/
        strCut(line, '\0', &lineIndex, &str2); /* copy all .string from line to str3 */
        if(str2 != NULL){ /*If str2 is null than data sequence is missing*/
          addString(&str2, data_table); /* Add string to data table */
          opcode = NOT_SET; /*Set opcode to skip switch later (skip to next line)*/
        }
        else{
          printf("ERROR in file %s - line %d: Invalid data or string sequence is missing\n", fileName, lineNumber);
          ERROR_LINE_SKIP
        }
      }
     opcode = NOT_SET; /*Set opcode to skip switch later (skip to next line)*/
    }
    /***End of data line check***/



    /***str1 is lable check***/
    if((isLable(str1)) != FALSE){ /*Check that str1 can be a lable*/
      islable = YES; /* Set flag to proceed accordingly */
    }
    if(islable == YES){ /* If str1 is a lable check if str2 is (1.) .data/.string or (2.) opcode */


        strCut(line, ' ', &lineIndex, &str2); /*If it haven't - Cut second word in line*/
        if(str2 != NULL){ /*If str2 is null than instraction is missing*/      /*Check that current line has not ended*/
          opcode = whichOpcode(str2, &data);  /*Check which opcode is called in str2 (if opcode is not called in this line - function return "NOT_SET")*/ 
          addSymbol(str1 , DC , IC , data); /*Add lable to symbol table*/          
        }
        else{
          printf("ERROR in file %s - line %d: No instraction after lable \n", fileName, lineNumber);
          ERROR_LINE_SKIP
        }
      

       
      /**Check incase str2 is .data  or .string:**/
      if(data == DATA){ /*If .data*/
        strCut(line, '\0', &lineIndex, &str3); /* copy all .data from line to str3 */
        if(str3 != NULL){ /*If str3 is null than data sequence is missing*/
          addData(&str3, data_table); /* Add data to data table */
          opcode = NOT_SET; /*Set opcode to skip switch later (skip to next line)*/        
        }
        else{
          printf("ERROR in file %s - line %d: Invalid data or string sequence is missing\n", fileName, lineNumber);
          ERROR_LINE_SKIP
        }
      }
      else if(data == STRING){ /*If .string*/
        strCut(line, '\0', &lineIndex, &str3); /* copy all .string from line to str3 */
        if(str3 != NULL){ /*If str3 is null than data sequence is missing*/
          addString(&str3, data_table); /* Add string to data table */
          opcode = NOT_SET; /*Set opcode to skip switch later (skip to next line)*/        
        }
        else{
          printf("ERROR in file %s - line %d: Invalid data or string sequence is missing\n", fileName, lineNumber);
          ERROR_LINE_SKIP   
        }
     }/**End of data check for str2**/
   } /***End of str1 is lable check***/
   
  
   /*If str1 is not a lable - then the line starts with opcode:*/
    else{
     opcode = whichOpcode(str1, &data); /*Check which opcode is called*/
   }
   
   if(opcode == NO_OPCODE && data == NO_DATA ){
     printf("ERROR in file %s - line %d: Opcode does not exist\n", fileName, lineNumber);
     ERROR_LINE_SKIP
   }



   /***Opcode swich:***/
   switch (opcode){ 
     /*opcodes with 2 operands:*/
     case 0: /* Opcode - "mov" */
     case 1: /* Opcode - "cmp" */
     case 2: /* Opcode - "add" */
     case 3: /* Opcode - "sub" */
     case 4: /* Opcode - "lea" */
     
       /***Copy operands to srings***/ 
       if(islable == YES){ /*If line has a lable - copy to str3 and str4 (The operands)*/ 
           strCut(line, ',', &lineIndex, &str3); /*One comma in between 2 operands*/ 
             if(ERROR == YES) {ERROR_LINE_SKIP} /*skip if strCut encountered an error*/      

           strCut(line, ' ', &lineIndex, &str4); 
             if(ERROR == YES) {ERROR_LINE_SKIP} /*skip if strCut encountered an error*/
           if(str4 == NULL){ /*If str4 is null than operand is missing*/
             printf("ERROR in file %s - line %d: A call for opcode was made but one or more operand missing \n", fileName, lineNumber);
             ERROR_LINE_SKIP
           }
         
       }
       else{ /*Else - copy to str3 and str4 (The operands)*/ 

           strCut(line, ',', &lineIndex, &str2); /*One comma in between 2 operands*/ 
         

           strCut(line, ' ', &lineIndex, &str3); 
         
       } /***End of Copy operands to srings***/
      
       
       
       if(str2 == NULL || str3 == NULL){ /*If st2, str3 or str4 is null than operand is missing*/
         printf("ERROR in file %s - line %d: A call for opcode was made but one or more operand missing \n", fileName, lineNumber);
         ERROR_LINE_SKIP
       }
       
       
       
       /***Check that structure of line is valid assembly code and add code to instructions table***/ 
       if(islable == YES){ /*If there is a lable in line*/
         methodCheck( &method_source, &method_dest, str3, str4, opcode, &firstReg, &secondReg, &IC); /* Check valid assembly structure and add immediate operands to table*/
         if(ERROR == NO){
         addCode(opcode, method_source, method_dest, firstReg, secondReg, data, &L); /* Code the first WORD of instruction */
         pendingIncreaseIC(); /*increase IC according to the words already coded in 'methodCheck' (immediate operands) */
         IC = L + IC; /*Add IC + L (Reminder: L - The number of additinal words needed to code this instruction - those words will be coded later)*/
         }
       }
       else{ /*Else - if there is not a lable in line*/
         methodCheck( &method_source, &method_dest, str2, str3, opcode, &firstReg, &secondReg, &IC);
         if(ERROR == NO){
         addCode(opcode, method_source, method_dest, firstReg, secondReg, data, &L);
         pendingIncreaseIC();
         IC = L + IC;
        }
       }
  
       break; /*Break switch*/	    
     /*opcodes with 1 operand:*/
     case 5: /* Opcode - "clr" */
     case 6: /* Opcode - "not" */
     case 7: /* Opcode - "inc" */
     case 8: /* Opcode - "dec" */
     case 9: /* Opcode - "jmp" */
     case 10: /* Opcode - "bne" */
     case 11: /* Opcode - "jsr" */
     case 12: /* Opcode - "red" */
     case 13: /* Opcode - "prn" */
     
     
       /***Copy operand to str2 or str3***/ 
       if(islable == YES){ /*If there is a lable in line*/

           strCut(line, '\0', &lineIndex, &str3); /*Line has a lable - copy operand to str3*/
             if(ERROR == YES) {ERROR_LINE_SKIP} /*skip if strCut encountered an error*/
           if(str3 == NULL){ /*If str3 is null than operand is missing*/
             printf("ERROR in file %s - line %d: A call for opcode was made but the operand is missing \n", fileName, lineNumber);
             ERROR_LINE_SKIP
           }
         
       }
       else{ /*Else - if there is not a lable in line*/
           strCut(line, '\0', &lineIndex, &str2); /*Line has a lable - copy operand to str2*/
             if(ERROR == YES) {ERROR_LINE_SKIP} /*skip if strCut encountered an error*/
           if(str2 == NULL){ /*If str2 is null than operand is missing*/
             printf("ERROR in file %s - line %d: A call for opcode was made but the operand is missing \n", fileName, lineNumber);
             ERROR_LINE_SKIP
           }
         
       } /***End of Copy operands to srings***/


       /***Check that structure of line is valid assembly code and add code to instructions table***/ 
       if(islable == YES){ /*If there is a lable in line*/
         methodCheck( &method_source, &method_dest, str3, NULL, opcode, &firstReg, &secondReg, &IC); /* Check valid assembly structure and add immediate operands to table*/
         if(ERROR == NO){
         secondReg = firstReg; /*Initialized destenition register*/
         addCode(opcode, method_source, method_dest, firstReg, secondReg, data, &L); /* Code the first WORD of instruction */
         pendingIncreaseIC(); /*increase IC according to the words already coded in 'methodCheck' (immediate operands) */
         IC = L + IC; /*Add IC + L (Reminder: L - The number of additinal words needed to code this instruction - those words will be coded later)*/
         }
       }
       else{ /*Else - if there is not a lable in line*/
         methodCheck( &method_source, &method_dest, str2, NULL, opcode, &firstReg, &secondReg, &IC);
         if(ERROR == NO){
         secondReg = firstReg;
         addCode(opcode, method_source, method_dest, firstReg, secondReg, data, &L);
         pendingIncreaseIC();
         IC = L + IC;
         }
       }

       break; /*Break switch*/
     /*opcodes with no operands:*/
     case 14: /* Opcode - "rts" */
     case 15: /* Opcode - "stop" */	
     
     if(lineIndex < lineLength){
       if(line[lineIndex] != ' '){ /*text after those opcode are not allowed (only white spaces allowed)*/
         ERROR = YES;
         printf("ERROR in file %s - line %d: Extraneous text after end of instraction\n", fileName, lineNumber);
         break;       
       }
     }
     
       if(opcode == 14){ /* if Opcode is "rts" code directly to instruction table */
         strcpy( data_code[IC].opcode, "001110000000000000000100"); /*Copy WORD to data table*/
       }
       else if (opcode == 15){ /* if Opcode is "stop" code directly to instruction table */
         strcpy( data_code[IC].opcode, "001111000000000000000100"); /*Copy WORD to data table*/
       }
       IC++; /*increase IC accordingly*/
       
       break;
       
     default:
       break;
   }/*end of switch*/
   
   
   /***Free memory allocated strings*:**/
   if(str1 != NULL){
     free(str1);
     str1 = NULL;
   }
   if(str2 != NULL){
     free(str2);
     str2 = NULL;
   }
   if(str3 != NULL){
     free(str3);
     str3 = NULL;
   }
   if(str4 != NULL){
     free(str4);
     str4 = NULL;
   }


   lineNumber++; /*increase line number index*/
   } /*While fgets loop*/
   
   
  } /*end of function*/





  void secondFileCheck(FILE * file){
    char line [LINE_BUFFER]; /* Maximum length of line in assembly file is 80 */
    char *str1 = NULL; 
    char *str2 = NULL; 
    int lineNumber = 0;
    
    while(fgets(line, MAX_LINE_SIZE, file) != NULL ){ /* read a line */
      int i = 0;
      flag addable = NO;
      lineIndex = 0; /* Index to current position in the line */
      
      strCut(line, ' ', &lineIndex, &str1); /*Cut first word in line*/
      
      
      /*Entry line check: */
      if (strcmp(str1 , ".entry") == 0){ /*Check if the first element in line is '.entry' */
        strCut(line, '\0', &lineIndex, &str2); /* Copy entry lable to str2 */
      if(isLableRef(str2) == TRUE){ /*Check that str2 can be a lable*/
        char temp[32]; /*Temp varible to compare lables*/
        
        /***insert entry type to symbol:***/
        for(i = 0; i < Symbolrows ; i++){ /*Loop to go through symbal table and check if this lable exist*/
          strcpy(temp , symbolTable[i].symbol_name);
          if(temp[strlen(temp)-1]  == ':'|| temp[strlen(temp)-1]  == ' '){
            temp[strlen(temp)-1] = '\0'; /*Remove ':' from lable*/ 
          }
          if (strcmp(str2, temp) == 0){ /*compare lable to be added entry type with the lables in symbol table*/
            addable = YES; /*if lable does not exist in the symbol table - it's addable*/
            break; /*Break loop of compare*/
          }
        }
        
        if(addable == YES){ /*If lable is addable - initialize entry_type in this symbol*/ 
          symbolTable[i].entry_type = ENTRY; 
        }
        else{ /*If lable is not addable - ERROR*/ 
          ERROR = YES;
          printf("ERROR in file %s - line %d: entry lable was suggested but this lable does not exist\n", fileName, lineNumber);
        }
      } 
      } /*End of entry line check*/
      
      /***Free memory allocated strings*:**/
      if(str1 != NULL){
        free(str1);
        str1 = NULL;
      }
      if(str2 != NULL){
        free(str2);
        str2 = NULL;
      }
      
      lineNumber++;/*increase line number index*/
    }/***End of while fgets loop**/
    
    if(ERROR == NO){
      addMissingCode(addressStackIndex); /*Codding the missing WORDS to instructions table*/
    }    

  } /*End of function*/
  
  
  
  
  /*Adding words not coded on the first time checking the file. paramater is the total number of Address missing from instruction table*/
  void addMissingCode(int FinalStackIndex){    
    int i; /*Index to be used in loop*/
    char temp[32]; /*Temp varible to later be used to compare lables */
    addressStackIndex = 0; /*Reset index of address stack to go through the data in stack (Reminder: Address of the missing instructions codes)*/
    ExtC = 0;
    
    while(FinalStackIndex >= 0){ /*Run loop through all address stored in address stack*/
      for(i = 0; i < Symbolrows ; i++){ /*Loop to go through symbal table*/
        strcpy(temp,symbolTable[i].symbol_name);
          if(temp[strlen(temp)-1]  == ':'|| temp[strlen(temp)-1]  == ' '){
            temp[strlen(temp)-1] = '\0'; /*Remove ':' from lable*/ 
          }
          if(addressStack[addressStackIndex].LABLE[0] == '&'){
        if (strcmp( addressStack[addressStackIndex].LABLE+1, temp ) == 0){ /*compare lable to be insert to with the lables in symbol table*/
          break; /*If there is a match - break*/
        }
          
          }
        else if (strcmp( addressStack[addressStackIndex].LABLE, temp ) == 0){ /*compare lable to be insert to with the lables in symbol table*/
          break; /*If there is a match - break*/
        }
      }
      
      /*Adding External WORD code to instruction table:*/
      if(symbolTable[i].symbol_type == EXTERNAL){
        strcpy( data_code[(addressStack[addressStackIndex].address)].opcode, "00000000000000000000000"); /*Copy WORD to data table*/
        strcpy( data_code[(addressStack[addressStackIndex].address)].E, "1" ); /*Tuen on E flag*/
        FinalStackIndex--; /*Decrese index by 1 (Reminder: loop stops when index is 0) */
        addressStackIndex++; /*increase index by 1 (next address in address stack) */
        ExtC++; /*Count how many external symbol type there is*/
      }
      /*Adding relative address WORD code to instruction table:*/
      else if(addressStack[addressStackIndex].LABLE[0] == '&' ){
        char tempBinary[WORD_LENGTH]; /*For binary conversion to be used with decimalToBinaryData*/     
        decimalToBinaryData( (symbolTable[i].symbol_address + 1) - addressStack[addressStackIndex].address ,tempBinary); /*Convert address to binary and store in tempBinary*/
        /*Copy WORD to data table:*/
        strcpy( data_code[(addressStack[addressStackIndex].address)].opcode, tempBinary+(24-21)); 
        strcpy( data_code[(addressStack[addressStackIndex].address)].A, "1"); /*Tuen on A flag*/
        strcpy( data_code[(addressStack[addressStackIndex].address)].R, "0" ); 
        strcpy( data_code[(addressStack[addressStackIndex].address)].E, "0"); 
        FinalStackIndex--;
        addressStackIndex++;
      }
      /*Adding direct address WORD code to instruction table:*/
      else{
        char tempBinary[WORD_LENGTH]; /*For binary conversion to be used with decimalToBinaryData*/
        decimalToBinaryData( symbolTable[i].symbol_address , tempBinary); /*Convert address to binary and store in tempBinary*/    
        /*Copy WORD to data table:*/
        strcpy( data_code[ (addressStack[addressStackIndex].address) ].opcode, tempBinary+(24-21)); 
        strcpy( data_code[(addressStack[addressStackIndex].address)].A, "0" ); 
        strcpy( data_code[(addressStack[addressStackIndex].address)].R, "1" ); /*Tuen on R flag*/
        strcpy( data_code[(addressStack[addressStackIndex].address)].E, "0"); 
        FinalStackIndex--;
        addressStackIndex++;
      }
    } /*End of while loop*/
 } /*End of function*/
 

/*** This function pend an increase to varible IC to be called later to 'pendingIncreaseIC' ***/
 void setPendingIC(){
   PendingIC++;
 }
 
 /*** This function increase IC if pendding is set ***/
 void pendingIncreaseIC(){
   while( PendingIC > 0 ){
     IC++;
     PendingIC--;
   }
 }
