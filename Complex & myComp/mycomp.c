#include "complex.h"
linkCompNums vars[LINK_VARS_LENGTH+1]; /*Declatring struct "linkCompNums" to link complex variables data (Declatring globaly for use of getData function)*/

int main(){
	/*Declaration and initialization:*/
	double temp1, temp2 = 0; /*To be used as number type paramaters in commands*/
	int i, j, k = 0;
	/*strings containing the command and the paramaters (this will be send to function X to analyzing):*/
	char *str_cmd, *str_param1, *str_param2, *str_param3, *userInput = NULL;
	complexNum A, B, C, D, E, F, result; /*Complex numbers*/
	linkFunctions commands[LINK_CMD_LENGTH+1]; /*Declatring struct "linkFunctions" to link function data*/
	flag STOP = NO; /*varible type flag to use to stop loop of program (used in command "stop")*/

	/*creating link between commands name and address*/
	commands[0].name = "read_comp";      commands[0].functionIndex = 0; commands[0].numOfParams = 3; commands[0].des = "Change value for complex number";
	commands[1].name = "print_comp";     commands[1].functionIndex = 1; commands[1].numOfParams = 1; commands[1].des = "Print complex number";
	commands[2].name = "add_comp";       commands[2].functionIndex = 2; commands[2].numOfParams = 2; commands[2].des = "Add two complex numbers";
	commands[3].name = "sub_comp";       commands[3].functionIndex = 3; commands[3].numOfParams = 2; commands[3].des = "subtract two complex numbers";
	commands[4].name = "mult_comp_real"; commands[4].functionIndex = 4; commands[4].numOfParams = 2; commands[4].des = "Multiple complex numbers with real number";
	commands[5].name = "mult_comp_img";  commands[5].functionIndex = 5; commands[5].numOfParams = 2; commands[5].des = "Multiple complex numbers with imaginary number";
	commands[6].name = "mult_comp_comp"; commands[6].functionIndex = 6; commands[6].numOfParams = 2; commands[6].des = "Multiple two complex numbers";
	commands[7].name = "abs_comp";       commands[7].functionIndex = 7; commands[7].numOfParams = 1; commands[7].des = "Print get absolute value of complex number";
	commands[8].name = "stop"; 	      commands[8].functionIndex = 8; commands[8].numOfParams = 0; commands[8].des = "Stop this program";
	commands[9].name = "not_valid";      commands[9].functionIndex = 9; commands[9].numOfParams = 0; commands[9].des = NULL;
	/*creating a link between complex numbers name and address */
	vars[0].name = "A"; vars[0].compNumAddress = &A;
	vars[1].name = "B"; vars[1].compNumAddress = &B;
	vars[2].name = "C"; vars[2].compNumAddress = &C;
	vars[3].name = "D"; vars[3].compNumAddress = &D;
	vars[4].name = "E"; vars[4].compNumAddress = &E;
	vars[5].name = "F"; vars[5].compNumAddress = &F;
	vars[6].name = "#"; vars[6].compNumAddress = &result;
	vars[7].name = "#"; vars[7].compNumAddress = NULL;



	/*Initializting ALL complex numbers to "0+0i":*/
	for (i = 0; i < LINK_VARS_LENGTH; i++) {
	  vars[i].compNumAddress->real = 0;
	  vars[i].compNumAddress->imaginary = 0;
	}/*end of first for loop*/
        

        /*Interaction with user*/
        printf("\n **Welcome to complex number calculator program**\n");
        printf("\nyou can use this program to calculate complex numbers\n");
        printf("\nList of available commands:\n");

	for (i = 0; i < 9; i++){
	  printf("\n  (%d) %s - %s",i+1,commands[i].name,commands[i].des);
	  if(i == 8){
	    printf("\n");
	  }
	}
        printf("\nList of available complex nubmber variables you can use:\n");
        
      	for (i = 0; i < 6; i++){
	  if(i < 5){
	    printf("%s, ",vars[i].name);
	  }
	  else{
	    printf("%s \n",vars[i].name);
	  }
	}  
	printf("\nThe complex number (a + bi) is consist of real part (a) and imaginary part (bi)\n");
	printf("\nNOTE: this program is case sensitive\nExample for input format:\n  (1)|read_comp A, 5.5, 6|\n  (2)|add_comp A , B|\n  (3)|abs_comp    A|");
        printf("\nThere should be comma between every two paramaters, spaces are allowed freely as long as the format is considered");
        printf("\nComma between the command and paramater is not allowd, and extraneous text after end of command as well\n");
        /*End of interaction with user*/
        
        
        
        /*Loop until end of file OR stop command change value of STOP flag*/
	while(STOP == NO && (input(&userInput)) != EOF ){ 
	flag valid_input = YES; /*Flag that will indacate if input of user is valid (will change if functions analyzing the input find invalid input)*/
        rest(); /*Reset indexes for analyzing function with every new input about to recive from user*/
        
        
	/*Skip if user did not enter input:*/	
	if((userInput) == NULL){ 
	continue;
	}
	
	
	printf("%s\n",userInput);

   
        /*input will be analyzed in phases, every analyzing function return if the part of the data in string is valid according to command*/
        if(valid_input == YES)
	{valid_input = cmdExtrect(&userInput, &str_cmd);}

        if(valid_input == YES)
	{valid_input = cmdCompare (userInput, str_cmd, commands);}

	if(valid_input == YES)
	{valid_input = firstParamExtrect(&userInput, &str_param1);}

	if(valid_input == YES)
	{valid_input = seconedParamExtrect(&userInput, &str_param2);}

	if(valid_input == YES)
	{valid_input = thirdParamExtrect(&userInput, &str_param3);}
	
	if(valid_input == YES)
	{valid_input = paramEquals(commands);}
        
	/*Transform indexes value from analysis file:*/
	tansData(&i, &j, &k);


	/*If input is not vaild start over:*/
	if(valid_input == NO){
	  continue;
	}
	
	/*Indexes initialized with tansData function will now be used to go to the command that user input
	as well as the commlex number variables, incase of number the program use atof to use as number:*/
     	switch (i){ 
     	  case 0: /*read_comp */
     	    temp1 = atof(str_param2);
     	    temp2 = atof(str_param3);
     	    
     	    read_comp(vars[j].compNumAddress, temp1, temp2);
     	    print_comp(vars[j].compNumAddress);
     	    
     	    
     	  break; /*Break switch*/

          case 1: /*print_comp*/
          case 7: /*abs_comp*/
            if (i == 1) {
              print_comp(vars[j].compNumAddress);
            }
            if (i == 7){
              temp1 = abs_comp(vars[j].compNumAddress);
              if(0 < (fabs(temp1) - (int)fabs(temp1))){    
                printf("The absolute value of ""%s"" is %.2f\n",vars[j].name,temp1);		  
              }
              else{
                printf("The absolute value of ""%s"" is %.0f\n",vars[j].name,temp1);		  
              }
            }
            
          break; /*Break switch*/	    
          
          case 2: /*add_comp*/
          case 3: /*sub_comp*/
          case 6: /*mult_comp_comp*/
            if (i == 2) {
              add_comp(vars[j].compNumAddress, vars[k].compNumAddress, vars[RESULT].compNumAddress);
            }
            else if (i == 3) {
              sub_comp(vars[j].compNumAddress, vars[k].compNumAddress, vars[RESULT].compNumAddress);
            }
            else if (i == 6) {
              mult_comp_comp(vars[j].compNumAddress, vars[k].compNumAddress, vars[RESULT].compNumAddress);
            }
            
          break; /*Break switch*/
          
          case 4: /*mult_comp_real*/ 		  	 
          case 5: /*mult_comp_img*/	
          
            temp1 = atof(str_param2);
          
            if (i == 4){		  
              mult_comp_real(vars[j].compNumAddress, temp1, vars[RESULT].compNumAddress);
            }
            else if(i == 5){
              mult_comp_img(vars[j].compNumAddress, temp1, vars[RESULT].compNumAddress);
            }
          
          break;
          
          case 8: 
          
            STOP = stop();
                        
          break;
          
          default:
          
          break;
		
	}/*end of switch*/
	
	
	/*end of use - free dynamically allocated strings unless is null*/
	if(str_cmd != NULL){
	  free(str_cmd);
	  str_cmd = NULL;
	}
	if(str_param1 != NULL){
	  free(str_param1);
	  str_param1 = NULL;
	}
	if(str_param2 != NULL){
	  free(str_param2); 
	  str_param2 = NULL;
	}
	if(str_param3 != NULL){
	  free(str_param3); 
	  str_param3 = NULL;
	}
	if(userInput != NULL){
	  free(userInput);
	  userInput = NULL;
	}

                
	}/*End of main loop*/


	return 0;
	
}/*End of main*/


/*this function will help get data of the complex numbers
 to firstParamCompare and seconedParamCompare (In 'analysis.c')*/
linkCompNums* getVars(){
  return vars;
}
