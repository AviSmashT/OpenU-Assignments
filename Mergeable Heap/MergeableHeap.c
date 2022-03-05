#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>
#include <string.h>
/*Author Avi Shem Tov*/

/*Creating boolean data type*/
typedef enum {FALSE, TRUE} boolean; 

/*Functions:*/
void make_heap();
void insert_sorted();
void insert();
void sorted_minimum();
void minimum();
void extract_min_sorted();
void extract_min();
void union_sort_list();
void union_list();
void print();  
boolean check_disjoint();


/*Creating struct node*/
struct node{ 
    struct node *prev;  
    struct node *next;  
    int key;  
};

/*Creating struct of heads pointers*/
struct heads{ 
    struct node *head;  
};

/*Global verables:*/
struct heads *plists = NULL; /*Head for list of lists*/
int listsIndex = 0; /* Index for linked lists (Struct heads)*/



/*Main program*/
int main (int argc, char *argv[]){

  int heapType = 0; /*User heap type choice*/
  char cmd[50]; /*User input command buffer*/

  /*User interface:*/
  printf("\n*********Mergeable Heap Program*********\n");  
  printf("\nThis program will create mergeable heaps using circular linked list\n");  
  printf("\n*******************************************************************\n");  
  printf("\nPlease select heaps type: \nA. The heaps are sorted.\nB. The heaps are not sorted.\nC. The heaps are not sorted and the groups of values are disjoint sets.\n"); 
    while(heapType == 0){ /*Check valid select*/
      printf("\nSelect by typing 1 for A, 2 for B or 3 for C: ");  
      scanf("%d",&heapType);
      getchar();
      if(heapType != 1 && heapType != 2 && heapType != 3 ){
        heapType = 0;
        printf("Invalid choice, Please try again.");
      }
    }
  printf("\n*** Functions supported: ***\n");  
  printf("'Make heap' - create new heap.\n");  
  printf("'Insert x' (as x is a number - The key/value) - Insert new element (node) to current heap.\n");  
  printf("'Minimum' - Show minimum (key) element of current heap.\n");
  printf("'Extract minimum' - Delete minimum (key) element of current heap.\n");  
  printf("'Union' - Merge all heaps.\n");  
  printf("'Print' - Print all heaps.\n");  
  printf("'Exit' - Quit the program.\n");  
    
  /*files*/
  FILE *input_file; /*FILE type for input file argument*/
  if(argc == 1){
    input_file = stdin;
  }
  else{
    input_file = fopen(argv[1], "r"); /*open argument file to read (user input) */
    /* if file is inaccessable - print error to stderr:*/
    if(input_file == NULL){ 
      perror("Error! first argument ");
    }
  }
  while( fgets(cmd, sizeof(cmd), input_file)){ /*Get commands from file*/
    for(int i = 0; cmd[i]; i++){ /*lower case all letters:*/
      cmd[i] = tolower(cmd[i]);
    }/*End of for loop*/
    
    cmd[strlen(cmd)-1]='\0'; /*Remove newline*/
      
    /******* Functions: *******/
    /*make heap func:*/
    if(strstr(cmd, "make heap") != NULL){ 
      make_heap();
    }
    /*Insert func:*/
    else if(strstr(cmd, "insert") != NULL){
      /*Extract number from cmd:*/
      char *c = cmd;
      int val;
      while (*c != '\0'){ /*Stop when end of line*/
        if (isdigit(*c)){ /*CHeck if digit*/
          val = (int)strtol(c, &c, 10); /*Get all digit using strtol and converting to int (10 digit for int)*/
        }
        else{
          c++; /*cmd char incremention*/
        }
      }/*End extract number*/
      if(heapType == 1){insert_sorted(val);} /*Sorted list*/
      else if(heapType == 2){insert(val);} /*Unsorted list*/
      else if(heapType == 3){ /*Unsorted list and check disjoint groups:*/
        boolean validKey = check_disjoint(val);
        if (validKey == TRUE){ /*If validKey == TRUE, insert new node. else, don't insert new node*/
          insert(val);
        }
      }
      }/*End of insert*/
      
      /*extract minimum func:*/
      else if(strstr(cmd, "extract minimum") != NULL){
        if(heapType == 1){extract_min_sorted();}
        else if(heapType == 2){extract_min();}
        else if(heapType == 3){extract_min();}
      }
      
      /*minimum func:*/
      else if(strstr(cmd, "minimum") != NULL){
        if(heapType == 1){sorted_minimum();}
        else if(heapType == 2){minimum();}
        else if(heapType == 3){minimum();}
      }
      
      
      /*union func:*/
      else if(strstr(cmd, "union") != NULL){ 
        if(heapType == 1){union_sort_list();}
        else if(heapType == 2){union_list();}
        else if(heapType == 3){union_list();}
      }
      
      else if(strstr(cmd, "print") != NULL){ 
        print();
      }
      
      else if(strstr(cmd, "exit") != NULL){
        for(int i = 0; i < listsIndex; i++){
          plists = plists+i;
            free(plists);
        }
        exit(0);   
      }
   
      else{ /*Invalid user input*/
        printf("%s is invalid command\n",cmd);
      }
      
  } /*End of while loop*/
 
  return 0;
    
} /* End of main*/


void make_heap(){
  if (listsIndex == 0){ /*If listsIndex == 0, there is not lists - create new head (pointer) for new list*/
    plists = (struct heads *)malloc((listsIndex + 1) * sizeof(struct heads) );
    if(!plists){ /*Check memory allocated successfully*/
      printf("\nMemory allocation failed");
      exit(0);
    }
    listsIndex = listsIndex +1; /*listsIndex++*/
  }
  else{
    struct heads *temPlists = (struct heads *)realloc(plists, (listsIndex + 1) * sizeof(struct heads) );
    if(!temPlists){ /*Check memory allocated successfully*/
      printf("\nMemory allocation failed");
      exit(0);
      }
    plists = temPlists; /*return pointer to allocated list of heads*/
    listsIndex = listsIndex +1; /*listsIndex++*/
  }
  printf("New heap created!\n");
}


void insert_sorted(int data){
  struct node *ptr,*temp; /*Creating struct nodes pointers - prt and temp*/
  plists = ( plists+(listsIndex-1) ); /*Change position to cureent linked list*/
  ptr = (struct node *)malloc(sizeof(struct node)); /*allocate space for node and return pointer to ptr*/
  if(!ptr){ /*Check memory allocated successfully*/
    printf("\nMemory allocation failed");  
  } 
  else{ /*if memory allocated - take key value to insert to node*/
    ptr -> key = data; /*Insert data to key of new node*/ 
    if(plists->head == NULL){ /*if list is empty* - assign ptr as head*/
      plists->head = ptr; /*HEAD POINTER*/
      ptr -> next = plists->head; /*Set next link*/
      ptr -> prev = plists->head; /*Set prev link*/
     }
    else{ /*If list is not empty: */
      temp = plists->head; /*Set temp pointer to equal head pointer*/
      while(listsIndex >= 1 || temp -> next != plists->head ){/*run loop until prt in it's right place*/ 
        struct node *head = plists-> head; /*Temp head pointer*/
        if((ptr->key) <= (head->key) ){ /* Prt is the smallest value - connect: temp , ptr, head */
          temp = head->prev;
          ptr->next = head;
          ptr->prev = temp;
          temp->next = ptr;
          head->prev = ptr;
          plists->head = ptr;
          break;
        }
        if((ptr->key) > (head->key) && (temp) == (plists->head) && (temp->next) == (plists->head) ){ /* if there is only one node and new node is bigger - connect: head , ptr */
          head-> next = ptr;
          ptr->prev = head;
          ptr->next = temp;
          temp->prev = ptr;
          break;
        }
        else if( (temp->key) <= (ptr->key) && (ptr->key) <= (temp->next->key)){ /* new node is a sandwich - connect: temp, ptr , tempNext */
          struct node *tempNext = temp->next;
          temp->next = ptr;
          ptr->prev = temp;
          tempNext->prev = ptr;
          ptr-> next = tempNext;
          break;
        }
        else if((temp->next) == (plists->head)){ /*New node is last node - connect: temp, ptr, head*/
          ptr->next = head;
          ptr->prev = temp;
          temp->next = ptr;
          head->prev = ptr;
          break;
        }
        temp = temp -> next; /*move temp pointer to next node*/ 
     } /*End of second else (sorting conditions)*/
   } /*End of first else (sorting conditions)*/
  }
  plists = ( plists-(listsIndex-1) ); /*Change position to first linked list*/
  printf("\nElement inserted (key = %d).\n", data);  
} /*End of insert*/






void insert(int data){  
   struct node *ptr,*temp; /*Creating struct nodes pointers - prt and temp*/
   plists = ( plists+(listsIndex-1) ); /*Change position to cureent linked list*/
   ptr = (struct node *)malloc(sizeof(struct node));  /*allocate space for node and return pointer to ptr*/
   if(!ptr){ /*Check memory allocated successfully*/
     printf("\nMemory allocation failed");  
   }
   else{ /*if memory allocated - take key value to insert to node*/
     ptr -> key = data; /*Insert data to key of new node*/
     if( plists->head == NULL){ /*if list is empty - assign ptr as head*/
       plists->head = ptr; /*HEAD POINTER*/
       ptr -> next = plists->head; /*Set next link*/
       ptr -> prev = plists->head; /*Set prev link*/
     }
     else{ /*If list is not empty: */
       struct node *head = plists-> head; /*Temp head pointer*/
       temp = plists->head; /*Set temp pointer to equal head pointer*/
       temp = temp -> prev; /*Set position to last node*/
       /*Relink*/
       temp -> next = ptr;  
       ptr -> prev = temp;  
       head -> prev = ptr;  
       ptr -> next = head;  
       head = ptr;  
     }  
     printf("\nElement inserted (key = %d).\n", data);  
   } 
  plists = ( plists-(listsIndex-1) ); /*Change position to first linked list*/
} /*End of insert*/





void extract_min(){
  struct node *temp, *head, *ptrMin; /*Creating struct nodes pointers - ptrMin - pointer to min value and temp, head for linking*/
  int min = 2147483647; /*biggest int*/
  ptrMin = NULL;
  head = (plists + (listsIndex-1) )->head; /*Point to current head*/
  if(head == NULL){ /*If current head is null - the list is empty*/
    printf("List is empty.\n");  
  }
  else{ /*find min in list:*/
    temp = plists->head; /*Set temp pointer to equal head pointer*/
    if(head->key < min){ /*CHECK HEAD FIRST! - if is smaller - store prt in ptrMin to use later*/
      min = head-> key;
      ptrMin = head;
    } 
    while(temp -> next != head){ /*Loop the rest of the list*/
      temp = temp -> next; /*Move temp pointer by one node*/
      if(temp->key < min){ /*Check if pointer is smalled - if true - store prt in ptrMin to use later*/
        min = temp-> key;
        ptrMin = temp;
      } /*End of if*/
    } /*End of while*/
  } /*End of else - end find min*/

  if(head->next == head){ /*Check if need to free memory (if last node deleted)*/
    head = NULL;   
    free((plists + listsIndex-1)->head);
    (plists + listsIndex-1)->head = NULL;
    printf("node extracted (key = %d).\n", min);
    }  
    else{ /*If deleted node from random position:*/
      struct node *nextPtr, *prevPtr;/*Help reconnect the list (ptr removed) - Prevnode, XXprtXX, nextnode*/
      temp = ptrMin; /*Temp will point to min node*/
      if(temp == head){ /*If min node is the head, set the ead as next on list*/
        (plists + listsIndex-1)->head = temp->next;
      }
      /*reconnect without min:*/
      nextPtr = temp->next;
      prevPtr = temp->prev;
      prevPtr->next = nextPtr;   
      nextPtr -> prev = prevPtr;  
      free(temp); /*free memory (delete)*/
      printf("node extracted (key = %d).\n", min);
    }
} /*End extract min*/




void extract_min_sorted(){
  int min;
  struct node *temp;
  struct node *head = (plists + (listsIndex-1) )->head; /*Point to current head*/
  if(head == NULL){ /*If current head is null - the list is empty*/
    printf("List is empty.\n");  
  }  
  else if(head->next == head){/*Check if need to free memory (if last node deleted)*/
    min = head->key; /*Store extracted value to be printed later*/
    head = NULL;   
    free((plists + (listsIndex-1))->head);
    (plists + (listsIndex-1))->head = NULL;
    printf("node extracted (key = %d).\n", min); 
    }  
    else{ /*If list > 1 - extract first node:*/
      min = head->key; /*Store extracted value to be printed later*/ 
      temp = head->prev;   
      temp -> next = head -> next;  
      head -> next -> prev = temp;  
      free((plists + (listsIndex-1))->head);  
      (plists + (listsIndex-1))->head = temp -> next;
      printf("node extracted (key = %d).\n", min); 
    }
}




void sorted_minimum(){
  printf("The minimum is %d. ", (plists + listsIndex-1)->head->key);
}




void print(){
  struct node *print_prt; /*Pointer to value to be printed*/
  if(plists->head == NULL){
    printf("\nThere is nothing to print on this list");  
  }     
  else{  
    printf("\n****List values****\n");
      for(int i = 0; i < listsIndex; i++){ /*Run on all heads*/
        printf("\nList number %d: \n", i+1);
        print_prt = ((plists + (i))->head );  
        while(print_prt -> next != (plists+i)->head){ /*Run on all list's value'*/
          printf("%d\n", print_prt -> key);  
          print_prt = print_prt -> next;  
        } /*End of while*/
        printf("%d\n", print_prt -> key);  
      } /*End of for loop*/
    } /*end of else*/
}




void minimum(){
  struct node *temp, *head; /*Creating struct nodes pointers - prt and temp*/
  int min = 2147483647; /*biggest int*/
  head = (plists + (listsIndex-1) )->head; 
  if(head == NULL){  /*If current head is null - list is empty*/
    printf("No lists \n");  
  }  
  else{ /*FInd min in list*/
    temp = plists->head; /*Set temp pointer to equal head pointer*/
    if(head->key < min){ /*CHECK HEAD FIRST! - if is smaller - store prt in ptrMin to use later*/
       min = head-> key;
    } 
    while(temp -> next != head){ /*Run on list*/ 
      if(temp->key < min){
        min = temp->key;     
      }
      temp = temp -> next;     
    }
  }  
  printf("The minimum is %d. ", min);     
} /*End of minimum*/




void union_list(){
  struct node *temp1, *temp2, *headPtr;
  if(plists->head == NULL){ /*If current head is null - list is empty*/
    printf("No lists \n");  
  }     
  else{  
    headPtr = ((plists+(listsIndex-1))->head)->prev; /*last node on last list*/
    for(int i = 0; (i+1) < listsIndex; i++){
      temp1 = (plists + (i))->head->prev; /*last node on first list*/
      temp2 = (plists + (i+1))->head; /*Head second list*/
      /*Merge lists: (temp1, temp2)*/
      temp1->next = temp2; 
      temp2->prev = temp1; 
    }
    temp1 = (plists + (0))->head; /*first node on first list*/
    temp1->prev = headPtr;
    headPtr->next = temp1;
    listsIndex = 1; /*Reset lists index*/
  }
}


void union_sort_list(){
  struct node *temp;
    if(plists->head == NULL){  /*If current head is null - list is empty*/
      printf("No lists \n");  
    }     
    else{  
      int tempInt = listsIndex; /*Store the value of listsIndex to use in loop*/
      listsIndex = 1; /*set list index for insert_sorted function (insert_sorted use this index)*/
      for(int i = 1; i < tempInt; i++){ /*Run on list's heads*/
        temp = (plists+i)->head;
        while(temp -> next != (plists+i)->head){ /*Run on current list*/
          insert_sorted(temp->key); /*Use insert_sorted to union lists*/
          temp = temp->next; /*Point to next node on list*/
        }
        insert_sorted(temp->key);
      }
      listsIndex = tempInt; /*Set old value of lists index to free allocated memory*/
    }
    for(int i = 1; i < listsIndex; i++){ /*free all list except the first list*/
      free((plists+i)->head);  
    }
   listsIndex = 1; /*Set new list index*/
}


boolean check_disjoint(int data){ /*Check if data paramater is already in one of the existing lists*/
  struct node *dataPtr; 
  for(int i = 0; i < listsIndex; i++){ /*Run on list's heads*/
    dataPtr = ((plists + (i))->head ); /*Points to current data checked*/
    if(dataPtr == NULL){ /*List is empty*/
      return TRUE;
    }
    while(dataPtr -> next != (plists+i)->head){  /*Run on current list*/
      if( (dataPtr -> key) == data ){ /*Check values*/
        printf("\nThe key is already in list number %d.\nElement not inserted\n", i);
        return FALSE; 
      } 
      dataPtr = dataPtr -> next; /*Point to next node on list*/
    }  

  }
  return TRUE; 
}


