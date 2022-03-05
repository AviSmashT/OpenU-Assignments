#include "assembler.h"


void writeFiles(char * argv) {
  FILE * output_file; /*FILE type for output file argument*/
  char * output_name;

  int EntC = 0;
  if (ERROR == NO) {
    output_name = (char * ) malloc(strlen(fileName) + FILE_EXTENSION_SIZE);
    strcpy(output_name, fileName);
    strcat(output_name, ".ob");
    output_file = fopen(output_name, "w"); /*open second argument file (output) as write to override existing content*/
    /* if file is inaccessable - print error to stderr:*/
    if (output_file == NULL) {
      printf("Unable to realloc memory for object File name %s\n", argv);
    }
    IC = 100;
    DC = 0;
    fprintf(output_file, "%d        %x\n", ICF - 100, DCF);
    while (IC < ICF) {
      int i = 0;
      int dec = 0;
      while (data_code[IC].opcode[i] != '\0') {
        if (data_code[IC].opcode[i] == '1')
          dec = dec * 2 + 1;
        else if (data_code[IC].opcode[i] == '0')
          dec *= 2;
        i++;
      }
      fprintf(output_file, "%07d   %06x\n", IC, dec); /*Print to file wirh padding left zeros*/
      IC++;
    }
    while (DC < DCF) {
      int i = 0;
      int dec = 0;

      while (data_table[DC].data[i] != '\0') {
        if (data_table[DC].data[i] == '1')
          dec = dec * 2 + 1;
        else if (data_table[DC].data[i] == '0')
          dec *= 2;
        i++;
      }
      fprintf(output_file, "%07d   %06x\n", IC + DC, dec);
      DC++;
    }
    fclose(output_file); /* close file */
    if (output_name != NULL)
      free(output_name);

    if (ExtC > 0) {
      int i = 0;
      int j = 0;
      output_name = (char * ) malloc(strlen(fileName) + FILE_EXTENSION_SIZE);
      strcpy(output_name, fileName);
      strcat(output_name, ".ext");
      output_file = fopen(output_name, "w"); /*open second argument file (output) as write to override existing content*/
      /* if file is inaccessable - print error to stderr:*/
      if (output_file == NULL) {
        printf("Unable to realloc memory for entry File name %s\n", argv);
      }

      while (i < Symbolrows) {

        if (symbolTable[i].symbol_type == EXTERNAL) {
          j = 0;
          while (j < addressStackIndex) {


            if (strcmp(symbolTable[i].symbol_name, addressStack[j].LABLE) == 0) {

              fprintf(output_file, "%s   %07d\n", addressStack[j].LABLE, addressStack[j].address); /*Print to file wirh padding left zeros*/

            }
            j++;

          }

        }
        if (symbolTable[i].entry_type == ENTRY) {
          EntC++;
        }

        i++;

      }

      fclose(output_file); /* close file */
      if (output_name != NULL)
        free(output_name);

    }

    if (EntC > 0) {
      int i = 0;
      output_name = (char * ) malloc(strlen(fileName) + FILE_EXTENSION_SIZE);
      strcpy(output_name, fileName);
      strcat(output_name, ".ent");
      output_file = fopen(output_name, "w"); /*open second argument file (output) as write to override existing content*/
      /* if file is inaccessable - print error to stderr:*/
      if (output_file == NULL) {
        printf("Unable to realloc memory for external File name %s\n", argv);
      }

      while (i < Symbolrows) {

        if (symbolTable[i].entry_type == ENTRY) {

          if (symbolTable[i].symbol_name[strlen(symbolTable[i].symbol_name) - 1] == ':') {
            symbolTable[i].symbol_name[strlen(symbolTable[i].symbol_name) - 1] = '\0';
          }
          fprintf(output_file, "%s   %07d\n", symbolTable[i].symbol_name, symbolTable[i].symbol_address); /*Print to file wirh padding left zeros*/

        }

        i++;
      }

      fclose(output_file); /* close file */
      if (output_name != NULL)
        free(output_name);
    }

  }

}
