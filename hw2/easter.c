/* 
 * Computes the date in March or April of Easter in a particular calendar
 * year using the algorithm given by Donald Knuth. Reads a list of years
 * in from stdin and outs all dates to stdout. Additionally confirms that
 * Easter day is a Sunday using Zeller's Congruence.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int calculate_Easter_date(int year);
int calculate_Easter_day_of_week(int easter_day, int year);

int main(void)
{
    /* Variables used for calculation of Easter's day */ 
    int year, scanf_return, easter_day;

    while(1)
    {
        /* Scan in year from stdin (typically test file) */ 
        scanf_return = scanf("%d", &year);

        /* Break out of loop when all years have been scanned */
        if (scanf_return == EOF)
        {
            break;
        }

        /* Calculate Easter Day */
        easter_day = calculate_Easter_date(year);

        /* If returned value is 0, given year was not valid */
        if (easter_day == 0)
        {
            fprintf(stderr, 
                "Year %i not in supported range [1582, 39999]", 
                year);
        }
        else if (easter_day > 0)
        {
            /* Use Zeller's Congruence to check that Easter Day is a Sunday */
            assert(calculate_Easter_day_of_week(easter_day, year) == 1);

            /* Output result to stdout */
            printf("%i - April %i\n", year, easter_day);
        }
        else
        {
            /* Use Zeller's Congruence to check that Easter Day is a Sunday */
            assert(calculate_Easter_day_of_week(easter_day, year) == 1);

            /* Output result to stdout */
            printf("%i - March %i\n", year, -1 * easter_day);
        }

    }

    return 0;
}

/* 
 * Computes the date of Easter for a particular year.
 * Uses the algorithm given by Donald Knuth with a modification that
 * the return value is negative if the date is in March, and positive
 * if it is in April.
 * 
 * [year] specifies the year to find the date of Easter in.
 *   NOTE: must be in the range [1582, 39999], otherwise return 0
 */
int calculate_Easter_date(int year)
{
    int golden_year, century, skipped_leap_years, correction_factor,
        modded_date, epact, date;

    /* Check if year is in supported range 
     * If not, return special value of 0.
     */
    if (year < 1582 || year > 39999)
    {
        return 0;
    }

    /* Compute golden year in 19-year Metonic cycle */
    golden_year = (year % 19) + 1;

    /* Compute century */
    century = year / 100 + 1;

    /* Compute number of skipped leap-years  */
    skipped_leap_years = 3 * century / 4 - 12;

    /* Compute lunar correction factor based on the moon's orbit */
    correction_factor = (8 * century + 5) / 25 - 5;

    /* Compute D where March ((-D) mod 7 + 7 is a Sunday) */
    modded_date = 5 * year / 4 - skipped_leap_years - 10;

    /* Compute epact, specifying when a full moon occurs */
    epact = (11 * golden_year + 20 + correction_factor 
                - skipped_leap_years) % 30;
    if ((epact == 25 && golden_year > 11) || epact == 24)
    {
        epact++;
    }

    /* Compute calendar full moon as "March date" */
    date = 44 - epact;
    date = date < 21 ? date + 30 : date;

    /* Compute the Sunday after the full moon */
    date = date + 7 - ((modded_date + date) % 7);

    /* Returns date in April */
    if (date > 31)
    {
        return date - 31;
    }
    /* Returns date in March */
    else
    {
        return -1 * date;
    }
}

/* 
 * Computes the day of the week of a particular Easter day.
 * Uses the algorithm at: en.wikipedia.org/wiki/Zeller's_congruence
 *
 * [easter_day] specifies the day of Easter, multipled by -1 if it in March
 * [year] is the corresponding year that has that day as Easter
 */
int calculate_Easter_day_of_week(int easter_day, int year)
{
    /* Variables used in Zeller's Congruence to confirm Easter is Sunday */
    int century_year, century, month, day_of_week;

    century_year = year % 100;
    century = (int) floor(year / 100);

    /* Indicates Easter is in April */ 
    if (easter_day > 0)
    {
        month = 4;
    }
    /* Indicates Easter is in March, and our day is negative (hacky) */
    else
    {
        month = 3;
        easter_day *= -1;
    }

    /* Compute day of the week from Zeller's Congruence */
    day_of_week = 
        (
        easter_day + 
        (int) floor(13 * (month + 1) / 5) + 
        century_year + 
        (int) floor(century_year / 4) + 
        (int) floor(century / 4) + 
        5 * century
        ) % 7;

    return day_of_week;
}
