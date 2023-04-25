#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "int_to_str.h"


char * int_to_string (unsigned int x){
    char str [11];
    bool ya_tomo_el_primer_digito = false;
    int y;
    unsigned int temp = x;

    for (int i = 9; i >= 0; i--)
    {
        unsigned int divisor = 1;
        
        for (int j = 0; j < i; j++)
        {
            divisor = divisor * 10;
        }

        y = temp / divisor;
        
        if (y >= 1 || ya_tomo_el_primer_digito)
        {
            ya_tomo_el_primer_digito = true;

            if (y < 1)
            {
                str[9-i] = '0';
            }
            else if (y < 2)
            {
                str[9-i] = '1';
                temp = temp - divisor;
            }
            else if (y < 3)
            {
                str[9-i] = '2';
                temp = temp - (2 * (divisor));
            }
            else if (y < 4)
            {
                str[9-i] = '3';
                temp = temp - (3 * (divisor));
            }
            else if (y < 5)
            {
                str[9-i] = '4';
                temp = temp - (4 * (divisor));
            }
            else if (y < 6)
            {
                str[9-i] = '5';
                temp = temp - (5 * (divisor));
            }
            else if (y < 7)
            {
                str[9-i] = '6';
                temp = temp - (6 * (divisor));
            }
            else if (y < 8)
            {
                str[9-i] = '7';
                temp = temp - (7 * (divisor));
            }
            else if (y < 9)
            {
                str[9-i] = '8';
                temp = temp - (8 * (divisor));
            }
            else{
                str[9-i] = '9';
                temp = temp - (9 * (divisor));
            }
        }
        else
        {
            str[9-i] = 'a';
        }
    }

    str [10] = '\0';
    char * res = malloc(sizeof(char) * 11);
    res = strcpy (res, str);
    return res;
}