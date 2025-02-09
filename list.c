#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "heapmgr.h"



list_t list_create(){

        return NULL;
}



int list_push(list_t *this_list, int add_value) {
    // Allocate memory for the new node
    node_t* new_node = my_malloc(sizeof(node_t));
    if (new_node == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed in list_push\n");
return -1; // Indicate failure
    }

    // Initialize the new node
    new_node->value = add_value;
    new_node->next = *this_list;

    // Update the list pointer to point to the new node
    *this_list = new_node;

    return add_value; // Return the added value
}

void list_print( list_t *this_list){


        node_t* curr = *this_list;



        while(1){
                if(curr == NULL){
                        break;
                }

                printf("-->%d", curr->value);
                curr = curr->next;
        }


        printf("\n");

}





int list_pop(list_t *this_list){

        if(*this_list == NULL){
                return -1;
        }


        node_t* tmp = *this_list;

        int retval = tmp->value;

        *this_list = (*this_list)->next;

        my_free(tmp);

        return retval;

}

