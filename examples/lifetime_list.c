/** @file lifetime_list.c -- Single Linked-list implementation of the lifetime (lt) variable.
 *
 * Copyright (C) Oscar Novo
 *
 * This file is part of the CoAP library libcoap. Please see README for terms of
 * use.
 *
 * lifetime_list is a single Linked-List implementation that stores the lifetimes of the resources.
 * lifetime_list provides uniformly named methods to insert, delete, display, and read an
 * element at the beginning of the list. These operations allow lifetime_list
 * to be used as a single-ended queue.
 *
 * @code
 *  [Conceptional Data Structure Diagram]
 *
 *  last~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
 *                                                          |
 *          +-----------+  single  +-----------+  single  +-|---------+
 *  first~~~|~>   0     |~~~~~~~~~~|~>   1     |~~~~~~~~~~|~>   N     |
 *          +-----|-----+  linked  +-----|-----+  linked  +-----|-----+
 *                |                      |                      |
 *          +-----v---------------+      |                +-----v-----+
 *          | DATA A              |      |                | DATA N    |
 *          +---------------------+      |                +-----------+
 *                 +---------------------v------------------+
 *                 | DATA B                                 |
 *                 +----------------------------------------+
 * @endcode
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include "lifetime_list.h"

static void append(unsigned long int num, coap_resource_t *node)
{
    struct node *temp,*right;
    temp= (struct node *)malloc(sizeof(struct node));
    temp->time=num;
    temp->resource=node;
    right=(struct node *)head;
    while(right->next != NULL)
    right=right->next;
    right->next =temp;
    right=temp;
    right->next=NULL;
}
 
 
 
static void add( unsigned long int num, coap_resource_t *node )
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->time=num;
    temp->resource=node;
    if (head== NULL)
    {
    head=temp;
    head->next=NULL;
    }
    else
    {
    temp->next=head;
    head=temp;
    }
}
static void addafter(unsigned long int num, int loc, coap_resource_t *node )
{
    int i;
    struct node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(struct node *)malloc(sizeof(struct node));
    temp->time=num;
    temp->resource=node;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}

void  display(item *r)
{
    r=head;
    if(r==NULL)
    {
    return;
    }
    while(r!=NULL)
    {
    printf("%zu ",r->time);
    r=r->next;
    }
    printf("\n");
}

/**
 * Create new linked-list
 *
 *
 * @return returns NULL.
 *
 * @code
 *  init_list();
 * @endcode
 *
 */
 
void init_list(){
    head=NULL;
}

/**
 * read_first(): Read the lifetime of the first element in the list.
 *
 *
 * @return lifetime of the first element of the list.
 *
 */
unsigned long int read_first(){
    item *r;
    r=head;
    if(r==NULL)
    {
    return 0;
    }
    else {
    return(r->time);
    }
}

/**
 * insert(): Insert a new element in the list sorted by time.
 *
 * @param lifetime  time to timeout the element 
 * @param resource pointer to the resource.
 *
 * @return returns NULL.
 *
 */
void insert(unsigned long int lifetime, struct coap_resource_t *resource)
{
    int c=0;
    struct node *temp;
    temp=head;
    if(temp==NULL)
    {
    add(lifetime, resource);
    }
    else
    {
    while(temp!=NULL)
    {
        if(temp->time<lifetime)
        c++;
        temp=temp->next;
    }
    if(c==0)
        add(lifetime, resource);
    else if(c<count())
        addafter(lifetime,++c, resource);
    else
        append(lifetime, resource);
    }
}

/**
 * deleteIfExist(): Delete all the elements in the list with the especific time and key.
 *
 * @param t lifetime.
 * @param key key of the resource in the hash table
 *
 * @return 1 if an element (or many elements) has been deleted from the list, 0 otherwise. 
 *
 * @note
 *  This function can delete several elements at the same time.
 */ 
int deleteIfExist(unsigned long int t, coap_key_t key)
{
    struct node *temp, *prev=NULL;
    temp=head;
    int found = 0;

    while(temp!=NULL)
    {
    if(temp->time==t)
    {
        /*TODO check that the 'key' in the hash table is the same before removing the element */
        if(temp==head)
        {
        head=temp->next;
        free(temp);
	temp=head;
        found = 1;
        }
        else
        {
        prev->next=temp->next;
        free(temp);
        temp=prev;
	found = 1;
        }
    }
    else if(temp->time>t){
        return found;
    }
    else
    {
        prev=temp;
        temp= temp->next;
    }
    }
    return found;
}

/**
 * timeout(): Delete all the elements in the list that timeout.
 *
 * @param timeout timeout.
 *
 * @return 1 if an element (or many elements) has been deleted from the list, 0 otherwise. 
 *
 * @note
 *  This function can delete several elements at the same time.
 */ 
int timeout(unsigned long int timeout)
{
    struct node *temp, *prev=NULL;
    temp=head;
    int found = 0;

    while(temp!=NULL)
    {
    if(temp->time<=timeout)
    {
        if(temp==head)
        {
        head=temp->next;
        free(temp);
	temp=head;
        found = 1;
        }
        else
        {
        prev->next=temp->next;
        free(temp);
        temp=prev;
	found = 1;
        }
    }
    else if(temp->time>timeout){
        return found;
    }
    else
    {
        prev=temp;
        temp= temp->next;
    }
    }
    return found;
}
 
/**
 * count(): Returns the number of elements in the list.
 *
 *
 * @return returns the number of elements in the list. 
 *
 */ 
int count()
{
    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
    n=n->next;
    c++;
    }
    return c;
}
