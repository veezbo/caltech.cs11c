#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "memcheck.h"

void calculateNextGeneration(int size, int prev[], int next[]);
void printArray(int size, int array[]);


int main(int argc, char *argv[])
{

    int numCells, numGens, *cells, *cells2, *cells_loop, *cells2_loop, i;

    /* Print usage when we don't have the three arguments necessary */
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s (numCells) (numGens)\n", argv[0]);
        exit(1);
    }

    numCells = atoi(argv[1]);
    numGens = atoi(argv[2]);

    /* Seed random number generator */
    srand(time(0));

    cells = (int *) malloc (numCells * sizeof(int));
    cells2 = (int *) malloc (numCells * sizeof(int));

    if (cells == NULL || cells2 == NULL)
    {
        fprintf(stderr, "Memory Allocation Failure!\n");
        exit(1);
    }

    /* Initialize the arrays with random values */
    cells_loop = cells;
    cells2_loop = cells2;
    for (i = 0; i < numCells; i++)
    {
        int randomBit = rand() % 2;
        *cells_loop = randomBit;
        *cells2_loop = randomBit;
        cells_loop++;
        cells2_loop++;
    }

    /* Print the first generation. */
    printArray(numCells, cells);

    /* Alternate between two arrays, calculating the next generation and
        printing the automaton out. */
    for (i = 0; i < numGens; i++)
    {
        if (i % 2 == 0)
        {
            calculateNextGeneration(numCells, cells, cells2);
            printArray(numCells, cells2);
        }
        else
        {
            calculateNextGeneration(numCells, cells2, cells);
            printArray(numCells, cells);
        }
    }

    free(cells);
    free(cells2);

    print_memory_leaks();

    return 0;
}

/* 
 * Computes the next generation given the previous one,
 * using the specific update rule given in the assignment.
 *
 * size: size of the automaton
 * *prev: pointer to the the previous generation
 * *next: the pointer of the memory to write the next generation to
 *
*/
void calculateNextGeneration(int size, int *prev, int *next)
{   
    int *pVal, *cVal, *nVal, i;

    *next = 0;
    *(next + (size - 1)) = 0;

    pVal = (prev);
    cVal = (prev + 1);
    nVal = (prev + 2);
    next++;

    for (i = 1; i < size - 1; i++)
    {
        if (*cVal == 0 && 
            ((*pVal == 1 && *nVal == 0) ||
                (*pVal == 0 && *nVal == 1)))
        {
            *next = 1;
        }
        else
        {
            *next = 0;
        }

        pVal++;
        cVal++;
        nVal++;
        next++;
    }
}

/* 
 * This function prints an array that represents a 1D
 * cellular automaton, printing '.' for an empty location
 * and '*' for a full location.

 * size : the size of the array given
 * array : the array that represents the automaton to print
*/
void printArray(int size, int *array)
{
    int i;
    for (i = 0; i < size; i++)
    {

        char c;
        if (*array == 0)
        {
            c = '.';
        }
        else
        {
            assert(*array == 1);
            c = '*';
        }
        printf("%c ", c);
        array++;
    }
    printf("\n");
}
