#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static const int MAX_HEAP = 1024*1024;
#define MIN_SIZE = 8

/* 
* purpose: Ensure the intialization of the heap to be managed
* input:   None
* return:  The start of the heap
*/
static void *get_heap(){

  int *header;
  static void* start=0;
  //if we have a heap already, great, return the front of it
  if (start != 0){
    return start;
  }

  //allocate MAX_HEAP bytes for our heap manager by moving the break
  if ( (start = sbrk(MAX_HEAP+4)) <0){
    perror("sbrk");
    return NULL;
  }
  //payloads need to be on an 8 byte boundry and the headers are 4, so...
  start+=4;

    //set the header for the whole big chunk (ignoring a prologue)
  header=start;
  *header = MAX_HEAP;

  //set the footer for the whole big chunk (ignoring an epilogue)
  header = sbrk(0);
  *(header-1)=MAX_HEAP;

  return start;
}

/*
* purpose: allocated memory on the heap using headers and footers
* input:   size - the amount of space to be allocated (w/o header and footer)
* return:  a pointer to the begining of the payload
*/
void *my_malloc(unsigned int size){
  int *current_header;
  int heap_size=MAX_HEAP;
  //make sure size is even
  if(size%2!=0){
          size=size+1;
  }
  //make sure memory is double word (8 bit) aligned
  int checker = size%8;
  printf("memory check: %d: \n", checker);
  while(checker != 0){
          //while size is not % by 8, add 2 until it is so
          size=size+2;
          checker=size%8;
          printf("Check: %d\n",checker);
          printf("size 2: %d\n", size);
  }
  //print size of memory being malloced
  printf("Size: %d\n", size);
  //get start of heap
  void* heap_start;
  heap_start=get_heap();

  current_header=heap_start;
  //declare ptr for next header and footer

int *next_header;
  int*footer;
  //check if we have enough space
  if(heap_size<size){
          return NULL;
  }
  //traverse heap to find suitable memory block
  while(*current_header %2 !=0 && heap_size >=size){
          heap_size -= *current_header -1;
          current_header=current_header+ *current_header/4+1;
  }
  //print location info
  printf("Current header: %d and %p\n", *current_header, current_header);
  //malloc if heap size sufficient
  if(heap_size>=size){
          if(heap_size==size){
                  footer=current_header+size/4+1;
                  *current_header=size+1;
                  *footer=size+1;
                  printf("allocated 1, header = %d\n", size);
          }else{
                  footer = current_header +size/4-1;
                  *current_header = size+1;
                  *footer=size+1;
                  next_header=footer+1;
                  *next_header=heap_size-size;
                  printf("next head: %p\n", next_header);
                  printf("allocated 2, header != %d\n", size);
          }
  }
          printf("Return %p", (current_header+1));
          return (current_header+1);

}

/*
* purpose: mark memory as unused and coellese ajacent blocks
* input:   memloc - pointer to payload of memory location to free
* return:  nothing
*/
void my_free(void *memloc){
        int *header = (int *)memloc -1;
        *header &= -1;
        int *next_header = (int *)((char *)memloc + (*header & ~1));
    if ((*next_header & 1) == 0) {
        // Merge with the next block
        *header += (*next_header & ~1);
    }

}

/*
* purpose: Print out the heap
* inputs:  None
*/
void print_heap(){

}
                
