/* a list struct lib
 * copyright @DingKai
 */
#include <stdio.h>

#ifndef _LIB_LIST_H
#define _LIB_LIST_H


typedef struct list_head 
{
    struct list_head* prev;
    struct list_head* next;

} list_head_t;



#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
/*
 * get the struct for this entry
 * @ptr:
 * @type:
 * @member:
 */
#define list_entry(ptr, type, member) \
    ({const typeof(((type *)0)->member)* __mptr = (ptr); \
     (type*)((char *)__mptr - offsetof(type, member));})


/*
 * list_for_each: iterate over a list
 * @iter: the struct list_head* to use as a loop cursor
 * @head: the head of your list
 * Note:  it's not safe, if you delete an entry from list in list_for_each
 *        the next access will be undefined, in this case, you'd better use 
 *        list_for_each_safe
 */
#define list_for_each(iter, head) \
    for(iter = (head)->next; iter != (head); iter = iter->next)

#define list_for_each_safe(iter, n, head) \
    for(iter = (head)->next, n = iter->next; \
        iter != (head); iter = n, n = n->next)



/*
 * get length of given list
 * @: given list
 * TODO:which kind data type we should return?
 * 
 */
static inline int list_len(struct list_head *l)
{
    int    length = 0;
    struct list_head *tmp = NULL;

    list_for_each(tmp, l) {
        length++;
    }
    return length;
}



static inline void list_init(struct list_head *l)
{
    l->prev = l;
    l->next = l;
}



/**
 * Insert a new entry between two known consecutive entries
 */
static inline void __list_add(struct list_head *new,
                     struct list_head *prev,
                     struct list_head *next)
{
    prev->next = new;
    new->prev = prev;
    new->next = next;
    next->prev = new;
}



/**
 * list_add: add an new entry
 * @new: new entry to be added
 * @head:list head to add it after
 *
 * Insert a new entry after the specified head
 */
static inline void list_add(list_head_t* new, list_head_t* head)
{
    __list_add(new, head, head->next);
}



/*
 * delete a list entry by making the prev/next
 * point to each other
 */
static inline void __list_del(struct list_head *prev,
                              struct list_head *next )
{
    prev->next = next;
    next->prev = prev;
}



/**
 * list_del: delete an entry
 * @entry: entry to be deleted
 */
static inline void list_del(list_head_t* entry)
{
    __list_del(entry->prev, entry->next);
    /* what we should make, NULL or @entry itself?
     * in kernel, it makes LIST_POISON1 & LIST_POISON2
     * But why ?
     */
    entry->prev = entry;
    entry->next = entry;
}


#endif
