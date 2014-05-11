/*
 * Red Black tree implemention. 
 * (C) 2014 DingKai<tracymacding@gmail.com>
 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _LIB_RBTREE_H
#define _LIB_RBTREE_H

#include <stdint.h>


#define RB_BLACK 0
#define RB_RED   1

struct rb_node {
    uint8_t color;
    struct  rb_node *rb_parent;
    struct  rb_node *rb_left;
    struct  rb_node *rb_right;
};


#define rb_set_left(p, c) { (p)->rb_left = c; c->rb_parent = (p); }
#define rb_set_right(p, c) { (p)->rb_right = c; c->rb_parent = (p); }
#define rb_left(p) (p)->rb_left
#define rb_right(p) (p)->rb_right
#define rb_parent(p) (p)->rb_parent

#define rb_color(n)  (n)->color
#define rb_set_color(n, color)  (n)->color = color



static void 
void rb_insert(struct rb_node*);
void rb_delete(struct rb_node*);

#endif
