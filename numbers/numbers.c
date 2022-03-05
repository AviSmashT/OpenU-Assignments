#include "header.h"


int main(int argc, char *argv[]){
int c; /*Current character with getc*/
int numCount = 0; /*Count current digits gathered from FILE to be converted to text (2 digit at most)*/
char numbers[NUMNER_SIZE]; /* Hold 2 digit number at most to be converted at a given time*/
char textToNum[STRING_NUM_SIZE]; /* Hold text converted from numbers inserted - this string changed by the function numToText*/ 
flag firstDig = NO;
FILE *input_file; /*FILE type for input file argument*/
FILE *output_file; /*FILE type for output file argument*/



/*Interaction with user if using standard output*/
if(argc == 1 || argc == 2){
  printf("**Convert number to words**\n");
  printf("Please enter a number between 0 to 99 and this program will convert the number to words\n");
  printf("Spaces is needed between the numbers\n");
  printf("If the number inserted is negative then the program will take the absolute value of that number\n");
  printf("If You enter a more than two digit number, only the first two digits will be converted\n");
  printf("Start entring numbers:\n\n");
}




switch(argc){ 
  case (1): /*case no arguments*/
    /*run loop until EOF */
    while((c = getc(stdin)) != EOF){
      if(isdigit(c)){ /*intake of digits only*/
        /*Check if multiply zero preceding a non-zero number: (ex: 0008 - is 8/eight):*/
        if(numCount == 0 && c != '0'){ 
           firstDig = YES; /*Flag if the first digit is a number and take the rest of the data normally*/
        }
        if(c == '0' &&  firstDig == NO){ /*If ZERO is preceding non-zero number - skip zero*/
          if(!peekNext(c, stdin)){ /*Check if next char in stdin is non-space*/ 
            continue; 
          }
        }
        numbers[numCount] = c; /*copy digit to string (later to be used in funcion to convert numbers)*/
        numCount++; /*count digit gathered*/
      }
      if(numCount == 2 || (numCount == 1 && peekNext(c, stdin)) ){ /*if counter is 2 digit OR counter is 1 and the next char is not a digit - proceed:*/
        /*If next char is a digit and and "numCount" is at 2 - thats mean the input is a three digit number. skip that last digit*/
        if(numCount == 2 && CheckNextDig( c, stdin)){  
        printf("\nYou entered a more than two digit number, only the first two digits will be converted:\n");/*Print a message to user*/ 
        }
        numbers[numCount] = '\0'; /*at the end of string close with '\0' */
        numToText(numbers, textToNum); /*Convert numbers to text (take numbers from "numbers" string and place the converted text in "textToNum" string)*/
        strcat( textToNum, "\n" ); /*add '\n' to write every number (as text) at next line */
        textToNum[strlen(textToNum)] = '\0'; /*at the end of string close with '\0' */
        fwrite(textToNum, sizeof(char), strlen(textToNum), stdout); /*Write string textToNum to stdout*/
        resetValues( &numCount, textToNum, numbers); /*Reset values of numCount and strings*/
        firstDig = NO;
      }
    }
    break; /*End case 1*/
    
  case (2):
  case (3): /*case 1 or 2 arguments*/
    
    input_file = fopen(argv[1], "r"); /*open first argument file to read (user input) */
    /* if file is inaccessable - print error to stderr:*/
    if(input_file == NULL){ 
      perror("Error! first argument ");
      break;
    }
    
    if(argc == 3){ /*If there is an output argument file, delete existing content from that file*/
      output_file = fopen(argv[2], "w"); /*open second argument file (output) as write to override existing content*/
      /* if file is inaccessable - print error to stderr:*/
      if(output_file == NULL){
        perror("Error! second argument ");
        break;
      }    
      fclose(output_file); /* close file */
    }
           
    /*run loop until '\n' or EOF:*/
    while( (c = fgetc(input_file)) != EOF){
      if(isdigit(c)){ /*intake of digits only*/
        /*Check if multiply zero preceding a non-zero number: (ex: 0008 - is 8/eight):*/
        if(numCount == 0 && c != '0'){
           firstDig = YES; /*Flag if the first digit is a number and take the rest of the data normally*/
        }
        if(c == '0' &&  firstDig == NO){ /*If ZERO is preceding non-zero number - skip zero*/
          if(!peekNext(c, input_file)){ /*Check if next char in input_file is non-space*/ 
            continue; 
          }
        }
        numbers[numCount] = c; /*copy digit to string (later to be used in funcion to convert numbers)*/
        numCount++; /*count digit gathered*/
      }
      if(numCount == 2 ||  (numCount == 1 && peekNext(c, input_file))){ /*if counter is 2 digit OR counter is 1 and the next char is not a digit - proceed:*/
        /*Checks if next char is a digit and and "numCount" is at 2 - thats mean the input is a three digit number. skip that last digit*/
        if(numCount == 2 && CheckNextDig( c, input_file)){  
          if(argc == 1 || argc == 2){ /*Print message stdout*/
            printf("You entered a more than two digit number, only the first two digits will be converted:\n");/*Print a message to user*/
          }
          else{ /*Print message to argument file*/
            output_file = fopen(argv[2], "a"); /*open second argument file to append (user output) */            
            /* if file is inaccessable - print error to stderr:*/
            if(output_file == NULL){
              perror("Error! second argument ");
              break;
            }
            fprintf(output_file,"\nYou entered a more than two digit number, only the first two digits will be converted:\n");/*Print a message to user*/
            fclose(output_file); /* close file */
          }
        }
        numbers[numCount] = '\0'; /*at the end of string close with '\0' */
        numToText(numbers, textToNum); /*Convert numbers to text (take numbers from "numbers" string and place the converted text in "textToNum" string)*/
        strcat( textToNum, "\n" ); /*add '\n' to write every number (as text) at next line */
        textToNum[strlen(textToNum)] = '\0'; /*at the end of string close with '\0' */
        
        /*Incase there are 2 arguments - output to file:*/
        if(argc == 3){
          output_file = fopen(argv[2], "a"); /*open second argument file to append (user output) */
          /* if file is inaccessable - print error to stderr:*/
          if(output_file == NULL){
            perror("Error! second argument ");
            break;
          }
          fwrite(textToNum, sizeof(char), strlen(textToNum), output_file); /*Write string textToNum to output_file*/
          fclose(output_file); /* close file */
        } /*End of output to file*/
        
        /*ELSE: Incase there is 1 argument - output to stdout:*/
        else if(argc < 3){
          fwrite(textToNum, sizeof(char), strlen(textToNum), stdout); /*Write string textToNum to stdout*/
        }    
      resetValues( &numCount, textToNum, numbers); /*Reset values of numCount and strings*/
      firstDig = NO;   
      } /*End of if*/
    
    } /*End of while*/
    
    fclose(input_file);  /* close file */ 
    break; /*End case 2 and 3*/
    
    
    default: /*More than 2 arguments - error to stderr file*/
      fprintf(stderr, "Error: Arguments passed are more than 2\nPlease run the program again with vaild arguments\n");
      break; /*End of default*/
    }
return 0;
}


/* convert a number into text
   Takes the first parameter "number" containing a number, convert it into text and write it into "text" string */
void numToText(char number[], char text[]){
    /*Database of numbers:*/
    char *ones_numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; 
    char *teens_numbers[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"}; 
    char *tens_numbers[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"}; 

    /*Incase of one digit number: */
    if (strlen(number) == 1){
      strcpy(text, ones_numbers[number[FIRST_DIG] - '0']); /*Get the sting from "ones_numbers" (in place of the digit in "number") and write to "text"*/
      return;
    }
   
    else{
       /*Incase of teens numbers (thirteen, fourteen...): */
      if (number[FIRST_DIG] == '1'){ 
        int num = ( number[FIRST_DIG] - '0' + number[SECOND_DIG] - '0' );  /*Add the digits of number in "num"*/
        strcpy(text, teens_numbers[num-1]); /*Get the sting from "teens_numbers" at place of ("num"-1) and write to "text"*/
        return;
      }
      
      /*Incase the number is 20:*/
      else if (number[FIRST_DIG] == '2' && number[SECOND_DIG] == '0'){ 
        strcpy(text, tens_numbers[FIRST_DIG]);
        return;
      }
    
      /*Incase the number is 21-99:*/
      else{ 
        strcpy(text, tens_numbers[(number[FIRST_DIG] - '0')-2]); /* write the first digit (converted) to "text"*/
          /*If second digit is not '0' - write:"*/
          if( (number[SECOND_DIG] - '0') != 0){
            strcat( text, " " ); /*To add space between the two words*/
            strcat( text, ones_numbers[number[SECOND_DIG] - '0'] ); /* write the second digit (converted) to "text"*/
          }
        return;
      }
    }
  
  return;
}

/*Peek to next char in FILE steam, return TRUE if there is space, '\n' or EOF*/
boolean peekNext(int c , FILE * stream){
  c = getc(stream); 
  if(isspace(c) || c == '\n' || c == EOF){
    ungetc(c, stream); /*Undo move in file*/
    return TRUE;
  }
  ungetc(c, stream); /*Undo move in file*/
  return FALSE;
}


/*Check if next char in FILE steam is a digit - If it's a digit, skip digit , return boolean*/
boolean CheckNextDig(int c , FILE * stream){
  c = getc(stream); 
  /*If next char is indeed a number, skip this char recursively until 'c' is not a char*/
  if(isdigit(c)){ 
    CheckNextDig(c , stream); /*skip 'c' recursively until 'c' is not a char*/
    return TRUE;
  }
  ungetc(c, stream); /*Undo move in file*/
  return FALSE;
}

/*Reset values of numCount, "textToNum" and "numbers"*/
void resetValues(int* numCount, char *textToNum, char* numbers){
  *numCount = 0;
  textToNum[0] = '\0';
  numbers[0] = '\0';
  numbers[1] = '\0';
  return;
}
