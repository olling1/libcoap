/*
 * lifetime_list.h -- Linked-list that stores the lifetime of every resource in the resource directory
 *
 * Copyright (C) Oscar Novo
 *
 * This file is part of the CoAP library libcoap. Please see README for terms
 * of use.
 */

/**
 * @file Lifetime_list.h
 * @brief Linked-list 
 */

#ifndef LIFETIME_LIST_H
#define LIFETIME_LIST_H

#include "resource.h"

/* types */
typedef struct node item;
item *head;

/* member functions */
void init_list(void);
void insert(unsigned long int timeout, coap_resource_t *resource);
int deleteIfExist(unsigned long int t, coap_key_t key);
int timeout(unsigned long int timeout);
void display(item *r);
int count(void);
unsigned long int read_first(void);

/**
 * list node data structure.
 */

struct node
{
    struct coap_resource_t *resource;	/*!< hash handle */
    unsigned long int time;	/*!< data */
    struct node *next;		/*!< next link */
};

#endif /* LIFETIME_LIST_H */

