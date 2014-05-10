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
    struct list_head test_list, *it;
    struct node *n;
    int i;

    list_init(&test_list);

    /*
     * insert ten nodes to test_list
     */
    for(i = 0; i < 10; i++) {
        n = (struct node*)malloc(sizeof(*n));
        n->a = i;
        list_add(&(n->l), &test_list);
    }
    
    // traverse all list node
    i = 0;
    list_for_each(it, &test_list) {
        printf("node %d: %d\n", i, list_entry(it, struct node, l)->a);
        i++;
    }
}
