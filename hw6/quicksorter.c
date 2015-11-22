/* 
 * This program sorts integers using the quicksort algorithm.
 * All values and flags are passed in by standard input.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "memcheck.h"

int main(int argc, char *argv[]);
node *quicksort(node *n);
void usage(char programName[]);


int main(int argc, char *argv[]) 
{
    int numCount = 0;
    int printValues = 1;
    int i;
    node *list, *sort;

    if (argc == 1)
    {
        usage(argv[0]);
        exit(1);
    }

    /* Loop through all command line arguments. */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            printValues = 0;
        }
        else 
        {
            /* Build the linkedlist, using a string to integer
             * conversion. */
            list = create_node(atoi(argv[i]), list);
            numCount++;
        }
    }

    /* If no numbers are passed in, display error in the form of a
     * usage statement, and exit. */
    if (numCount == 0)
    {
        usage(argv[0]);
        exit(1);
    }

    /* Now, sort the linkedlist using the quicksort function. */
    sort = quicksort(list);
    free_list(list);

    /* Finally, if the [-q] flag given, suppress any output.
       Otherwise, print out the values in the array on a separate line. */
    if (printValues)
    {
        print_list(sort);
    }

    free_list(sort);

    print_memory_leaks();

    return 0;
}

/* 
 * This function uses the quicksort algorithm to sort
 * the given linkedlist.

 * node : the node at the head of the linkedlist
 * returns: the head of a copy of a sorted version of the given linkedlist
*/
node *quicksort(node *n)
{
    node *sorted;

    /* If node is either null, or the end of a list, it is already sorted. */
    if (n == NULL || n->next == NULL)
    {
        sorted = copy_list(n);
    }
    /* Otherwise, use the quicksort algorithm. */
    else
    {
        node *loop, *first, *small, *large,
            *small_sort, *large_sort, *small_first_sort;
        small = NULL;
        large = NULL;

        /* First, create a copy of the first element. */
        first = create_node(n->data, NULL);
        loop = n->next;

        /* Create linkedlists that have values smaller and larger than 
            the value of the first element. */
        while (loop != NULL)
        {
            if (loop->data < first->data)
            {
                small = create_node(loop->data, small);
            }
            else
            {
                large = create_node(loop->data, large);
            }
            loop = loop->next;
        }
        free_list(loop);

        /* Sort the smaller and larger lists */
        small_sort = quicksort(small);
        free_list(small);

        large_sort = quicksort(large);
        free_list(large);

        /* Append the lists together, and return the result. */
        small_first_sort = append_lists(small_sort, first);
        free_list(small_sort);
        free_list(first);

        sorted = append_lists(small_first_sort, large_sort);
        free_list(large_sort);
        free_list(small_first_sort);
    }

    assert(is_sorted(sorted));
    return sorted;

}

/* 
 * Print usage statement for this program. Used when an error is
 * generated, or the program is called incorrectly.
*/
void usage(char programName[])
{
    fprintf(stderr, "usage: %s [-q] n1 [n2 ...]\n \
        n1, n2, etc.: integers\n", programName);
}
