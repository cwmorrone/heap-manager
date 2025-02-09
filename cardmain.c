  // main.c for a linked list of cards

#include <stdio.h>
#include "stack.h"
#include "list.h"
#define PUSH            's'
#define POP                     'p'
#define PEEK            'k'
#define FIND_MAX        'f'
#define PRINT           't'
#define QUIT            'q'





int main(int argc, char *argv[])
{
  char command;


  stack_t my_stack = stack_create();
  int more_commands=1;

int result;

  int n;
  while (more_commands){

    printf("Command s: push, p: pop, k: peek, f: find max, t: print, q: quit\n");
    scanf("%c", &command);
    getchar();

    if (command == PUSH ){
      /* read in card from user. Other commands do not requie this. */
        //card = card_create();

                        printf("A number to push: ");
                        scanf("%d", &n);
                        //get rid of the \n character
                        getchar();
    }

    switch (command)
    {
      case PUSH:
          /*push a card to the stack*/
                        result = push(&my_stack, n);
         printf("Push: %d\n", result);
              break;
      case POP:
          /*pop a card out of the stack*/
                        result = pop(&my_stack);
                        printf("Pop: %d\n", result);
              break;
      case PEEK:
          /*look at the top of  the stack*/
                        result = peek(&my_stack);
         printf("Peek: %d\n", result);
         break;
      case FIND_MAX:
          /*find the max value in the stack*/
         break;
      case PRINT:
          /*print all the cards in  the stack*/
                        stack_print(&my_stack);
                        break;
      case QUIT:
          /*free your stack and end your program*/
                        more_commands=0;
              break;
      default:
                        printf("Invalid command!\n");
                        break;
    }
  }

  return 0;

}
