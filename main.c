//  Project Title: Balanced Symbol Checker

//  Created by Roselle Mata
//  Copyright © 2020 Roselle Mata. All rights reserved.

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define TRUE  1
#define FALSE 0

int DebugMode;

typedef struct Stack 
{
    char* arr;
    int topindex;
    int total;
} Stack;

// this function is responsible for initializing the stack
void init(Stack *my_stack) 
{
    my_stack->total = 2; 
    my_stack->topindex = -1;
    my_stack->arr = (char*)malloc(sizeof(char)*my_stack->total);
}

// this function is responsible for checking if the stack is empty
int is_empty (Stack *my_stack)
{
  if ( my_stack->topindex  == -1)
    return TRUE;
  else
    return FALSE;
}

// this function is responsible for pushing/adding an element onto the stack
// this function is also responsible for growing the array if needed
void push(Stack *my_stack, char symbol) {

    // double size if needed
    if (my_stack->topindex == my_stack->total - 1) {
        char *temp; 
        temp = (char *) malloc ( sizeof (char) * (my_stack->total*2));  
        for (int i = 0 ; i < my_stack->total ; i++) {
            temp[i] = my_stack->arr[i];
        }

        free (my_stack->arr);
        my_stack->arr = temp;
        printf("Stack size increased from %d to %d\n", my_stack->total, my_stack->total*2);
        my_stack->total = my_stack->total * 2;
    }
    my_stack->topindex++;
    my_stack->arr[my_stack->topindex] = symbol;

    if(DebugMode) {
        printf("Character %c was pushed into the stack\n", symbol);
    }
}

// this function is responsible for accessing/returning the top element on the stack
char top(Stack *my_stack) {
    if(my_stack->topindex == -1) 
        return '*';
    return my_stack->arr[my_stack->topindex];
}


// this function is responsible popping/removing an element off of the stack;
void pop(Stack *my_stack) {

    if(DebugMode) {
        printf("Character %c was popped from the stack\n", top(my_stack));
    }
    my_stack->topindex = my_stack->topindex-1;
}

// this function clear the stack so that it is empty and ready to be used again
void clear (Stack *my_stack)
{
  free(my_stack->arr);
  init(my_stack);
}


int main (int argc, char** argv)
{
    Stack my_stack; // create stack
    init(&my_stack); // initializw new stack


    char input[301];    
    /* check for command line argument of -d */
    DebugMode = FALSE;
    int i;
    for ( i = 0; i < argc; i++)
        if ( strcmp (argv[i], "-d") == 0)
            DebugMode = TRUE; 
    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf ("\nEnter input parenthesis to see if they are balance or q to quit\n");
        printf ("Example: {}() or <<}}\n");
        fgets(input, 300, stdin); 
        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
           i++;
        }
        input[i] = '\0';  
        /* check if user enter q or Q to quit program */
        if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
            break;


        /* run the algorithm to determine is input is balanced */ 

        int errorFlag = 0;

        for (int i = 0; i < strlen(input); i++) {


            // check which current symbol
            if ((input[i] == '(') || (input[i] == '[') || (input[i] == '{') || (input[i] == '<')) {
                push(&my_stack, input[i]);
            }

            else if ((input[i] == ')') || (input[i] == ']') || (input[i] == '}') || (input[i] == '>')) {
                
                if (((top(&my_stack) == '(') && (input[i] == ')')) ||
                    ((top(&my_stack) == '{') && (input[i] == '}')) ||
                    ((top(&my_stack) == '[') && (input[i] == ']')) ||
                    ((top(&my_stack) == '<') && (input[i] == '>'))) {
                        
                        pop(&my_stack);
                }  

                else if (is_empty(&my_stack)) {

                    for (int k = 0; k < i; k++) {
                        printf(" ");
                    }

                    if(input[i] == ')') {
                        printf("^ missing (\n");
                    }

                    else if (input[i] == '}') {
                        printf("^ missing {\n");
                    }

                    else if (input[i] == ']') {
                        printf("^ missing [\n");
                    }

                    else if (input[i] == '>') {
                        printf("^ missing <\n");
                    }
                    
                    errorFlag = 1;
                    break;
                }    

                else {

                    for (int k = 0; k < i; k++) {
                        printf(" ");
                    }

                    if (top(&my_stack) == '(') {
                        printf("^ expecting )\n");
                    }

                    else if (top(&my_stack) == '[') {
                        printf("^ expecting ]\n");
                    }

                    else if (top(&my_stack) == '{') {
                        printf("^ expecting }\n");
                    }

                    else if (top(&my_stack) == '<') {
                        printf("^ expecting >\n");
                    }
                    errorFlag = 1;
                    break;
                }          
            }
        }

        if (is_empty(&my_stack) && (errorFlag != 1)) {
            printf("Balanced\n");
        }

        else if (!is_empty(&my_stack) && (errorFlag != 1)){
            for (int k = 0; k < strlen(input); k++) {
                printf(" ");
            }
            if (top(&my_stack) == '(') {
                printf("^ missing )\n");
            }
            else if (top(&my_stack) == '[') {
                printf("^ missing ]\n");
            }
            else if (top(&my_stack) == '{') {
                printf("^ missing }\n");
            }
            else if (top(&my_stack) == '<') {
                printf("^ missing >\n");
            }
        }
        clear(&my_stack);
    }   
    printf ("\nGoodbye\n");

    free(my_stack.arr);

    return 0;
}