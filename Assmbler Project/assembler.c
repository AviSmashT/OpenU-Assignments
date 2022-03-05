#include "assembler.h"

int main(int argc, char *argv[]){
  int i = 1; /*Index for loop - go through argument files*/
  int indexFileName = 0; /*Pointer to file name*/
  FILE *input_file; /*FILE type for input file argument*/  
  fileName = NULL; /*Pointer to file name */
  ICF = 0; /*Final instraction counter */
  DCF = 0; /*Final data counter */


    for( i = 1; i < argc; i++){ /* go through argument input files*/
      /***Creating and copy file name - later to be used in the write files function***/
      fileName = (char *)malloc(strlen(argv[i]) + FILE_EXTENSION_SIZE);/* memory allocate with the size of filename + file extension size (3)*/
      strcpy(fileName , argv[i]);
      strcat(fileName , ".as");
      
      
      /** Open input file sent as argument **/
      input_file = fopen(fileName, "r");
      if(!input_file){ /* Incase the program is unable to access file: */
        printf("Error: Program was unsuccessful openning file '%s' -" 
        "Please verify that file extension is '.as'\nNote: File extension should not be include in argument\n", argv[i]);
        free(fileName);
        continue;
      }
      
      firstFileCheck(input_file); /*First file check*/ 
      ICF = IC; /*initialize final instructions counter*/
      DCF = DC; /*initialize final data counter*/
      rewind(input_file); /*Rewind file pointer to the beginning of the file*/
      secondFileCheck(input_file); /*Second file check*/ 
      strCut(argv[i], '.' , &indexFileName , &fileName); /* Copy file name without extension */
      
      /***Reset value to default and free memory allocated varibles***/
      indexFileName = 0;
      writeFiles(argv[i]);
      fclose(input_file); 
      free(addressStack);
      free(symbolTable);
      free(fileName);
    }

  return 0;
  
}

