#ifndef _STACK_H_
#define _STACK_H_



#include "list.h"


typedef list_t stack_t;


stack_t stack_create();

int push(stack_t *this_stack, int add_value);

int pop(stack_t *this_stack);


int peek(stack_t *this_stack);


void stack_print(stack_t *this_stack);




#endif
~                              
