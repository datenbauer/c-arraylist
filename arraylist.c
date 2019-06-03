#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 1 // must no be zero (see arraylist_enlarge())

enum STATUS {
    FAILURE,
    SUCCESS
};

typedef struct arraylist {
    int capacity;   // how many elements can currently fit in
    int *content;   // pointer to array with content
    int size;       // current number of elements
} arraylist_t;

/*
 * Returns pointer to freshly created arraylist which
 * can hold INITIAL_SIZE elements.
 */
arraylist_t* new_arraylist() {
    arraylist_t *init = (arraylist_t*)malloc(sizeof (arraylist_t));
    int *content = malloc(INITIAL_CAPACITY);

    init->capacity = INITIAL_CAPACITY;
    init->content = content;
    init->size = 0;
    
    return init;
}

/*
 * Returns size of given list.
 */
int arraylist_size(arraylist_t *list) {
    return list->size;
}

/*
 * Enlarges the capacity of given list (doubles it).
 * Returns SUCCESS if allocation was possible, else FAILURE.
 */
int arraylist_enlarge(arraylist_t *list) {
    if((list->content = realloc(list->content, 2*list->capacity))==NULL) {
        return FAILURE;
    }
    list->capacity *= 2;
    return SUCCESS;
}

/*
 * Appends element to list (next free slot).
 * Returns SUCCESS if appending was successfull, else FAILURE.
 */
int arraylist_append(arraylist_t *list, int val) {
    if(list->size==list->capacity){     // list is full -> enlarge
        if(arraylist_enlarge(list)==FAILURE)
        return FAILURE;
    }
    list->content[list->size] = val;
    list->size++;
    return SUCCESS;
}

/*
 * Prepends a value to the list (add at index 0).
 * Returns SUCCESS if prepending was successfull, else FAILURE.
 */
int arraylist_prepend(arraylist_t *list, int val) {
    if(list->size==list->capacity){     // list is full -> enlarge
        if(arraylist_enlarge(list)==FAILURE)
        return FAILURE;
    }
    for(int i=list->size; i>0; i--) {
        // move each element one slot up
        list->content[i] = list->content[i-1];
    }
    list->content[0] = val;
    list->size++;
    return SUCCESS;
}

/*
 * Gets element from list at given index.
 * Index must be between 0 and arraylist_size(arraylist_t*)-1.
 */
int arraylist_get(arraylist_t *list, int idx) {
    return list->content[idx];
}

/*
 * Removes element from list at given index.
 * Returns SUCCESS if removal was successfull, else FAILURE.
 */
int arraylist_remove(arraylist_t *list, int idx) {
    if(idx<0 || idx >= list->size) {
        return FAILURE;
    }
    for(int i=0; i<list->size-1; i++) {
        list->content[i] = i < idx ? list->content[i] : list->content[i+1];
    }
    return SUCCESS;
}

/* Nur zum Testen */
void list_list(arraylist_t *list) {
    for(int i=0; i<list->size; i++) {
        printf("%d\n", list->content[i]);
    }
}

int main() {
    arraylist_t *list = new_arraylist();
    
    printf("size before insertion: %d\n", arraylist_size(list));
    arraylist_append(list, 1);
    arraylist_append(list, 2);
    arraylist_append(list, 3);
    arraylist_append(list, -3534);
    arraylist_append(list, 334);

    printf("size after insertion: %d\n", arraylist_size(list));
    printf("capacity after insertion: %d\n", list->capacity);
    printf("inserted value: %d\n", arraylist_get(list, 1));

    arraylist_prepend(list, 14);
    printf("size after insertion: %d\n", arraylist_size(list));
    printf("inserted value: %d\n", arraylist_get(list, 0));
    printf("listing of values:\n");
    list_list(list);
    printf("\n");
    arraylist_remove(list, 3);
    list_list(list);

    return 0;
}