#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct node
{
   int a;
   struct list_head l;
};



int main()
{
    struct list_head test_list, *it, *tmp;
    struct node *n;
    int i;

    list_init(&test_list);

    /*
     * list_add test
     * insert ten nodes to test_list
     * insert node after head each time 
     */
    for(i = 0; i < 10; i++) {
        n = (struct node*)malloc(sizeof(*n));
        n->a = i;
        list_add(&(n->l), &test_list);
    }


    if(list_len(&test_list) != 10) {
        printf("we expected list len:10, but got: %d\n", list_len(&test_list));
        return -1;
    }
    
    /* 
     * macro list_for_each test
     */
    i = 0;
    list_for_each(it, &test_list) {
        printf("Node %d: %d\n", i, list_entry(it, struct node, l)->a);
        i++;
    }

    /*
     * list_del() test
     */
    list_for_each_safe(it, tmp, &test_list) {
        list_del(it);
        printf("Delte node: %d\n", list_entry(it, struct node, l)->a);
    }

    /*
     * afetr delete, test whether list_size() is 0 
     */
    if(list_len(&test_list) != 0) {
        printf("we expected list len is 0, but got: %d\n", list_len(&test_list));
        return -1;
    }
    


    /*
     * list_add test
     * insert ten nodes to test_list
     * insert node before head each time 
     */
    for(i = 0; i < 10; i++) {
        n = (struct node*)malloc(sizeof(*n));
        n->a = i;
        list_add(&(n->l), test_list.prev);
    }


    if(list_len(&test_list) != 10) {
        printf("we expected list len:10, but got: %d\n", list_len(&test_list));
        return -1;
    }
    
    /* 
     * macro list_for_each test
     */
    i = 0;
    list_for_each(it, &test_list) {
        printf("Node %d: %d\n", i, list_entry(it, struct node, l)->a);
        i++;
    }

    /*
     * list_del() test
     */
    list_for_each_safe(it, tmp, &test_list) {
        list_del(it);
        printf("Delte node: %d\n", list_entry(it, struct node, l)->a);
    }

    /*
     * afetr delete, test whether list_size() is 0 
     */
    if(list_len(&test_list) != 0) {
        printf("we expected list len is 0, but got: %d\n", list_len(&test_list));
        return -1;
    }

    return 0;
}
