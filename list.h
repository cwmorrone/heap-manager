#ifndef _LIST_H_
#define _LIST_H_

typedef struct node_s {
        int value;
        struct node_s * next;
} node_t;


typedef node_t* list_t;


list_t list_create();


int list_push(list_t *this_list, int add_value);



void list_print( list_t *this_list);


int list_pop(list_t *this_list);





#endif
~                      
