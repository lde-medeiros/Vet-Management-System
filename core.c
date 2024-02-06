
#define _CRT_SECURE_NO_WARNINGS
// System Libraries
#include <stdio.h>
#include <ctype.h>
// User-Defined Libraries
#include "core.h"

// Function to clear the standard input buffer (modifications had to be made like EOF)
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // do nothing!
    }
}
// Function to wait for the user to input the enter key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
// Function to get integer input
int inputInt(void)
{
    int value, keeptrying = 1, rc;
    char after;
    do {
    rc = scanf("%d%c",&value,&after);
    if (rc == 0 || after != '\n')
    {
        printf("Error! Input a whole number: ");
        clearInputBuffer();
    }
    else
    {
        keeptrying = 0;
    }
} while (keeptrying == 1);

    return value;
}
// Function to get positive int input
int inputIntPositive(void)
{
    int value, keeptrying = 1, rc;
    char after;
    do {
        rc = scanf("%d%c", &value, &after);
        if (rc == 0 || after != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            keeptrying = 0;
        }
    } while (keeptrying == 1);
    return value;
}
//Function to get int input within a range
int inputIntRange(int lowerBound,int upperBound)
{
    int value, keeptrying = 1, rc;
    char after;
    do {
        rc = scanf("%d%c", &value, &after);
        if (rc == 0 || after != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else if (value < lowerBound || value > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ",lowerBound,upperBound);
        }
        else
        {
            keeptrying = 0;
        }
    } while (keeptrying == 1);
    return value;
}
// Function to get char input to match any char in the string
char inputCharOption(char* validChars)
{
    int i, keeptrying = 1, rc;
    char letter, after;
    do
    {
        rc = scanf(" %c%c", &letter, &after);
        if (rc == 0 || after != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
            clearInputBuffer();
        }
        else
        {
            i = 0;
            while (validChars[i] != '\0' && keeptrying == 1)
            {
                if (letter == validChars[i])
                {
                    keeptrying = 0;
                }
                i = i +1;
            }

            if (keeptrying == 1)
            {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }
    } while (keeptrying == 1);
    return letter;
}
// Function to get a string within a range of length (min and max)
void inputCString(char* cString, int minNumChars, int maxNumChars)
{
    int i, length = 0, keeptrying = 1;
    char value[100] = {'\0'};
    do
    {
        scanf("%[^\n]",value);
        clearInputBuffer();
        length = 0;
        for (i = 0; value[i] != '\0'; i++)
        {
            length++;
        }
        if (minNumChars == maxNumChars && length != minNumChars)
        {
            printf("Invalid %d-digit number! Number: ", minNumChars);
        }
        else if (length > maxNumChars)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxNumChars);
        }
        else if (length < minNumChars)
        {
            printf("ERROR: String length must be between %d and %d chars: ",minNumChars,maxNumChars);
        }

        else
        {
            keeptrying = 0;
            for (i = 0; value[i] != '\0'; i++)
            {
                cString[i] = value[i];
            }
            cString[i] = '\0';
        }
    } while (keeptrying == 1);
    return;
}
//Function to format and display a phone num 
void displayFormattedPhone(const char* cString)

{
    int i, j, allDigits = 1;
    char phoneNum[14] = {'\0'};
    for (i = 0; i < 13; i++)
    {
        if (i == 0)
        {
            phoneNum[i] = '(';
        }
        else if (i == 4)
        {
            phoneNum[i] = ')';
        }
        else if (i == 8)
        {
            phoneNum[i] = '-';
        }
        else
        {
            phoneNum[i] = '_';
        }
    }
    if (cString ==NULL)
    {
            printf("%s",phoneNum);
    }
    else
    {
        for (i = 0; cString[i] != '\0'; i++)
        {
            if (isdigit(cString[i]) == 0)
            {
                printf("%s", phoneNum);
                allDigits = 0;
            }
        }
        if (i != 10)
        {
            printf("%s",phoneNum);
        }
        else if (allDigits == 1)
        {
            i = 0;
            for (j = 0; j < 13; j++)
            {
                if (j != 0 && j != 4 && j != 8)
                {
                    phoneNum[j] = cString[i];
                    i++;
                }
            }
            printf("%s", phoneNum);
        }
    }
    return;
}