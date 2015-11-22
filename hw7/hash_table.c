/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

/* Takes a string and produces a hash value for it in the
   range [0, NSLOTS) */
int hash(char *s)
{
    int h = 0;
    char *loop = s;
    /* Loop through the characters of the string, cast to int, 
        take the sum mod NSLOTS */
    while (*loop)
    {
        h += (int) *loop;
        h %= NSLOTS;
        loop++;
    }
    return h;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *n = (node *) malloc(sizeof(node));
    n->key = key;
    n->value = value;
    return n;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *f;
    int count = 0;
    while (list)
    {
        f = list;
        list = list->next;
        free(f->key);
        free(f);
        count++;
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table *h = (hash_table *) malloc(sizeof(hash_table));
    
    /* slot is filled with NSLOTS null linked lists */
    h->slot = (node **) malloc(NSLOTS * sizeof(node *));
    return h;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    node **slot;
    slot = &ht->slot[0];
    /* Simply loop through the linked lists and free them */
    for (i = 0; i < NSLOTS; i++)
    {
        free_list(*slot);
        slot++;
    }
    /* Free the struct's slot pointer and the struct pointer itself */
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int h = hash(key);
    node *list = ht->slot[h];
    /* If the linked list at the hash value is null, 
        it is not in the hash table */
    if (list == NULL) 
    {
        return 0;
    }
    /* Otherwise, loop over the linked list to search for it */
    while (list)
    {
        if (strcmp(list->key, key) == 0)
        {
            return list->value;
        }
        list = list->next;
    }
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    node *first, *list;
    int h = hash(key);

    first = ht->slot[h];
    list = first;
    /* Loop through the linked list at the hashed location */
    while(list)
    {
        /* If a match for the key is found, set the new value */
        if(strcmp(list->key, key) == 0)
        {
            list->value = value;
            /* With a match, additionally free the key value */
            free(key);
            return;
        }
        list = list->next;
    }
    /* If no match is found, create a node and update the linked list */
    list = create_node(key, value);
    list->next = first;
    ht->slot[h] = list;
}

/* Print out the contents of a linked list as key/value pairs. */
void print_linked_list(node *n)
{
    /* Print out each node in the linked list, as a
        key/value pair, (key, value) */
    while (n)
    {
        printf("%s %i\n", n->key, n->value);
        n = n->next;
    }
}

/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node **slot;
    slot = &ht->slot[0];
    /* Loop through the linked lists in the hash table, 
        and print them */
    for (i = 0; i < NSLOTS; i++)
    {
        print_linked_list(*slot);
        slot++;
    }
}

