#include "stack.h"
#include <stdlib.h>


stack_t stack_create(){

        return list_create();
}

int push(stack_t *this_stack, int add_value){
        return list_push(this_stack, add_value);
}

int pop(stack_t *this_stack){
        return list_pop(this_stack);
}


int peek(stack_t *this_stack){

        if(*this_stack == NULL)
                return -1;
        else
                return (*this_stack)->value;


}


void stack_print (stack_t *this_stack){

        list_print(this_stack);
}
~                 
