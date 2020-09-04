/**********************************************************************************************************************************
//
//  NAME:                         Marcos Buccat 
//
//  HOMEWORK:                     3b
//
//  CLASS:                        ICS 212
//
//  INSTRUCTOR:                   Ravi Narayan
//
//  DATE:                         February 13, 2020
//
//  FILE:                         user_interface.c
//
//  DESCRIPTION:
//    This file contains all of the user interface prototype and definition.
//    This will intereact with the user by prompting user to input the given 
//    options to add, print, remove or modify the records.
//
*************************************************************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int debugmode = 0;

void user_interface();
void getaddress(char[], int);
void get_user_input(char[], int);
void getname(char[], int);
void check_input(int*, int*, int*, char[]);

/*************************************************************************************************************************************
//
//  Function Name:                          main
//
//  DESCRIPTION:                            The main of this function to run the user interface_function
//
//  PARAMETERS:                             argc (int)      : The number of command line argument
//                                          argu (char * []): The actual argument inputed to the command line
//
//  Return Values:                          -1: The program cannont run due to incorrect comman inputed
//                                           1: Successfuly ran the program and in debug mode
//                                           0: Successfully ran the program but not in debug mode
//
*************************************************************************************************************************************/

int main(int argc, char * argu[])
{
    int result;

    result = -1;

    if (argc < 3)
    {
        if (argc == 2)
        {
            if (strcmp(argu[1], "debug") == 0)
            {
                debugmode = 1;
                printf("\n\t*** Degbug Mode ***\n\n");
                user_interface();
                result = 1;
            }

            if (strcmp(argu[1], "debug") != 0)
            {
                printf("Error, Incorrect Command for debug.");
                printf(" Enter \'debug\' after the executable.\n");
            }
        }

        if (argc == 1)
        {
            user_interface();
            result = 0;
        }
    }

    if (argc >= 3)
    {
        printf("Command Not recognized\n");
    }

    return result;
}

/*******************************************************************************************************************
//
//  Function Name:                        getAddress
//
//  DESCRIPTION:                          Gets the address from the user. This will keep accepting inputs from user
//                                        until the user enters a special key to stop inputing.
//
//  PARAMETERS:                           address (char *): The address array to store the address.
//                                        size (int)      : The maximize size of the array to store the address, which is
//                                                          (size - 2) to have enough space to input the enter key and null.    
//
//  RETURN VALUE:                         NONE
//
*********************************************************************************************************************/

void getaddress(char address[], int size)
{
    int running;
    int index;
    char input;
    char clear[100];
    char temp[80];

    running = 1;
    size = size - 2;
    index = 0;

    if (debugmode == 1)
    {
        printf("\n========================== Debug mode =========================\n\n");
        printf("\tEnter getaddress\n");
        printf("Stored in address: %s\n", address);
        printf("Max size: %d\n", size);
        printf("\nCan only accept 78 maximum charactors!\n");
    }
    printf("Enter \'$\' to input the Address\n");
    printf("Enter Address: ");

    while (running == 1)
    {
        input = fgetc(stdin);
        temp[index] = input;
        if (input == '$')
        {
            temp[index] = '\0';
            running = 0;
        }
        index++;
        if (index == size)
        {
            printf("Warning reached max size\n");
            running = 0;
        }
    }
    for (index = 0; temp[index] != '\0'; index++)
    {
        address[index] = temp[index];
    }

    address[index] = '\0';
    fgets(clear, 98, stdin);
    printf("\n");
    if (debugmode == 1)
    {
        printf("ADDRESS: %s\n", address);
        printf("\n======================= Exit get address  ======================\n\n");
    }
}

/*******************************************************************************************************************
//  Function Name:                        get_user_input
//
//  DESCRIPTION:                          Gets the option input from the user.
//
//  PARAMETERS:                           input (char *): The char array to store the input
//                                        size (int)      : The maximize size of the array to store the address, which is
//                                                          (size - 2) to have enough space to input the enter key and null.
//
//  RETURN VALUE:                         NONE
//
*********************************************************************************************************************/

void get_user_input(char input[], int size)
{
    int run;
    int index;
    char temp[100];
    char extra[10];
    char charac;

    index = 0;
    run = 1;
    size = size - 2;

    if (debugmode == 1)
    {
        printf("\n========================== Debug mode =========================\n\n");
        printf("\tEnter get_user_input\n");
        printf("Stored in input: %s\n", input);
        printf("Max size: %d\n", size);
        printf("Enter Input: ");
    }

    while (run == 1)
    {
        charac = fgetc(stdin);
        if (index >= size)
        {
            extra[0] = charac;
        }
        if (index != size)
        {
            temp[index] = charac;
        }
        if (charac == '\n')
        {
            run = 0;
        }
        if (index == size && debugmode == 1)
        {
            printf("Warrning max input!\n");
        }
        index++;
    }

    temp[index] = '\0';
    extra[0] = '\0';

    if (debugmode == 1)
    {
        printf("The Input:%s\nExtras:%s\n", temp, extra);
        printf("\n=================== Exit get user input ======================\n\n");
    }
    for (index = 0; temp[index] != '\0'; index++)
    {
        if (temp[index] == ' ')
        {
            temp[index] = '@';
        }
        input[index] = temp[index];
    }
    input[index] = '\0';
}

/*******************************************************************************************************************
//
//  Function Name:                        getname
//
//  DESCRIPTION:                          Gets the name from the user. This will keep accepting inputs from user
//                                        until the user enters a enter key to stop inputing.
//
//  PARAMETERS:                           name (char *): The address array to store the address.
//                                        size (int)   : The maximize size of the array to store the address, which is
//                                                       (size - 2) to have enough space to input the enter key and null.
//
//  RETURN VALUE:                         NONE
//
*********************************************************************************************************************/

void getname(char name[], int size)
{
    int run;
    int index;
    int count_ints;
    int accepted_char;
    int special_chars;
    int letters;
    char extra[100];
    int max_input;

    max_input = size - 2;
    run = 1;
    count_ints = 0;
    accepted_char = 0;
    special_chars = 0;
    letters = 0;

    if (debugmode == 1)
    {
        printf("\n========================== Debug mode =========================\n\n");
        printf("\tEnter getname\n");
        printf("Stored in input: %s\n", name);
        printf("Max size: %d\n", size);
    }
    while (run == 1)
    {
        printf("Enter Name: ");
        fgets(name, max_input, stdin);

        for (index = 0; name[index] != '\0'; index++)
        {
            if (name[index] == '.')
            {
                accepted_char++;
            }
            if (name[index] == '\n')
            {
                name[index] = '\0';
            }
        }
        index++;
        if (index >= max_input)
        {
            fgets(extra, 98, stdin);
            printf("%s\n", name);
        }

        check_input(&count_ints, &letters, &special_chars, name);
        special_chars = special_chars - accepted_char;

        if (debugmode == 1)
        {
            printf("Index: %d\nNumber of Ints: %d\n", index, count_ints);
            printf("Number of Letters: %d\n", letters);
            printf("Number of Special Chars: %d\n", (special_chars + accepted_char));
            printf("Acceptable char \'.\': %d\n", accepted_char);
        }

        if (special_chars > 0 && count_ints == 0 && letters == 0)
        {
            printf("Invalid name, \'Chars only detected\'. Try again\n");
        }
        if (special_chars == 0 && count_ints > 0 && letters == 0)
        {
            printf("Invalid name, \'Ints only detected\'. Try again\n");
        }
        if ((special_chars > 0 || count_ints > 0) && letters > 0)
        {
            printf("Invalid name, \'mix chars detected\'. Try again\n");
        }
        if (special_chars == 0 && count_ints == 0 && letters > 0)
        {
            run = 0;
        }
        accepted_char = 0;
    }

    if (debugmode == 1)
    {
        printf("\n========================= Exit get name ========================\n\n");
    }
}

/*******************************************************************************************************************
//
//  Function Name:                        check_input
//
//  DESCRIPTION:                          Checks the input for letters, numbers and special chars.
//                                        This function is used to check the getname inputs for special chars or
//                                        integers. And this function is used for get_user_input to check for letters
//                                        and special chars.
//
//  PARAMETERS:                           num_ints (int *)    : The address to store the number of integers read from input
//                                        num_letts (int *)   : The address to store the number of letters read from input
//                                        num_chars (int *)   : The address to store the number of speical chars read from input
//                                        input (char[])      : The input to be reading and looking for letters, special chars
//                                                              and integers.
//
//  RETURN VALUE:                         NONE
//
*********************************************************************************************************************/

void check_input(int * num_ints, int * num_letts, int * num_chars, char input[])
{
    int index;
    int non_letters;
    int letters;
    int special_char;

    non_letters = 0;
    letters = 0;
    special_char = 0;
    if (debugmode == 1)
    {
        printf("\n========================== Debug mode =========================\n\n");
        printf("\tEnter Check_input\n");
        printf("Checking input: %s\n", input);
        printf("Number of ints: %d\n", *num_ints);
        printf("Number of letters: %d\n", *num_letts);
        printf("Number of special chars: %d\n\n", *num_chars);
    }
    for (index = 0; input[index] != '\0'; index++)
    {
        if (input[index] >= '0' && input[index] <= '9')
        {
            non_letters++;
        }
        if ((input[index] >= 'a' && input[index] <= 'z') || (input[index] >= 'A' && input[index] <= 'Z'))
        {
            letters++;
        }
        if ((input[index] >= '!' && input[index] <= '/') || (input[index] >= ':' && input[index] <= '@'))
        {
            special_char++;
        }
        if ((input[index] >= '[' && input[index] <= '`') || (input[index] >= '{' && input[index] <= '}'))
        {
            special_char++;
        }
    }
    *num_ints = non_letters;
    *num_letts = letters;
    *num_chars = special_char;

    if (debugmode == 1)
    {
        printf("Number of ints: %d\n", *num_ints);
        printf("Number of letters: %d\n", *num_letts);
        printf("Number of special chars: %d\n", *num_chars);
        printf("\n========================= Exit check input ========================\n\n");
    }
}

/*****************************************************************************************************************
//
//  Function Name:                        user_interface
//
//  DESCRIPTION:                          This function will be the one that runs the interface. This will display
//                                        the introduction and direction for the user. The user will be asked to input
//                                        the specified options to do the following: add, print, modify or delete a record.
//
//  PARAMETERS:                           None
//
//  Return Values:                        None
//
*****************************************************************************************************************/

void user_interface()
{
    struct record * start = NULL;
    int run;
    int accountno;
    int option;
    int valid;
    int non_letter;
    int letter;
    int non_ints;
    int special_char;

    char name[25];
    char address[80];
    char numbers[13];
    char input[10];

    char tittle[] = "\n\tThe Bank Interface\n";
    char intro[] = "Welcome to the Bank Menue\n";
    char direct[] = "Enter the following options\n";
    char option_one[] = "\tEnter \'1\' to add a record\n";
    char option_two[] = "\tEnter \'2\' to print a record\n";
    char option_three[] = "\tEnter \'3\' to print all records\n";
    char option_four[] = "\tEnter \'4\' to modify a record\n";
    char option_five[] = "\tEnter \'5\' to remove a record\n";
    char option_six[] = "\tEnter \'6\' to exit the program\n";
    char invalid_input[] = "Error Invalid input. Try again!\n";

    run = 1;
    non_ints = 0;
    valid = 0;
    option = 0;
    accountno = 0;
    if (debugmode == 1)
    {
        printf("\n====================== Debug mode =========================\n\n");
        printf("\tEnter user function\n");
    }
    readfile(&start, "add.txt");
    printf("%s%s\n", tittle, intro);
    printf("%s%s%s%s", direct, option_one, option_two, option_three);
    printf("%s%s%s\n", option_four, option_five, option_six);

    while (run == 1)
    {
        printf("Enter an option: ");
        get_user_input(input, 5);
        check_input(&non_letter, &letter, &special_char, input);
        if (input[0] == '-' && special_char == 1 && letter == 0 && non_letter != 0)
        {
            option = atoi(input);
            non_letter = 0;
            letter = 0;
            special_char = 0;
        }
        if (letter == 0 && non_letter != 0 && special_char == 0)
        {
            option = atoi(input);
            non_letter = 0;
            letter = 0;
            special_char = 0;
        }

        if ((letter > 0 || special_char > 0) && non_letter >= 0)
        {
            option = 0;
            non_ints = 1;
        }

        if (debugmode == 1)
        {
            printf("Option: %d\n", option);
        }
        printf("\n");

        if (option == 1)
        {
            printf("\tAccount number must be Integers greater than \'0\'.\n");

            while (valid == 0)
            {
                printf("Enter Account number: ");

                get_user_input(numbers, 9);

                printf("\n");

                check_input(&non_letter, &letter, &special_char, numbers);

                if (letter == 0 && non_letter != 0 && special_char == 0)
                {
                    accountno = atoi(numbers);
                }

                if (accountno <= 0)
                {
                    printf("\n%s", invalid_input);
                    printf("\nAccount number must be postive");
                    printf("Integers ONLY and be greater than \'0\'\n");
                }

                if (accountno >= 1)
                {
                    valid = 1;
                }

                letter = 0;
                non_letter = 0;
                special_char = 0;
            }

            getname(name, 25);
            getaddress(address, 80);
            addRecord(&start, accountno, name, address);

            valid = 0;
        }

        if (option == 2)
        {
            printf("\tAccount number must be Integers greater than \'0\'.\n");

            while (valid == 0)
            {
                printf("Enter Account number: ");

                get_user_input(numbers, 9);

                check_input(&non_letter, &letter, &special_char, numbers);

                if (letter == 0 && non_letter != 0 && special_char == 0)
                {
                    accountno = atoi(numbers);
                }

                if (accountno <= 0)
                {
                    printf("\n%s", invalid_input);
                    printf("\nAccount number must be postive");
                    printf("Integers ONLY and be greatern than \'0\'\n");
                }

                if (accountno >= 1)
                {
                    valid = 1;
                }

                letter = 0;
                non_letter = 0;
                special_char = 0;
            }

            printRecord(start, accountno);
            valid = 0;
        }

        if (option == 3)
        {
            printAllRecords(start);
        }

        if (option == 4)
        {
            printf("\tAccount number must be Integers greater than \'0\'.\n");

            while (valid == 0)
            {
                printf("Enter Account number: ");

                get_user_input(numbers, 9);

                check_input(&non_letter, &letter, &special_char, numbers);

                if (letter == 0 && non_letter != 0 && special_char == 0)
                {
                    accountno = atoi(numbers);
                }

                if (accountno <= 0)
                {
                    printf("\n%s", invalid_input);
                    printf("\nAccount number must be postive");
                    printf("Integers ONLY and be greater than \'0\'\n");
                }

                if (accountno >= 1)
                {
                    valid = 1;
                }

                non_letter = 0;
                letter = 0;
                special_char = 0;
            }

            valid = 0;
            getaddress(address, 80);
            modifyRecord(start, accountno, address);
        }

        if (option == 5)
        {
            printf("\tAccount number must be Integers greater than \'0\'.\n");

            while (valid == 0)
            {
                printf("Enter Account number: ");

                get_user_input(numbers, 9);

                check_input(&non_letter, &letter, &special_char, numbers);

                if (letter == 0 && non_letter != 0 && special_char == 0)
                {
                    accountno = atoi(numbers);
                }

                if (accountno <= 0)
                {
                    printf("\n%s", invalid_input);
                    printf("\nAccount number must be postive");
                    printf(" Integers ONLY and be greater than \'0\'\n");
                }

                if (accountno >= 1)
                {
                    valid = 1;
                }

                special_char = 0;
                letter = 0;
                non_letter = 0;
            }
            valid = 0;
            deleteRecord(&start, accountno);
        }

        if (option == 6)
        {
            writefile(start, "add.txt");
            cleanup(&start);

            if (debugmode == 1)
            {
                printf("Start After Exit Program: %p\n", (void*) start);
                printf("\n====================== Exit Main  =========================\n\n");
            }
            printf("\n\tExiting program\n");
            run = 0;
        }

        if (option <= -1)
        {
            printf("Warning Invalid Input. \'Negative\' input detected! Try again!\n");
            if (debugmode == 1)
            {
                printf("\tInvalid\n");
            }
        }

        if (option == 0 && non_ints == 1)
        {
            printf("Warning Invalid Input. \'Non Integers\' detected! Try again!\n");
            if (debugmode == 1)
            {
                printf("\tInvalid\n");
            }
            printf("\n");
        }
        if (option == 0 && non_ints == 0)
        {
            printf("Warning Invalid Input. \'Zero\' input detected! Try again!\n");
            if (debugmode == 1)
            {
                printf("\tInvalid\n");
            }
        }

        if (option > 6)
        {
            printf("Warning Invalid Input. \'Large\' Input detected! Try again!\n");
            if (debugmode == 1)
            {
                printf("\tInvalid\n");
            }
        }

        if (run == 1)
        {
            printf("\n%s%s%s%s", direct, option_one, option_two, option_three);
            printf("%s%s%s\n", option_four, option_five, option_six);
        }
        accountno = 0;
        non_letter = 0;
        letter = 0;
        special_char = 0;
        option = 0;
        non_ints = 0;
    }
}
