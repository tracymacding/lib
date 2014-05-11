#include "rbtree.h"
#include <stdio.h>


/*
 * left rotate under n, example:
 *      (n)                    (q)
 *      / \    left_rotate     / \
 *    (p) (q)  ----------->  (n) (y)
 *        / \  with node n   / \
 *      (x) (y)            (p) (x)
 */
static void rb_left_rotate(struct rb_node *n)
{
    struct rb_node *q = rb_right(n);
    struct rb_node *x = rb_left(q);

    rb_set_left(q, n);
    rb_set_right(n, x);
}


/*
 * right rotate under n, example:
 *      (n)                     (p)
 *      / \    right_rotate     / \
 *    (p) (q)  ----------->   (x) (n)
 *    / \      with node n        / \
 *  (x) (y)                     (y) (q)   
 */
static void rb_right_rotate(struct rb_node *n)
{
    struct rb_node *p = rb_left(n);
    struct rb_node *y = rb_right(p);

    rb_set_right(p, n);
    rb_set_left(n, y);
}


/*
 * insert a new rb node into root
 * @new: rb node to be inserted whose color is RB_RED
 * @root:root node of a rbtree new will be inserted
 */
void rb_insert(struct rb_node *new, struct rb_node *root)
{
    struct rb_node *parent, *gparent, *uncle;

    for(;;) {
        parent = rb_parent(new);
        /*
         * case1: new node is root
         * set color RB_BLACK and return
         */
        if(root == new) {
            rb_set_color(new, RB_BLACK);
            break;
        }
        /*
         * case2: parent node is RB_BLACK
         * do nothing
         */
        if(rb_color(parent) == RB_BLACK) {
            break;
        }

        /*
         * case3: parent color is RB_RED, in this case
         * gparent node can not be NULL
         */
        gparent = rb_parent(parent);
        assert(gparent != NULL);

        if(parent == rb_right(gparent)) {
            uncle = rb_left(gparent);
        } else {
            uncle = rb_right(gparent);
        }

        /* parent color is RB_RED */
        switch(rb_color(uncle)) {
            /* case3-1: parent and uncle are RB_RED, in this case
             * 1). set parent RB_BLACK;
             * 2). set uncle  RB_BLACK;
             * 3). set gparent RB_RED;
             * 4). make gparent as current node and bottom up
             */
            case RB_RED:
                rb_set_color(parent,  RB_BLACK);
                rb_set_color(uncle,   RB_BLACK);
                rb_set_color(gparent, RB_RED);
                new = gparent;
                break;
            case RB_BLACK:
                /*
                 * case3-2: parent and uncle are RB_RED, and new is right child of parent
                 * in this case
                 * 1). reset new = parent
                 * 2). left rotate with parent
                 */
                if(new == rb_right(parent)) {
                    new = parent;
                    rb_left_rotate(parent);
                /*
                 * case3-3: parent and uncle are RB_RED, and new is left child of parent
                 * in this case
                 * 1). set parent RB_BLACK
                 * 2). set gparent RB_RED
                 * 3). right rotate with gparent
                 */
                } else {
                    rb_set_color(parent, RB_BLACK);
                    rb_set_color(gparent, RB_RED);
                    rb_right_rotate(gparent);
                }
                break;
            default:
                break;
        }
    }
}

