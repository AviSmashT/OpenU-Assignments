#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/*Declaration:*/
void printMat (int mat[N][N]);
boolean path(int mat[N][N], int u, int v);


/*main:*/
int main()
{
/*Declaration and initializtion:*/
  adjmat A; /*Creating matrix NxN*/
  int i = 0; /*for loop*/
  int j = 0; /*for loop*/
  int u = 0; /*Varible for path - father*/
  int v = 0; /*Varible for path - son*/
  boolean result = 0; /*Hold the value returned from path - to indicate what to print: true or false*/

  /*Input*/
  printf("\nThis program recevie a tree matrix. The matrix will be printed and then checks if there is a path from node u to node v.\n");
  printf("The number of nodes in this tree is %d (0-%d). You need to insert %d values (0 or 1).\n", N, (N-1), (N*N));
  printf("Make sure there is space between the values. \nYou can press enter after every value input or every line input of the matrix. \nNow please enter the matrix values:");

  /*initializing matrix with input*/
  for (i = 0; i < N; i++){ /*rows*/
    for(j = 0; j < N; j++){ /*columns*/
      scanf("%d", &A[i][j]);
    }
    printf("\n");
  }


  /*Output - Printing matrix*/
  printMat(A);


  /*Checks if there is a path from u to v in Matrix-Tree*/
  printf("\nTo check if there is a path between node u to node v \nPlease enter the value of u first and then the value of v\nYou can press enter after every input or insert the two values in the same line (make sure there is space between the values) \n");
  printf("To quit enter the values '-1' and -1' \n");

  while (scanf("%d %d", &u, &v) == 2 && !(u == -1 && v == -1)){ /*while loop until scanf input is -1 -1 or EOF*/

    /*return boolean value from path to result and print it:*/
    result = path(A,u,v);

    if(result == TRUE)
    printf("\nThere is a path from %d to %d\n\nNext input: ", u, v);
    else
    printf("\nThere isn't a path from %d to %d\n\nNext input: ", u, v);

  }/*end of while*/

  printf("\nProgram ended\n");

  return 0;
} /*End of main*/




void printMat (int mat[N][N]){
  int i = 0;
  int j = 0;
  int z = 0;

  /*printing matrix index lines(row)*/
  printf("     ");
  for(z = 0; z < N; z++){
    printf("%d  ", z);
  }
  printf("\n\n");
  /*end of printing matrix index lines(row)*/

  /*printing matrix index lines(columns) and data:*/
  for (i = 0; i < N; i++){

    /*printing matrix index lines(columns)*/
    if(i > 9){  /*To print aling matrix, if N is 2-digit number then print with one more space:*/
      printf("%d  ", i);}
      else{
        printf("%d   ", i);
      }/*end of printing matrix index lines(column)*/


      /*Print matrix data*/
      for(j = 0; j < N; j++){

        if(j > 9){  /*To print aling matrix, if N is 2-digit number then print with one more space:*/
          printf("  %d ", mat[i][j]);}
          else {
            printf(" %d ", mat[i][j]);}
          } /*end of for (printing matrix data)*/

          printf("\n");
        } /*end of for (matrix index lines and data):*/
        printf("\n");
      }/*end of printMat*/


boolean path(int mat[N][N], int u, int v){
  int i = 0;
  int j = 0;
  int count = 0;
  int *p;
  int arrayCon = 0;

       
  if( (u > (N-1)) || (v > (N-1)) ){ /*if paramaters is bigger than N return faluse*/
    printf("\nInvalid paramaters");
    return FALSE;
    }

  if( u < 0 || v < 0 ){ /*if paramaters is smaller than 0 return faluse*/
    printf("\nInvalid paramaters");
    return FALSE;
    }
    
   if(u == v){return TRUE;}; /*if paramaters are the same - return faluse*/


   /*if u (father) is at the bottom of the tree (all value is 0 in 'u' row) - return false:*/
   for (i = 0, count = 0; i < N; i++){
     count += mat[u][i];
     }

   if(count == 0){
     return FALSE;
     }/*end*/

        /*if u (father) is the root of the tree (all value is 0 in 'u' column) - return true:*/
   for (i = 0, count = 0; i < N; i++){
     count += mat[i][u];
     }

   if(count == 0){
     return TRUE;
     }/*end*/


   /*Crateing array to store all nodes under 'u'*/
   p = (int *) malloc(sizeof(int));
   
   if(!p){ /*Quit if malloc failed*/
     printf("Unable to malloc\n");
     return FALSE;
     }

        /*Inserting 'u' to array*/
   p[arrayCon] = u;
   arrayCon++;/*Counting array size/useage*/

   /*Storing all nodes under 'u' in array*/
   while ((j < arrayCon) && (arrayCon < (N*N))){ /*While loop run until j (index of arrayCon) is equals array counter or until array is equals N*N 
                                                 (this is of course in case of invalid input...and we don't stop at (arrayCon < (N)) because we still want to check as-is in that logic)*/
       
          
    /*
    Tracking the sons of 'u' with the value of "p[j]", which we place at rows in matrix and then index "i" will search for all sons that are value of "p[j]"
    meaning if there is 1 in mat[p[j]][i] then add node to array after extnding array with realloc:*/
     for (i = 0; i < N; i++){ /*Index row in matrix*/
       if(mat[p[j]][i] == 1){
         p = (int *) realloc(p, (1+arrayCon)*sizeof(int)); /*extnding array with realloc*/
         if(!p){ /*Quit if realloc failed*/
           printf("Unable to realloc\n");
           return FALSE;
         }
         p[arrayCon] = i; /*add node to array*/
         arrayCon++; /*Counting array size/useage*/
       }
     }/*End of for loop*/
          
     j++;/*Index arrayCon +1*/
   }/*End of while loop*/
   
   if(arrayCon > (N)){/*matrix that represent a genuine tree need to have (N-1) true values (and the array should have N values including the father)*/
     printf("\nThe number of True values in the matrix is bigger than %d, The matrix does not represent a genuine tree. Please check the matrix inserted for accurate result of path ",(N-1));
     }

   /*Comparing all nodes stored in array with 'v':*/
   for (i = 0; i < arrayCon; i++){
     if (p[i] == v){
     return TRUE; /*If there is a match return true:*/
     }
   }
   free(p); /*free array p from memory*/
   
   return FALSE;
   
} /*End of path function*/
