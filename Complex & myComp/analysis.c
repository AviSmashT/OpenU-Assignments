#include "complex.h"
flag firstParamCompare(char *str_param1, linkCompNums *vars);        
flag secondParamCompare(char *str_param2, linkCompNums *vars);
static int paramCon = 0;
static int i, j, k, l = 0; 
/*Indexes:
i index for userinput sring
j index of command to be used
k index of first complex number to be used 
l index of second complex number to be used
*/

      /*Extrect command name:*/
      flag cmdExtrect(char **userInput, char **str_cmd){
        int stringIndex = 0;
	  for (i = 0; i < (strlen(*userInput)); i++){/*loop will check userInput will stop on return flag*/
	    /*if stringIndex is 0 - create a string*/
            if (stringIndex == 0){
              *str_cmd = (char*)malloc(sizeof(char));
            }
            /*expend string only if non-space character or end of string (for '\0')*/
            else if((!isspace(*(*userInput+i))) || (i+1) == (strlen(*userInput))){ 
	      *str_cmd = (char*)realloc(*str_cmd, (1 + stringIndex) * sizeof(char));
            }
            
            
	    if(!isspace(*(*userInput+i))){ /*if input string is while spaces - skip , else - copy to str_cmd (isspace return 0 if character is not space)*/
	      if (!*str_cmd) { /*Quit if realloc failed*/
	        printf("Unable to realloc\n");
	        return NO;/*Flag to stop this check*/
	        break;
	      }
	      *(*str_cmd+stringIndex) = *(*userInput+i); /*copy and next ++*/
	      stringIndex++;
	    }
	    /*Extrect  paramaters(paramCon+1) only if there is white spaces after a non-white spaces*/
	    else if (i != 0 && (isspace(*(*userInput+(i-1)) )==0) && (isspace(*(*userInput+i))!=0) ){
	      paramCon++; /*Count+1 parameter*/
	      *(*str_cmd+stringIndex) = '\0'; /*Mark end of string*/
	      break;
	    }
	    if((i+1) == (strlen(*userInput))){ /*incase end of string*/
              *(*str_cmd+stringIndex) = '\0'; /*Mark end of string*/
            }
            
          }/*END OF for loop to extrect command name*/
          
        return YES;
      }
	        
	/*Compare user input to command names*/          
        flag cmdCompare (char *userInput, char *str_cmd, linkFunctions *commands){ 	        
          for (j = 0; ((int)commands[j].functionIndex != LINK_CMD_LENGTH); j++){
            if (strcmp(str_cmd, (char*)commands[j].name) == 0) {
              break; /*If there is a match - break (index i will indicate the command we will use (with switch))*/
	    }
	  }
	  if(j == 9){ /*If i equals 9, the name of function doesn't exist */
	    printf("Undefined command name\n");
	    return NO;
	  }
	  if((i+1 == (strlen(userInput))) && j != 8){ /*incase end of string and command is not stop*/
	    printf("Missing paramater\n");
            return NO;
          }
          return YES;
        }/*END OF Compare user input to command names*/
        
        
        
        

	/*Extrect First paramater*/   
        flag firstParamExtrect( char **userInput, char **str_param1){
	  int stringIndex = 0; /*Reset subString index*/
          flag paramspace = NO;
	  for(i++ ; i < (strlen(*userInput)); i++){ 
	    if(j == 8 && (!isspace(*(*userInput+i)))){ /*If the command is stop and there is a any charctor as paramater, return false*/
	      printf("Extraneous text after end of command\n");
	      return NO;
	    }
	    /*if stringIndex is 0 and *userInput+i in not space - create a string:*/
            if(stringIndex == 0 && isspace(*(*userInput+i))==0){ 
              *str_param1 = (char*)malloc(sizeof(char));
            }/*expend string only if non-space character or end of string (for '\0'):*/
            else if(isspace(*(*userInput+i))==0 || ((i+1) == (strlen(*userInput)) && (stringIndex != 0))){ 
              *str_param1 = (char*)realloc(*str_param1, (1 + stringIndex) * sizeof(char));
                /*Quit if realloc failed:*/
	        if (!*str_param1){ 
	          printf("Unable to realloc\n"); 
	          return NO;
                }
            } 
           /*End of string allocation*/        
            
            /*Illegal comma Check - If there is a comma before first paramater inserted:*/
	    if((*(*userInput+(i)) == ',') && stringIndex == 0){
	      printf("Illegal comma\n");	 
	      *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/
	      return NO; /*input is NOT VALID - therefore will not be sent to function*/
	    }
	    /*Check White spaces after input: |Example: "5  5" won't be allowed, but "5    ," will be allowed|*/
	    else if(isspace(*(*userInput+(i-1)))!=0 && isspace(*(*userInput+i))==0 && stringIndex > 0){
	      paramspace = YES; /*Flag if there is spaces after an input (non-white spaces) to paramater*/
	    }
	    /*if input string is not white spaces or ',' - copy to str_param*/
	    if (isspace(*(*userInput+i))==0 && *(*userInput+i) != ','){
	      if(paramspace == YES){ /*IF flas is YES - error massage and return false*/
	        *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/
	        if(j == 1 || j == 7){
	          printf("Extraneous text after end of command\n");
	          return NO;
	        }
	        if((j >= 2 && j <= 6) || j == 0){
	          printf("Missing comma\n");
	          return NO;
	        }
	      }
	      *(*str_param1+stringIndex) = *(*userInput+i); /*Write character on substring*/
	      stringIndex++; /*Next index at sting*/
	    }
	    /*Incase of end of user input string - various ways to end program:*/	      
	    if((i+1) == (strlen(*userInput))){ /*check if its end of stirng*/		 
	      if(*(*userInput+i) == ','){ 
	        /*if There is a comma - error massage depending on the command:*/	     
	        if(j == 1 || j == 7 ){ /*Case "Extraneous text after end of command"*/
	          printf("Extraneous text after end of command\n");
	          *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/
	          return NO;
	        }
	      }
	      
	      if((j == 0 || (j >= 2 && j <= 6)) && (stringIndex > 0)){ /*Case "Missing paramater" for commands that require more than 1 parameter*/
	        printf("Missing paramater\n");
	        *(*str_param1+stringIndex) = '\0';           
	        return NO;
	      }	      
	      if(stringIndex == 0 && isspace(*(*userInput+i))!=0){ /*Case "Missing paramater" - when string for param 1 contain spaces only*/
	      *str_param1 = NULL;
	      printf("Missing paramater\n");
	      return NO;
	      }
	      *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/  
	      /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	      If not, flag and send an error massage:*/
	      if((j >= 0 && j <= 6) || j == 7){
	        if(firstParamCompare(*str_param1, getVars()) != YES){ /*Checking complex num*/
	          return NO;
	        }
	      }
	      break;
	    }
	    /*if there is another comma, we can proceed to check next parameter:*/
	    else if (*(*userInput+i) == ','){
	      if(*(*userInput+i) == ','){
	        if(j == 1 || j == 7 ){ /*If command is 1 or 7 - this is extraneous text */
	          printf("Extraneous text after end of command\n");
	          *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/
	          return NO;
	        }
	      }
	      paramCon++; /*Count+1 parameter*/
	      *(*str_param1+stringIndex) = '\0'; /*Mark end of string*/ 
	      /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	      If not, flag and send an error massage:*/ 
	      if(j >= 0 && j <= 6){
	        if(firstParamCompare(*str_param1, getVars()) != YES){
	          return NO;
	        }
	      }
	      else if( j == 7 ){
	        if(firstParamCompare(*str_param1, getVars()) != YES){
	          return NO;
	        }
	      }
	      break;       
	    }
	  }/*END OF for loop to extrect First paramater*/ 

        return YES;

        }	        
	        
	       

        /*Extrect second paramater*/
        flag seconedParamExtrect( char **userInput, char **str_param2){
	  int stringIndex = 0; /*Reset subString index*/
          flag paramspace = NO;
	  for (i++ ; i < (strlen(*userInput)) && (j != 8); i++){ 
	    /*if stringIndex is 0 and *userInput+i in not space - create a string:*/
	    if(stringIndex == 0 && isspace(*(*userInput+i)==0)){
	      *str_param2 = (char*)malloc(sizeof(char));
	    }
            /*Extend string if userInput[i] is num, char or comma OR if end of usernput string:*/
	    else if(isspace(*(*userInput+i))==0 || ((i+1) == (strlen(*userInput)) && (stringIndex != 0))){
	      *str_param2 = (char*)realloc(*str_param2, (1 + stringIndex) * sizeof(char));
	      /*Quit if realloc failed:*/
	      if (!*str_param2){ 
	        printf("Unable to realloc\n");
	        return NO;
	      }
	    }
	    /*End of string allocation*/ 
	    
              /*Multiple consecuitive commas check: |Example: ",," or ",  ,"|*/
              /*this will be indicated If there is a comma before first paramater inserted*/
	      if( *(*userInput+i) == ',' && stringIndex == 0){
	         printf("Multiple consecuitive commas\n");
	         *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/
	         return NO; /*input is NOT VALID - therefore will not be sent to function*/
	         break; /*Break loop to stop analyzing input*/
	      }
	      /*Check White spaces after input:*/
	      else if(isspace(*(*userInput+i-1))!=0 && isspace(*(*userInput+i))==0 && stringIndex > 0){
	        paramspace = YES; /*Flag if there is spaces after an input (non-white spaces) to paramater*/
	      }
	      /*if input string is not white spaces or ',' - copy to str_param*/
	      if (isspace(*(*userInput+i))==0 && *(*userInput+i) != ','){
	        if(paramspace == YES){ /*IF flas is YES - error massage and return false*/
	          *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/
	            if(j >= 2 && j <= 6){
	              printf("Extraneous text after end of command\n");
	              return NO;
	              break;
	              if(j == 0){
	                printf("Missing comma\n");
	                return NO;
	                break;
	              }
	            }
	        }
	        *(*str_param2+stringIndex) = *(*userInput+i); /*Write character on substring*/
	        stringIndex++; /*Next index at sting*/
	      }
	      /*Incase of end of user input string - various ways to end program:*/	      
	      if((i+1) == (strlen(*userInput))){ /*check if its end of stirng*/	
	        /*if There is a comma - error massage depending on the command:*/
	        if(*(*userInput+i) == ','){ 
	          if(j >= 2 && j <= 6){
	            printf("Extraneous text after end of command\n");
	            return NO;
	            *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/
	            break;
	          }
	      	  if(j == 0 ){
	      	    printf("Missing paramater\n");
	      	    return NO;
	      	    *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/
	      	    break;
	      	  }
	        }
	        *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/ 
	        /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	        If not, flag and send an error massage:*/
	        if( (j >= 2 && j <= 3) || j == 6 ){
	          if(secondParamCompare(*str_param2, getVars()) != YES){ /*Checking complex num*/
	            return NO;
	          }
	        }
	        else if( (j >= 4 && j <= 5) || j == 0 || j == 7 ){
	          if(isdigitstr(*str_param2) != TRUE){ /*Checking if valid number*/
	          printf("Invalid parameter - Not a number\n");
	          return NO;
	          }
	        }
	                 
                break;
              }
              /*if there is another comma, we can proceed to check next parameter:*/
              else if (*(*userInput+i) == ','){ 
                if(j >= 2 && j <= 6){ /*If command is 2-6 - this is extraneous text */
                  printf("Extraneous text after end of command\n");
                  return NO;
                  *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/
                  break;
                }
	        paramCon++; /*Count+1 parameter*/
	        *(*str_param2+stringIndex) = '\0'; /*Mark end of string*/    
	        /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	        If not, flag and send an error massage:*/
	        if( (j >= 2 && j <= 3) || j == 6 ){
	          if(secondParamCompare( *str_param2,  getVars()  ) != YES){
	            return NO;
	          }
	        }
	        else if( (j >= 4 && j <= 5) || j == 0 || j == 7 ){
	          if(isdigitstr(*str_param2) != TRUE){
	          printf("Invalid parameter - Not a number\n");
	          return NO;
	          }
	        }
	      break;       
	      }
	  }

          return YES;
        }	        
	        
	        
	 /*Extrect third paramater*/ 
        flag thirdParamExtrect( char **userInput, char **str_param3){
	  int stringIndex = 0; /*Reset subString index*/
          flag paramspace = NO; 
	  for (i++ ; i < (strlen(*userInput)) && (j != 8); i++){
            /*if stringIndex is 0 and *(*userInput+i) in not space - create a string:*/
            if(stringIndex == 0 && isspace(*(*userInput+i))==0){ 
              *str_param3 = (char*)malloc(sizeof(char));
            }
            /*Extend string if userInput[i] is num, char or comma OR if end of usernput string:*/
            else if(isspace(*(*userInput+i))==0 || ((i+1) == (strlen(*userInput)) && (stringIndex != 0))){ 
              *str_param3 = (char*)realloc(*str_param3, (1 + stringIndex) * sizeof(char));
              /*Quit if realloc failed:*/
	      if (!*str_param3){ 
	        printf("Unable to realloc\n");
	        return NO;
	        break;
              }
            }
            /*End of string allocation*/
            
            /*Multiple consecuitive commas check*/
	    if( (*(*userInput+i) == ',') && stringIndex == 0 ){/*If there is a comma before first paramater - print and start over*/
	      printf("Multiple consecuitive commas\n");
	      *(*str_param3+stringIndex) = '\0'; /*Mark end of string*/
	      return NO;
	      break;
	    }
	    /*Check White spaces after input:*/
	    else if(isspace(*(*userInput+i)-1)!=0 && isspace(*(*userInput+i))==0 && stringIndex > 0){
	      paramspace = YES; /*Flag if there is spaces after an input (non-white spaces) to paramater*/
	    }
	    /*if input string is white spaces or ',' - skip, else copy to str_param*/
	    if(isspace(*(*userInput+i))==0 && *(*userInput+i) != ','  ){
	      if(paramspace == YES){
	        *(*str_param3+stringIndex) = '\0'; /*Mark end of string*/
	         if(j == 0){
	           printf("Extraneous text after end of command\n");
	           return NO;
	           break;
	         }
	      }
	      *(*str_param3+stringIndex) = *(*userInput+i);
	      stringIndex++;
	    }	        
	    
	    /*incase this is the end of string:*/
	    if((i+1) == (strlen(*userInput))){ 
	      if(*(*userInput+i) == ','){     	     
	        if(j == 0 ){
	          printf("Extraneous text after end of command\n");
	          return NO;
	          break;	      
	        }	                      
	      }
	      *(*str_param3+stringIndex) = '\0'; /*Mark end of string*/   
	      /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	      If not, flag and send an error massage:*/
	        if( j == 0 ){
	          if(isdigitstr(*str_param3) != TRUE){
	            printf("Invalid parameter - Not a number\n"); 
	            return NO;
	          }
	        }       	 
	      break;
	    }  	        
	    /*if there is another comma, we can proceed to check next parameter:*/
	    else if (*(*userInput+i) == ','){
	      paramCon++;/*Count+1 parameter*/
	      *(*str_param3+stringIndex) = '\0'; /*Mark end of string*/ 
	      /*We reached the point of end parameter check, we will use the function to check if the paramater is valid to this command
	      If not, flag and send an error massage:*/
	        if( j == 0 ){
	          if(isdigitstr(*str_param3) != TRUE){
	            printf("Invalid parameter - Not a number\n"); 
	            return NO;
	          }
	        }
	      break;
	    }
	  }
	  
          return YES;
        }
        
        
        
        /*Compare user input of first paramater to complex number variables*/
        flag firstParamCompare(char *str_param1, linkCompNums *vars){ 	        
          for (k = 0; k != LINK_VARS_LENGTH ; k++){  /*check var array (with comp variables - linkCompNums)*/
            if (strcmp(str_param1, (char*)vars[k].name) == 0){ /*if variable found, save in index j*/
              break;
            }
          }
          if (k == 7) { /*if variable haven't found - error message and return NO, else return YES*/
            printf("Undefined complex variable\n");
            return NO; 
          }
          return YES;
        }
        
        
        
        /*Compare user input of second paramater to complex number variables*/
        flag secondParamCompare(char *str_param2, linkCompNums *vars){ 	        
          for (l = 0; l != LINK_VARS_LENGTH; l++){  /*check var array (with comp variables - linkCompNums)*/ 
            if (strcmp(str_param2, (char*)vars[l].name) == 0){ /*if variable found, save in index l*/
              break;
            }
          }
          if (l == 7) { /*if variable haven't found - error message and return NO, else return YES*/
            printf("Undefined complex variable\n");
            return NO; 
          }
          return YES;
        }



        /*Use ParamCon to check if paramater is missing*/
        flag paramEquals(linkFunctions *commands){
	  if (((int)commands[j].numOfParams) > (paramCon)){
	    printf("Missing paramaters\n");
	    return NO;
	  }	  
          if(paramCon >= 4){
            printf("Extraneous text after end of command\n");
            return NO;
          }
          return YES;
        }



        /*Passing data of indexes via paramaters from this file to main 
        (Those indexes have will indicate the which command and which varible to use after analyzing):*/
        void tansData(int *cmdIndex, int *param1Index, int *param2Index){
          *cmdIndex = j; /*cmd index*/
          *param1Index = k; /*First comp index*/
          *param2Index = l; /*Second comp index*/
        }



        /*Rest all static indexes to 0 (Used in main when checking new command form user):*/
        void rest(void){
          i = 0;
          j = 0;
          k = 0;
          l = 0;
          paramCon = 0;
        }



        
        /*Check if a string contain a number, return boolean:*/
        boolean isdigitstr(char* str){
	  int index = 0;
	  int counternumbers = 0; /*count digits in the string*/
	  int counterdouble = 0; /*count dots (indicate double)*/
	  int counternegative = 0; /*count negative sign*/
	  flag first = YES; /*flag for negative sign in number, making sure its first*/

	  for (index = 0; index < strlen(str); index++) { /*Loop until recived string ends*/
	    if (isdigit(str[index]) != 0) {
	       counternumbers++;
	     }
	   
	     else if (str[index] == '.') {
	       counterdouble++;
	     }
	     else if (str[index] == '-') {
	       counternegative++;
	       if(index != 0){
	         first = NO;
	       }
	     }
	  }
	  /*If the string is a number he will meet all those conditions and return TRUE*/
	  if ((counterdouble < 2) && (counternegative < 2) && (((counternumbers)+(counterdouble)+(counternegative)) == strlen(str)) && first == YES && counternumbers != 0){
	    return TRUE;
	  }
	return FALSE;
        }
        
        
        
        
        /*Read input from user via stdin and store in memory as a string
        Pointer passed as paramater will be stored with the input of user:*/
        int input(char **str){ 
          int c = 0;
          int i = 0, j = 1;
          *str = (char*)malloc(sizeof(char));
          printf("\nPlease enter a command:\n");

          while (c != '\n' && c != EOF){
           /*read the input from stdin*/
           c = getc(stdin);
          /*reallocate memory for character to be stored*/
         *str = (char*)realloc(*str, j * sizeof(char));
    
          /*Quit if realloc failed:*/
          if (!*str){ 
            printf("Unable to realloc\n"); 
            return NO;
           }

          /*storing character at str[i]*/
          *(*str+i) = c;

            i++; /*next str index to be stored*/
            j++; /*resize str size by 1*/
          }
          /*If eof, return EOF, if NULL return 0, else if there is a string return 1*/
          if(c == EOF){
          *(*str+(i-1)) = '\0'; /*Mark end of string at i-1 to remove '\n')*/
          printf("\nERORR: Input reached end of file before recived a command to stop this program\n");
          return EOF;
        }
          else if(i == 1){
           free(*str);
          *str = NULL;
          return 0;
         }

         else{
           *(*str+(i-1)) = '\0'; /*Mark end of string at i-1 to remove '\n')*/
           return 1;
         }
        }


