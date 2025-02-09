#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 10000

typedef struct Node {
    size_t size;
    struct Node* next;
} Node;

static char memory[MEMORY_SIZE];

static Node* head = NULL;

void* my_malloc(int size) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            if (current->size - size > sizeof(Node)) {
                // Split the block
                Node* new_block = (Node*)((char*)current + sizeof(Node) + size);
                new_block->size = current->size - size - sizeof(Node);
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            return (void*)((char*)current + sizeof(Node));
        }
        prev = current;
        current = current->next;
    }
    return NULL; // Out of memory
}

void my_free(void* ptr) {
    if (ptr == NULL) return;
Node* block = (Node*)((char*)ptr - sizeof(Node));
    Node* current = head;

    while (current != NULL && current < block) {
        if ((char*)current + current->size + sizeof(Node) == (char*)block) {
            // Merge current block with block
            current->size += block->size + sizeof(Node);
            block = current;
            break;
        }
        current = current->next;
    }

    if (current != NULL) {
        block->next = current->next;
        current->next = block;
    } else {
        block->next = head;
        head = block;
    }
}

void display_free_blocks() {
    Node* current = head;
    printf("Free Blocks:\n");
    while (current != NULL) {
        printf("Address: %p, Size: %zu\n", (void*)((char*)current + sizeof(Node)), current->size);
        current = current->next;
    }
}

int main() {
    Node* initial_block = (Node*)memory;
    initial_block->size = MEMORY_SIZE - sizeof(Node);
    initial_block->next = NULL;
    head = initial_block;

    // Allocate and free memory
    void* ptr1 = my_malloc(100);
    printf("Allocated memory at address: %p\n", ptr1);
    display_free_blocks();

    void* ptr2 = my_malloc(200);
    printf("Allocated memory at address: %p\n", ptr2);
    display_free_blocks();

    my_free(ptr1);
    printf("Freed memory at address: %p\n", ptr1);
    display_free_blocks();

    my_free(ptr2);
    printf("Freed memory at address: %p\n", ptr2);
    display_free_blocks();

    return 0;
}
