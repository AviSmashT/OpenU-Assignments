#include "complex.h"


      void read_comp(struct complexN* pointer, double temp1, double temp2){
	/*Real*/
	pointer->real = (temp1);
	/*image*/
	pointer->imaginary = (temp2);

	return;
      }


      void print_comp(struct complexN* pointer) {
	if (0 < (fabs(pointer->real) - (int)fabs(pointer->real))) { /*checks if the number have fractional part*/
	  printf("%.2f", pointer->real); /*print with fractional part*/
	}
	else {/*print without fractional part*/
	  printf("%.0f", (pointer->real));
	}
	
	if (0 < (fabs(pointer->imaginary) - (int)fabs(pointer->imaginary))){ /*checks if the number have fractional part*/
	  if (pointer->imaginary >= 0) {
	    printf("+(%.2f)i", pointer->imaginary); /*if the number have a fractional part imag and also positive - print with parentheses*/
	  }
	  else{
	    printf("-(%.2f)i", fabs(pointer->imaginary)); /*if the number have a fractional part, is imag and also negative - print without operator*/
	  }
	}
	else{/*else if the number don't have a fractional part*/
	  if (pointer->imaginary >= 0){
	    printf("+%.0fi", (pointer->imaginary)); /*if the number is imag and also positive - print normally (without fractional part)*/
	  }
	  else{
	    printf("-%.0fi", (fabs(pointer->imaginary))); /*if the number is imag and also negative - print without operator*/
	  }
	}
	printf("\n");
      }/*end of printComp function*/
      
      
      void add_comp(struct complexN* pointer, struct complexN* pointer2, struct complexN* result){
        result->real = pointer->real + pointer2->real;
        result->imaginary = pointer->imaginary + pointer2->imaginary;
        
        print_comp(result);/*Print result*/

	return;
      }
      
      
      
      void sub_comp(struct complexN* pointer, struct complexN* pointer2, struct complexN* result) {
        result->real = pointer->real - pointer2->real;
        result->imaginary = pointer->imaginary - pointer2->imaginary;
        
        print_comp(result);/*Print result*/
        
        return;
      }
      
      
      
      void mult_comp_real(struct complexN* pointer, double temp1, struct complexN* result){
      
        result->real = temp1 * pointer->real;
        result->imaginary = temp1 * pointer->imaginary;
      
        /*Canceling signed (Signed zero)*/
        if (result->real == 0){
          result->real = 0;
        }
        if(result->imaginary == 0){
          result->imaginary = 0;
        }
      
        print_comp(result);/*Print result*/
      
        return;
      }
      
      
      void mult_comp_img(struct complexN* pointer, double temp1, struct complexN* result){
      
        result->real = temp1 * pointer->imaginary - ((temp1 * pointer->imaginary) * 2);
        result->imaginary = temp1 * pointer->real;
        
        /*Canceling signed (Signed zero)*/
        if (result->real == 0){
          result->real = 0;
        }
        if(result->imaginary == 0){
          result->imaginary = 0;
        }
      
        print_comp(result);/*Print result*/
      
        return;
      }
      
      void mult_comp_comp(struct complexN* pointer, struct complexN* pointer2, struct complexN* result){
      
        result->real = (pointer->real * pointer2->real) - (pointer->imaginary * pointer2->imaginary);
        result->imaginary = (pointer->real * pointer2->imaginary) + (pointer->imaginary * pointer2->real);

        /*Canceling signed (Signed zero)*/
        if (result->real == 0){
          result->real = 0;
        }
        if(result->imaginary == 0){
          result->imaginary = 0;
        }
      
        print_comp(result);/*Print result*/
      
        return;
      }
      
      double abs_comp(struct complexN* pointer) {
        double absvalue = 0;
        absvalue = sqrt(pow(pointer->real, 2) + pow(pointer->imaginary, 2));
        
        return absvalue; /*Return value of abs_comp to print to user*/
      }

        flag stop(void){

        return YES; /*Return YES to stop varible from type flag to make loop main stpp*/
        }
