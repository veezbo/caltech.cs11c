/* 
 * This program sorts upwards of 32 integers using either minimum element
 * or bubble sort (as specified by flags), and optionally prints out
 * the sorted array. All values and flags are passed in by standard input.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* The maximum number of integers that this program will sort. */
#define MAXNUMS 32

int main(int argc, char *argv[]);
void minsort(int numElements, int array[]);
void bubblesort(int numElements, int array[]);
void usage(char programName[]);

int main(int argc, char *argv[]) 
{
    int nums[MAXNUMS];
    int numCount = 0;

    int sortBubble = 0;
    int printValues = 1;

    int i;

    /* Loop through all command line arguments. */
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            sortBubble = 1;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            printValues = 0;
        }
        else 
        {
            /* If the number of values passed in is too many, display error
             * in the form of a usage statement, and exit. */
            if (numCount >= MAXNUMS)
            {
                usage(argv[0]); 
                exit(1);
            }

            /* Else store that value in the array, using a string to integer
             * conversion. */
            nums[numCount] = atoi(argv[i]);
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

    /* If [-b] flag given, sort using bubble sort. */
    if (sortBubble)
    {
        bubblesort(numCount, nums);
    }
    /* Else, use minsort. */
    else 
    {
        minsort(numCount, nums);
    }

    /* Finally, if the [-q] flag given, suppress any output.
       Otherwise, print out the values in the array on a separate line. */
    if (printValues)
    {
        for (i = 0; i < numCount; i++)
        {
            printf("%i\n", nums[i]);
        }
    }

    return 0;
}

/* 
 * This function uses the minimum element sorting algorithm to sort the
 * input integer array.

 * numElements : the number of elements in the array
 * array : the array of integers to sort
*/
void minsort(int numElements, int array[])
{
    int start = 0;
    int smallest = start;
    int tempArrayStart;
    int index;
    int i;

    while (start < numElements)
    {
        /* Start search for the smallest element after all the'start'
         * smallest elements have already been found. */
        smallest = start;

        /* Search for the next smallest element */
        for (index = start; index < numElements; index++)
        {
            if (array[index] < array[smallest])
            {
                smallest = index;
            }
        }

        /* Swap that element with the element in the spot it should be in. */
        tempArrayStart = array[start];
        array[start] =  array[smallest];
        array[smallest] = tempArrayStart;

        start++;
    }

    /* Check that the array is sorted correctly. */
    for (i = 1; i < numElements; i++)
    {
        assert(array[i] >= array[i - 1]);
    }
}

/* 
 * This function uses the bubble sorting algorithm to sort the
 * input integer array.

 * numElements : the number of elements in the array
 * array : the array of integers to sort
*/
void bubblesort(int numElements, int array[])
{
    int i;
    int swapped = 1;
    int tempElement;

    do
    {
        /* Indicates whether this pass has had a swapping */
        swapped = 0;
        for (i = 1; i < numElements; i++)
        {
            /* If two adjacent elements are out of order, then swap them 
             * and mark that there was a swapping during this pass.
             */
            if (array[i - 1] > array[i])
            {
                tempElement = array[i];
                array[i] = array[i - 1];
                array[i - 1] = tempElement;
                swapped = 1;
            }
        }
    }
    while (swapped);

    /* Check that the array is sorted correctly. */
    for (i = 1; i < numElements; i++)
    {
        assert(array[i] >= array[i - 1]);
    }

}

/* 
 * Print usage statement for this program. Used when an error is
 * generated, or the program is called incorrectly.
*/
void usage(char programName[])
{
    fprintf(stderr, "usage: %s integers [-b] [-q]\n", programName);
}
